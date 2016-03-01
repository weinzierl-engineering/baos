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

#ifndef __KDRIVE_BAOS_ENUMERATOR_H__
#define __KDRIVE_BAOS_ENUMERATOR_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/API.h"

namespace Poco
{
namespace Net
{

class IPAddress;
class MulticastSocket;
class NetworkInterface;

}
} // end namespace Poco::Net

namespace kdrive
{
namespace baos
{

/*!
	\class BaosEnumerator
	\brief Finds all available IP BAOS devices on the network

	The BaosEnumerator scans all available network interfaces
	and searches for the list of BAOS devices on the network.
	The information returned is a tuple of:

		name,
		interface ip address (local),
		BAOS IP address (remote)
		version (the object server protocol version)

	This device information can be directly given to the
	StreamConnection to create a connection.

	See also the Enumerator sample and the LightSwitcher sample
	for an example of how to use the BaosEnumerator

	\note BaosEnumerator supports only IP Baos devices.
	FT 1.2 Serial device are not supported.
*/
class kdriveRPC_baos_API BaosEnumerator
{
public:
	/*!
		Creates a Baos Enumerator.
		If autoScan is true it will automatically scan the network
		If false, you will have to explicitly run scan
	*/
	BaosEnumerator(bool autoScan = true);

	/*!
		Destroys the BaosEnumerator
	*/
	~BaosEnumerator();

	typedef BaosDevice Device;
	typedef BaosDevices Devices;

	/*!
		Enumerates all network interfaces
		and for each available network interfaces
		searches for baos devices.
		The loopback interface is ignored.
	*/
	const Devices& scan();

	/*!
		Returns the list of found devices
	*/
	const Devices& getDevices() const;

	/*!
		Finds device information for a BAOS device with a human-readable
		name that matches the specified name. This is a case-insensitive
		check. The BAOS devices typically have the MAC address programmed
		as their name in production. To change its name you can use the ETS
		software, or the Net'n Node software by writing to the specific property.

		If a device is not found that matches name an exception is thrown.
	*/
	const Device& find(const std::string& name) const;

	/*!
		Finds device information for a BAOS device that matches
		a specified IP Address. If a device is not found that
		matches ipAddress an exception is thrown.
	*/
	const Device& findByAddress(const std::string& ipAddress) const;

	/*!
		Returns the name field of the device tuple
	*/
	const std::string& getName(const Device& device) const;

	/*!
		Returns the interface ip address of the device tuple
	*/
	const std::string& getInterfaceAddress(const Device& device) const;

	/*!
		Returns the BAOS device address of the device tuple
	*/
	const std::string& getAddress(const Device& device) const;

	/*!
		Returns the protocol version of the device tuple
	*/
	unsigned char getVersion(const Device& device) const;

private:
	void scanInterface(const Poco::Net::NetworkInterface& networkInterface);
	void sendSearchRequestFrame(Poco::Net::MulticastSocket& socket);
	void waitForSearchResponseFrames(Poco::Net::MulticastSocket& socket);
	bool waitForRx(Poco::Net::MulticastSocket& socket, std::vector<unsigned char>& buffer);
	void addDevice(const std::vector<unsigned char>& buffer, const Poco::Net::IPAddress& networkInterface);

private:
	Devices devices_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_ENUMERATOR_H__
