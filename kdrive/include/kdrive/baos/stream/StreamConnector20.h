
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#ifndef __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR20_H__
#define __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR20_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/stream/StreamConnector.h"
#include "kdrive/baos/core/BaosPacketFactory.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/baos/protocols/Protocol.h"
#include <array>
#include <memory>
#include <string>
#include <vector>

namespace kdrive
{
namespace baos
{

/*!
	\class StreamConnector20
	\brief The StreamConnector is responsible for creating
	a TCP/IP stream connection with the baos server with version 2.0
*/

class kdriveRPC_baos_API StreamConnector20 : public StreamConnector
{
public:
	typedef std::shared_ptr<StreamConnector20> Ptr;

	StreamConnector20();
	StreamConnector20(const std::string& remoteHost, unsigned short port);
	virtual ~StreamConnector20();

private:
	virtual void rxImpl() override;

private:
	virtual std::size_t encapsulate(const connector::Packet::Ptr packet, unsigned char* buffer, std::size_t bufferSize) override;

	void onReceive(const unsigned char* buffer, std::size_t length);
	bool packetize(int& bufferOffset);
	void onReceiveFrame(const unsigned char* transportFrame, std::size_t length);

private:
	std::array<unsigned char, BufferSize> rxBuffer_; /*!< Buffer used in rxImpl */
	std::vector<unsigned char> frameBuffer_; /*!< Buffer with received byte stream */
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR20_H__
