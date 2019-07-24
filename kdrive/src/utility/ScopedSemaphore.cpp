//
// Copyright (c) 2002-2019 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/utility/ScopedSemaphore.h"
#include <Poco/Logger.h>
#include <Poco/Semaphore.h>

using namespace kdrive::utility;
using Poco::Semaphore;
using Poco::Logger;

/*******************************
** ScopedSemaphore
********************************/

ScopedSemaphore::ScopedSemaphore(Semaphore& semaphore)
	: semaphore_(semaphore)
{
	semaphore_.wait();
}

ScopedSemaphore::~ScopedSemaphore()
{
	semaphore_.set();
}

/*******************************
** ScopedSemaphoreWithTraces
********************************/

ScopedSemaphoreWithTraces::ScopedSemaphoreWithTraces(Semaphore& semaphore, Logger& logger,
        const std::string& name)
	: semaphore_(semaphore)
	, logger_(logger)
	, name_(name)
{
	poco_information_f1(logger_, "Wait for semaphore %s", name_);
	semaphore_.wait();
	poco_information_f1(logger_, "Semaphore captured %s", name_);
}

ScopedSemaphoreWithTraces::~ScopedSemaphoreWithTraces()
{
	poco_information_f1(logger_, "Release semaphore %s", name_);
	semaphore_.set();
}

void ScopedSemaphoreWithTraces::setName(const std::string& name)
{
	name_ = name;
}

const std::string& ScopedSemaphoreWithTraces::getName() const
{
	return name_;
}
