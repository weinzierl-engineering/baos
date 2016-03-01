//
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#include "pch/kdrive_pch.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/connector/CallbackThread.h"
#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include <Poco/Timer.h>
#include <Poco/SingletonHolder.h>
#include <boost/assert.hpp>

using Poco::AbstractTimerCallback;
using Poco::Exception;
using Poco::Runnable;
using Poco::Thread;
using Poco::ThreadPool;
using Poco::Event;
using Poco::Logger;
using Poco::FastMutex;
using Poco::ScopedLock;
using Poco::SingletonHolder;
using Poco::Timer;
using namespace kdrive::connector;

CLASS_LOGGER("kdrive.connector.CallbackThread")

/**********************************
** Anonymous namespace
***********************************/

namespace
{

struct StopConstants
{
	enum
	{
	    Initial = -1,
	    Stop = 0,
	    Run = 1,
	    RequestStop = 2
	};
};

static FastMutex uniqueIdMutex;

int uniqueId()
{
	FastMutex::ScopedLock lock(uniqueIdMutex);

	static unsigned count = 0;
	++count;
	return count;
}

void notifyStart(CallbackThread::Signals& signals)
{
	try
	{
		signals.start();
	}
	catch (...)
	{
		poco_error(LOGGER(), "notifyStart failed with unhandled exception");
	}
}

void notifyStop(CallbackThread::Signals& signals)
{
	try
	{
		signals.stop();
	}
	catch (...)
	{
		poco_error(LOGGER(), "notifyStop failed with unhandled exception");
	}
}

void notifyException(CallbackThread::Signals& signals, std::exception& e)
{
	try
	{
		signals.exception(e);
	}
	catch (...)
	{
		poco_error(LOGGER(), "notifyException failed with unhandled exception");
	}
}

void setEvent(Event& e)
{
	try
	{
		e.set();
	}
	catch (...)
	{
		poco_error(LOGGER(), "setEvent failed with unhandled exception");
	}
}

void resetEvent(Event& e)
{
	try
	{
		e.reset();
	}
	catch (...)
	{
		poco_error(LOGGER(), "resetEvent failed with unhandled exception");
	}
}

} // end anonymous namespace

/**********************************
** CallbackThread
***********************************/

CallbackThread::CallbackThread(Callback callback, long sleep, const std::string& name)

	: sleep_(sleep),
	  id_(0),
	  callback_(callback),
	  status_(StopConstants::Initial),
	  yield_(true),
	  name_(name)
{
	BOOST_ASSERT(callback_ && "Invalid Callback");
}

CallbackThread::~CallbackThread()
{
	try
	{
		stop();
	}
	catch (...)
	{
	}
}

int CallbackThread::getId() const
{
	return id_;
}

void CallbackThread::setSleep(long sleep)
{
	sleep_ = sleep;
}

long CallbackThread::getSleep() const
{
	return sleep_;
}

void CallbackThread::setName(const std::string& name)
{
	name_ = name;
}

const std::string& CallbackThread::getName() const
{
	return name_;
}

void CallbackThread::stop()
{
	if (isRunning())
	{
		requestStopInternal();
		waitStopSync();
	}
	else if (isStopRequested())
	{
		// Wait until the thread is stopped
		// (e.g. stop request from the thread self or from ActiveFunction)
		waitStopSync();
	}
}

bool CallbackThread::tryWaitStop(long milliseconds)
{
	return stopEvent_.tryWait(milliseconds);
}

bool CallbackThread::isRunning() const
{
	return status_ == StopConstants::Run;
}

bool CallbackThread::isStopRequested() const
{
	return status_ == StopConstants::RequestStop;
}

bool CallbackThread::isStopped() const
{
	return status_ == StopConstants::Stop;
}

/*
	Our stop condition is either:
	sleep is 0, which means we have a fast loop,
	and we use the stop value to determine the stop event

	sleep is > 0 and we use the event to handle the stop case

	Special case: On the first loop we wait check only the current stop event value and do not wait the sleep time.
*/
bool CallbackThread::canLoop(bool firstLoop)
{
	const bool fastLoop = !sleep_;
	if (fastLoop)
	{
		return (status_ == StopConstants::Run) ? true : false;
	}
	else
	{
		const bool shouldStop = tryWaitStop(firstLoop ? 1 : sleep_);
		return shouldStop ? false : true;
	}
}

void CallbackThread::setYield(bool yield)
{
	yield_ = yield;
}

void CallbackThread::set()
{
	userEvent_.set();
}

void CallbackThread::wait()
{
	userEvent_.wait();
}

void CallbackThread::wait(long milliseconds)
{
	userEvent_.wait(milliseconds);
}

bool CallbackThread::tryWait(long milliseconds)
{
	return userEvent_.tryWait(milliseconds);
}

CallbackThread::Signals& CallbackThread::getSignals()
{
	return signals_;
}

/*!
	Our stop condition is either:
	sleep is 0, which means we have a fast loop,
	and we use the stop value to determine the stop event

	sleep is > 0 and we use the event to handle the stop case

	We use the two separate mechanisms for performance reasons,
	using the event is slow when we have a sleep of 0
	i.e. we still block a little, performance is much better when
	we use the atomic counter stop.

	Also, if sleep is 0 we add a thread yield to stop the case where
	a receive thread takes all the processing. You can disable this
	by setting yield to 0
*/
void CallbackThread::run()
{
	bool firstLoop = true;
	bool setStopEvent = false;

	id_ = uniqueId();
	status_ = StopConstants::Run;

	Logger& logger = LOGGER();
	poco_debug_f2(logger, "Callback thread running [id %d, %s]", getId(), getName());

	notifyStart(signals_);

	while (canLoop(firstLoop))
	{
		if (firstLoop)
		{
			setEvent(syncStartEvent_);
			firstLoop = false;
		}

		try
		{
			callback_();

			if (!sleep_ && yield_)
			{
				Thread::yield();
			}
		}
		catch (Exception& exception)
		{
			poco_error_f2(logger, "Callback thread terminated by unhandled Poco exception [id %d]: %s",
			              getId(), exception.displayText());

			notifyException(signals_, exception);
			setStopEvent = true;
		}
		catch (std::exception& exception)
		{
			const std::string what = exception.what();
			poco_error_f2(logger, "Callback thread terminated by unhandled std::exception [id %d]: %s",
			              getId(), what);

			notifyException(signals_, exception);
			setStopEvent = true;
		}
		catch (...)
		{
			poco_error_f1(logger, "Callback thread terminated by unhandled exception [id %d]", getId());

			std::exception e;
			setStopEvent = true;
		}

		if (setStopEvent)
		{
			requestStopInternal();
		}
	}

	notifyStop(signals_);
	status_ = StopConstants::Stop;
	setEvent(syncStopEvent_);

	poco_debug_f2(logger, "Callback thread stopped [id %d, name %s]", getId(), getName());
}

void CallbackThread::waitStartSync(long milliseconds)
{
	if (!syncStartEvent_.tryWait(milliseconds))
	{
		poco_warning_f2(LOGGER(), "Callback thread timeout start sync [id %d, name %s]", getId(), getName());
	}
}

void CallbackThread::waitStopSync(long milliseconds)
{
	if (!syncStopEvent_.tryWait(milliseconds))
	{
		poco_warning_f2(LOGGER(), "Callback thread timeout stop sync [id %d, name %s]", getId(), getName());
	}
}

void CallbackThread::requestStopInternal()
{
	status_ = StopConstants::RequestStop;
	setEvent(stopEvent_);
	poco_debug_f2(LOGGER(), "Callback thread stop requested [id %d, %s]", getId(), getName());
}

void CallbackThread::setToInitialState()
{
	status_ = StopConstants::Initial;
	resetEvent(syncStartEvent_);
	resetEvent(syncStartEvent_);
	resetEvent(syncStopEvent_);
}

/**********************************
** CallbackThreadManager
***********************************/

CallbackThreadManager::CallbackThreadManager(CallbackThread& callbackThread, bool scoped, bool useThreadPool)

	: callbackThread_(callbackThread),
	  scoped_(scoped),
	  useThreadPool_(useThreadPool)
{
	if (scoped_)
	{
		start();
	}
}

CallbackThreadManager::~CallbackThreadManager()
{
	try
	{
		stop();
	}
	catch (...)
	{
	}
}

void CallbackThreadManager::start()
{
	if (!callbackThread_.isRunning())
	{
		callbackThread_.setToInitialState();

		if (useThreadPool_)
		{
			ThreadPool& threadPool = ThreadPoolHolder::instance().threadPool_;
			threadPool.start(callbackThread_);
			callbackThread_.waitStartSync();
		}
		else
		{
			BOOST_ASSERT(!thread_ && "Thread must be null, this is a serious problem. Fix now.");

			thread_ = std::make_shared<Thread>();
			thread_->start(callbackThread_);
			callbackThread_.waitStartSync();
		}
	}
}

void CallbackThreadManager::start(long sleep)
{
	callbackThread_.setSleep(sleep);
	start();
}

void CallbackThreadManager::stop()
{
	callbackThread_.stop();

	if (useThreadPool_)
	{
		ThreadPool& threadPool = ThreadPoolHolder::instance().threadPool_;
		threadPool.collect();
	}
	else if (thread_)
	{
		if (!thread_->tryJoin(5000))
		{
			poco_error_f2(LOGGER(), "Unable to join thread [id %d, name %s]", callbackThread_.getId(), callbackThread_.getName());
		}
		thread_.reset();
	}

	callbackThread_.setToInitialState();
}

bool CallbackThreadManager::isRunning() const
{
	return callbackThread_.isRunning();
}

ThreadPool& CallbackThreadManager::getThreadPool()
{
	ThreadPool& threadPool = ThreadPoolHolder::instance().threadPool_;
	return threadPool;
}

CallbackThreadManager::ThreadPoolHolder::ThreadPoolHolder()

	: threadPool_(MinCapacity, MaxCapacity)
{
}

CallbackThreadManager::ThreadPoolHolder& CallbackThreadManager::ThreadPoolHolder::instance()
{
	static SingletonHolder<ThreadPoolHolder> holder;
	return *holder.get();
}

/**********************************
** ActiveFunction
***********************************/

ActiveFunction::ActiveFunction(Callback callback, long sleep, const std::string& name, bool useThreadPool)

	: callback_(callback),
	  callbackThread_(std::bind(&ActiveFunction::callbackAdaptor, this), sleep, name),
	  callbackThreadManager_(callbackThread_, false, useThreadPool)
{
}

ActiveFunction::~ActiveFunction()
{
}

CallbackThread& ActiveFunction::getCallbackThread()
{
	return callbackThread_;
}

const CallbackThread& ActiveFunction::getCallbackThread() const
{
	return callbackThread_;
}

void ActiveFunction::start()
{
	callbackThreadManager_.start();
}

void ActiveFunction::start(long sleep)
{
	callbackThreadManager_.start(sleep);
}

void ActiveFunction::stop()
{
	callbackThreadManager_.stop();
}

void ActiveFunction::stopFromWithinCallback()
{
	callbackThread_.requestStopInternal();
}

bool ActiveFunction::isRunning() const
{
	return callbackThreadManager_.isRunning();
}

void ActiveFunction::callbackAdaptor()
{
	if (callback_)
	{
		callback_(*this);
	}
}

/**********************************
** utility functions
***********************************/

Poco::Timer& kdrive::connector::startTimer(Timer& timer, const AbstractTimerCallback& method)
{
	timer.start(method, CallbackThreadManager::getThreadPool());
	return timer;
}
