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

#ifndef __KDRIVE_BAOS_CORE_SERVER_FUNCTION_H__
#define __KDRIVE_BAOS_CORE_SERVER_FUNCTION_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/BaosConnector.h"

namespace kdrive
{
namespace baos
{

/*******************************
** ServerFunction
********************************/

class ServerFunction
{
public:
	ServerFunction(BaosConnector::Ptr connector);
	~ServerFunction();

	DataResponse::Ptr rpc(DataRequest::Ptr request,
	                      unsigned long timeout = ProtocolConstants::Timeout);

private:
	ServerFunction();
	ServerFunction(const ServerFunction& ServerFunction);
	ServerFunction& operator=(const ServerFunction& ServerFunction);

	void send(DataRequest::Ptr request);
	DataResponse::Ptr receive(connector::Connector& connector, unsigned long timeout);
	void waitResponse(connector::Connector& connector, unsigned long timeout);
	void validateResponse();

private:
	unsigned short errorCode_;
	BaosConnector::Ptr connector_;
	DataRequest::Ptr request_;
	DataResponse::Ptr response_;
};

/*******************************
** rpc
********************************/

template <class Packet>
typename Packet::Response::Ptr rpc(BaosConnector::Ptr connector,
                                   typename Packet::Request::Ptr request,
                                   unsigned long timeout = ProtocolConstants::Timeout)
{
	ServerFunction serverFunction(connector);
	DataResponse::Ptr dataResponse = serverFunction.rpc(request, timeout);
	typename Packet::Response::Ptr response =
	    std::dynamic_pointer_cast<typename Packet::Response>(dataResponse);
	return response;
}

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_SERVER_FUNCTION_H__
