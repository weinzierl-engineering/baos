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

#ifndef __KDRIVE_BAOS_CORE_PROTOCOL_DECODER_H__
#define __KDRIVE_BAOS_CORE_PROTOCOL_DECODER_H__

#include "kdrive/baos/Config.h"
#include "kdrive/connector/Forwards.h"
#include <boost/signals2.hpp>

namespace kdrive
{
namespace baos
{

/*!
	\class ProtocolDecoder
	\brief A utility class to decode the communication between the client and the remote baos device
*/
class kdriveRPC_baos_API ProtocolDecoder
{
public:
	ProtocolDecoder();
	ProtocolDecoder(connector::Connector& connector);
	~ProtocolDecoder();

	void connect(connector::Connector& connector);
	void disconnect();

	void decode(std::string& s, std::shared_ptr<connector::Packet> packet, int direction);

private:
	void onPacket(std::shared_ptr<connector::Packet> packet, int direction);
	void formatString(std::string& s, std::shared_ptr<connector::Packet> packet);
	std::string log(unsigned char subService);

private:
	boost::signals2::scoped_connection connection_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_PROTOCOL_DECODER_H__
