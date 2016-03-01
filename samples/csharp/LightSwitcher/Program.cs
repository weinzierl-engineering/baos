// 
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
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

namespace LightSwitcher
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
                    baosConnection.connectIpByName("Baos-Sample", true);
                    Connector connector = new Connector(baosConnection);

					// turn light on, sleep, turn light off
					switchLight(connector, true);
					waitTimeout(connector);
					switchLight(connector, false);

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

        static void switchLight(Connector connector, bool enabled)
        {
            BaosDatapoint d = new BaosDatapoint(connector, 1);

            if (d.getBoolean() != enabled)
            {
                string description = d.getDescription();
                string action = enabled ? "on" : "off";

                Console.WriteLine("Switching {0} : {1}", description, action);
                d.setBoolean(enabled);
            }
        }

        static void waitTimeout(Connector connector)
        {
            int timeout = BaosParameter.readParameter(connector, 1);
            System.Threading.Thread.Sleep(timeout);
        }
    }
}
