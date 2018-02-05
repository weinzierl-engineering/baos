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

#ifndef __KDRIVE_BAOS_H__
#define __KDRIVE_BAOS_H__

/*!
	\mainpage

	\section Introduction

	This header includes all the top level BAOS interpretation classes.
	and form the main BAOS API

	The kdrive BAOS client library is a C++ implementation of the
	KnxBAOS Protocol Versions 1.2 and 2.0. A managed C++ .NET wrapper is also
	implemented to enable application development with C# or Visual Basic .NET.
	The class library aligns itself with the KnxBAOS protocol, and for each
	protocol message type a corresponding class is available to send/receive the message data.
	In addition several convenience classes are provided to interpret the information,
	such as a Datapoint class for converting the raw byte stream into a specific parameter type.

	For information on the BAOS device, see:
	http://www.weinzierl.de/en/products/770.html
	http://www.weinzierl.de/en/products/771.html
	http://www.weinzierl.de/en/products/772.html

	\section Tutorial

	This section presents several simple tutorials.
	For more information please refer to the kdrive BAOS samples.

	\subsection set_dpt Set a Datapoint Value

	\code

		ScopedBaosConnection connection(ipAddress);
		Connector::Ptr connector = connection.getConnector();
		BaosDatapoint d(connector, 1);
		d.setBoolean(enabled);

	\endcode

	First we instantiate a ScopedBaosConnection. This class is responsible
	for creating a TCP/IP Stream Connector which automatically connects to the BAOS device.
	When the ScopedBaosConnection goes out of scope it automatically closes the
	connection (i.e. RAII). The second line gets the abstract Connector from the
	ScopedBaosConnection. This connector is used in the library to abstract away physical
	communication details. We create a BaosDatapoint class and provide it with the connector
	and the datapoint id, in this case 1 indicating the first id. Finally we set the boolean value.
	Note, there are a number of formatting functions available to set datapoint values.

	\subsection set_dpt Datapoint Indications

	\code

		ScopedBaosConnection connection(ipAddress);
		BaosConnector::Ptr connector = connection.getConnector();
		BaosEvent baosEvent(connector);
		baosEvent.setDatapointEvent(onDatapointIndication);

		...

		void onDatapointIndication(BaosDatapoint& datapoint)
		{
			... do something with the indication
		}

	\endcode

	In this example we wait for an asynchronous datapoint value indication from
	the BAOS device using the BaosEvent class. Each Connector has a packet
	notification signal which passes Rx and Tx packets from the connector to
	(multiple) observers (in this case,	a packet is a BAOS protocol message).
	This notification mechanism includes all packets sent to and from the BAOS device
	however we need to filter these packets	when we are only interested in the
	asynchronous datapoint indication messages. This is what happens in BaosEvent.
	When an indication arrives, it is forwarded to the callback function. Note:
	all GetDatapointValue responses are also treated as indications, so on startup
	you can simply request the datapoint values for all objects that you are interested
	in and handle the responses with the standard indication handler.

	\subsection dp_desc Read datapoint descriptions

	\code

		ScopedBaosConnection connection(ipAddress);
		BaosConnector::Ptr connector = connection.getConnector();

		// reads all configured (enabled) datapoint descriptions from the device
		BaosDatapointDescriptions baosDatapointDescriptions(connector);
		baosDatapointDescriptions.readFromDevice();

		// trace the descriptions
		const BaosDatapointDescriptions::Descriptions descriptions = baosDatapointDescriptions.getDescriptions();
		for (const auto& item, descriptions)
		{
			poco_information(LOGGER(), "");
			const BaosDatapointDescription& desc = item.second;
			poco_information_f1(LOGGER(), "Datapoint id: %d", static_cast<int>(desc.getId()));
			poco_information_f1(LOGGER(), "Datapoint type: %d", static_cast<int>(desc.getDatapointType()));

			// reads the datapoint string
			BaosDatapoint datapoint(connector, desc.getId());
			poco_information_f1(LOGGER(), "Description string: %s", datapoint.getDescriptionString());
		}


	\endcode

	In this example we reads all (in the ETS) enabled datapoint descriptions.

	\example BaosEventListener.cpp
	\example BaosDatapointDescription.cpp
	\example BaosEnumerator.cpp
	\example BaosIndicationListener.cpp
	\example BaosLightSwitcher.cpp
	\example BaosMultiConnector.cpp
	\example BaosMultiThreaded.cpp
	\example BaosSerial.cpp
*/

#include "kdrive/baos/Headers.h"

#endif // __KDRIVE_BAOS_H__
