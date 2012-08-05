using System;
using System.IO;
using System.Linq;
using System.Text;
using WebCam_Capture;
using System.Collections.Generic;
using System.Diagnostics;
using System.ComponentModel;



namespace WinFormCharpWebCam
{
    //Design by Pongsakorn Poosankam
    class WebCam
    {
        private WebCamCapture webcam;

        private System.Windows.Forms.PictureBox _FrameImage;
        private System.Windows.Forms.PictureBox _FrameImage2;
        
        private int FrameNumber = 30;

        public void InitializeWebCam(ref System.Windows.Forms.PictureBox ImageControl2)
        {
            // define os parametros de inicializacao da camera 
            // chamado na construcao do form main 
            webcam = new WebCamCapture();
            webcam.FrameNumber = ((ulong)(0ul));
            webcam.TimeToCapture_milliseconds = FrameNumber;


            webcam.ImageCaptured += new WebCamCapture.WebCamEventHandler(webcam_ImageCaptured);
            //_FrameImage = ImageControl;
            _FrameImage2 = ImageControl2;
        }

        void webcam_ImageCaptured(object source, WebcamEventArgs e)
        {


           // aqui eu vou inserir meu tratgamento  e.WebCamImage

           // Process.Start("IExplore.exe", "C:\\myPath\\myFile.htm");
           // Process.Start("IExplore.exe");
            //_FrameImage.Image = e.WebCamImage;
            // O problema aqui era permissão. Tem que salvar em uma pasta com permissao



            //imgCapture.Image = imgVideo.Image;
            e.WebCamImage.Save("C:\\imagemproc\\saida.bmp");

            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "C:\\imagemproc\\WinFormCharpWebCam\\Release\\OpenCV.EXE";
            startInfo.Arguments = "webcam";
            startInfo.CreateNoWindow = true;
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.UseShellExecute = false;
            Process p;
            p = Process.Start(startInfo);

            p.WaitForExit();
            p.Close();



            _FrameImage2.WaitOnLoad = false;
            _FrameImage2.LoadAsync("C:\\imagemproc\\saida2.bmp");

             

        }

        public void Start()
        {
            webcam.TimeToCapture_milliseconds = FrameNumber;
            webcam.Start(0);
        }

        public void Stop()
        {
            webcam.Stop();
        }

        public void Continue()
        {
            // change the capture time frame
            webcam.TimeToCapture_milliseconds = FrameNumber;

            // resume the video capture from the stop
            webcam.Start(this.webcam.FrameNumber);
        }

        public void ResolutionSetting()
        {
            webcam.Config();
        }

        public void AdvanceSetting()
        {
            webcam.Config2();
        }

    }
}
