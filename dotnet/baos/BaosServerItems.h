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

#pragma once

#include "kdriveManagedConfig.h"
#include "Connector.h"
#include <kdrive/baos/BaosServerItems.h>

namespace unmanaged
{
typedef kdrive::baos::BaosServerItems BaosServerItems;
}

namespace kdrive
{
namespace baos
{
namespace bindings
{

/// <summary>
///	BaosServerItems is used to get/set the server item parameters
///	from/on the remote device. 
/// </summary>
/// <remarks>
///	It wraps the GetServerItem and SetServerItem services,
///	which are byte based and provides the appropriate interpretation to
///	convert the parameters to their corresponding values.
/// </remarks>
public ref class BaosServerItems
{
public:

	/// <summary>
	///	Creates a BaosServerItems object with a specified connector
	/// </summary>
	BaosServerItems(Connector^ connector)

		: serverItem_(0)
	{
		try
		{
			serverItem_ = new unmanaged::BaosServerItems(connector->getUnmanaged());
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Destroys the BaosServerItems.
	///	Destructor cleans up unmanaged and managed resources.
	/// </summary>
	~BaosServerItems()
	{
		// call finalizer to release unmanaged resources
		this->!BaosServerItems();
	}

	/// <summary>
	///	Gets the hardware type.
	/// </summary>
	/// <remarks>
	///	Can be used to identify the hardware type.<br />
	///	It is mapped to property PID_HARDWARE_TYPE in the device object.<br />
	///	Server item: hardware type, id 1
	/// </remarks>
	array<unsigned char>^ getHardwareType()
	{
		try
		{
			const std::vector<unsigned char>& data = serverItem_->getHardwareType();
			return interop::ArrayCreator::Copy(&data[0], data.size());
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the version of the ObjectServer hardware
	/// </summary>
	/// <remarks>
	///	Coding Ex.: 0x10 = Version 1.0<br />
	///	Server item: hardware version, id 2
	/// </remarks>
	unsigned char getHardwareVersion()
	{
		try
		{
			return serverItem_->getHardwareVersion();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the version of ObjectServer firmware.
	/// </summary>
	/// <remarks>
	///	Coding Ex.: 0x10 = Version 1.0<br />
	///	Server item: firmware version, id 3
	/// </remarks>
	unsigned char getFirmwareVersion()
	{
		try
		{
			return serverItem_->getFirmwareVersion();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the KNX manufacturer code of the device.
	/// </summary>
	/// <remarks>
	///	Not modified by ETS.<br />
	///	It is mapped to property PID_MANUFACTURER_ID in the device object.<br />
	///	Server item: KNX manufacture code DEV, id 4
	/// </remarks>
	unsigned int getManufactureCodeDevice()
	{
		try
		{
			return serverItem_->getManufactureCodeDevice();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the KNX manufacturer code loaded by ETS.
	/// </summary>
	/// <remarks>
	///	It is mapped to bytes 0 and 1 of property<br />
	///	PID_APPLICATION_VER in the application object.<br />
	///	Server item: KNX manufacture code APP, id 5
	/// </remarks>
	unsigned int getManufactureCodeApp()
	{
		try
		{
			return serverItem_->getManufactureCodeApp();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the id of application loaded by ETS.
	/// </summary>
	/// <remarks>
	///	It is mapped to bytes 2 and 3 of property<br />
	///	PID_APPLICATION_VER in the application object.<br />
	///	Server item: application id (ETS), id 6
	/// </remarks>
	unsigned int getApplicationId()
	{
		try
		{
			return serverItem_->getApplicationId();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the version of application loaded by ETS.
	/// </summary>
	/// <remarks>
	///	It is mapped to byte 4 of property PID_APPLICATION_VER
	///	in application object.<br />
	///	Server item: application version (ETS), id 7
	/// </remarks>
	unsigned char getApplicationVersion()
	{
		try
		{
			return serverItem_->getApplicationVersion();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets KNX serial number of device.
	/// </summary>
	/// <remarks>
	///	It is mapped to property PID_SERIAL_NUMBER in the device object.<br />
	///	Server item: serial number, id 8
	/// </remarks>
	array<unsigned char>^ getSerialNumber()
	{
		try
		{
			const std::vector<unsigned char>& data = serverItem_->getSerialNumber();
			return interop::ArrayCreator::Copy(&data[0], data.size());
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the time since reset in ms.
	/// </summary>
	/// <remarks>
	///	Server item: time since reset, id 9
	/// </remarks>
	unsigned long getTimeSinceReset()
	{
		try
		{
			return serverItem_->getTimeSinceReset();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true if the KNX bus is connected, otherwise false.
	/// </summary>
	/// <remarks>
	///	Server item: bus connection state, id 10
	/// </remarks>
	bool isBusConnected()
	{
		try
		{
			return serverItem_->isBusConnected();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the maximal buffer size.
	/// </summary>
	/// <remarks>
	///	Server item: Maximal buffer size, id 11
	/// </remarks>
	unsigned int getMaxBufferSize()
	{
		try
		{
			return serverItem_->getMaxBufferSize();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the length of the description string.
	/// </summary>
	/// <remarks>
	///	Server item: Length of description string, id 12
	/// </remarks>
	unsigned int getLengthOfDescriptionString()
	{
		try
		{
			return serverItem_->getLengthOfDescriptionString();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Possible values for server item Baudrate, id 13
	/// </summary>
	enum class Baudrate
	{
		Unknown = unmanaged::BaosServerItems::Unknown,
		B19200 = unmanaged::BaosServerItems::B19200,
		B115200 = unmanaged::BaosServerItems::B115200
	};

	/// <summary>
	///	Sets the Baudrate
	/// </summary>
	/// <remarks>
	///	Values: BaosServerItems::Unknown,
	///	BaosServerItems::BB19200, BaosServerItems::B115200
	/// <seealso cref="Baudrate" />
	/// </remarks>
	void setBaudrate(unsigned char baudrate)
	{
		try
		{
			return serverItem_->setBaudrate(baudrate);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets the baudrate.
	/// </summary>
	/// <remarks>
	///	Server item: Baudrate, id 13
	/// <seealso cref="Baudrate" />
	/// </remarks>
	unsigned char getBaudrate()
	{
		try
		{
			return serverItem_->getBaudrate();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets the current buffer size.
	/// </summary>
	/// <remarks>
	///	Server item: Current buffer size, id 14
	/// </remarks>
	void setBufferSize(unsigned int bufferSize)
	{
		try
		{
			return serverItem_->setBufferSize(bufferSize);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets the current buffer size.
	/// </summary>
	/// <remarks>
	///	Server item: Current buffer size, id 14
	/// </remarks>
	unsigned int getBufferSize()
	{
		try
		{
			return serverItem_->getBufferSize();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Possible values for server item ProgrammingMode, id 15
	/// </summary>
	enum class ProgrammingMode
	{
		NotActive = unmanaged::BaosServerItems::NotActive,
		Active = unmanaged::BaosServerItems::Active
	};

	/// <summary>
	///	Sets the programming mode
	/// </summary>
	/// <remarks>
	///	Values: ProgrammingMode::NotActive ProgrammingMode::Active<br />
	///	Server item: Programming mode, id 15
	/// <seealso cref="ProgrammingMode" />
	/// </remarks>
	void setProgrammingMode(unsigned char programmingMode)
	{
		try
		{
			return serverItem_->setProgrammingMode(programmingMode);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets the programming mode.
	/// </summary>
	/// <remarks>
	///	Server item: Programming mode, id 15
	/// <seealso cref="ProgrammingMode" />
	/// </remarks>
	unsigned char getProgrammingMode()
	{
		try
		{
			return serverItem_->getProgrammingMode();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the version of the ObjectServer binary protocol
	/// </summary>
	/// <remarks>
	///	Server item: Protocol Version (Binary), id 16
	/// </remarks>
	unsigned char getBinaryProtocolVersion()
	{
		try
		{
			return serverItem_->getBinaryProtocolVersion();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Possible values for server item Indication Sending, id 17
	/// </summary>
	enum class IndicationSetting
	{
		IndicationSetting_NotActive = unmanaged::BaosServerItems::IndicationSetting_NotActive,
		IndicationSetting_Active = unmanaged::BaosServerItems::IndicationSetting_Active
	};

	/// <summary>
	///	Sets the indication setting
	/// </summary>
	/// <remarks>
	///	Values: IndicationSetting::IndicationSetting_NotActive IndicationSetting::IndicationSetting_Active<br />
	///	Server item: Indication Sending, id 17
	/// </remarks>
	void setIndicationSetting(unsigned char indicationSetting)
	{
		try
		{
			return serverItem_->setIndicationSetting(indicationSetting);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets the indication setting
	/// </summary>
	/// <remarks>
	///	Server item: Indication Sending, id 17
	/// </remarks>
	unsigned char getIndicationSetting()
	{
		try
		{
			return serverItem_->getIndicationSetting();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the version of the ObjectServer web services protocol
	/// </summary>
	/// <remarks>
	///	Server item: Protocol Version (WebService), id 18
	/// </remarks>
	unsigned char getWebServicesProtocolVersion()
	{
		try
		{
			return serverItem_->getWebServicesProtocolVersion();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

protected:
	/// <summary>
	///	Finalizer (non-deterministic destructor) 
	///	cleans up unmanaged resources.
	/// </summary>
	!BaosServerItems()
	{
		try
		{
			if (serverItem_)
			{
				delete serverItem_;
				serverItem_ = 0;
			}
		}
		catch (...)
		{
		}
	}

private:
	unmanaged::BaosServerItems* serverItem_;
};

}
}
} // end namespace kdrive::baos::bindings
