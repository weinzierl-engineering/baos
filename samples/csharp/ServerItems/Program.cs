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

using System;
using System.Collections.Generic;
using System.Text;
using kdrive.baos.bindings;

namespace ServerItems
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

					readServerItems(connector);

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

        static void readServerItems(Connector connector)
        {
            BaosServerItems baosServerItems = new BaosServerItems(connector);
            Console.WriteLine("Hardware Type: {0}", ByteArrayAsString(baosServerItems.getHardwareType()));
            Console.WriteLine("Hardware Version: 0x{0:X2}", baosServerItems.getHardwareVersion());
            Console.WriteLine("Firmware Version: 0x{0:X2}", baosServerItems.getFirmwareVersion());
            Console.WriteLine("Manufacture Code Device: {0}", baosServerItems.getManufactureCodeDevice());
            Console.WriteLine("Manufacture Code App: {0}", baosServerItems.getManufactureCodeApp());
            Console.WriteLine("Application Id: {0}", baosServerItems.getApplicationId());
            Console.WriteLine("Application Version: 0x{0:X2}", baosServerItems.getApplicationVersion());
            Console.WriteLine("Serial Number: {0}", ByteArrayAsString(baosServerItems.getSerialNumber()));
            Console.WriteLine("Time Since Reset: {0}", baosServerItems.getTimeSinceReset());
            Console.WriteLine("Bus Connected: {0}", baosServerItems.isBusConnected());
            Console.WriteLine("Max Buffer Size: {0}", baosServerItems.getMaxBufferSize());
            Console.WriteLine("Buffer Size: {0}", baosServerItems.getBufferSize());
            Console.WriteLine("Length of Description String: {0}", baosServerItems.getLengthOfDescriptionString());
            Console.WriteLine("Programming Mode: {0}", baosServerItems.getProgrammingMode());
        }

        static string ByteArrayAsString(byte[] byteArray)
        {
            if (byteArray == null || byteArray.Length == 0)
                return "";

            StringBuilder builder = new StringBuilder(byteArray.Length * 5 + 2);
            for (int byteIndex = 0; byteIndex < byteArray.Length; byteIndex++)
            {
                if (byteIndex != 0)
                {
                    builder.Append(' ');
                }
                builder.AppendFormat("{0:X2}", byteArray[byteIndex]);
            }
            return builder.ToString();
        }
    }
}


