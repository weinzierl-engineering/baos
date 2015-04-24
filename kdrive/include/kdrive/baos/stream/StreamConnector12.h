
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

#ifndef __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR12_H__
#define __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR12_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/stream/StreamConnector.h"
#include "kdrive/baos/core/BaosPacketFactory.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/baos/protocols/Protocol.h"
#include <array>
#include <memory>
#include <string>

namespace kdrive
{
namespace baos
{

/*!
	\class StreamConnector12
	\brief The StreamConnector is responsible for creating
	a TCP/IP stream connection with the baos server with version 1.2
*/

class kdriveRPC_baos_API StreamConnector12 : public StreamConnector
{
public:
	typedef std::shared_ptr<StreamConnector12> Ptr;

	StreamConnector12();
	StreamConnector12(const std::string& remoteHost, unsigned short port);
	virtual ~StreamConnector12();

private:
	virtual void rxImpl() override;

	virtual std::size_t encapsulate(const connector::Packet::Ptr packet, unsigned char* buffer, std::size_t bufferSize) override;
	int packetize(unsigned char* buffer, std::size_t bufferSize);
	int receiveGetServerItemRes(unsigned char* buffer, std::size_t bufferSize);
	int receiveSetServerItemRes(unsigned char* buffer, std::size_t bufferSize);
	int receiveGetDatapointDescriptionRes(unsigned char* buffer, std::size_t bufferSize);
	int receiveGetDescriptionStringRes(unsigned char* buffer, std::size_t bufferSize);
	int receiveGetDatapointValueRes(unsigned char* buffer, std::size_t bufferSize);
	int receiveSetDatapointValueRes(unsigned char* buffer, std::size_t bufferSize);
	int receiveGetParameterByteRes(unsigned char* buffer, std::size_t bufferSize);
	int receiveDatapointValueInd(unsigned char* buffer, std::size_t bufferSize);
	int rx(unsigned char* buffer, std::size_t bufferSize, int pos, int length);

private:
	std::array<unsigned char, BufferSize> rxBuffer_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR12_H__
