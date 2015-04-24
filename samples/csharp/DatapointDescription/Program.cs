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

using System;
using System.Collections.Generic;
using System.Text;
using kdrive.baos.bindings;

namespace DatapointDescription
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                // enable the logger, writes to the console
                kdrive.Logger.SetConsoleChannel();

                BaosConnection baosConnection = new BaosConnection();
                using (baosConnection)
				{
					// create a TPC/IP connection with the remote BAOS device
                    baosConnection.connectIpByName("Baos-Sample");
                    Connector connector = new Connector(baosConnection);

					readDatapointDescriptions(connector);

                    baosConnection.disconnect();
				}
            }
            catch (kdrive.KdriveException exception)
            {
                Console.WriteLine(exception.Message);
            }
            finally
            {
                // release the logging resources
                kdrive.Logger.Shutdown();
            }
        }

        static void readDatapointDescriptions(Connector connector)
        {
            try
            {
                BaosDatapointDescriptions baosDatapointDescriptions = new BaosDatapointDescriptions(connector);
                baosDatapointDescriptions.readFromDevice();
                List<BaosDatapointDescription> descriptions = baosDatapointDescriptions.getDescriptions();

                Console.WriteLine("{0} items found", descriptions.Count);

                foreach (BaosDatapointDescription desc in descriptions)
                {
                    String size = desc.isBitType() ? string.Format("{0} Bits", desc.getValueTypeSizeBits()) :
                        string.Format("{0} Bytes", desc.getValueTypeSizeBytes());

                    Console.WriteLine("");
                    Console.WriteLine("Datapoint id {0}", desc.getId());
                    Console.WriteLine("Datapoint type: {0}, Size: {1}", desc.getDatapointType(), size);
                }
            }
            catch (kdrive.KdriveException exception)
            {
                Console.WriteLine(exception.Message);
            }
        }
    }
}
