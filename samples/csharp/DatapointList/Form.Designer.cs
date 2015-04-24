namespace DatapointList
{
    partial class Form1
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
            this.editConnection = new System.Windows.Forms.TextBox();
            this.radioByName = new System.Windows.Forms.RadioButton();
            this.radioByIP = new System.Windows.Forms.RadioButton();
            this.buttonRead = new System.Windows.Forms.Button();
            this.dataGridView = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // editConnection
            // 
            this.editConnection.Location = new System.Drawing.Point(207, 12);
            this.editConnection.Name = "editConnection";
            this.editConnection.Size = new System.Drawing.Size(129, 20);
            this.editConnection.TabIndex = 1;
            this.editConnection.Text = "192.168.1.1";
            // 
            // radioByName
            // 
            this.radioByName.AutoSize = true;
            this.radioByName.Location = new System.Drawing.Point(12, 12);
            this.radioByName.Name = "radioByName";
            this.radioByName.Size = new System.Drawing.Size(90, 17);
            this.radioByName.TabIndex = 4;
            this.radioByName.Text = "Device Name";
            this.radioByName.UseVisualStyleBackColor = true;
            this.radioByName.CheckedChanged += new System.EventHandler(this.radioByName_CheckedChanged);
            // 
            // radioByIP
            // 
            this.radioByIP.AutoSize = true;
            this.radioByIP.Checked = true;
            this.radioByIP.Location = new System.Drawing.Point(117, 12);
            this.radioByIP.Name = "radioByIP";
            this.radioByIP.Size = new System.Drawing.Size(76, 17);
            this.radioByIP.TabIndex = 5;
            this.radioByIP.TabStop = true;
            this.radioByIP.Text = "IP-Address";
            this.radioByIP.UseVisualStyleBackColor = true;
            this.radioByIP.CheckedChanged += new System.EventHandler(this.radioByIP_CheckedChanged);
            // 
            // buttonRead
            // 
            this.buttonRead.Location = new System.Drawing.Point(348, 8);
            this.buttonRead.Name = "buttonRead";
            this.buttonRead.Size = new System.Drawing.Size(116, 27);
            this.buttonRead.TabIndex = 6;
            this.buttonRead.Text = "Read";
            this.buttonRead.UseVisualStyleBackColor = true;
            this.buttonRead.Click += new System.EventHandler(this.buttonRead_Click);
            // 
            // dataGridView
            // 
            this.dataGridView.AllowUserToAddRows = false;
            this.dataGridView.AllowUserToDeleteRows = false;
            this.dataGridView.AllowUserToOrderColumns = true;
            this.dataGridView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Location = new System.Drawing.Point(12, 53);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.ReadOnly = true;
            this.dataGridView.Size = new System.Drawing.Size(452, 174);
            this.dataGridView.TabIndex = 10;
            this.dataGridView.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_CellContentClick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(476, 239);
            this.Controls.Add(this.dataGridView);
            this.Controls.Add(this.buttonRead);
            this.Controls.Add(this.radioByIP);
            this.Controls.Add(this.radioByName);
            this.Controls.Add(this.editConnection);
            this.Name = "Form1";
            this.Text = "Datapoint List";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox editConnection;
        private System.Windows.Forms.RadioButton radioByName;
        private System.Windows.Forms.RadioButton radioByIP;
		private System.Windows.Forms.Button buttonRead;
		private System.Windows.Forms.DataGridView dataGridView;
    }
}

