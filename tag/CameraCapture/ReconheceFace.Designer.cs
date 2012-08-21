namespace CameraCapture
{
    partial class ReconheceFace
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
            ReleaseData();
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
            this.flipVerticalButton = new System.Windows.Forms.Button();
            this.flipHorizontalButton = new System.Windows.Forms.Button();
            this.captureButton = new System.Windows.Forms.Button();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.captureImageBox = new Emgu.CV.UI.ImageBox();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.reconheceBox1 = new Emgu.CV.UI.ImageBox();
            this.reconheceBox2 = new Emgu.CV.UI.ImageBox();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.captureImageBox)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.reconheceBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.reconheceBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // flipVerticalButton
            // 
            this.flipVerticalButton.Location = new System.Drawing.Point(309, 363);
            this.flipVerticalButton.Name = "flipVerticalButton";
            this.flipVerticalButton.Size = new System.Drawing.Size(102, 23);
            this.flipVerticalButton.TabIndex = 5;
            this.flipVerticalButton.Text = "Flip Vertical";
            this.flipVerticalButton.UseVisualStyleBackColor = true;
            // 
            // flipHorizontalButton
            // 
            this.flipHorizontalButton.Location = new System.Drawing.Point(166, 363);
            this.flipHorizontalButton.Name = "flipHorizontalButton";
            this.flipHorizontalButton.Size = new System.Drawing.Size(102, 23);
            this.flipHorizontalButton.TabIndex = 4;
            this.flipHorizontalButton.Text = "Flip Horizontal";
            this.flipHorizontalButton.UseVisualStyleBackColor = true;
            // 
            // captureButton
            // 
            this.captureButton.Location = new System.Drawing.Point(19, 363);
            this.captureButton.Name = "captureButton";
            this.captureButton.Size = new System.Drawing.Size(102, 23);
            this.captureButton.TabIndex = 3;
            this.captureButton.Text = "Start Capture";
            this.captureButton.UseVisualStyleBackColor = true;
            this.captureButton.Click += new System.EventHandler(this.captureButton_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Location = new System.Drawing.Point(19, 43);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.captureImageBox);
            this.splitContainer1.Size = new System.Drawing.Size(429, 251);
            this.splitContainer1.SplitterDistance = 395;
            this.splitContainer1.TabIndex = 6;
            // 
            // captureImageBox
            // 
            this.captureImageBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.captureImageBox.Location = new System.Drawing.Point(0, 0);
            this.captureImageBox.Name = "captureImageBox";
            this.captureImageBox.Size = new System.Drawing.Size(395, 251);
            this.captureImageBox.TabIndex = 2;
            this.captureImageBox.TabStop = false;
            // 
            // splitContainer3
            // 
            this.splitContainer3.Location = new System.Drawing.Point(458, 43);
            this.splitContainer3.Name = "splitContainer3";
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.reconheceBox1);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.Controls.Add(this.reconheceBox2);
            this.splitContainer3.Size = new System.Drawing.Size(484, 251);
            this.splitContainer3.SplitterDistance = 232;
            this.splitContainer3.TabIndex = 7;
            // 
            // reconheceBox1
            // 
            this.reconheceBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.reconheceBox1.Location = new System.Drawing.Point(0, 0);
            this.reconheceBox1.Name = "reconheceBox1";
            this.reconheceBox1.Size = new System.Drawing.Size(232, 251);
            this.reconheceBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.reconheceBox1.TabIndex = 4;
            this.reconheceBox1.TabStop = false;
            // 
            // reconheceBox2
            // 
            this.reconheceBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.reconheceBox2.Location = new System.Drawing.Point(0, 0);
            this.reconheceBox2.Name = "reconheceBox2";
            this.reconheceBox2.Size = new System.Drawing.Size(248, 251);
            this.reconheceBox2.TabIndex = 5;
            this.reconheceBox2.TabStop = false;
            // 
            // ReconheceFace
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(954, 408);
            this.Controls.Add(this.splitContainer3);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.flipVerticalButton);
            this.Controls.Add(this.flipHorizontalButton);
            this.Controls.Add(this.captureButton);
            this.Name = "ReconheceFace";
            this.Text = "ReconheceFace";
            this.Load += new System.EventHandler(this.ReconheceFace_Load);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.captureImageBox)).EndInit();
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel2.ResumeLayout(false);
            this.splitContainer3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.reconheceBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.reconheceBox2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button flipVerticalButton;
        private System.Windows.Forms.Button flipHorizontalButton;
        private System.Windows.Forms.Button captureButton;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private Emgu.CV.UI.ImageBox captureImageBox;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private Emgu.CV.UI.ImageBox reconheceBox1;
        private Emgu.CV.UI.ImageBox reconheceBox2;
    }
}