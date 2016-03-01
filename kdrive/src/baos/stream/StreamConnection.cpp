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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/stream/StreamConnection.h"

using namespace kdrive::baos;

StreamConnection::StreamConnection()
{
}

StreamConnection::~StreamConnection()
{
}

void StreamConnection::connect(const std::string remoteHost, unsigned char version, bool decodeProtocol)
{
	connectIp(remoteHost, version, decodeProtocol);
}

void StreamConnection::connect(const BaosDevice& baosDevice, bool decodeProtocol)
{
	connectIp(baosDevice, decodeProtocol);
}

void StreamConnection::connectByName(const std::string& name, bool decodeProtocol)
{
	connectIpByName(name, decodeProtocol);
}

void StreamConnection::connectByAddress(const std::string& ipAddress, bool decodeProtocol)
{
	connectIpByAddress(ipAddress, decodeProtocol);
}

void StreamConnection::connectNat(const std::string& ipAddress,
                                  unsigned short port,
                                  unsigned char version,
                                  bool decodeProtocol)
{
	connectIpNat(ipAddress, port, version, decodeProtocol);
}
