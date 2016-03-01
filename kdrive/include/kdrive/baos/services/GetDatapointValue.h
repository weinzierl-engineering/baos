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

#ifndef __KDRIVE_BAOS_SERVICES_GET_DATAPOINT_VALUE_H__
#define __KDRIVE_BAOS_SERVICES_GET_DATAPOINT_VALUE_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/ServiceRunner.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/baos/core/ServerItem.h"
#include <memory>
#include <vector>

namespace kdrive
{
namespace baos
{

class kdriveRPC_baos_API GetDatapointValue : public ServiceRunner
{
public:
	/*!
		Creates a GetDatapointValue service bound to a connection
		Sets the default filter to GetAll
	*/
	GetDatapointValue(std::shared_ptr<BaosConnector> connector);

	/*!
		Destroys the GetDatapointValue service
	*/
	virtual ~GetDatapointValue();

	/*!
		Filters are used to indicate which datapoint values to return
		as part of the GetDatapointValue request.
		Filters are only supported from version 2.0 of the BAOS protocol
		For 1.2 the request is equivalent to GetAll, irrespecive of filter value
	*/
	enum Filters
	{
	    GetAll = 0x00,	/*!< Get All Datpoint Values */
	    GetValid,		/*!< Get All Valid Datpoint Values */
	    GetUpdated		/*!< Get All Updated Datpoint Values */
	};

	/*!
		set the filter value used in the get datapoint value request
	*/
	void setFilter(unsigned char filter);

	/*!
		\return the filter value
	*/
	unsigned char getFilter();

	/*!
		sends a GetDatapointValue.Req
		and waits for a GetDatapointValue.Res
	*/
	void rpc(unsigned short offset, unsigned short count,
	         unsigned long timeout = ServiceRunner::Timeout);

	typedef ServerItem Value;			/*!< The GetDatapointValue return ServerItem formatted data */
	typedef std::vector<Value> Values;	/*!< the list of server item values received from the device */

	/*!
		Gets a Datapoint Value from the list
		Throws an exception if index is out of range
		\return Datapoint Value at index, index is the position in the list, not the id
		\sa find
	*/
	const Value& at(int index) const;

	/*!
		Finds a Datapoint Value in the list based on the id
		\return the datapoint value if found, otherwise an exception is thrown
	*/
	const Value& find(unsigned short id) const;

	/*!
		\return the list of datapoint values
	*/
	const Values& getValues() const;

private:
	Values values_;
	unsigned char filter_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_SERVICES_GET_DATAPOINT_VALUE_H__
