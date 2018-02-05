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

#pragma once

#include "kdriveManagedConfig.h"
#include "Connector.h"
#include <kdrive/baos/BaosParameter.h>

namespace kdrive
{
namespace baos
{
namespace bindings
{

/// <summary>
///	Read a parameter byte from the BAOS device.
///	This parameter byte should be configured with the ETS application.
/// </summary>
public ref class BaosParameter
{
public:
	/// <summary>
	///	Reads a parameter byte from the remote device.
	///	The id should correspond to the parameter id in the ETS project.
	/// </summary>
	static unsigned char readParameter(Connector^ connector, unsigned char id)
	{
		return kdrive::baos::readParameter(connector->getUnmanaged(), id);
	}
};

}
}
} // end namespace kdrive::baos::bindings

