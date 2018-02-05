#
# Copyright (c) 2002-2018 WEINZIERL ENGINEERING GmbH
# All rights reserved.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
# SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
# WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
#
#
# This module is used to configure the (subset of the) kdrive library 
# for the BAOS SDK
#
# Following variables are defined in a parent CMakeList.txt:
# KDRIVE_LIBRARY_NAME: The target library name (e.g. kdriveBAOS)
# WZSDK_LINKMODE: Link mode (STATIC or SHARED)
# SYSTEM_LIBS: System Libraries (e.g. setupapi, pthread, ...)

######################################################################
# kdrive
######################################################################

# ---------- LOCATION OF KDRIVE INCLUDE AND SRC DIRECTORIES

set(KDRIVE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(KDRIVE_INCLUDE "${KDRIVE_DIR}/include")
set(KDRIVE_SRC "${KDRIVE_DIR}/src")

MESSAGE( STATUS "PATH KDRIVE_INCLUDE: " ${KDRIVE_INCLUDE} )
MESSAGE( STATUS "PATH KDRIVE_SRC: " ${KDRIVE_SRC} )

# ---------- SOURCE AND HEADER FILES

# ---------- kdrive component: baos

set(KDRIVE_BAOS_INCLUDE "${KDRIVE_INCLUDE}/kdrive/baos")
set(KDRIVE_BAOS_SRC "${KDRIVE_SRC}/baos")

# baos top files

set (KDRIVE_BAOS_HEADER_FILES_TOP
  ${KDRIVE_BAOS_INCLUDE}/Baos.h
  ${KDRIVE_BAOS_INCLUDE}/BaosConnection.h
  ${KDRIVE_BAOS_INCLUDE}/BaosDatapoint.h
  ${KDRIVE_BAOS_INCLUDE}/BaosDatapointDescriptions.h 
  ${KDRIVE_BAOS_INCLUDE}/BaosEnumerator.h
  ${KDRIVE_BAOS_INCLUDE}/BaosEvent.h
  ${KDRIVE_BAOS_INCLUDE}/BaosHeartbeat.h 
  ${KDRIVE_BAOS_INCLUDE}/BaosParameter.h
  ${KDRIVE_BAOS_INCLUDE}/BaosServerItems.h
  ${KDRIVE_BAOS_INCLUDE}/BaosTimers.h
  ${KDRIVE_BAOS_INCLUDE}/Config.h
  ${KDRIVE_BAOS_INCLUDE}/Headers.h
)

set (KDRIVE_BAOS_SOURCE_FILES_TOP
  ${KDRIVE_BAOS_SRC}/BaosConnection.cpp
  ${KDRIVE_BAOS_SRC}/BaosDatapoint.cpp
  ${KDRIVE_BAOS_SRC}/BaosDatapointDescriptions.cpp
  ${KDRIVE_BAOS_SRC}/BaosEnumerator.cpp
  ${KDRIVE_BAOS_SRC}/BaosEvent.cpp
  ${KDRIVE_BAOS_SRC}/BaosHeartbeat.cpp
  ${KDRIVE_BAOS_SRC}/BaosParameter.cpp
  ${KDRIVE_BAOS_SRC}/BaosServerItems.cpp
  ${KDRIVE_BAOS_SRC}/BaosTimers.cpp
)

source_group("baos" FILES ${KDRIVE_BAOS_HEADER_FILES_TOP})
source_group("baos" FILES ${KDRIVE_BAOS_SOURCE_FILES_TOP})

# baos core files

set (KDRIVE_BAOS_HEADER_FILES_CORE
  ${KDRIVE_BAOS_INCLUDE}/core/API.h
  ${KDRIVE_BAOS_INCLUDE}/core/BaosConnector.h
  ${KDRIVE_BAOS_INCLUDE}/core/BaosPacketFactory.h
  ${KDRIVE_BAOS_INCLUDE}/core/BaosProtocolDecoder.h
  ${KDRIVE_BAOS_INCLUDE}/core/Core.h
  ${KDRIVE_BAOS_INCLUDE}/core/DataPacket.h
  ${KDRIVE_BAOS_INCLUDE}/core/ErrorCodes.h
  ${KDRIVE_BAOS_INCLUDE}/core/Exception.h
  ${KDRIVE_BAOS_INCLUDE}/core/FixPocoException.h
  ${KDRIVE_BAOS_INCLUDE}/core/Headers.h
  ${KDRIVE_BAOS_INCLUDE}/core/Forwards.h
  ${KDRIVE_BAOS_INCLUDE}/core/ServerFunction.h
  ${KDRIVE_BAOS_INCLUDE}/core/ServerItem.h
  ${KDRIVE_BAOS_INCLUDE}/core/ServiceRunner.h
  ${KDRIVE_BAOS_INCLUDE}/core/String.h
  ${KDRIVE_BAOS_INCLUDE}/core/Timer.h
)

set (KDRIVE_BAOS_SOURCE_FILES_CORE
  ${KDRIVE_BAOS_SRC}/core/API.cpp
  ${KDRIVE_BAOS_SRC}/core/BaosConnector.cpp
  ${KDRIVE_BAOS_SRC}/core/BaosPacketFactory.cpp
  ${KDRIVE_BAOS_SRC}/core/BaosProtocolDecoder.cpp
  ${KDRIVE_BAOS_SRC}/core/DataPacket.cpp
  ${KDRIVE_BAOS_SRC}/core/ErrorCodes.cpp
  ${KDRIVE_BAOS_SRC}/core/Exception.cpp
  ${KDRIVE_BAOS_SRC}/core/ServerFunction.cpp
  ${KDRIVE_BAOS_SRC}/core/ServerItem.cpp
  ${KDRIVE_BAOS_SRC}/core/ServiceRunner.cpp
  ${KDRIVE_BAOS_SRC}/core/String.cpp
  ${KDRIVE_BAOS_SRC}/core/Timer.cpp
)

source_group("baos\\core" FILES ${KDRIVE_BAOS_HEADER_FILES_CORE})
source_group("baos\\core" FILES ${KDRIVE_BAOS_SOURCE_FILES_CORE})

# baos ft12 files

set (KDRIVE_BAOS_HEADER_FILES_FT12
  ${KDRIVE_BAOS_INCLUDE}/ft12/FT12Connector.h
  ${KDRIVE_BAOS_INCLUDE}/ft12/Headers.h
)

set (KDRIVE_BAOS_SOURCE_FILES_FT12
  ${KDRIVE_BAOS_SRC}/ft12/FT12Connector.cpp
)

LIST(APPEND KDRIVE_BAOS_HEADER_FILES ${KDRIVE_BAOS_HEADER_FILES_FT12})
LIST(APPEND KDRIVE_BAOS_SOURCE_FILES ${KDRIVE_BAOS_SOURCE_FILES_FT12})

source_group("baos\\ft12" FILES ${KDRIVE_BAOS_HEADER_FILES_FT12})
source_group("baos\\ft12" FILES ${KDRIVE_BAOS_SOURCE_FILES_FT12})

# baos protocols files

set (KDRIVE_BAOS_HEADER_FILES_PROTOCOLS
  ${KDRIVE_BAOS_INCLUDE}/protocols/Headers.h
  ${KDRIVE_BAOS_INCLUDE}/protocols/Protocol.h
  ${KDRIVE_BAOS_INCLUDE}/protocols/Protocol12.h
  ${KDRIVE_BAOS_INCLUDE}/protocols/Protocol2x.h
)

set (KDRIVE_BAOS_SOURCE_FILES_PROTOCOLS
  ${KDRIVE_BAOS_SRC}/protocols/Protocol.cpp
  ${KDRIVE_BAOS_SRC}/protocols/Protocol12.cpp
  ${KDRIVE_BAOS_SRC}/protocols/Protocol2x.cpp
)

source_group("baos\\protocols" FILES ${KDRIVE_BAOS_HEADER_FILES_PROTOCOLS})
source_group("baos\\protocols" FILES ${KDRIVE_BAOS_SOURCE_FILES_PROTOCOLS})

# baos services files

set (KDRIVE_BAOS_HEADER_FILES_SERVICES 
  ${KDRIVE_BAOS_INCLUDE}/services/GetDatapointDescription.h
  ${KDRIVE_BAOS_INCLUDE}/services/GetDatapointValue.h
  ${KDRIVE_BAOS_INCLUDE}/services/GetDescriptionString.h
  ${KDRIVE_BAOS_INCLUDE}/services/GetParameterByte.h
  ${KDRIVE_BAOS_INCLUDE}/services/GetServerItem.h
  ${KDRIVE_BAOS_INCLUDE}/services/GetTimer.h
  ${KDRIVE_BAOS_INCLUDE}/services/Headers.h
  ${KDRIVE_BAOS_INCLUDE}/services/Services.h
  ${KDRIVE_BAOS_INCLUDE}/services/SetDatapointHistoryCommand.h
  ${KDRIVE_BAOS_INCLUDE}/services/SetDatapointValue.h
  ${KDRIVE_BAOS_INCLUDE}/services/SetServerItem.h
  ${KDRIVE_BAOS_INCLUDE}/services/SetTimer.h
)

set (KDRIVE_BAOS_SOURCE_FILES_SERVICES 
  ${KDRIVE_BAOS_SRC}/services/GetDatapointDescription.cpp
  ${KDRIVE_BAOS_SRC}/services/GetDatapointValue.cpp
  ${KDRIVE_BAOS_SRC}/services/GetDescriptionString.cpp
  ${KDRIVE_BAOS_SRC}/services/GetParameterByte.cpp
  ${KDRIVE_BAOS_SRC}/services/GetServerItem.cpp
  ${KDRIVE_BAOS_SRC}/services/GetTimer.cpp
  ${KDRIVE_BAOS_SRC}/services/SetDatapointHistoryCommand.cpp
  ${KDRIVE_BAOS_SRC}/services/SetDatapointValue.cpp
  ${KDRIVE_BAOS_SRC}/services/SetServerItem.cpp
  ${KDRIVE_BAOS_SRC}/services/SetTimer.cpp
)

source_group("baos\\services" FILES ${KDRIVE_BAOS_HEADER_FILES_SERVICES})
source_group("baos\\services" FILES ${KDRIVE_BAOS_SOURCE_FILES_SERVICES})

# baos stream files

set (KDRIVE_BAOS_HEADER_FILES_STREAM
  ${KDRIVE_BAOS_INCLUDE}/stream/Headers.h
  ${KDRIVE_BAOS_INCLUDE}/stream/Stream.h
  ${KDRIVE_BAOS_INCLUDE}/stream/StreamConnection.h
  ${KDRIVE_BAOS_INCLUDE}/stream/StreamConnector.h
  ${KDRIVE_BAOS_INCLUDE}/stream/StreamConnector12.h
  ${KDRIVE_BAOS_INCLUDE}/stream/StreamConnector2x.h
)

set (KDRIVE_BAOS_SOURCE_FILES_STREAM
  ${KDRIVE_BAOS_SRC}/stream/StreamConnection.cpp
  ${KDRIVE_BAOS_SRC}/stream/StreamConnector.cpp
  ${KDRIVE_BAOS_SRC}/stream/StreamConnector12.cpp
  ${KDRIVE_BAOS_SRC}/stream/StreamConnector2x.cpp
)

source_group("baos\\stream" FILES ${KDRIVE_BAOS_HEADER_FILES_STREAM})
source_group("baos\\stream" FILES ${KDRIVE_BAOS_SOURCE_FILES_STREAM})

# baos files (all)

LIST(APPEND KDRIVE_BAOS_HEADER_FILES 
  ${KDRIVE_BAOS_HEADER_FILES_TOP}
  ${KDRIVE_BAOS_HEADER_FILES_CORE}
  ${KDRIVE_BAOS_HEADER_FILES_FT12}
  ${KDRIVE_BAOS_HEADER_FILES_PROTOCOLS}
  ${KDRIVE_BAOS_HEADER_FILES_SERVICES}
  ${KDRIVE_BAOS_HEADER_FILES_STREAM}
)

LIST(APPEND KDRIVE_BAOS_SOURCE_FILES 
  ${KDRIVE_BAOS_SOURCE_FILES_TOP}
  ${KDRIVE_BAOS_SOURCE_FILES_CORE}
  ${KDRIVE_BAOS_SOURCE_FILES_FT12}
  ${KDRIVE_BAOS_SOURCE_FILES_PROTOCOLS}
  ${KDRIVE_BAOS_SOURCE_FILES_SERVICES}
  ${KDRIVE_BAOS_SOURCE_FILES_STREAM}
)

# ---------- kdrive component: connector

set(KDRIVE_CONNECTOR_INCLUDE "${KDRIVE_INCLUDE}/kdrive/connector")
set(KDRIVE_CONNECTOR_SRC "${KDRIVE_SRC}/connector")

set (KDRIVE_CONNECTOR_HEADER_FILES
  ${KDRIVE_CONNECTOR_INCLUDE}/CallbackThread.h
  ${KDRIVE_CONNECTOR_INCLUDE}/Config.h
  ${KDRIVE_CONNECTOR_INCLUDE}/Connector.h
  ${KDRIVE_CONNECTOR_INCLUDE}/ConnectorNotificationHandler.h
  ${KDRIVE_CONNECTOR_INCLUDE}/ErrorCodes.h
  ${KDRIVE_CONNECTOR_INCLUDE}/Events.h
  ${KDRIVE_CONNECTOR_INCLUDE}/Forwards.h
  ${KDRIVE_CONNECTOR_INCLUDE}/Headers.h
  ${KDRIVE_CONNECTOR_INCLUDE}/Packet.h
  ${KDRIVE_CONNECTOR_INCLUDE}/PacketFactory.h
  ${KDRIVE_CONNECTOR_INCLUDE}/PacketNotification.h
  ${KDRIVE_CONNECTOR_INCLUDE}/PacketTrace.h
  ${KDRIVE_CONNECTOR_INCLUDE}/QueueConnector.h
  ${KDRIVE_CONNECTOR_INCLUDE}/ScopedConnectorSignals.h
  ${KDRIVE_CONNECTOR_INCLUDE}/Semaphore.h
  ${KDRIVE_CONNECTOR_INCLUDE}/Wait.h
)
  
set (KDRIVE_CONNECTOR_SOURCE_FILES
  ${KDRIVE_CONNECTOR_SRC}/CallbackThread.cpp
  ${KDRIVE_CONNECTOR_SRC}/Connector.cpp
  ${KDRIVE_CONNECTOR_SRC}/ConnectorNotificationHandler.cpp
  ${KDRIVE_CONNECTOR_SRC}/Events.cpp
  ${KDRIVE_CONNECTOR_SRC}/Packet.cpp
  ${KDRIVE_CONNECTOR_SRC}/PacketFactory.cpp
  ${KDRIVE_CONNECTOR_SRC}/PacketNotification.cpp
  ${KDRIVE_CONNECTOR_SRC}/PacketTrace.cpp
  ${KDRIVE_CONNECTOR_SRC}/QueueConnector.cpp
  ${KDRIVE_CONNECTOR_SRC}/ScopedConnectorSignals.cpp
  ${KDRIVE_CONNECTOR_SRC}/Wait.cpp
)

source_group("connector" FILES ${KDRIVE_CONNECTOR_HEADER_FILES})
source_group("connector" FILES ${KDRIVE_CONNECTOR_SOURCE_FILES})

# ---------- kdrive component: ft12

set(KDRIVE_FT12_INCLUDE "${KDRIVE_INCLUDE}/kdrive/ft12")
set(KDRIVE_FT12_SRC "${KDRIVE_SRC}/ft12")

set (KDRIVE_FT12_HEADER_FILES
  ${KDRIVE_FT12_INCLUDE}/Config.h
  ${KDRIVE_FT12_INCLUDE}/Forwards.h
  ${KDRIVE_FT12_INCLUDE}/FT12.h
  ${KDRIVE_FT12_INCLUDE}/FT12Packetizer.h
  ${KDRIVE_FT12_INCLUDE}/Headers.h
)

set (KDRIVE_FT12_SOURCE_FILES
  ${KDRIVE_FT12_SRC}/FT12.cpp
  ${KDRIVE_FT12_SRC}/FT12Packetizer.cpp
)

source_group("ft12" FILES ${KDRIVE_FT12_HEADER_FILES})
source_group("ft12" FILES ${KDRIVE_FT12_SOURCE_FILES})

# ---------- kdrive component: io.serial

set(KDRIVE_IO_SERIAL_INCLUDE "${KDRIVE_INCLUDE}/kdrive/io/serial")
set(KDRIVE_IO_SERIAL_SRC "${KDRIVE_SRC}/io/serial")

set (KDRIVE_IO_SERIAL_HEADER_FILES
  ${KDRIVE_IO_SERIAL_INCLUDE}/Config.h
  ${KDRIVE_IO_SERIAL_INCLUDE}/SerialPort.h
  ${KDRIVE_IO_SERIAL_INCLUDE}/SerialPort_POSIX.h
  ${KDRIVE_IO_SERIAL_INCLUDE}/SerialPort_WIN32.h
)

set (KDRIVE_IO_SERIAL_SOURCE_FILES
  ${KDRIVE_IO_SERIAL_SRC}/SerialPort.cpp
)

source_group("io\\serial" FILES ${KDRIVE_IO_SERIAL_HEADER_FILES})
source_group("io\\serial" FILES ${KDRIVE_IO_SERIAL_SOURCE_FILES})

# ---------- kdrive component: knx

set(KDRIVE_KNX_INCLUDE "${KDRIVE_INCLUDE}/kdrive/knx")
set(KDRIVE_KNX_SRC "${KDRIVE_SRC}/knx")

# knx top files

set (KDRIVE_KNX_HEADER_FILES_TOP
  ${KDRIVE_KNX_INCLUDE}/Config.h
  ${KDRIVE_KNX_INCLUDE}/Knx.h
)

set (KDRIVE_KNX_SOURCE_FILES_TOP
)

source_group("knx" FILES ${KDRIVE_KNX_HEADER_FILES_TOP})
source_group("knx" FILES ${KDRIVE_KNX_SOURCE_FILES_TOP})

# knx core files

set (KDRIVE_KNX_HEADER_FILES_CORE
  ${KDRIVE_KNX_INCLUDE}/core/Core.h
  ${KDRIVE_KNX_INCLUDE}/core/Buffer.h
  ${KDRIVE_KNX_INCLUDE}/core/ByteStream.h
)

set (KDRIVE_KNX_SOURCE_FILES_CORE
  ${KDRIVE_KNX_SRC}/core/Buffer.cpp
  ${KDRIVE_KNX_SRC}/core/ByteStream.cpp
)

source_group("knx\\core" FILES ${KDRIVE_KNX_HEADER_FILES_CORE})
source_group("knx\\core" FILES ${KDRIVE_KNX_SOURCE_FILES_CORE})

# knx datapoint files

set (KDRIVE_KNX_HEADER_FILES_DATAPOINT
  ${KDRIVE_KNX_INCLUDE}/datapoint/Datapoint.h
  ${KDRIVE_KNX_INCLUDE}/datapoint/DatapointFactory.h
  ${KDRIVE_KNX_INCLUDE}/datapoint/FloatConverter.h
  ${KDRIVE_KNX_INCLUDE}/datapoint/Headers.h
)

set (KDRIVE_KNX_SOURCE_FILES_DATAPOINT
  ${KDRIVE_KNX_SRC}/datapoint/Datapoint.cpp
  ${KDRIVE_KNX_SRC}/datapoint/DatapointFactory.cpp
  ${KDRIVE_KNX_SRC}/datapoint/FloatConverter.cpp
)

source_group("knx\\datapoint" FILES ${KDRIVE_KNX_HEADER_FILES_DATAPOINT})
source_group("knx\\datapoint" FILES ${KDRIVE_KNX_SOURCE_FILES_DATAPOINT})

# knx defines files

set (KDRIVE_KNX_HEADER_FILES_DEFINES
  ${KDRIVE_KNX_INCLUDE}/defines/DatapointTypes.h
  ${KDRIVE_KNX_INCLUDE}/defines/FT12Constants.h
)

set (KDRIVE_KNX_SOURCE_FILES_DEFINES
  ${KDRIVE_KNX_SRC}/defines/DatapointTypes.cpp
)

source_group("knx\\defines" FILES ${KDRIVE_KNX_HEADER_FILES_DEFINES})
source_group("knx\\defines" FILES ${KDRIVE_KNX_SOURCE_FILES_DEFINES})

# knx telegrams files

set (KDRIVE_KNX_HEADER_FILES_TELEGRAMS
)

set (KDRIVE_KNX_SOURCE_FILES_TELEGRAMS
)

source_group("knx\\telegrams" FILES ${KDRIVE_KNX_HEADER_FILES_TELEGRAMS})
source_group("knx\\telegrams" FILES ${KDRIVE_KNX_SOURCE_FILES_TELEGRAMS})

# knx telegrams/formatters files

set (KDRIVE_KNX_HEADER_FILES_TELEGRAMS_FORMATTERS
  ${KDRIVE_KNX_INCLUDE}/telegrams/formatters/Formatter.h
  ${KDRIVE_KNX_INCLUDE}/telegrams/formatters/Formatters.h
)

set (KDRIVE_KNX_SOURCE_FILES_TELEGRAMS_FORMATTERS
  ${KDRIVE_KNX_SRC}/telegrams/formatters/Formatter.cpp
)

source_group("knx\\telegrams\\formatters" FILES ${KDRIVE_KNX_HEADER_FILES_TELEGRAMS_FORMATTERS})
source_group("knx\\telegrams\\formatters" FILES ${KDRIVE_KNX_SOURCE_FILES_TELEGRAMS_FORMATTERS})

# knx telegrams/ft12 files

set (KDRIVE_KNX_HEADER_FILES_TELEGRAMS_FT12
  ${KDRIVE_KNX_INCLUDE}/telegrams/ft12/AckFrame.h
  ${KDRIVE_KNX_INCLUDE}/telegrams/ft12/ControlField.h
  ${KDRIVE_KNX_INCLUDE}/telegrams/ft12/FixedLengthFrame.h
  ${KDRIVE_KNX_INCLUDE}/telegrams/ft12/FT12.h
  ${KDRIVE_KNX_INCLUDE}/telegrams/ft12/VariableLengthFrame.h
)

set (KDRIVE_KNX_SOURCE_FILES_TELEGRAMS_FT12
  ${KDRIVE_KNX_SRC}/telegrams/ft12/AckFrame.cpp
  ${KDRIVE_KNX_SRC}/telegrams/ft12/ControlField.cpp
  ${KDRIVE_KNX_SRC}/telegrams/ft12/FixedLengthFrame.cpp
  ${KDRIVE_KNX_SRC}/telegrams/ft12/VariableLengthFrame.cpp
)

source_group("knx\\telegrams\\ft12" FILES ${KDRIVE_KNX_HEADER_FILES_TELEGRAMS_FT12})
source_group("knx\\telegrams\\ft12" FILES ${KDRIVE_KNX_SOURCE_FILES_TELEGRAMS_FT12})

# knx files (all)

LIST(APPEND KDRIVE_KNX_HEADER_FILES 
  ${KDRIVE_KNX_HEADER_FILES_TOP}
  ${KDRIVE_KNX_HEADER_FILES_CORE}
  ${KDRIVE_KNX_HEADER_FILES_DATAPOINT}
  ${KDRIVE_KNX_HEADER_FILES_DEFINES}
  ${KDRIVE_KNX_HEADER_FILES_TELEGRAMS}
  ${KDRIVE_KNX_HEADER_FILES_TELEGRAMS_FORMATTERS}
  ${KDRIVE_KNX_HEADER_FILES_TELEGRAMS_FT12}
)

LIST(APPEND KDRIVE_KNX_SOURCE_FILES 
  ${KDRIVE_KNX_SOURCE_FILES_TOP}
  ${KDRIVE_KNX_SOURCE_FILES_CORE}
  ${KDRIVE_KNX_SOURCE_FILES_DATAPOINT}
  ${KDRIVE_KNX_SOURCE_FILES_DEFINES}
  ${KDRIVE_KNX_SOURCE_FILES_TELEGRAMS}
  ${KDRIVE_KNX_SOURCE_FILES_TELEGRAMS_FORMATTERS}
  ${KDRIVE_KNX_SOURCE_FILES_TELEGRAMS_FT12}
)

# ---------- kdrive component: utility

set(KDRIVE_UTILITY_INCLUDE "${KDRIVE_INCLUDE}/kdrive/utility")
set(KDRIVE_UTILITY_SRC "${KDRIVE_SRC}/utility")

set (KDRIVE_UTILITY_HEADER_FILES
  ${KDRIVE_UTILITY_INCLUDE}/Config.h
  ${KDRIVE_UTILITY_INCLUDE}/Forwards.h
  ${KDRIVE_UTILITY_INCLUDE}/Headers.h
  ${KDRIVE_UTILITY_INCLUDE}/Logger.h
  ${KDRIVE_UTILITY_INCLUDE}/LoggerFormatter.h
  ${KDRIVE_UTILITY_INCLUDE}/PropertyCollection.h
  ${KDRIVE_UTILITY_INCLUDE}/ScopedSemaphore.h
)

set (KDRIVE_UTILITY_SOURCE_FILES
  ${KDRIVE_UTILITY_SRC}/LoggerFormatter.cpp
  ${KDRIVE_UTILITY_SRC}/PropertyCollection.cpp
  ${KDRIVE_UTILITY_SRC}/ScopedSemaphore.cpp
)

source_group("utility" FILES ${KDRIVE_UTILITY_HEADER_FILES})
source_group("utility" FILES ${KDRIVE_UTILITY_SOURCE_FILES})

# ---------- kdrive (all)

LIST(APPEND KDRIVE_HEADER_FILES 
  ${KDRIVE_CONNECTOR_HEADER_FILES}
  ${KDRIVE_BAOS_HEADER_FILES}
  ${KDRIVE_FT12_HEADER_FILES}
  ${KDRIVE_IO_SERIAL_HEADER_FILES}
  ${KDRIVE_KNX_HEADER_FILES}
  ${KDRIVE_UTILITY_HEADER_FILES}
)

LIST(APPEND KDRIVE_SOURCE_FILES 
  ${KDRIVE_CONNECTOR_SOURCE_FILES}
  ${KDRIVE_BAOS_SOURCE_FILES}
  ${KDRIVE_FT12_SOURCE_FILES}
  ${KDRIVE_IO_SERIAL_SOURCE_FILES}
  ${KDRIVE_KNX_SOURCE_FILES}
  ${KDRIVE_UTILITY_SOURCE_FILES}
)

# ---------- PRECOMPILED HEADERS

enable_precompiled_headers("${KDRIVE_SRC}/pch/kdrive_pch.h" KDRIVE_SOURCE_FILES)
include_directories("${KDRIVE_SRC}")

# ---------- TARGET

add_definitions(-Dkdrive_EXPORTS)

add_library(${KDRIVE_LIBRARY_NAME} ${WZSDK_LINKMODE}
  ${KDRIVE_HEADER_FILES}
  ${KDRIVE_SOURCE_FILES}
)

# kdrive need Poco Foundation and Poco Net
add_dependencies(${KDRIVE_LIBRARY_NAME} Net Foundation)
target_link_libraries(${KDRIVE_LIBRARY_NAME} Net Foundation ${SYSTEM_LIBS})