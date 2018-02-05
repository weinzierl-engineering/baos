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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/BaosParameter.h"
#include "kdrive/baos/services/GetParameterByte.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/Exception.h"
#include <vector>

using namespace kdrive::connector;
using namespace kdrive::baos;

unsigned char kdrive::baos::readParameter(BaosConnector::Ptr connector, unsigned short offset)
{
	std::vector<unsigned char> v;
	readParameters(connector, v, offset, 1);
	if (v.size() != 1)
	{
		throw ClientException("Unable to read parameter byte");
	}
	return v.at(0);
}


void kdrive::baos::readParameters(BaosConnector::Ptr connector,
                                  std::vector<unsigned char>& data,
                                  unsigned short offset,
                                  unsigned short count)
{
	GetParameterByte service(connector);
	service.rpc(offset, count, ProtocolConstants::Timeout);
	data = service.getData();
}
