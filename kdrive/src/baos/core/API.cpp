//
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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/core/API.h"

using namespace kdrive::baos;

const unsigned char ProtocolConstants::MainService = 0xF0;

const unsigned short MulticastProtocolConstants::Port = 3671;
const std::string MulticastProtocolConstants::Address = "224.0.23.12";

bool ProtocolVersions::is1x(unsigned char version)
{
	return version == ProtocolVersions::V12;
}

bool ProtocolVersions::is2x(unsigned char version)
{
	return version == ProtocolVersions::V20;
}
