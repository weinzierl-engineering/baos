<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.lightBulb1 = New System.Windows.Forms.PictureBox
        Me.channel1On = New System.Windows.Forms.Button
        Me.channel1Off = New System.Windows.Forms.Button
        Me.Panel1 = New System.Windows.Forms.Panel
        Me.Panel2 = New System.Windows.Forms.Panel
        Me.lightBulb2 = New System.Windows.Forms.PictureBox
        Me.channel2Off = New System.Windows.Forms.Button
        Me.channel2On = New System.Windows.Forms.Button
        Me.Label1 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        CType(Me.lightBulb1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.Panel1.SuspendLayout()
        Me.Panel2.SuspendLayout()
        CType(Me.lightBulb2, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'lightBulb1
        '
        Me.lightBulb1.Image = Global.PushButtonDemo.My.Resources.Resources.lightbulb_off
        Me.lightBulb1.Location = New System.Drawing.Point(17, 45)
        Me.lightBulb1.Name = "lightBulb1"
        Me.lightBulb1.Size = New System.Drawing.Size(68, 105)
        Me.lightBulb1.TabIndex = 0
        Me.lightBulb1.TabStop = False
        '
        'channel1On
        '
        Me.channel1On.Location = New System.Drawing.Point(106, 45)
        Me.channel1On.Name = "channel1On"
        Me.channel1On.Size = New System.Drawing.Size(75, 23)
        Me.channel1On.TabIndex = 1
        Me.channel1On.Text = "On"
        Me.channel1On.UseVisualStyleBackColor = True
        '
        'channel1Off
        '
        Me.channel1Off.Location = New System.Drawing.Point(106, 86)
        Me.channel1Off.Name = "channel1Off"
        Me.channel1Off.Size = New System.Drawing.Size(75, 23)
        Me.channel1Off.TabIndex = 2
        Me.channel1Off.Text = "Off"
        Me.channel1Off.UseVisualStyleBackColor = True
        '
        'Panel1
        '
        Me.Panel1.BackColor = System.Drawing.Color.White
        Me.Panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.Panel1.Controls.Add(Me.Label1)
        Me.Panel1.Controls.Add(Me.lightBulb1)
        Me.Panel1.Controls.Add(Me.channel1Off)
        Me.Panel1.Controls.Add(Me.channel1On)
        Me.Panel1.Location = New System.Drawing.Point(18, 12)
        Me.Panel1.Name = "Panel1"
        Me.Panel1.Size = New System.Drawing.Size(200, 184)
        Me.Panel1.TabIndex = 3
        '
        'Panel2
        '
        Me.Panel2.BackColor = System.Drawing.Color.White
        Me.Panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.Panel2.Controls.Add(Me.Label2)
        Me.Panel2.Controls.Add(Me.lightBulb2)
        Me.Panel2.Controls.Add(Me.channel2Off)
        Me.Panel2.Controls.Add(Me.channel2On)
        Me.Panel2.Location = New System.Drawing.Point(224, 12)
        Me.Panel2.Name = "Panel2"
        Me.Panel2.Size = New System.Drawing.Size(200, 184)
        Me.Panel2.TabIndex = 4
        '
        'lightBulb2
        '
        Me.lightBulb2.Image = Global.PushButtonDemo.My.Resources.Resources.lightbulb_off
        Me.lightBulb2.Location = New System.Drawing.Point(21, 45)
        Me.lightBulb2.Name = "lightBulb2"
        Me.lightBulb2.Size = New System.Drawing.Size(68, 105)
        Me.lightBulb2.TabIndex = 0
        Me.lightBulb2.TabStop = False
        '
        'channel2Off
        '
        Me.channel2Off.Location = New System.Drawing.Point(106, 86)
        Me.channel2Off.Name = "channel2Off"
        Me.channel2Off.Size = New System.Drawing.Size(75, 23)
        Me.channel2Off.TabIndex = 2
        Me.channel2Off.Text = "Off"
        Me.channel2Off.UseVisualStyleBackColor = True
        '
        'channel2On
        '
        Me.channel2On.Location = New System.Drawing.Point(106, 45)
        Me.channel2On.Name = "channel2On"
        Me.channel2On.Size = New System.Drawing.Size(75, 23)
        Me.channel2On.TabIndex = 1
        Me.channel2On.Text = "On"
        Me.channel2On.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(14, 17)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(64, 13)
        Me.Label1.TabIndex = 3
        Me.Label1.Text = "Channel 1"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.Location = New System.Drawing.Point(18, 17)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(64, 13)
        Me.Label2.TabIndex = 4
        Me.Label2.Text = "Channel 2"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(439, 208)
        Me.Controls.Add(Me.Panel2)
        Me.Controls.Add(Me.Panel1)
        Me.Name = "Form1"
        Me.Text = "Push Button Demo"
        CType(Me.lightBulb1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.Panel1.ResumeLayout(False)
        Me.Panel1.PerformLayout()
        Me.Panel2.ResumeLayout(False)
        Me.Panel2.PerformLayout()
        CType(Me.lightBulb2, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents lightBulb1 As System.Windows.Forms.PictureBox
    Friend WithEvents channel1On As System.Windows.Forms.Button
    Friend WithEvents channel1Off As System.Windows.Forms.Button
    Friend WithEvents Panel1 As System.Windows.Forms.Panel
    Friend WithEvents Panel2 As System.Windows.Forms.Panel
    Friend WithEvents lightBulb2 As System.Windows.Forms.PictureBox
    Friend WithEvents channel2Off As System.Windows.Forms.Button
    Friend WithEvents channel2On As System.Windows.Forms.Button
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label

End Class
