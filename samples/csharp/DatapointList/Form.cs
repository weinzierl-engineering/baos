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

namespace DatapointList
{
    public partial class Form1 : Form
    {
        /// <summary>
		/// Constructor
		/// Here we initialize the components and start the kdrive logger.
        /// </summary>
        public Form1()
        {
            InitializeComponent();
            FormClosing += new FormClosingEventHandler(Form1_FormClosing);

			// init data grid view
			dataGridView.Columns.Add("ColumnId", "ID");
			dataGridView.Columns.Add("ColumnDescription", "Description");
			dataGridView.Columns.Add("ColumnSize", "Size"); 
			dataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
			dataGridView.Columns["ColumnDescription"].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
			
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
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                kdrive.Logger.Shutdown();
            }
            catch (kdrive.KdriveException exception)
            {
                MessageBox.Show(exception.Message, "Exception",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }            
        }

        /// <summary>
		/// Event handler for click buttonRead
		/// First we create a connection to the device
		/// with the Name or IP in the textbox. Is that device not available, we see
		/// an error message in the messagebox. Otherwise we create the connection and read
		/// out the datapoints properties
        /// </summary>
        private void buttonRead_Click(object sender, EventArgs e)
        {
			// clear old data from the data grid
			dataGridView.Rows.Clear();

			if (editConnection.Text == "")
			{
				MessageBox.Show("Please insert a valid IP-Address or Name");
				return;
			}

			try
			{
                BaosConnection baosConnection = new BaosConnection();
                using (baosConnection)
				{
					if (radioByIP.Checked)
					{
						// create a TPC/IP connection with the remote BAOS device by IPv4 address
                        baosConnection.connectIp(editConnection.Text, true);
					}
					else
					{
						//Connecting with the device which has this Name
                        baosConnection.connectIpByName(editConnection.Text, true);
					}

                    Connector connector = new Connector(baosConnection);

					//Reading the datapoints
					readDatapointDescriptions(connector);

                    baosConnection.disconnect();
				}
			}
			catch (kdrive.KdriveException exception)
			{
				MessageBox.Show(exception.Message, "Exception",
					MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
			}
        }

        /// <summary>
		/// Here we read out the datapoints and add the description to the dataGridView
        /// </summary>
        public void readDatapointDescriptions(Connector connector)
        {
			try
			{
				// change mouse cursor to busy
				this.Cursor = Cursors.WaitCursor;

				// get datapoint description
				BaosDatapointDescriptions baosDatapointDescriptions = new BaosDatapointDescriptions(connector);
				baosDatapointDescriptions.readFromDevice();
				List<BaosDatapointDescription> descriptions = baosDatapointDescriptions.getDescriptions();

				foreach (BaosDatapointDescription desc in descriptions)
				{
					BaosDatapoint datapoint = new BaosDatapoint(connector, desc.getId());

					String size = desc.isBitType() ? string.Format("{0} Bits", desc.getValueTypeSizeBits()) :
						string.Format("{0} Bytes", desc.getValueTypeSizeBytes());
					dataGridView.Rows.Add(datapoint.getId(), datapoint.getDescription(), size);
				}
			}
			catch (kdrive.KdriveException exception)
			{
				MessageBox.Show(exception.Message, "Exception",
					MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
			}
			finally
			{
				// reset mouse cursor
				this.Cursor = Cursors.Default;
			}
        }

        /// <summary>
		/// Set the default text (IP address) in the textbox when the IP radio button is checked
        /// </summary>
        private void radioByIP_CheckedChanged(object sender, EventArgs e)
        {
            //Default IP at the textbox
            editConnection.Text = "192.168.1.1";
        }

        /// <summary>
		/// Set the default text (Device name) in the textbox when the Name radio button is checked
        /// </summary>
        private void radioByName_CheckedChanged(object sender, EventArgs e)
        {
            //Default Name at the textbox
			editConnection.Text = "Baos-Sample";
        }

        private void dataGridView_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
