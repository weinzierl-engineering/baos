//
// Copyright (c) 2002-2018 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#ifndef __KDRIVE_CONNECTOR_CALLBACK_THREAD_H__
#define __KDRIVE_CONNECTOR_CALLBACK_THREAD_H__

#include "kdrive/connector/Config.h"
#include <Poco/Runnable.h>
#include <Poco/Thread.h>
#include <Poco/ThreadPool.h>
#include <Poco/Event.h>
#include <Poco/AtomicCounter.h>
#include <boost/signals2.hpp>
#include <exception>
#include <string>
#include <memory>
#include <functional>

namespace Poco
{

class AbstractTimerCallback;
class Timer;

} // end namespace Poco

namespace kdrive
{
namespace connector
{

class CallbackThreadManager;
class ActiveFunction;

/**********************************
** CallbackThread
***********************************/

class kdriveConnector_API CallbackThread final : public Poco::Runnable
{
public:
	typedef std::function<void ()> Callback;

	CallbackThread(Callback callback, long sleep = 0, const std::string& name = "Unknown");
	virtual ~CallbackThread();

	/*!
		\return the unique callback thread id if the thread has been set
	*/
	int getId() const;

	/*!
		Sets the sleep period between each callback
	*/
	void setSleep(long sleep);

	/*!
		Gets the sleep period
	*/
	long getSleep() const;

	/*!
		Sets the thread name
	*/
	void setName(const std::string& name);

	/*!
		Gets the thread name
	*/
	const std::string& getName() const;

	/*!
		indicates that the thread should stop
		this does not cancel, but sets an Event
		that the thread periodically checks
	*/
	void stop();

	/*!
		waits on the stop event
	*/
	bool tryWaitStop(long milliseconds);

	/*!
		\return true if the thread is running
	*/
	bool isRunning() const;

	/*!
		\return true if the thread has run and is now wait for stop
	*/
	bool isStopRequested() const;

	/*!
		\return true if the thread has run and is now stopped
	*/
	bool isStopped() const;

	/*!
		Indicates whether the thread loop can continue to run
		This should be called from within the thread loop
		and can also be used by the ActiveThread if it implements its own
		thread loop
	*/
	bool canLoop(bool firstLoop = false);

	/*!
		Sets whether Thread::yield is called
		when sleep it 0. The default is true
	*/
	void setYield(bool yield = true);

	/*!
		the thread has an Poco::Event that can be used for
		thread synchronisation, this can be performed in the
		callback function and the thread owner/caller
		it is not used by the CallbackThread class
		this event is separate from the stop event
	*/
	void set();
	void wait();
	void wait(long milliseconds);
	bool tryWait(long milliseconds);

	struct Signals
	{
		typedef boost::signals2::signal<void ()> Start;
		typedef boost::signals2::signal<void ()> Stop;
		typedef boost::signals2::signal<void (std::exception&)> Exception;

		Start start;
		Stop stop;
		Exception exception;
	};

	Signals& getSignals();

protected:
	/*!
		we don't expect exceptions, i.e. they should be handled by the callback function
		so if we get once we simply stop the thread event loop
	*/
	void run() override;

	/*!
		Wait until the thread is in the thread loop
	*/
	void waitStartSync(long milliseconds = 1000);

	/*!
		Wait until the thread leaving the thread loop
	*/
	void waitStopSync(long milliseconds = 1000);

	/*!
		called from within a thread to request it to stop
		if a user, call stop. if a ActiveThread callback
		that needs to stop the thread, use requestStopInternal
	*/
	void requestStopInternal();

	/*!
		indicates that the thread is in the initial start state
		so it can be re-run, otherwise it will remain in the stop
		state and not enter the run loop. This is really only called
		by the CallbackThreadManager and can be safely ignored
	*/
	void setToInitialState();

protected:
	friend class CallbackThreadManager;
	friend class ActiveFunction;

private:
	CallbackThread();

private:
	long sleep_;
	int id_;
	Callback callback_;
	Poco::AtomicCounter status_;
	Poco::AtomicCounter yield_;
	Poco::Event stopEvent_;
	Poco::Event syncStartEvent_;
	Poco::Event syncStopEvent_;
	Poco::Event userEvent_;
	Signals signals_;
	std::string name_;
};

/**********************************
** CallbackThreadManager
***********************************/

/*!
	\class CallbackThreadManager
	RAII for Thread start/stop for CallbackThreads
	The CallbackThreadManagerImpl keeps a reference to the CallbackThread
	and starts the thread on construction
	stops and joins the thread on destruction
*/
class kdriveConnector_API CallbackThreadManager final
{
public:
	/*!
		Creates a CallbackThreadManager
	*/
	explicit CallbackThreadManager(CallbackThread& callbackThread, bool scoped = true, bool useThreadPool = true);

	/*!
		Copy constructor is deleted
	*/
	CallbackThreadManager(const CallbackThreadManager&) = delete;

	/*!
		Destroys the CallbackThreadManager
	*/
	~CallbackThreadManager();

	/*!
		Assignment Operator is deleted
	*/
	CallbackThreadManager& operator=(const CallbackThreadManager&) = delete;

	void start();
	void start(long sleep);
	void stop();
	bool isRunning() const;

	static Poco::ThreadPool& getThreadPool();

private:
	struct ThreadPoolHolder
	{
		ThreadPoolHolder();
		static ThreadPoolHolder& instance();
		Poco::ThreadPool threadPool_;

	private:
		enum Defaults
		{
			MinCapacity = 2,
			MaxCapacity = 500
		};
	};

private:
	std::shared_ptr<Poco::Thread> thread_;
	CallbackThread& callbackThread_;
	bool scoped_;
	bool useThreadPool_;
};

/**********************************
** ActiveFunction
***********************************/

class kdriveConnector_API ActiveFunction final
{
public:
	typedef std::function<void (ActiveFunction& activeFunction)> Callback;

	/*!
		Creates a ActiveFunction
	*/
	explicit ActiveFunction(Callback callback, long sleep = 0, const std::string& name = "Unknown", bool useThreadPool = true);

	/*!
		Copy constructor is deleted
	*/
	ActiveFunction(const ActiveFunction&) = delete;

	/*!
		Destroys the ActiveFunction
	*/
	~ActiveFunction();

	/*!
		Assignment Operator is deleted
	*/
	ActiveFunction& operator=(const ActiveFunction&) = delete;

	CallbackThread& getCallbackThread();
	const CallbackThread& getCallbackThread() const;
	void start();
	void start(long sleep);
	void stop();
	void stopFromWithinCallback();
	bool isRunning() const;

private:
	void callbackAdaptor();

private:
	Callback callback_;
	CallbackThread callbackThread_;
	CallbackThreadManager callbackThreadManager_;
};

/**********************************
** utility functions
***********************************/

/*!
	Start the timer with the thread pool from CallbackThreadManager
*/
kdriveConnector_API Poco::Timer& startTimer(Poco::Timer& timer, const Poco::AbstractTimerCallback& method);

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_DETAIL_CALLBACK_THREAD_H__
