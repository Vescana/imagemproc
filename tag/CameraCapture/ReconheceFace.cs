//----------------------------------------------------------------------------
//  Copyright (C) 2004-2012 by EMGU. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Emgu.CV;
using Emgu.CV.CvEnum;
using System.IO;
using Emgu.CV.Structure;
using Emgu.Util;

namespace CameraCapture
{
    public partial class ReconheceFace : Form
    {
        private Capture _capture = null;
        private bool _captureInProgress;
        private HaarCascade haar;

        public ReconheceFace()
        {
            InitializeComponent();
            try
            {
                _capture = new Capture();
                _capture.ImageGrabbed += ProcessFrame;
            }
            catch (NullReferenceException excpt)
            {
                MessageBox.Show(excpt.Message);
            }
        }

        private  void ProcessFrame(object sender, EventArgs arg)
        {


            Image<Bgr, Byte> frame = _capture.RetrieveBgrFrame();

            //Image<Gray, Byte> grayFrame = frame.Convert<Gray, Byte>();
            //Image<Gray, Byte> smallGrayFrame = grayFrame.PyrDown();
            //Image<Gray, Byte> smoothedGrayFrame = smallGrayFrame.PyrUp();
            //Image<Gray, Byte> cannyFrame = smoothedGrayFrame.Canny(new Gray(100), new Gray(60));

            
           // grayscaleImageBox.Image = grayFrame;
           // smoothedGrayscaleImageBox.Image = smoothedGrayFrame;
           // cannyImageBox.Image = cannyFrame;

            // there's only one channel (greyscale), hence the zero index
            //var faces = nextFrame.DetectHaarCascade(haar)[0];
            Image<Gray, Byte> grayFrame = frame.Convert<Gray, Byte>();
           // var faces = HaarCascade.Detect(grayFrame, 1.4, 4, HAAR_DETECTION_TYPE.DO_CANNY_PRUNING, new Size(frame.Width / 8, frame.Height / 8),new Size(frame.Width / 8, frame.Height / 8);     

            // aplica o haar carregado no load do form na imagem cinza 
            var faces = haar.Detect(grayFrame, 1.4, 2, HAAR_DETECTION_TYPE.DO_CANNY_PRUNING, new Size(frame.Width / 8, frame.Height / 8), new Size((frame.Width + 2) / 8, (frame.Height + 2) / 8));    
            

            //HaarCascade.Detect(grayFrame, 1.4, 4, HAAR_DETECTION_TYPE.DO_CANNY_PRUNING, new Size(frame.Width / 8, frame.Height / 8),new Size(frame.Width / 8, frame.Height / 8);        
           // grayframe.DetectHaarCascade(haar, 1.4, 4,HAAR_DETECTION_TYPE.DO_CANNY_PRUNING,new Size(nextFrame.Width / 8, nextFrame.Height / 8))[0];
            
            // aplica a ROI na imagem 
            foreach (var face in faces)
            {
                
                    frame.Draw(face.rect, new Bgr(0, double.MaxValue, 0), 3);
                    grayFrame.ROI = face.rect;
                    if (face.rect != null) reconheceBox1.Image = grayFrame; 
            }

            captureImageBox.Image = frame;
           

            /// aprende 
            /// 
            int i, offset;



        }

      

        private void ReleaseData()
        {
            if (_capture != null)
                
                _capture.Dispose();
        }

        private void FlipHorizontalButtonClick(object sender, EventArgs e)
        {
            if (_capture != null) _capture.FlipHorizontal = !_capture.FlipHorizontal;
        }

        private void FlipVerticalButtonClick(object sender, EventArgs e)
        {
            if (_capture != null) _capture.FlipVertical = !_capture.FlipVertical;
        }

        private void captureButton_Click(object sender, EventArgs e)
        {
            if (_capture != null)
            {
                if (_captureInProgress)
                {  //stop the capture
                    captureButton.Text = "Start Capture";
                    _capture.Pause();
                }
                else
                {
                    //start the capture
                    captureButton.Text = "Stop";
                    _capture.Start();
                }

                _captureInProgress = !_captureInProgress;
            }
        }


        unsafe private void Reconhecedor(object sender, EventArgs e)
        {
            CriaROI();

        }
        unsafe private void CriaROI()
        {
            MCvSeq* pFaceRectSeq;
            string faceCascadeFilename = "C:\\imagemproc\\WinFormCharpWebCam\\bin\\Release\\haarcascade_profileface.xml";
           // CvInvoke.cvReleaseHaarClassifierCascade(faceCascade);
            

        }

        private void ReconheceFace_Load(object sender, EventArgs e)
        {
            haar = new HaarCascade("haarcascade_frontalface_alt2.xml");
        }
    }
}
