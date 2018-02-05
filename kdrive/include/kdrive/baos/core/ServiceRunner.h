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

#ifndef __KDRIVE_BAOS_CORE_SERVICE_RUNNER__
#define __KDRIVE_BAOS_CORE_SERVICE_RUNNER__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/baos/core/API.h"
#include <memory>

namespace kdrive
{
namespace baos
{

class kdriveRPC_baos_API ServiceRunner
{
public:
	typedef DataPacket::Buffer Buffer;

	virtual ~ServiceRunner();

	unsigned short getOffset() const;
	unsigned short getCount() const;
	const Buffer& getBuffer() const;

	enum
	{
	    Timeout = ProtocolConstants::Timeout
	};

protected:
	ServiceRunner(std::shared_ptr<BaosConnector> connector);
	std::shared_ptr<BaosConnector> getConnector(bool validate = true) const;
	void rpc(unsigned char subService, unsigned short offset,
	         unsigned short count, unsigned long timeout);
	void setDataResponse(std::shared_ptr<DataResponse> dataResponse);
	std::shared_ptr<DataResponse> getDataResponse(bool validate = true) const;

private:
	std::shared_ptr<BaosConnector> connector_;
	std::shared_ptr<DataResponse> dataResponse_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_SERVICE_RUNNER__
