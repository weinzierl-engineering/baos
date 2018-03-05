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

#ifndef __KDRIVE_BAOS_CORE_DATA_PACKET_H__
#define __KDRIVE_BAOS_CORE_DATA_PACKET_H__

#include "kdrive/baos/Config.h"
#include "kdrive/connector/Packet.h"
#include <vector>
#include <memory>


namespace kdrive
{
namespace baos
{

/*************************************
** Data Packet
**************************************/

struct HeaderPolicy;

using DataPacketBase = connector::Packet;

class kdriveRPC_baos_API DataPacket : public DataPacketBase
{
public:
	typedef std::shared_ptr<DataPacket> Ptr;
	typedef std::vector<unsigned char> Buffer;

	virtual ~DataPacket();

	void setMainService(unsigned char mainService);
	unsigned char getMainService() const;

	void setSubService(unsigned char subService);
	unsigned char getSubService() const;

	void setOffset(unsigned short offset);
	unsigned short getOffset() const;

	void setCount(unsigned short count);
	unsigned short getCount() const;

	void setBuffer(const Buffer& buffer);
	Buffer& getBuffer();
	const Buffer& getBuffer() const;

	void setHeaderPolicy(std::shared_ptr<HeaderPolicy> headerPolicy);

	void setVersion(unsigned char version);
	unsigned char getVersion() const;

protected:
	DataPacket();
	std::size_t sizeImpl() const override;
	std::size_t readFromBufferImpl(const unsigned char* buffer, std::size_t bufferSize) override;
	std::size_t writeToBufferImpl(unsigned char* buffer, std::size_t bufferSize) const override;

private:
	DataPacket(const DataPacket&);
	DataPacket& operator=(const DataPacket&);
	std::size_t sizeOfHeader() const;
	std::size_t readHeader(const unsigned char* buffer, std::size_t bufferSize);
	std::size_t writeHeader(unsigned char* buffer, std::size_t bufferSize) const;
	std::size_t sizeOfBody() const;
	std::size_t readBody(const unsigned char* buffer, std::size_t bufferSize);
	std::size_t writeBody(unsigned char* buffer, std::size_t bufferSize) const;

private:
	std::shared_ptr<HeaderPolicy> headerPolicy_;
	unsigned char version_;
	unsigned char mainService_;
	unsigned char subService_;
	unsigned short offset_;
	unsigned short count_;
	Buffer buffer_;

	enum Attributes
	{
		MainService = 0,
		SubService,
		Offset,
		Count
	};
};

/*************************************
** Data Request
**************************************/

struct kdriveRPC_baos_API DataRequest : public DataPacket
{
	typedef std::shared_ptr<DataRequest> Ptr;
};

/*************************************
** Data Response
**************************************/

struct kdriveRPC_baos_API DataResponse : public DataPacket
{
	typedef std::shared_ptr<DataResponse> Ptr;
};

/*************************************
** Data Indication
**************************************/

struct kdriveRPC_baos_API DataIndication : public DataResponse
{
	typedef std::shared_ptr<DataIndication> Ptr;
};

/*************************************
** DatapointValueIndication
**************************************/

struct kdriveRPC_baos_API DatapointValueIndication : public DataIndication
{
	typedef std::shared_ptr<DatapointValueIndication> Ptr;
};

/*************************************
** ServerItemIndication
**************************************/

struct kdriveRPC_baos_API ServerItemIndication : public DataIndication
{
	typedef std::shared_ptr<ServerItemIndication> Ptr;
};

/*************************************
** Error Response
**************************************/

struct kdriveRPC_baos_API ErrorResponse : public DataResponse
{
	typedef std::shared_ptr<ErrorResponse> Ptr;
	unsigned char getErrorCode() const;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_DATA_PACKET_H__
