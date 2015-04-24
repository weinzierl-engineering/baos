'
' Copyright (c) 2002-2014 WEINZIERL ENGINEERING GmbH
' All rights reserved.
'
' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
' FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
' SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, 
' WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
' WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE 
' 

Imports kdrive.baos.bindings

Module Module1

    Sub Main()

        Try
            ' enable the logger, writes to the console
            kdrive.Logger.SetConsoleChannel()

            Using baosConnection As New BaosConnection()
                ' create a TPC/IP connection with the remote BAOS device
                baosConnection.connectIpByName("Baos-Sample")
                Dim connector As New Connector(baosConnection)

                ' turn light on, sleep, turn light off
                switchLight(connector, True)
                waitTimeout(connector)
                switchLight(connector, False)

                baosConnection.disconnect()
            End Using

        Catch ex As Exception
            Console.WriteLine(ex.Message)
        Finally
            ' release the logging resources
            kdrive.Logger.Shutdown()
        End Try

    End Sub

    Sub switchLight(ByRef connector As Connector, ByVal enabled As Boolean)

        Dim d As New BaosDatapoint(connector, 1)

        If (d.getBoolean() <> enabled) Then
            Dim description As String = d.getDescription()
            Dim action As String = If(enabled, "on", "off")
            Console.WriteLine("Switching {0} : {1}", description, action)

            d.setBoolean(enabled)
        End If

    End Sub

    Sub waitTimeout(ByRef connector As Connector)

        Dim timeout As Integer
        timeout = BaosParameter.readParameter(connector, 1)
        System.Threading.Thread.Sleep(timeout)

    End Sub

End Module
