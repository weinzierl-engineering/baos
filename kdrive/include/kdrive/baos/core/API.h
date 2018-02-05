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
	    V20 = 0x20, /*!<Protocol Version 2.0 (e.g. for BAOS 771/772/777)*/
	    LATEST = V20
	};

	static bool is1x(unsigned char version);
	static bool is2x(unsigned char version);
};

struct kdriveRPC_baos_API BaosDatapointCommands
{
	enum Commands
	{
	    NoCommand = 0x00,
	    SetNewValue = 0x01,
	    SendValueOnBus = 0x02,
	    SetNewValueAndSendOnBus = 0x03,
	    ReadNewValueViaBus = 0x04,
	    ClearTransmissionState = 0x05
	};
};

struct kdriveRPC_baos_API BaosTimerTypes
{
	enum TriggerTypes
	{
	    TriggerDate = 1,
	    TriggerInterval = 2
	};

	enum JobTypes
	{
	    JobSetDatapointValue = 1
	};
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
	    DPT_1 = 0x01, /*!< DPT 1 (1 Bit, Boolean) */
	    DPT_2 = 0x02, /*!< DPT 2 (2 Bit, Control) */
	    DPT_3 = 0x03, /*!< DPT 3 (4 Bit, Dimming, Blinds) */
	    DPT_4 = 0x04, /*!< DPT 4 (8 Bit, Character Set) */
	    DPT_5 = 0x05, /*!< DPT 5 (8 Bit, Unsigned Value) */
	    DPT_6 = 0x06, /*!< DPT 6 (8 Bit, Signed Value) */
	    DPT_7 = 0x07, /*!< DPT 7 (2 Byte, Unsigned Value) */
	    DPT_8 = 0x08, /*!< DPT 8 (2 Byte, Signed Value) */
	    DPT_9 = 0x09, /*!< DPT 9 (2 Byte, Float Value) */
	    DPT_10 = 0x0A, /*!< DPT 10 (3 Byte, Time) */
	    DPT_11 = 0x0B, /*!< DPT 11 (3 Byte, Date) */
	    DPT_12 = 0x0C, /*!< DPT 12 (4 Byte, Unsigned Value) */
	    DPT_13 = 0x0D, /*!< DPT 13 (4 Byte, Signed Value) */
	    DPT_14 = 0x0E, /*!< DPT 14 (4 Byte, Float Value) */
	    DPT_15 = 0x0F, /*!< DPT 15 (4 Byte, Access) */
	    DPT_16 = 0x10, /*!< DPT 16 (14 Byte, String) */
	    DPT_17 = 0x11, /*!< DPT 17 (1 Byte, Scene Number) */
	    DPT_18 = 0x12, /*!< DPT 18 (1 Byte, Scene Control) */
	    DPT_20 = 0x20, /*!< DPT 20 (1 Byte) */
	    DPT_232 = 0x21, /*!< DPT 232 (3-byte colour RGB) */
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
	    HardwareType = 1, /*!< (Read Only; 6 bytes) */
	    HardwareVersion = 2, /*!< (Read Only; 1 byte) */
	    FirmwareVersion = 3, /*!< (Read Only; 1 byte) */
	    ManufactureCodeDevice = 4, /*!< (Read Only; 2 bytes) */
	    ManufactureCodeApp = 5, /*!< (Read Only; 2 bytes) */
	    ApplicationId = 6, /*!< (Read Only; 2 bytes) */
	    ApplicationVersion = 7, /*!< (Read Only; 2 bytes) */
	    SerialNumber = 8, /*!< (Read Only; 6 bytes) */
	    TimeSinceReset = 9, /*!< (Read Only; 4 bytes) */
	    BusConnected = 10, /*!< (Read Only; 1 byte) */
	    MaxBufferSize = 11, /*!< (Read/Write; 2 bytes) */
	    LengthOfDescriptionString = 12, /*!< (Read Only; 2 bytes) */
	    BaudrateItem = 13, /*!< (Read/Write; 1 byte) */
	    CurrentBufferSize = 14, /*!< (Read Only; 2 bytes) */
	    ProgrammingModeItem = 15, /*!< (Read/Write; 1 bytes) */
	    BinaryProtocolVersion = 16,	/*!< Version of the ObjectServer binary protocol (Read Only; 1 byte; from V2.0) */
	    IndicationSetting = 17,	/*!< Indicates whether indications are sent (Read/Write; 1 byte; from V2.0) */
	    WebServicesProtocolVersion = 18, /*!< Version of the ObjectServer web services protocol (Read Only; 1 byte; from V2.0) */
	    RestServiceProtocolVersion = 19, /*!< (Read Only; 1 byte; from V2.1) */
	    IndividualAddress = 20, /*!< (Read Only; 2 byte; from V2.1) */
	    MacAddress = 21, /*!< (Read Only; 6 byte; from V2.1) */
	    TunnellingEnabled = 22, /*!< (Read Only; 1 byte; from V2.1) */
	    BaosBinaryEnabled = 23, /*!< (Read Only; 1 byte; from V2.1) */
	    BaosWebEnabled = 24, /*!< (Read Only; 1 byte; from V2.1) */
	    BaosRestEnabled = 25, /*!< (Read Only; 1 byte; from V2.1) */
	    HttpFileEnabled = 26, /*!< (Read Only; 1 byte; from V2.1) */
	    SearchRequestEnabled = 27, /*!< (Read Only; 1 byte; from V2.1) */
	    IsStructured = 28, /*!< (Read Only; 1 byte; from V2.1) */
	    MaxManagementClients = 29, /*!< (Read Only; 1 byte; from V2.1) */
	    ConnectedManagementClients = 30, /*!< (Read Only; 1 byte; from V2.1) */
	    MaxTunnellingClients = 31, /*!< (Read Only; 1 byte; from V2.1) */
	    ConnectedTunnellingClients = 32, /*!< (Read Only; 1 byte; from V2.1) */
	    MaxBaosUdpClients = 33, /*!< (Read Only; 1 byte; from V2.1) */
	    ConnectedBaosUdpClients = 34, /*!< (Read Only; 1 byte; from V2.1) */
	    MaxBaosTcpClients = 35, /*!< (Read Only; 1 byte; from V2.1) */
	    ConnectedBaosTcpClients = 36, /*!< (Read Only; 1 byte; from V2.1) */
	    DeviceFriendlyName = 37, /*!< (Read Only; 30 bytes; from V2.1) */
	    MaxDatapoints = 38, /*!< (Read Only; 2 bytes; from V2.1) */
	    ConfiguredDatapoints = 39, /*!< (Read Only; 2 bytes; from V2.1) */
	    MaxParameterBytes = 40, /*!< (Read Only; 2 bytes; from V2.1) */
	    DownloadCounter = 41, /*!< (Read Only; 2 bytes; from V2.1) */
	    IPAssignment = 42, /*!< (Read Only; 1 byte; from V2.1) */
	    IPAddress = 43, /*!< (Read Only; 4 bytes; from V2.1) */
	    SubnetMask = 44, /*!< (Read Only; 4 bytes; from V2.1) */
	    DefaultGateway = 45, /*!< (Read Only; 4 bytes; from V2.1) */
	    TimeSinceResetUnit = 46, /*!< (Read Only; 1 byte; from V2.1) */
	    SystemTime = 47, /*!< (Read Only; variable length; from V2.1) */
	    SystemTimezoneOffset = 48, /*!< (Read Only; 1 byte (signed); from V2.1) */
	    MenuEnabled = 49, /*!< (Read Only; 1 byte; from V2.1) */
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
	    BufferTooSmall = 3, /*!< Buffer is too small */
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
	    MinRequest                          = 0x01,
	    GetServerItem                       = 0x01,
	    SetServerItem                       = 0x02,
	    GetDatapointDescription             = 0x03,
	    GetDescriptionString                = 0x04,
	    GetDatapointValue                   = 0x05,
	    SetDatapointValue                   = 0x06,
	    GetParameterByte                    = 0x07,
	    GetDatapointHistoryCommand          = 0x08,
	    GetDatapointHistoryState            = 0x09,
	    GetDatapointHistory                 = 0x0A,
	    GetTimer                            = 0x0B,
	    SetTimer                            = 0x0C,
	    MaxRequest                          = 0x0C,
	};
};

struct kdriveRPC_baos_API ResponseFunctions
{
	enum Responses
	{
	    MinResponse                         = 0x81,
	    GetServerItem                       = 0x81,
	    SetServerItem                       = 0x82,
	    GetDatapointDescription             = 0x83,
	    GetDescriptionString                = 0x84,
	    GetDatapointValue                   = 0x85,
	    SetDatapointValue                   = 0x86,
	    GetParameterByte                    = 0x87,
	    GetDatapointHistoryCommand          = 0x88,
	    GetDatapointHistoryState    		= 0x89,
	    GetDatapointHistory         		= 0x8A,
	    GetTimer                    		= 0x8B,
	    SetTimer                    		= 0x8C,
	    MaxResponse                         = 0x8C
	};
};

struct kdriveRPC_baos_API IndicationFunctions
{
	enum Functions
	{
	    MinIndication                       = 0xC1,
	    DatapointValueIndication            = 0xC1,
	    ServerItemIndication				= 0xC2,
	    MaxIndication                       = 0xC2
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
