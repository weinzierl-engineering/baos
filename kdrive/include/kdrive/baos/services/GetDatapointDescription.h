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

#ifndef __KDRIVE_BAOS_SERVICES_GET_DATAPOINT_DESCRIPTION_H__
#define __KDRIVE_BAOS_SERVICES_GET_DATAPOINT_DESCRIPTION_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/ServiceRunner.h"
#include "kdrive/baos/core/Forwards.h"
#include <memory>
#include <tuple>
#include <vector>

namespace kdrive
{
namespace baos
{

class kdriveRPC_baos_API GetDatapointDescription : public ServiceRunner
{
public:
	GetDatapointDescription(std::shared_ptr<BaosConnector> connector);
	virtual ~GetDatapointDescription();

	void rpc(unsigned short offset, unsigned short count,
	         unsigned long timeout = ServiceRunner::Timeout);

	enum DescriptorFields
	{
		Id = 0,
		ValueType,
		ConfigFlags,
		DatapointType,
	};

	typedef std::tuple<unsigned short, unsigned char, unsigned char, unsigned char> Descriptor;
	typedef std::vector<Descriptor> Descriptors;

	const Descriptor& at(int index) const;
	const Descriptors& getDescriptors() const;

private:
	Descriptors descriptors_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_SERVICES_GET_DATAPOINT_DESCRIPTION_H__
