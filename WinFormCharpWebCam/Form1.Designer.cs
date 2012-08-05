namespace WinFormCharpWebCam
{
    //Design by Pongsakorn Poosankam
    partial class mainWinForm
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
            this.imgCapture = new System.Windows.Forms.PictureBox();
            this.bntStart = new System.Windows.Forms.Button();
            this.bntStop = new System.Windows.Forms.Button();
            this.bntContinue = new System.Windows.Forms.Button();
            this.bntVideoFormat = new System.Windows.Forms.Button();
            this.bntVideoSource = new System.Windows.Forms.Button();
            this.imgFace1 = new System.Windows.Forms.PictureBox();
            this.imgFace2 = new System.Windows.Forms.PictureBox();
            this.captureTest1 = new System.Windows.Forms.Button();
            this.captureTest2 = new System.Windows.Forms.Button();
            this.recognize = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.imgCapture)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgFace1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgFace2)).BeginInit();
            this.SuspendLayout();
            // 
            // imgCapture
            // 
            this.imgCapture.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.imgCapture.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.imgCapture.Location = new System.Drawing.Point(10, 12);
            this.imgCapture.Name = "imgCapture";
            this.imgCapture.Size = new System.Drawing.Size(320, 240);
            this.imgCapture.TabIndex = 1;
            this.imgCapture.TabStop = false;
            // 
            // bntStart
            // 
            this.bntStart.Location = new System.Drawing.Point(10, 270);
            this.bntStart.Name = "bntStart";
            this.bntStart.Size = new System.Drawing.Size(41, 23);
            this.bntStart.TabIndex = 2;
            this.bntStart.Text = "Start";
            this.bntStart.UseVisualStyleBackColor = true;
            this.bntStart.Click += new System.EventHandler(this.bntStart_Click);
            // 
            // bntStop
            // 
            this.bntStop.Location = new System.Drawing.Point(57, 270);
            this.bntStop.Name = "bntStop";
            this.bntStop.Size = new System.Drawing.Size(49, 23);
            this.bntStop.TabIndex = 3;
            this.bntStop.Text = "Stop";
            this.bntStop.UseVisualStyleBackColor = true;
            this.bntStop.Click += new System.EventHandler(this.bntStop_Click);
            // 
            // bntContinue
            // 
            this.bntContinue.Location = new System.Drawing.Point(112, 270);
            this.bntContinue.Name = "bntContinue";
            this.bntContinue.Size = new System.Drawing.Size(61, 23);
            this.bntContinue.TabIndex = 4;
            this.bntContinue.Text = "Continue";
            this.bntContinue.UseVisualStyleBackColor = true;
            this.bntContinue.Click += new System.EventHandler(this.bntContinue_Click);
            // 
            // bntVideoFormat
            // 
            this.bntVideoFormat.Location = new System.Drawing.Point(337, 269);
            this.bntVideoFormat.Name = "bntVideoFormat";
            this.bntVideoFormat.Size = new System.Drawing.Size(107, 23);
            this.bntVideoFormat.TabIndex = 7;
            this.bntVideoFormat.Text = "Video Format";
            this.bntVideoFormat.UseVisualStyleBackColor = true;
            this.bntVideoFormat.Click += new System.EventHandler(this.bntVideoFormat_Click);
            // 
            // bntVideoSource
            // 
            this.bntVideoSource.Location = new System.Drawing.Point(450, 269);
            this.bntVideoSource.Name = "bntVideoSource";
            this.bntVideoSource.Size = new System.Drawing.Size(107, 23);
            this.bntVideoSource.TabIndex = 8;
            this.bntVideoSource.Text = "Video Source";
            this.bntVideoSource.UseVisualStyleBackColor = true;
            this.bntVideoSource.Click += new System.EventHandler(this.bntVideoSource_Click);
            // 
            // imgFace1
            // 
            this.imgFace1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.imgFace1.Location = new System.Drawing.Point(337, 12);
            this.imgFace1.Name = "imgFace1";
            this.imgFace1.Size = new System.Drawing.Size(115, 115);
            this.imgFace1.TabIndex = 9;
            this.imgFace1.TabStop = false;
            // 
            // imgFace2
            // 
            this.imgFace2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.imgFace2.Location = new System.Drawing.Point(458, 12);
            this.imgFace2.Name = "imgFace2";
            this.imgFace2.Size = new System.Drawing.Size(115, 115);
            this.imgFace2.TabIndex = 10;
            this.imgFace2.TabStop = false;
            // 
            // captureTest1
            // 
            this.captureTest1.Location = new System.Drawing.Point(355, 133);
            this.captureTest1.Name = "captureTest1";
            this.captureTest1.Size = new System.Drawing.Size(75, 23);
            this.captureTest1.TabIndex = 11;
            this.captureTest1.Text = "Capture";
            this.captureTest1.UseVisualStyleBackColor = true;
            this.captureTest1.Click += new System.EventHandler(this.captureTest1_Click);
            // 
            // captureTest2
            // 
            this.captureTest2.Location = new System.Drawing.Point(482, 133);
            this.captureTest2.Name = "captureTest2";
            this.captureTest2.Size = new System.Drawing.Size(75, 23);
            this.captureTest2.TabIndex = 12;
            this.captureTest2.Text = "Capture";
            this.captureTest2.UseVisualStyleBackColor = true;
            this.captureTest2.Click += new System.EventHandler(this.captureTest2_Click);
            // 
            // recognize
            // 
            this.recognize.Location = new System.Drawing.Point(354, 167);
            this.recognize.Name = "recognize";
            this.recognize.Size = new System.Drawing.Size(75, 23);
            this.recognize.TabIndex = 13;
            this.recognize.Text = "Reconhecer";
            this.recognize.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.recognize.UseVisualStyleBackColor = true;
            this.recognize.Click += new System.EventHandler(this.recognize_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(435, 170);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(133, 20);
            this.textBox1.TabIndex = 14;
            // 
            // mainWinForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(580, 305);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.recognize);
            this.Controls.Add(this.captureTest2);
            this.Controls.Add(this.captureTest1);
            this.Controls.Add(this.imgFace2);
            this.Controls.Add(this.imgFace1);
            this.Controls.Add(this.bntVideoSource);
            this.Controls.Add(this.bntVideoFormat);
            this.Controls.Add(this.bntContinue);
            this.Controls.Add(this.bntStop);
            this.Controls.Add(this.bntStart);
            this.Controls.Add(this.imgCapture);
            this.Name = "mainWinForm";
            this.Text = "WinForm C# WebCam";
            this.Load += new System.EventHandler(this.mainWinForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.imgCapture)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgFace1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgFace2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox imgCapture;
        private System.Windows.Forms.Button bntStart;
        private System.Windows.Forms.Button bntStop;
        private System.Windows.Forms.Button bntContinue;
        private System.Windows.Forms.Button bntVideoFormat;
        private System.Windows.Forms.Button bntVideoSource;
        private System.Windows.Forms.PictureBox imgFace1;
        private System.Windows.Forms.PictureBox imgFace2;
        private System.Windows.Forms.Button captureTest1;
        private System.Windows.Forms.Button captureTest2;
        private System.Windows.Forms.Button recognize;
        private System.Windows.Forms.TextBox textBox1;
    }
}

