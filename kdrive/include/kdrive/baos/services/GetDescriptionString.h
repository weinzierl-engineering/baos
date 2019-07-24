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

#ifndef __KDRIVE_BAOS_SERVICES_GET_DESCRIPTION_STRING_H__
#define __KDRIVE_BAOS_SERVICES_GET_DESCRIPTION_STRING_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/ServiceRunner.h"
#include "kdrive/baos/core/Forwards.h"
#include <memory>
#include <string>
#include <vector>

namespace kdrive
{
namespace baos
{

class kdriveRPC_baos_API GetDescriptionString : public ServiceRunner
{
public:
	GetDescriptionString(std::shared_ptr<BaosConnector> connector);

	virtual ~GetDescriptionString();

	void rpc(unsigned short offset, unsigned short count,
	         unsigned long timeout = ServiceRunner::Timeout);

	typedef std::vector<std::string> Strings;

	const std::string& at(int index) const;
	const Strings& getStrings() const;

private:
	Strings strings_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_SERVICES_GET_DESCRIPTION_STRING_H__
