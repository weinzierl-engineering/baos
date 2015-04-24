namespace PushButtonDemo
{
	partial class PushButtonDemo
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panelChannel1 = new System.Windows.Forms.Panel();
            this.labelChannel1 = new System.Windows.Forms.Label();
            this.buttonChannel1Off = new System.Windows.Forms.Button();
            this.buttonChannel1On = new System.Windows.Forms.Button();
            this.lightBulbChannel1 = new System.Windows.Forms.PictureBox();
            this.panelChannel2 = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonChannel2Off = new System.Windows.Forms.Button();
            this.buttonChannel2On = new System.Windows.Forms.Button();
            this.lightBulbChannel2 = new System.Windows.Forms.PictureBox();
            this.groupBoxChannel3 = new System.Windows.Forms.GroupBox();
            this.buttonReadTemperature = new System.Windows.Forms.Button();
            this.editTemperature = new System.Windows.Forms.TextBox();
            this.editConnection = new System.Windows.Forms.TextBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.buttonDisconnect = new System.Windows.Forms.Button();
            this.radioByName = new System.Windows.Forms.RadioButton();
            this.radioByIP = new System.Windows.Forms.RadioButton();
            this.groupBoxVisualisation = new System.Windows.Forms.GroupBox();
            this.panelChannel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.lightBulbChannel1)).BeginInit();
            this.panelChannel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.lightBulbChannel2)).BeginInit();
            this.groupBoxChannel3.SuspendLayout();
            this.groupBoxVisualisation.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelChannel1
            // 
            this.panelChannel1.BackColor = System.Drawing.Color.White;
            this.panelChannel1.Controls.Add(this.labelChannel1);
            this.panelChannel1.Controls.Add(this.buttonChannel1Off);
            this.panelChannel1.Controls.Add(this.buttonChannel1On);
            this.panelChannel1.Controls.Add(this.lightBulbChannel1);
            this.panelChannel1.Location = new System.Drawing.Point(6, 13);
            this.panelChannel1.Name = "panelChannel1";
            this.panelChannel1.Size = new System.Drawing.Size(194, 189);
            this.panelChannel1.TabIndex = 1;
            // 
            // labelChannel1
            // 
            this.labelChannel1.AutoSize = true;
            this.labelChannel1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelChannel1.Location = new System.Drawing.Point(14, 22);
            this.labelChannel1.Name = "labelChannel1";
            this.labelChannel1.Size = new System.Drawing.Size(64, 13);
            this.labelChannel1.TabIndex = 0;
            this.labelChannel1.Text = "Channel 1";
            // 
            // buttonChannel1Off
            // 
            this.buttonChannel1Off.Location = new System.Drawing.Point(103, 88);
            this.buttonChannel1Off.Name = "buttonChannel1Off";
            this.buttonChannel1Off.Size = new System.Drawing.Size(75, 23);
            this.buttonChannel1Off.TabIndex = 2;
            this.buttonChannel1Off.Text = "Off";
            this.buttonChannel1Off.UseVisualStyleBackColor = true;
            this.buttonChannel1Off.Click += new System.EventHandler(this.channel1Off_Click);
            // 
            // buttonChannel1On
            // 
            this.buttonChannel1On.Location = new System.Drawing.Point(103, 49);
            this.buttonChannel1On.Name = "buttonChannel1On";
            this.buttonChannel1On.Size = new System.Drawing.Size(75, 23);
            this.buttonChannel1On.TabIndex = 1;
            this.buttonChannel1On.Text = "On";
            this.buttonChannel1On.UseVisualStyleBackColor = true;
            this.buttonChannel1On.Click += new System.EventHandler(this.channel1On_Click);
            // 
            // lightBulbChannel1
            // 
            this.lightBulbChannel1.Image = global::PushButtonDemo.Properties.Resources.lightbulb_off;
            this.lightBulbChannel1.Location = new System.Drawing.Point(17, 49);
            this.lightBulbChannel1.Name = "lightBulbChannel1";
            this.lightBulbChannel1.Size = new System.Drawing.Size(67, 102);
            this.lightBulbChannel1.TabIndex = 0;
            this.lightBulbChannel1.TabStop = false;
            // 
            // panelChannel2
            // 
            this.panelChannel2.BackColor = System.Drawing.Color.White;
            this.panelChannel2.Controls.Add(this.label2);
            this.panelChannel2.Controls.Add(this.buttonChannel2Off);
            this.panelChannel2.Controls.Add(this.buttonChannel2On);
            this.panelChannel2.Controls.Add(this.lightBulbChannel2);
            this.panelChannel2.Location = new System.Drawing.Point(206, 13);
            this.panelChannel2.Name = "panelChannel2";
            this.panelChannel2.Size = new System.Drawing.Size(194, 189);
            this.panelChannel2.TabIndex = 0;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(14, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Channel 2";
            // 
            // buttonChannel2Off
            // 
            this.buttonChannel2Off.Location = new System.Drawing.Point(103, 88);
            this.buttonChannel2Off.Name = "buttonChannel2Off";
            this.buttonChannel2Off.Size = new System.Drawing.Size(75, 23);
            this.buttonChannel2Off.TabIndex = 2;
            this.buttonChannel2Off.Text = "Off";
            this.buttonChannel2Off.UseVisualStyleBackColor = true;
            this.buttonChannel2Off.Click += new System.EventHandler(this.channel2Off_Click);
            // 
            // buttonChannel2On
            // 
            this.buttonChannel2On.Location = new System.Drawing.Point(103, 49);
            this.buttonChannel2On.Name = "buttonChannel2On";
            this.buttonChannel2On.Size = new System.Drawing.Size(75, 23);
            this.buttonChannel2On.TabIndex = 1;
            this.buttonChannel2On.Text = "On";
            this.buttonChannel2On.UseVisualStyleBackColor = true;
            this.buttonChannel2On.Click += new System.EventHandler(this.channel2On_Click);
            // 
            // lightBulbChannel2
            // 
            this.lightBulbChannel2.Image = global::PushButtonDemo.Properties.Resources.lightbulb_off;
            this.lightBulbChannel2.Location = new System.Drawing.Point(17, 49);
            this.lightBulbChannel2.Name = "lightBulbChannel2";
            this.lightBulbChannel2.Size = new System.Drawing.Size(67, 102);
            this.lightBulbChannel2.TabIndex = 0;
            this.lightBulbChannel2.TabStop = false;
            // 
            // groupBoxChannel3
            // 
            this.groupBoxChannel3.Controls.Add(this.buttonReadTemperature);
            this.groupBoxChannel3.Controls.Add(this.editTemperature);
            this.groupBoxChannel3.Location = new System.Drawing.Point(6, 208);
            this.groupBoxChannel3.Name = "groupBoxChannel3";
            this.groupBoxChannel3.Size = new System.Drawing.Size(394, 49);
            this.groupBoxChannel3.TabIndex = 1;
            this.groupBoxChannel3.TabStop = false;
            this.groupBoxChannel3.Text = "KNX 2-byte float";
            // 
            // buttonReadTemperature
            // 
            this.buttonReadTemperature.Location = new System.Drawing.Point(313, 16);
            this.buttonReadTemperature.Name = "buttonReadTemperature";
            this.buttonReadTemperature.Size = new System.Drawing.Size(75, 23);
            this.buttonReadTemperature.TabIndex = 1;
            this.buttonReadTemperature.Text = "Read";
            this.buttonReadTemperature.UseVisualStyleBackColor = true;
            this.buttonReadTemperature.Click += new System.EventHandler(this.buttonReadTemperature_Click);
            // 
            // editTemperature
            // 
            this.editTemperature.Location = new System.Drawing.Point(6, 19);
            this.editTemperature.Name = "editTemperature";
            this.editTemperature.ReadOnly = true;
            this.editTemperature.Size = new System.Drawing.Size(301, 20);
            this.editTemperature.TabIndex = 0;
            // 
            // editConnection
            // 
            this.editConnection.Location = new System.Drawing.Point(12, 43);
            this.editConnection.Name = "editConnection";
            this.editConnection.Size = new System.Drawing.Size(403, 20);
            this.editConnection.TabIndex = 2;
            this.editConnection.Text = "192.168.1.1";
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(221, 12);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(98, 25);
            this.buttonConnect.TabIndex = 3;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // buttonDisconnect
            // 
            this.buttonDisconnect.Enabled = false;
            this.buttonDisconnect.Location = new System.Drawing.Point(326, 12);
            this.buttonDisconnect.Name = "buttonDisconnect";
            this.buttonDisconnect.Size = new System.Drawing.Size(91, 25);
            this.buttonDisconnect.TabIndex = 4;
            this.buttonDisconnect.Text = "Disconnect";
            this.buttonDisconnect.UseVisualStyleBackColor = true;
            this.buttonDisconnect.Click += new System.EventHandler(this.buttonDisconnect_Click);
            // 
            // radioByName
            // 
            this.radioByName.AutoSize = true;
            this.radioByName.Location = new System.Drawing.Point(12, 18);
            this.radioByName.Name = "radioByName";
            this.radioByName.Size = new System.Drawing.Size(90, 17);
            this.radioByName.TabIndex = 0;
            this.radioByName.Text = "Device Name";
            this.radioByName.UseVisualStyleBackColor = true;
            this.radioByName.CheckedChanged += new System.EventHandler(this.radioByName_CheckedChanged);
            // 
            // radioByIP
            // 
            this.radioByIP.AutoSize = true;
            this.radioByIP.Checked = true;
            this.radioByIP.Location = new System.Drawing.Point(115, 18);
            this.radioByIP.Name = "radioByIP";
            this.radioByIP.Size = new System.Drawing.Size(76, 17);
            this.radioByIP.TabIndex = 1;
            this.radioByIP.TabStop = true;
            this.radioByIP.Text = "IP-Address";
            this.radioByIP.UseVisualStyleBackColor = true;
            this.radioByIP.CheckedChanged += new System.EventHandler(this.radioByIP_CheckedChanged);
            // 
            // groupBoxVisualisation
            // 
            this.groupBoxVisualisation.Controls.Add(this.panelChannel1);
            this.groupBoxVisualisation.Controls.Add(this.panelChannel2);
            this.groupBoxVisualisation.Controls.Add(this.groupBoxChannel3);
            this.groupBoxVisualisation.Enabled = false;
            this.groupBoxVisualisation.Location = new System.Drawing.Point(10, 69);
            this.groupBoxVisualisation.Name = "groupBoxVisualisation";
            this.groupBoxVisualisation.Size = new System.Drawing.Size(405, 264);
            this.groupBoxVisualisation.TabIndex = 5;
            this.groupBoxVisualisation.TabStop = false;
            // 
            // PushButtonDemo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(429, 345);
            this.Controls.Add(this.radioByIP);
            this.Controls.Add(this.radioByName);
            this.Controls.Add(this.buttonDisconnect);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.groupBoxVisualisation);
            this.Controls.Add(this.editConnection);
            this.Name = "PushButtonDemo";
            this.Text = "Push Button Demo";
            this.panelChannel1.ResumeLayout(false);
            this.panelChannel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.lightBulbChannel1)).EndInit();
            this.panelChannel2.ResumeLayout(false);
            this.panelChannel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.lightBulbChannel2)).EndInit();
            this.groupBoxChannel3.ResumeLayout(false);
            this.groupBoxChannel3.PerformLayout();
            this.groupBoxVisualisation.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panelChannel1;
        private System.Windows.Forms.PictureBox lightBulbChannel1;
        private System.Windows.Forms.Label labelChannel1;
        private System.Windows.Forms.Button buttonChannel1Off;
        private System.Windows.Forms.Button buttonChannel1On;
        private System.Windows.Forms.Panel panelChannel2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonChannel2Off;
        private System.Windows.Forms.Button buttonChannel2On;
        private System.Windows.Forms.PictureBox lightBulbChannel2;
        private System.Windows.Forms.GroupBox groupBoxChannel3;
        private System.Windows.Forms.Button buttonReadTemperature;
        private System.Windows.Forms.TextBox editTemperature;
        private System.Windows.Forms.TextBox editConnection;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Button buttonDisconnect;
        private System.Windows.Forms.RadioButton radioByName;
        private System.Windows.Forms.RadioButton radioByIP;
		private System.Windows.Forms.GroupBox groupBoxVisualisation;

    }
}

