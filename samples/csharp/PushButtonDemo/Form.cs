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

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using kdrive.baos.bindings;

namespace PushButtonDemo
{
    public partial class PushButtonDemo : Form
    {
        /// <summary>
        /// The BaosConnection implements a TCP/IP connection 
        /// with the BAOS device
        /// </summary>
        BaosConnection baosConnection;

        /// <summary>
        /// The connector is created by the BaosConnection and is used
        /// in all BAOS functions that require communication with the device
        /// In this way we can create other Connectors that communicate via
        /// KnxNetIP (UDP/IP) or FTP1.2 (Serial) for example
        /// Currently only a TCP/IP and FTP1.2 (Serial) connector exists
        /// </summary>
        Connector connector;

        /// <summary>
        /// When a datapoint indication or a get datapoint value response 
        /// arrives from the BAOS device an event is raised. 
        /// This is handled by the BaosEvent class. 
        /// </summary>
        BaosEvent baosEvent;

        /// <summary>
        /// Here we define our Group Object numbers. These should correspond to
        /// the communication objects in the ETS Project for the BAOS device
        /// In this project we have 5 group objects:
        /// - Channel 1 Request : 1 bit boolean, switches the light on
        /// - Channel 1 Status Response : 1 bit boolean, status indication to 
        ///   indicate the light has been switched
        /// - And the same again for Channel 2
		/// - Channel 3 Temperature Status Response : 2 byte float
        /// </summary>
        enum GroupObject { Ch1Request = 1, Ch1Status, Ch2Request, Ch2Status, Ch3Temperature };

        /// <summary>
		/// Constructor
		/// Here we initialize the component and start the kdrive logger.
        /// </summary>
		public PushButtonDemo()
        {
            InitializeComponent();
			FormClosing += new FormClosingEventHandler(PushButtonDemo_FormClosing);

			try
			{
				// start the logger
				kdrive.Logger.SetConsoleChannel();
			}
			catch (kdrive.KdriveException exception)
			{
				MessageBox.Show(exception.Message, "Exception",
					MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
			} 
        }

        /// <summary>
        /// Release the resources
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		private void PushButtonDemo_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
				// disconnect the connection (if connected) to the bas device
				disconnectBaos();

                kdrive.Logger.Shutdown();
            }
            catch (kdrive.KdriveException exception)
            {
                MessageBox.Show(exception.Message, "Exception",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }            
        }

		/// <summary>
		/// Here we create our connection with the BAOS device
		/// First we create the StreamConnection and connect to the remote device
		/// Connect takes the name or the IP address of the BAOS device 
		/// (which performs an enumeration to find the associated IP address and protocol).
		/// Then we create the Connector from the Stream Connection and start the keep-alive thread.
		/// Finally we attach to the datapoint events. This calls our function
		/// onDatapointEvent when a datapoint indication or response is received
		/// </summary>
		private void buttonConnect_Click(object sender, EventArgs e)
		{
			if (editConnection.Text == "")
			{
				MessageBox.Show("Please insert a valid IP-Address or Name");
				return;
			}

			try
			{
				// create the connection
				baosConnection = new BaosConnection();
				if (radioByIP.Checked)
				{
					// connect to the device by IPv4 address
                    baosConnection.connectIp(editConnection.Text, true);
				}
				else
				{
					// connect to the device by device friendly name
                    baosConnection.connectIpByName(editConnection.Text, true);
				}
                connector = new Connector(baosConnection);

				// connect the events
				baosEvent = new BaosEvent(connector);
				baosEvent.DatapointEvent += new BaosEvent.DatapointEventHandler(onDatapointEventInThreadContext);
				baosEvent.enable();

				// read the status of all datapoints
				readDatapoints();

				// enable and disable controls
				buttonConnect.Enabled = false;
				buttonDisconnect.Enabled = true;
				groupBoxVisualisation.Enabled = true;
				radioByName.Enabled = false;
				radioByIP.Enabled = false;
				editConnection.Enabled = false;
			}
			catch (kdrive.KdriveException exception)
			{
				MessageBox.Show(exception.Message, "Exception",
				MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
			}
		}

		/// <summary>
		/// Release the resources and disconnect
		/// </summary>
		private void buttonDisconnect_Click(object sender, EventArgs e)
		{
			// enable and disable controls
			buttonConnect.Enabled = true;
			buttonDisconnect.Enabled = false;
			groupBoxVisualisation.Enabled = false;
			radioByName.Enabled = true;
			radioByIP.Enabled = true;
			editConnection.Enabled = true;

			// disconnect the connection to the bas device
			disconnectBaos();
		}

        /// <summary>
        /// Event handler for Channel 1 On Button
        /// we send a datapoint value request to the BAOS device
        /// </summary>
        private void channel1On_Click(object sender, EventArgs e)
        {
            sendBoolean((ushort)GroupObject.Ch1Request, true);
        }

        /// <summary>
        /// Event handler for Channel 1 Off Button
        /// we send a datapoint value request to the BAOS device
        /// </summary>
        private void channel1Off_Click(object sender, EventArgs e)
        {
            sendBoolean((ushort)GroupObject.Ch1Request, false);
        }

        /// <summary>
        /// Event handler for Channel 2 On Button
        /// we send a datapoint value request to the BAOS device
        /// </summary>
        private void channel2On_Click(object sender, EventArgs e)
        {
            sendBoolean((byte)GroupObject.Ch2Request, true);
        }

        /// <summary>
        /// Event handler for Channel 2 Off Button
        /// we send a datapoint value request to the BAOS device
        /// </summary>
        private void channel2Off_Click(object sender, EventArgs e)
        {
            sendBoolean((byte)GroupObject.Ch2Request, false);
        }

        /// <summary>
		/// Event handler for Channel 3 Read Temperature Button
		/// we sends a datapoint value read to the BAOS device
        /// The response is returned via the BaosEvent event indication
        /// so we don't have to handle it here
	    /// </summary>
		private void buttonReadTemperature_Click(object sender, EventArgs e)
        {
            if (!readFloat((byte)GroupObject.Ch3Temperature))
            {
                MessageBox.Show("Unable to read value from Baos", "Exception", 
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }


		/// <summary>
		/// This function will called from the event handler. It is in the context of the notification thread.
		/// It is not safe here to update the gui, so we must invoke to run it in the main thread
		/// </summary>
		private void onDatapointEventInThreadContext(object sender, BaosDatapoint datapoint)
		{
			Invoke(new BaosEvent.DatapointEventHandler(onDatapointEvent), new object[] { sender, datapoint });
		}

		/// <summary>
		/// This function will called in the main thread
		/// The datapoint indication event handler
		/// We show that the light has been switched
		/// by changing the image associated with the indicated channel
		/// </summary>
		private void onDatapointEvent(object sender, BaosDatapoint datapoint)
		{
			try
			{
				ushort dpId = datapoint.getId();
				switch (dpId)
				{
					case (ushort)GroupObject.Ch1Status:
					case (ushort)GroupObject.Ch2Status:
						switchLight(dpId, datapoint.getBoolean());
						break;
					case (ushort)GroupObject.Ch3Temperature:
						updateFloat(dpId, datapoint.get2OctetFloat());
						break;
				}

			}
			catch (kdrive.KdriveException exception)
			{
				MessageBox.Show(exception.Message, "Exception",
					MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
			}
		}

		/// <summary>
		/// Release the resources and disconnect
		/// </summary>
		private void disconnectBaos()
		{
			try
			{
				if (baosEvent != null)
				{
					baosEvent.disable();
				}

				if (baosConnection != null)
				{
                    baosConnection.disconnect();
                    baosConnection.Dispose();
				}
			}
			catch (kdrive.KdriveException exception)
			{
				MessageBox.Show(exception.Message, "Exception",
					MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
			}
		}

        /// <summary>
        /// We read the value of the status datapoints to update the light images
        /// and the float value.
        /// 
        /// i.e. on startup we have to read to ensure we show the correct
        /// status of the bus. otherwise we could show that the light is off when it
        /// is on. Note: the response is handled by the event handler from BaosEvent,
        ///  so we don't have to do anything here...
        /// 
        /// This function also handles checking that the Baos has been property configured 
        /// for this application.
        /// </summary>
        private void readDatapoints()
        {
            bool success = true;

	        success = readBoolean((byte)GroupObject.Ch1Request);
	        success = readBoolean((byte)GroupObject.Ch1Status) && success;
	        success = readBoolean((byte)GroupObject.Ch2Request) && success;
	        success = readBoolean((byte)GroupObject.Ch2Status) && success;
	        success = readFloat((byte)GroupObject.Ch3Temperature) && success;

	        if (!success)
	        {
                MessageBox.Show("Unable to read all datapoints.\n" +
			        "This app may not function correctly!\n" +
			        "Please check the Baos ETS configuration", "Warning", 
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
	        }
        }

        /// <summary>
        /// Sends the datapoint value write request to the BAOS device
        /// Our datapoint is a 1 bit boolean value, so we use the setBoolean function
        /// There are several other encoding functions available, please refer to the
        /// documentation
        /// </summary>
        private void sendBoolean(ushort id, bool enabled)
        {
            try
            {
                if (connector != null)
                {
                    BaosDatapoint datapoint = new BaosDatapoint(connector, id);
                    datapoint.setBoolean(enabled);
                }
            }
            catch (kdrive.KdriveException exception)
            {
                MessageBox.Show(exception.Message, "Exception",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        /// <summary>
        /// Reads the datapoint value from the BAOS device
        /// The response is returned via the BaosEvent event indication
        /// so we don't have to handle it here (i.e. same code as indication
        /// we just show the status of the light)
        /// </summary>
        bool readBoolean(ushort id)
        {
            bool success = false;

            try
            {
                if (connector != null)
                {
                    BaosDatapoint baosDatapoint = new BaosDatapoint(connector, id);
                    baosDatapoint.getBoolean();
                    success = true;
                }
            }
            catch (kdrive.KdriveException exception)
            {
                MessageBox.Show(exception.Message, "Exception",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

            return success;
        }

        /// <summary>
        /// Reads the datapoint value from the BAOS device
        /// The response is returned via the BaosEvent event indication
        /// so we don't have to handle it here
        /// </summary>
        bool readFloat(ushort id)
        {
            bool success = false;

            try
            {
                if (connector != null)
                {
                    BaosDatapoint baosDatapoint = new BaosDatapoint(connector, id);
                    baosDatapoint.get2OctetFloat();
                    success = true;
                }
            }
            catch (kdrive.KdriveException exception)
            {
                MessageBox.Show(exception.Message, "Exception",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

            return success;
        }

        /// <summary>
        /// Switch Light changes the bitmap image in the GUI depending on the
        /// group object value and whether it is enabled
        /// </summary>
        private void switchLight(ushort id, bool enabled)
        {
            bool isChannel1 = id == (ushort)GroupObject.Ch1Status;
            bool isChannel2 = id == (ushort)GroupObject.Ch2Status;

            if (isChannel1 || isChannel2)
            {
                PictureBox box = isChannel1 ? lightBulbChannel1 : lightBulbChannel2;

                Bitmap image = enabled ? global::PushButtonDemo.Properties.Resources.lightbulb :
                    global::PushButtonDemo.Properties.Resources.lightbulb_off;

                box.Image = image;
            }
        }

        /// <summary>
        /// Updates the displayed float value
        /// </summary>
        private void updateFloat(ushort id, float value)
        {
            if (id == (ushort)GroupObject.Ch3Temperature)
            {
                editTemperature.Text = value.ToString();
            }
        }

        /// <summary>
		/// Set the default text (IP address) in the textbox when the IP radio button is checked
        /// </summary>
        private void radioByIP_CheckedChanged(object sender, EventArgs e)
        {
            editConnection.Text = "192.168.1.1";
        }

        /// <summary>
		/// Set the default text (Device name) in the textbox when the Name radio button is checked
        /// </summary>
        private void radioByName_CheckedChanged(object sender, EventArgs e)
        {
			editConnection.Text = "Baos-Sample";
        }
    }
}
