using System;
using System.Linq;
using System.Text;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.ComponentModel;
using System.Collections.Generic;
using System.IO;
using System.Diagnostics;

namespace WinFormCharpWebCam
{
    //Design by Pongsakorn Poosankam
    public partial class mainWinForm : Form
    {
        public void ExecuteOpenCV(string arg)
        {
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "C:\\imagemproc\\WinFormCharpWebCam\\Release\\OpenCV.EXE";
            startInfo.Arguments = arg;
            startInfo.CreateNoWindow = true;
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.UseShellExecute = false;
            Process p;
            p = Process.Start(startInfo);

            p.WaitForExit();
            p.Close();
        }

        public mainWinForm()
        {
            InitializeComponent();
        }
        WebCam webcam;
        private void mainWinForm_Load(object sender, EventArgs e)
        {
            webcam = new WebCam();
            webcam.InitializeWebCam(ref imgCapture);
        }

        private void bntStart_Click(object sender, EventArgs e)
        {

            webcam.Start();


        }

        private void bntStop_Click(object sender, EventArgs e)
        {
            webcam.Stop();
        }

        private void bntContinue_Click(object sender, EventArgs e)
        {
            webcam.Continue();
        }

        private void bntCapture_Click(object sender, EventArgs e)
        {

            //imgCapture.Image = imgVideo.Image;
            /*imgVideo.Image.Save("C:\\Users\\max\\Desktop\\EasyWebCam\\saida.bmp");
                   
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "C:\\Users\\max\\Desktop\\EasyWebCam\\WinFormCharpWebCam\\Release\\OpenCV.EXE";
            startInfo.Arguments = "C:\\Users\\max\\Desktop\\EasyWebCam\\saida.bmp";
            startInfo.CreateNoWindow = true;
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.UseShellExecute = false;
            Process p;
            p=Process.Start(startInfo);
            
            p.WaitForExit();
            p.Close();
            
           imgCapture.WaitOnLoad = false;
           imgCapture.LoadAsync("C:\\Users\\max\\Desktop\\EasyWebCam\\saida2.bmp"); ;*/

        }


        private void bntSave_Click(object sender, EventArgs e)
        {
            Helper.SaveImageCapture(imgCapture.Image);

        }

        private void bntVideoFormat_Click(object sender, EventArgs e)
        {
            webcam.ResolutionSetting();
        }

        private void bntVideoSource_Click(object sender, EventArgs e)
        {
            webcam.AdvanceSetting();
        }

        private void imgVideo_Click(object sender, EventArgs e)
        {
            bntCapture_Click(sender, e);
        }

        private void captureTest1_Click(object sender, EventArgs e)
        {
            ExecuteOpenCV("captureTest1");

            imgFace1.WaitOnLoad = false;
            imgFace1.LoadAsync("C:\\imagemproc\\WinFormCharpWebCam\\bin\\Release\\test1_show.jpg");
        }

        private void captureTest2_Click(object sender, EventArgs e)
        {
            ExecuteOpenCV("captureTest2");

            imgFace2.WaitOnLoad = false;
            imgFace2.LoadAsync("C:\\imagemproc\\WinFormCharpWebCam\\bin\\Release\\test2_show.jpg");
        }

        private void recognize_Click(object sender, EventArgs e)
        {
            ExecuteOpenCV("recognize");
        }

        
        
    }
}
