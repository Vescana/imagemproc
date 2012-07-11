
#include "stdafx.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <iostream>
#include <math.h>


/* versao 1.0 , antiga
// Perform face detection on the input image, using the given Haar Cascade.
// Returns a rectangle for the detected region in the given image.
CvRect detectFaceInImage(IplImage *inputImg, CvHaarClassifierCascade* cascade)
{
	// Smallest face size.
	CvSize minFeatureSize = cvSize(20, 20);
	// Only search for 1 face.
	int flags = CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_DO_ROUGH_SEARCH;
	// How detailed should the search be.
	float search_scale_factor = 1.1f;
	IplImage *detectImg;
	IplImage *greyImg = 0;
	CvMemStorage* storage;
	CvRect rc;
	double t;
	CvSeq* rects;
	CvSize size;
	int i, ms, nFaces;
	storage = cvCreateMemStorage(0);
	cvClearMemStorage( storage );


	// If the image is color, use a greyscale copy of the image.
	detectImg = (IplImage*)inputImg;
	if (inputImg->nChannels > 1) {
		size = cvSize(inputImg->width, inputImg->height);
		greyImg = cvCreateImage(size, IPL_DEPTH_8U, 1 );
		cvCvtColor( inputImg, greyImg, CV_BGR2GRAY );
		detectImg = greyImg;	// Use the greyscale image.
	}

	// Detect all the faces in the greyscale image.
	t = (double)cvGetTickCount();
	rects = cvHaarDetectObjects( detectImg, cascade, storage,search_scale_factor, 3, flags, minFeatureSize);
	t = (double)cvGetTickCount() - t;
	ms = cvRound( t / ((double)cvGetTickFrequency() * 1000.0) );
	nFaces = rects->total;
	printf("Face Detection took %d ms and found %d objects\n", ms, nFaces);

	// Get the first detected face (the biggest).
	if (nFaces > 0)
		rc = *(CvRect*)cvGetSeqElem( rects, 0 );
	else
		rc = cvRect(-1,-1,-1,-1);	// Couldn't find the face.
	
	if (greyImg)
	{
		
		CvPoint verticeinic, verticefim ; 
		verticeinic.x = rc.x-rc.width; 
		verticeinic.y = rc.y-rc.height; 

		verticefim.x = rc.x+rc.width; 
		verticefim.y = rc.y+rc.height; 



		//cvRectangle(greyImg,verticeinic,verticeinic,CV_RGB(255,0,0)  );
		cvSaveImage("C:\\Users\\max\\Desktop\\EasyWebCam\\saida2.bmp",greyImg);
		
		cvReleaseImage( &greyImg );
	}
	cvReleaseMemStorage( &storage );
	cvReleaseHaarClassifierCascade( &cascade );

	return rc;	// Return the biggest face found, or (-1,-1,-1,-1).
}

*/
int main(int argc, char** argv)
{
  IplImage *inputImg = cvLoadImage(argv[1]);
//IplImage *inputImg = cvLoadImage("C:\\Users\\max\\Desktop\\EasyWebCam\\saida.bmp",CV_LOAD_IMAGE_GRAYSCALE);
CvSeq * pFaceRectSeq;
// Haar Cascade file, used for Face Detection.	
char *faceCascadeFilename = "C:\\Users\\max\\Desktop\\EasyWebCam\\WinFormCharpWebCam\\bin\\Release\\haarcascade_frontalface_default.xml";
// Load the HaarCascade classifier for face detection.
CvHaarClassifierCascade* faceCascade;
//IplImage *inputImg = cvLoadImage(argv[1]);
faceCascade = (CvHaarClassifierCascade*)cvLoad(faceCascadeFilename, 0, 0, 0);
if( !faceCascade ) {
	printf("Couldnt load Face detector '%s'\n", faceCascadeFilename);
	exit(1);
}
CvMemStorage * pStorage = 0 ;
pStorage=cvCreateMemStorage(0);

pFaceRectSeq = cvHaarDetectObjects(inputImg,faceCascade,pStorage,1.1,3,CV_HAAR_DO_CANNY_PRUNING,cvSize(0,0));
int i=0;

if (i<pFaceRectSeq->total) 
{
	for (i=0;i<=pFaceRectSeq->total;i++)
	{
		CvRect * r = (CvRect *)cvGetSeqElem(pFaceRectSeq,i);
		CvPoint pt1 = {r->x,r->y};
		CvPoint pt2 = {r->x +r->width  ,r->y+r->height};
		cvRectangle(inputImg,pt1,pt2,CV_RGB(255,0,0),3,4,0);

	}
}
	//cvNamedWindow( "Source", 1 );
	//cvShowImage( "Source", inputImg );
	//cvWaitKey(0);
	cvSaveImage("C:\\Users\\max\\Desktop\\EasyWebCam\\saida2.bmp",inputImg);
	cvReleaseImage(&inputImg);
	if (pStorage) cvReleaseMemStorage(&pStorage);
	if(faceCascade) cvReleaseHaarClassifierCascade(&faceCascade);

}





/* main do detector de faces , primeira tentativa


// Perform face detection on the input image, using the given Haar classifier
CvRect faceRect = detectFaceInImage(inputImg, faceCascade);
// Make sure a valid face was detected.
if (faceRect.width > 0) {
	printf("Detected a face at (%d,%d)!\n", faceRect.x, faceRect.y);
}
  // desenhar o retangulo na face 

CvPoint inic, fim ; 

inic.x=faceRect.x;
inic.y=faceRect.y;

fim.x=inic.x+40;
fim.y=inic.y+40;

//.... Use 'faceRect' and 'inputImg' ....
cvCircle(inputImg,inic,10,CV_RGB(255,0,0));

cvRectangle(inputImg,inic,fim,CV_RGB(255,0,0));
cvNamedWindow( "Hough", 1 );
cvShowImage( "Hough", inputImg );
cvWaitKey(0);
//cvReleaseHaarClassifierCascade( &faceCascade );


*/



/*


//main do detector de linhas 

	//IplImage *src = cvLoadImage("C:\\Users\\max\\Desktop\\EasyWebCam\\photo.jpg",CV_LOAD_IMAGE_GRAYSCALE );
//	IplImage *src = cvLoadImage("C:\\Users\\max\\Desktop\\EasyWebCam\\photo.jpg");
     		IplImage *src = cvLoadImage(argv[1]);

    {
        IplImage* dst = cvCreateImage( cvGetSize(src), 8, 1 );
        IplImage* color_dst = cvCreateImage( cvGetSize(src), 8, 3 );
        CvMemStorage* storage = cvCreateMemStorage(0);
        CvSeq* lines = 0;
        int i;
        cvCanny( src, dst, 50, 200, 3 );
        cvCvtColor( dst, color_dst, CV_GRAY2BGR );
#if 1
        lines = cvHoughLines2( dst, storage, CV_HOUGH_STANDARD, 1, CV_PI/180, 150, 0, 0 );

        for( i = 0; i < lines->total; i++ )
        {
            float* line = (float*)cvGetSeqElem(lines,i);
            float rho = line[0];
            float theta = line[1];
            CvPoint pt1, pt2;
            double a = cos(theta), b = sin(theta);
            if( fabs(a) < 0.001 )
            {
                pt1.x = pt2.x = cvRound(rho);
                pt1.y = 0;
                pt2.y = color_dst->height;
            }
            else if( fabs(b) < 0.001 )
            {
                pt1.y = pt2.y = cvRound(rho);
                pt1.x = 0;
                pt2.x = color_dst->width;
            }
            else
            {
                pt1.x = 0;
                pt1.y = cvRound(rho/b);
                pt2.x = cvRound(rho/a);
                pt2.y = 0;
            }
            cvLine( color_dst, pt1, pt2, CV_RGB(255,0,0), 3, 8 );
        }
#else
        lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 80, 30, 10 );
        for( i = 0; i < lines->total; i++ )
        {
            CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
            cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 3, 8 );
        }
#endif
      //  cvNamedWindow( "Source", 1 );
       // cvShowImage( "Source", src );

     //   cvNamedWindow( "Hough", 1 );
     //   cvShowImage( "Hough", color_dst );
		cvSaveImage("C:\\Users\\max\\Desktop\\EasyWebCam\\saida2.bmp",dst);
//        cvWaitKey(0);
    }

*/