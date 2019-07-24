
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

#ifndef __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR2X_H__
#define __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR2X_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/stream/StreamConnector.h"
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
	\class StreamConnector2x
	\brief The StreamConnector is responsible for creating
	a TCP/IP stream connection with the baos server with version 2x
*/

class kdriveRPC_baos_API StreamConnector2x : public StreamConnector
{
public:
	typedef std::shared_ptr<StreamConnector2x> Ptr;

	StreamConnector2x();
	StreamConnector2x(const std::string& remoteHost, unsigned short port);
	virtual ~StreamConnector2x();

public:
	static const std::string ConnectorTypeLabel;

protected:
	void resetPropertiesImpl() override;

	void openImpl() override;
	void rxImpl() override;

private:
	std::size_t encapsulate(const std::shared_ptr<connector::Packet> packet, unsigned char* buffer, std::size_t bufferSize) override;

	void onReceive(const unsigned char* buffer, std::size_t length);
	bool packetize(int& bufferOffset);
	void onReceiveFrame(const unsigned char* transportFrame, std::size_t length);

private:
	std::array<unsigned char, BufferSize> rxBuffer_; /*!< Buffer used in rxImpl */
	std::vector<unsigned char> frameBuffer_; /*!< Buffer with received byte stream */
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR2X_H__
