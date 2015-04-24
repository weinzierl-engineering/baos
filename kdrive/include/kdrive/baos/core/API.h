//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#ifndef __KDRIVE_BAOS_CORE_API_H__
#define __KDRIVE_BAOS_CORE_API_H__

#include "kdrive/baos/Config.h"
#include <vector>
#include <string>
#include <tuple>

namespace kdrive
{
namespace baos
{

struct kdriveRPC_baos_API ProtocolConstants
{
	enum
	{
	    Timeout = 5000
	};

	static const unsigned char MainService;
};

/*!
	BAOS protocol versions
*/
struct kdriveRPC_baos_API ProtocolVersions
{
	enum Versions
	{
	    Unknown = 0, /*!< The protocol version is unknown*/

	    V12 = 0x01, /*!<Protocol Version 1.2 (e.g. for BAOS 770)*/
	    V20 = 0x20 /*!<Protocol Version 2.0 (e.g. for BAOS 771 and BAOS 772)*/
	};
};

struct kdriveRPC_baos_API BaosDatapointCommands
{
	static const unsigned char NoCommand;
	static const unsigned char SetNewValue;
	static const unsigned char SendValueOnBus;
	static const unsigned char SetNewValueAndSendOnBus;
	static const unsigned char ReadNewValueViaBus;
	static const unsigned char ClearTransmissionState;
};

/*!
	BAOS datapoint types (DPT)

	<b>Specifications:</b>
	\li KNX ObjectServer protocol (Version 2.0)<br />
		Appendix D. Datapoint types (DPT)
*/
struct kdriveRPC_baos_API BaosDatapointTypes
{
	enum DPT
	{
	    DatapointDisabled = 0, /*!< Datapoint disabled */
	    DPT_1, /*!< DPT 1 (1 Bit, Boolean) */
	    DPT_2, /*!< DPT 2 (2 Bit, Control) */
	    DPT_3, /*!< DPT 3 (4 Bit, Dimming, Blinds) */
	    DPT_4, /*!< DPT 4 (8 Bit, Character Set) */
	    DPT_5, /*!< DPT 5 (8 Bit, Unsigned Value) */
	    DPT_6, /*!< DPT 6 (8 Bit, Signed Value) */
	    DPT_7, /*!< DPT 7 (2 Byte, Unsigned Value) */
	    DPT_8, /*!< DPT 8 (2 Byte, Signed Value) */
	    DPT_9, /*!< DPT 9 (2 Byte, Float Value) */
	    DPT_10, /*!< DPT 10 (3 Byte, Time) */
	    DPT_11, /*!< DPT 11 (3 Byte, Date) */
	    DPT_12, /*!< DPT 12 (4 Byte, Unsigned Value) */
	    DPT_13, /*!< DPT 13 (4 Byte, Signed Value) */
	    DPT_14, /*!< DPT 14 (4 Byte, Float Value) */
	    DPT_15, /*!< DPT 15 (4 Byte, Access) */
	    DPT_16, /*!< DPT 16 (14 Byte, String) */
	    DPT_17, /*!< DPT 17 (1 Byte, Scene Number) */
	    DPT_18, /*!< DPT 18 (1 Byte, Scene Control) */
	    Unknown = 255 /*!< Unknown DPT */
	};
};

/*!
	BAOS server items

	<b>Specifications:</b>
	\li KNX ObjectServer protocol (Version 2.0)<br />
		Appendix A. Item IDs
*/
struct kdriveRPC_baos_API ServerItemProperties
{
	enum Items
	{
	    HardwareType = 1,
	    HardwareVersion = 2,
	    FirmwareVersion = 3,
	    ManufactureCodeDevice = 4,
	    ManufactureCodeApp = 5,
	    ApplicationId = 6,
	    ApplicationVersion = 7,
	    SerialNumber = 8,
	    TimeSinceReset = 9,
	    BusConnected = 10,
	    MaxBufferSize = 11,
	    LengthOfDescriptionString = 12,
	    BaudrateItem = 13,
	    CurrentBufferSize = 14,
	    ProgrammingModeItem = 15,
	    BinaryProtocolVersion = 16,			/*!< Version of the ObjectServer binary protocol, Read Only, from V2.0 */
	    ProtocolVersion = BinaryProtocolVersion, /*!< \deprecated, use BinaryProtocolVersion instead */
	    IndicationSetting = 17,				/*!< Indicates whether indications are sent, Read/Write, from V2.0 */
	    WebServicesProtocolVersion = 18		/*!< Version of the ObjectServer web services protocol, Read Only, from V2.0 */
	};
};

/*!
	BAOS server error codes

	<b>Specifications:</b>
	\li KNX ObjectServer protocol (Version 2.0)<br />
		Appendix B. Error Codes
*/
struct kdriveRPC_baos_API BaosServerErrorCodes
{
	enum Codes
	{
	    None = 0, /*!< No error */
	    Internal = 1, /*!< Internal error */
	    NoItemFound = 2, /*!< No item found */
	    BufferToSmall = 3, /*!< Buffer is too small */
	    ItemNotWriteable = 4, /*!< Item is not writable */
	    ServiceNotSupported = 5, /*!< Service is not supported */
	    BadServiceParameter = 6, /*!< Bad service parameter */
	    WrongDpId = 7, /*!< Wrong datapoint ID */
	    BadDpCmd = 8, /*!< Bad datapoint command */
	    BadDpValueLength = 9, /*!< Bad length of datapoint value */
	    MessageInconsistent = 10, /*!< Message inconsistent */
	    ObjectServerIsBusy = 11, /*!< Object server is busy */
	};
};

struct kdriveRPC_baos_API StreamProtocolConstants
{
	enum
	{
		Port = 12004,
		Id = 0x42414F53
	};

	enum PacketTypes
	{
	    Request = 0x00,
	    Response = 0x80,
	    Indication = 0x0C
	};
};

struct kdriveRPC_baos_API MulticastProtocolConstants
{
	static const unsigned short Port;
	static const std::string Address;
};

struct kdriveRPC_baos_API RequestFunctions
{
	enum Requests
	{
	    GetServerItem                       = 0x01,
	    SetServerItem                       = 0x02,
	    GetDatapointDescription             = 0x03,
	    GetDescriptionString                = 0x04,
	    GetDatapointValue                   = 0x05,
	    SetDatapointValue                   = 0x06,
	    GetParameterByte                    = 0x07
	};
};

struct kdriveRPC_baos_API ResponseFunctions
{
	enum Requests
	{
	    GetServerItem                       = 0x81,
	    SetServerItem                       = 0x82,
	    GetDatapointDescription             = 0x83,
	    GetDescriptionString                = 0x84,
	    GetDatapointValue                   = 0x85,
	    SetDatapointValue                   = 0x86,
	    GetParameterByte                    = 0x87
	};
};

struct kdriveRPC_baos_API IndicationFunctions
{
	enum Functions
	{
	    DatapointValueIndication            = 0xC1,
	    ServerItemIndication				= 0xC2
	};
};

struct kdriveRPC_baos_API BaosDeviceAttr
{
	enum
	{
	    Name = 0,
	    InterfaceAddress,
	    Address,
	    Version
	};

	typedef std::tuple<std::string, std::string, std::string, unsigned char> Device;
	typedef std::vector<Device> Devices;
};

typedef BaosDeviceAttr::Device BaosDevice;
typedef BaosDeviceAttr::Devices BaosDevices;

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_API_H__
