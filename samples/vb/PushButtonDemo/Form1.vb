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

Public Class Form1

    ' The BaosConnection implements a TCP/IP connection 
    ' with the BAOS device
    Dim baosConnection As BaosConnection

    ' The connector is created by the BaosConnection and is used
    ' in all BAOS functions that require communication with the device
    ' In this way we can create other Connectors that communicate via
    ' KnxNetIP (UDP/IP) or FTP1.2 (Serial) for example
    ' Currently only a TCP/IP and FTP1.2 (Serial) connector exists
    Dim connector As Connector

    ' When a datapoint indication or a get datapoint value response 
    ' arrives from the BAOS device an event is raised. 
    ' This is handled by the BaosEvent class. 
    Dim baosEvent As BaosEvent

    ' Here we define our Group Object numbers. These should correspond to
    ' the communication objects in the ETS Project for the BAOS device
    ' In this project we have 4 group objects:
    ' Channel 1 Request : 1 bit boolean, switches the light on
    ' Channel 2 Status Response : 1 bit boolean, status indication to 
    ' indicate the light has been switched
    ' And the same again for Channel 2
    Private Enum GroupObject As Integer
        Ch1Request = 1
        Ch1Status = 2
        Ch2Request = 3
        Ch2Status = 4
    End Enum

    Public Sub New()
        Try
            InitializeComponent()

            ' start the logger
            kdrive.Logger.SetConsoleChannel()
        Catch ex As kdrive.KdriveException
            Console.WriteLine(ex.Message)
        End Try
    End Sub

    ' Here we create our connection with the BAOS device
    ' First we create the BaosConnection and connect to the remote device
    ' Connect takes the name BAOS device (which performs an enumeration 
    ' to find the associated IP address).
    ' Then we create the Connector from the BaosConnection
    ' Finally we attach to the datapoint events. This calls our function
    ' onDatapointEvent when a datapoint indication or response is received
    Private Sub Form1_FormLoad(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Try
            ' create the connection
            baosConnection = New BaosConnection()
            baosConnection.connectIpByName("Baos-Sample")
            connector = New Connector(baosConnection)

            ' connect the events
            baosEvent = New BaosEvent(connector)
            AddHandler baosEvent.DatapointEvent, AddressOf OnDatapointEventInThreadContext
            baosEvent.enable()

            ' read the status of the two channels
            ' the response is handled by the event handler from BaosEvent
            Read(GroupObject.Ch1Status)
            Read(GroupObject.Ch2Status)
        Catch ex As kdrive.KdriveException
            Console.WriteLine(ex.Message)
        End Try
    End Sub

    Private Sub Form1_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        Try
            If (Not baosEvent Is Nothing) Then
                baosEvent.disable()
            End If

            If (Not baosConnection Is Nothing) Then
                baosConnection.disconnect()
            End If

            kdrive.Logger.Shutdown()

        Catch ex As kdrive.KdriveException
            Console.WriteLine(ex.Message)
        End Try
    End Sub

    ' This function will called from the event handler. It is in the context of the notification thread.
    ' It is not safe here to update the gui, so we must invoke to run it in the main thread
    Public Sub OnDatapointEventInThreadContext(ByVal sender As Object, ByVal datapoint As BaosDatapoint)
        Invoke(New BaosEvent.DatapointEventHandler(AddressOf OnDatapointEvent), New Object() {sender, datapoint})
    End Sub

    ' This function will called in the main thread
    ' The datapoint indication event handler
    ' We show that the light has been switched
    ' by changing the image associated with the indicated channel
    Public Sub OnDatapointEvent(ByVal sender As Object, ByVal datapoint As BaosDatapoint)
        Try
            Dim dpId As UShort = datapoint.getId()

            Select Case dpId
                Case GroupObject.Ch1Status, GroupObject.Ch2Status
                    SwitchLight(dpId, datapoint.getBoolean())
            End Select

        Catch ex As kdrive.KdriveException
            Console.WriteLine(ex.Message)
        End Try
    End Sub

    ' Event handler for Channel 1 On Button, we send a datapoint value request to the BAOS device
    Private Sub channel1On_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles channel1On.Click
        Send(GroupObject.Ch1Request, True)
    End Sub

    ' Event handler for Channel 1 Off Button, we send a datapoint value request to the BAOS device
    Private Sub channel1Off_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles channel1Off.Click
        Send(GroupObject.Ch1Request, False)
    End Sub

    ' Event handler for Channel 2 On Button, we send a datapoint value request to the BAOS device
    Private Sub channel2On_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles channel2On.Click
        Send(GroupObject.Ch2Request, True)
    End Sub

    ' Event handler for Channel 2 Off Button, we send a datapoint value request to the BAOS device
    Private Sub channel2Off_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles channel2Off.Click
        Send(GroupObject.Ch2Request, False)
    End Sub

    ' Sends the datapoint value write request to the BAOS device
    ' Our datapoint is a 1 bit boolean value, so we use the setBoolean function
    ' There are several other encoding functions available, please refer to the
    ' documentation
    Private Sub Send(ByVal groupObject As GroupObject, ByVal enabled As Boolean)
        Dim d As New BaosDatapoint(connector, groupObject)
        d.setBoolean(enabled)
    End Sub

    ' Reads the datapoint value from the BAOS device
    ' The response is returned via the BaosEvent event indication
    ' so we don't have to handle it here (i.e. same code as indication
    ' we just show the status of the light)
    Private Sub Read(ByVal groupObject As GroupObject)
        Try
            If (Not connector Is Nothing) Then
                Dim d As New BaosDatapoint(connector, groupObject)
                d.getData()
            End If
        Catch ex As kdrive.KdriveException
            Console.WriteLine(ex.Message)
        End Try
    End Sub

    ' Switch Light changes the bitmap image in the GUI depending on the
    ' group object value and whether it is enabled
    Private Sub SwitchLight(ByVal ind As Integer, ByVal enabled As Boolean)

        Dim box As PictureBox
        Dim image As Bitmap

        If (ind = GroupObject.Ch1Status Or ind = GroupObject.Ch2Status) Then

            If (ind = GroupObject.Ch1Status) Then
                box = Me.lightBulb1
            Else
                box = Me.lightBulb2
            End If

            If (enabled = True) Then
                image = Global.PushButtonDemo.My.Resources.Resources.lightbulb
            Else
                image = Global.PushButtonDemo.My.Resources.Resources.lightbulb_off
            End If

            switchImage(box, image)

        End If

    End Sub

    ' Changes the image
    Private Sub SwitchImage(ByRef box As PictureBox, ByRef image As Bitmap)
        box.Image = image
    End Sub

End Class
