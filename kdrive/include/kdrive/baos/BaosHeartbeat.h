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

#ifndef __KDRIVE_BAOS_HEARTBEAT_H__
#define __KDRIVE_BAOS_HEARTBEAT_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/connector/CallbackThread.h"
#include <memory>

namespace kdrive
{
namespace baos
{

/*!
	\class BaosHeartbeat

	BaosHeartbeat sends periodically a heartbeat.

	We can also use this class to monitor the server connection.
	If there is a problem with the heartbeat we can auto-terminate
	the connection and raise an event. This is disabled by default
	to ensure backward compatibility with the original implementation.

	\deprecated
	In a previous version did the StreamConnector no heartbeat.
	Now th StreamConnector implemented internally the heartbeat.
	So this class is no more needed. Its exists only for backward compatibility.
*/

class kdriveRPC_baos_API BaosHeartbeat
{
public:
	/*!
		Creates a BaosHeartbeat and associates it with a connection
		precondition: connector is not null
	*/
	BaosHeartbeat(std::shared_ptr<BaosConnector> connector, unsigned int interval = 1000);

	/*!
		Destroys the BaosHeartbeat
		Stops the hearbeat thread if it is still active
	*/
	virtual ~BaosHeartbeat();

	/*!
		Starts the heartbeat thread. If the thread has already been started
		nothing will happen.
	*/
	void start();

	/*!
		Stops the heartbeat thread.
		If the thread is already stopped nothing will happen.
	*/
	void stop();

	/*!
		Returns true if the last request was successful
	*/
	bool isAlive() const;

	/*!
		Returns the last successful value of the server item
		time since reset. This is called periodically as the hearbeat
	*/
	unsigned long getTimeSinceReset() const;

	/*!
		If autoTerminate is true we disconnect the connection
		and raise the terminated event as soon as isAlive is false
	*/
	void setAutoTerminate(bool autoTerminate, int failCount = 3);

private:

	/*!
		The thread handler. This function is called periodically
		(the timeout is set in the callback thread constructor).
		It simply gets the time since last reset (however it doesn't
		really matter what it does as all we want to do it connect
		to the baos device to ensure it doesn't auto-close the connection.
	*/
	void sendHeartbeat();

private:
	std::shared_ptr<BaosConnector> connector_;
	connector::ActiveFunction activeFunction_;
	bool alive_;
	bool autoTerminate_;
	int autoTerminateFailCount_;
	int autoTerminateFailCounter_;
	unsigned long timeSinceReset_;
};

/*!
	\class ScopedBaosHeartbeat

	Auto starts and stops the Hearbeat class using RAII.

	\deprecated
	This class exists only for backward compatibility.

	\sa BaosHeartbeat
*/

class kdriveRPC_baos_API ScopedBaosHeartbeat : public BaosHeartbeat
{
public:
	/*!
		Creates a ScopedBaosHeartbeat and auto-starts the heartbeat thread.
		precondition: connector is not null
	*/
	ScopedBaosHeartbeat(std::shared_ptr<BaosConnector> connector, unsigned int interval = 1000);

	/*!
		Destroys the scoped boas heartbeat. Stops the hearbeat thread.
	*/
	virtual ~ScopedBaosHeartbeat();
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_HEARTBEAT_H__

