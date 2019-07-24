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
#include "BaosDatapoint.h"
#include <kdrive/baos/BaosEvent.h>
#include <memory>

namespace unmanaged
{
typedef std::shared_ptr<kdrive::baos::BaosConnector> ConnectorPtr;
typedef kdrive::baos::BaosEvent BaosEvent;
typedef kdrive::baos::BaosDatapoint BaosDatapoint;
typedef kdrive::baos::ServerItem ServerItem;
typedef void (*BaosEventDatapointEvent)(BaosDatapoint&);
typedef void (*BaosEventBusConnectedEvent)(bool);
typedef void (*BaosEventConnectorClosedEvent)();
}

namespace kdrive
{
namespace baos
{
namespace bindings
{

/// <summary>
///	BAOS Events (datapoint modified, bus connected and connector closed)
/// </summary>
public ref class BaosEvent
{
public:
	/// <summary>
	///	Creates a BaosEvent
	///	Requires a connector.
	/// </summary>
	/// <remarks>
	///	Note: the callbacks occur in the context of the notification thread,
	///	and not in the main thread (or the GUI thread). If you are developing
	///	an application in C# for example that needs to update the GUI
	///	you should connect to the BaosEvent events and in your code re-raise 
	///	the event so it is in the main gui thread context. See Invoke for 
	///	more information. An example is implemented in the C# samples for the 
	///	PushButtonDemo:
	///
	///	<code>
	///
	///		void onDatapointEventInThreadContext(object sender, BaosDatapoint datapoint)
	///		{
	///			Invoke(new BaosEvent.DatapointEventHandler(onDatapointEvent), new object[] { sender, datapoint });
	///		}
	///
	///	</code>
	/// </remarks>
	BaosEvent(Connector^ connector)

		: connector_(connector)
	{
		try
		{
			// we use an internal delegate as a callback function from the unmanaged code
			// the following code does the interop marshalling

			System::IntPtr ptr;

			baosEvent_ = new unmanaged::BaosEvent(connector->getUnmanaged(), false);

			// datapoint event
			datapointEventDelegate_ = gcnew DatapointEventDelegate(this, &BaosEvent::onDatapointEvent);
			ptr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(datapointEventDelegate_);
			baosEvent_->setDatapointEvent(static_cast<unmanaged::BaosEventDatapointEvent>(ptr.ToPointer()));

			// bus connected event
			busConnectedEventDelegate_ = gcnew BusConnectedEventDelegate(this, &BaosEvent::onBusConnectedEvent);
			ptr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(busConnectedEventDelegate_);
			baosEvent_->setBusConnectedEvent(static_cast<unmanaged::BaosEventBusConnectedEvent>(ptr.ToPointer()));

			// connector closed event
			connectorClosedEventDelegate_ = gcnew ConnectorClosedEventDelegate(this, &BaosEvent::onConnectorClosedEvent);
			ptr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(connectorClosedEventDelegate_);
			baosEvent_->setConnectorClosedEvent(static_cast<unmanaged::BaosEventConnectorClosedEvent>(ptr.ToPointer()));
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Destroys the BaosEvent.
	///	Destructor cleans up unmanaged and managed resources.
	/// </summary>
	~BaosEvent()
	{
		// call finalizer to release unmanaged resources
		this->!BaosEvent();
	}

	/// <summary>
	///	Enables (starts) the event callback notifications
	/// </summary>
	void enable()
	{
		try
		{
			baosEvent_->enable();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Disables (stops) the event callback notifications
	/// </summary>
	void disable()
	{
		try
		{
			baosEvent_->disable();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

public:
	/// <summary>
	///	The callback is handled using the event system
	/// </summary>
	delegate void DatapointEventHandler(Object^ sender, BaosDatapoint^ datapoint);
	event DatapointEventHandler^ DatapointEvent;

	/// <summary>
	///	Callback function called when a server value indication is
	///	received to indicate whether the bus is connected or not
	/// </summary>
	delegate void BusConnectedEventHandler(Object^ sender, bool connected);
	event BusConnectedEventHandler^ BusConnectedEvent;

	/// <summary>
	///	Callback function called when the connector is disconnected
	/// </summary>
	delegate void ConnectorClosedEventHandler(Object^ sender);
	event ConnectorClosedEventHandler^ ConnectorClosedEvent;

protected:
	/// <summary>
	///	Finalizer (non-deterministic destructor) 
	///	cleans up unmanaged resources.
	/// </summary>
	!BaosEvent()
	{
		try
		{
			if (baosEvent_)
			{
				baosEvent_->disable();
				delete baosEvent_;
				baosEvent_ = 0;
			}
		}
		catch (...)
		{
		}
	}

private:
	void onDatapointEvent(unmanaged::BaosDatapoint& baosDatapoint)
	{
		try
		{
			const unmanaged::ServerItem& serverItem = baosDatapoint.getServerItem();
			array<unsigned char>^ data = interop::ArrayCreator::Copy(&serverItem.data[0], serverItem.data.size());
			BaosDatapoint^ d = gcnew BaosDatapoint(connector_, serverItem.id, serverItem.serviceData, data);
			DatapointEvent(this, d);
		}
		catch (...)
		{
		}
	}

	void onBusConnectedEvent(bool connected)
	{
		try
		{
			BusConnectedEvent(this, connected);
		}
		catch (...)
		{
		}
	}

	void onConnectorClosedEvent()
	{
		try
		{
			ConnectorClosedEvent(this);
		}
		catch (...)
		{
		}
	}

private:
	delegate void DatapointEventDelegate(unmanaged::BaosDatapoint& datapoint);
	delegate void BusConnectedEventDelegate(bool connected);
	delegate void ConnectorClosedEventDelegate();

	Connector^ connector_;
	unmanaged::BaosEvent* baosEvent_;
	DatapointEventDelegate^ datapointEventDelegate_;
	BusConnectedEventDelegate^ busConnectedEventDelegate_;
	ConnectorClosedEventDelegate^ connectorClosedEventDelegate_;
};

}
}
} // end namespace kdrive::baos::bindings
