
#include "stdafx.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <iostream>
#include <math.h>
#include <string.h> // adicionado para o recognize
#include "cvaux.h" // adicionado para o recognize

// Código do recognize
// --------------------

// Adicionado código para escrita de reconhecimento em arquivo
FILE *fp;

//// Global variables
IplImage ** faceImgArr        = 0; // array of face images
CvMat    *  personNumTruthMat = 0; // array of person numbers
int nTrainFaces               = 0; // the number of training images
int nEigens                   = 0; // the number of eigenvalues
IplImage * pAvgTrainImg       = 0; // the average image
IplImage ** eigenVectArr      = 0; // eigenvectors
CvMat * eigenValMat           = 0; // eigenvalues
CvMat * projectedTrainFaceMat = 0; // projected training faces


//// Function prototypes
void learn();
void recognize();
void doPCA();
void storeTrainingData();
int  loadTrainingData(CvMat ** pTrainPersonNumMat);
int  findNearestNeighbor(float * projectedTestFace);
int  loadFaceImgArray(char * filename);


//////////////////////////////////
// learn()
//
void learn()
{
	int i, offset;

	// load training data
	nTrainFaces = loadFaceImgArray("train.txt");
	if( nTrainFaces < 2 )
	{
		fprintf(stderr,
		        "Need 2 or more training faces\n"
		        "Input file contains only %d\n", nTrainFaces);
		return;
	}

	// do PCA on the training faces
	doPCA();

	// project the training images onto the PCA subspace
	projectedTrainFaceMat = cvCreateMat( nTrainFaces, nEigens, CV_32FC1 );
	offset = projectedTrainFaceMat->step / sizeof(float);
	for(i=0; i<nTrainFaces; i++)
	{
		//int offset = i * nEigens;
		cvEigenDecomposite(
			faceImgArr[i],
			nEigens,
			eigenVectArr,
			0, 0,
			pAvgTrainImg,
			//projectedTrainFaceMat->data.fl + i*nEigens);
			projectedTrainFaceMat->data.fl + i*offset);
	}

	// store the recognition data as an xml file
	storeTrainingData();
}


//////////////////////////////////
// recognize()
//
void recognize()
{
	int i, nTestFaces  = 0;         // the number of test images
	CvMat * trainPersonNumMat = 0;  // the person numbers during training
	float * projectedTestFace = 0;

	// adicionado código para escrita em arquivo
	fp = fopen ("recognize.txt","w");

	// load test images and ground truth for person number
	nTestFaces = loadFaceImgArray("test.txt");
	printf("%d test faces loaded\n", nTestFaces);

	// load the saved training data
	if( !loadTrainingData( &trainPersonNumMat ) ) return;

	// project the test images onto the PCA subspace
	projectedTestFace = (float *)cvAlloc( nEigens*sizeof(float) );
	for(i=0; i<nTestFaces; i++)
	{
		int iNearest, nearest, truth;

		// project the test image onto the PCA subspace
		cvEigenDecomposite(
			faceImgArr[i],
			nEigens,
			eigenVectArr,
			0, 0,
			pAvgTrainImg,
			projectedTestFace);

		iNearest = findNearestNeighbor(projectedTestFace);
		truth    = personNumTruthMat->data.i[i];
		nearest  = trainPersonNumMat->data.i[iNearest];

		//printf para fprintf
		fprintf(fp, "nearest = %d, Truth = %d\n", nearest, truth);
	}

	fclose(fp);
}


//////////////////////////////////
// loadTrainingData()
//
int loadTrainingData(CvMat ** pTrainPersonNumMat)
{
	CvFileStorage * fileStorage;
	int i;

	// create a file-storage interface
	fileStorage = cvOpenFileStorage( "facedata.xml", 0, CV_STORAGE_READ );
	if( !fileStorage )
	{
		fprintf(stderr, "Can't open facedata.xml\n");
		return 0;
	}

	nEigens = cvReadIntByName(fileStorage, 0, "nEigens", 0);
	nTrainFaces = cvReadIntByName(fileStorage, 0, "nTrainFaces", 0);
	*pTrainPersonNumMat = (CvMat *)cvReadByName(fileStorage, 0, "trainPersonNumMat", 0);
	eigenValMat  = (CvMat *)cvReadByName(fileStorage, 0, "eigenValMat", 0);
	projectedTrainFaceMat = (CvMat *)cvReadByName(fileStorage, 0, "projectedTrainFaceMat", 0);
	pAvgTrainImg = (IplImage *)cvReadByName(fileStorage, 0, "avgTrainImg", 0);
	eigenVectArr = (IplImage **)cvAlloc(nTrainFaces*sizeof(IplImage *));
	for(i=0; i<nEigens; i++)
	{
		char varname[200];
		sprintf( varname, "eigenVect_%d", i );
		eigenVectArr[i] = (IplImage *)cvReadByName(fileStorage, 0, varname, 0);
	}

	// release the file-storage interface
	cvReleaseFileStorage( &fileStorage );

	return 1;
}


//////////////////////////////////
// storeTrainingData()
//
void storeTrainingData()
{
	CvFileStorage * fileStorage;
	int i;

	// create a file-storage interface
	fileStorage = cvOpenFileStorage( "facedata.xml", 0, CV_STORAGE_WRITE );

	// store all the data
	cvWriteInt( fileStorage, "nEigens", nEigens );
	cvWriteInt( fileStorage, "nTrainFaces", nTrainFaces );
	cvWrite(fileStorage, "trainPersonNumMat", personNumTruthMat, cvAttrList(0,0));
	cvWrite(fileStorage, "eigenValMat", eigenValMat, cvAttrList(0,0));
	cvWrite(fileStorage, "projectedTrainFaceMat", projectedTrainFaceMat, cvAttrList(0,0));
	cvWrite(fileStorage, "avgTrainImg", pAvgTrainImg, cvAttrList(0,0));
	for(i=0; i<nEigens; i++)
	{
		char varname[200];
		sprintf( varname, "eigenVect_%d", i );
		cvWrite(fileStorage, varname, eigenVectArr[i], cvAttrList(0,0));
	}

	// release the file-storage interface
	cvReleaseFileStorage( &fileStorage );
}


//////////////////////////////////
// findNearestNeighbor()
//
int findNearestNeighbor(float * projectedTestFace)
{
	//double leastDistSq = 1e12;
	double leastDistSq = DBL_MAX;
	int i, iTrain, iNearest = 0;

	for(iTrain=0; iTrain<nTrainFaces; iTrain++)
	{
		double distSq=0;

		for(i=0; i<nEigens; i++)
		{
			float d_i =
				projectedTestFace[i] -
				projectedTrainFaceMat->data.fl[iTrain*nEigens + i];
			//distSq += d_i*d_i / eigenValMat->data.fl[i];  // Mahalanobis
			distSq += d_i*d_i; // Euclidean
		}

		if(distSq < leastDistSq)
		{
			leastDistSq = distSq;
			iNearest = iTrain;
		}
	}

	return iNearest;
}


//////////////////////////////////
// doPCA()
//
void doPCA()
{
	int i;
	CvTermCriteria calcLimit;
	CvSize faceImgSize;

	// set the number of eigenvalues to use
	nEigens = nTrainFaces-1;

	// allocate the eigenvector images
	faceImgSize.width  = faceImgArr[0]->width;
	faceImgSize.height = faceImgArr[0]->height;
	eigenVectArr = (IplImage**)cvAlloc(sizeof(IplImage*) * nEigens);
	for(i=0; i<nEigens; i++)
		eigenVectArr[i] = cvCreateImage(faceImgSize, IPL_DEPTH_32F, 1);

	// allocate the eigenvalue array
	eigenValMat = cvCreateMat( 1, nEigens, CV_32FC1 );

	// allocate the averaged image
	pAvgTrainImg = cvCreateImage(faceImgSize, IPL_DEPTH_32F, 1);

	// set the PCA termination criterion
	calcLimit = cvTermCriteria( CV_TERMCRIT_ITER, nEigens, 1);

	// compute average image, eigenvalues, and eigenvectors
	cvCalcEigenObjects(
		nTrainFaces,
		(void*)faceImgArr,
		(void*)eigenVectArr,
		CV_EIGOBJ_NO_CALLBACK,
		0,
		0,
		&calcLimit,
		pAvgTrainImg,
		eigenValMat->data.fl);

	cvNormalize(eigenValMat, eigenValMat, 1, 0, CV_L1, 0);
}


//////////////////////////////////
// loadFaceImgArray()
//
int loadFaceImgArray(char * filename)
{
	FILE * imgListFile = 0;
	char imgFilename[512];
	int iFace, nFaces=0;


	// open the input file
	if( !(imgListFile = fopen(filename, "r")) )
	{
		fprintf(stderr, "Can\'t open file %s\n", filename);
		return 0;
	}

	// count the number of faces
	while( fgets(imgFilename, 512, imgListFile) ) ++nFaces;
	rewind(imgListFile);

	// allocate the face-image array and person number matrix
	faceImgArr        = (IplImage **)cvAlloc( nFaces*sizeof(IplImage *) );
	personNumTruthMat = cvCreateMat( 1, nFaces, CV_32SC1 );

	// store the face images in an array
	for(iFace=0; iFace<nFaces; iFace++)
	{
		// read person number and name of image file
		fscanf(imgListFile,
			"%d %s", personNumTruthMat->data.i+iFace, imgFilename);

		// load the face image
		faceImgArr[iFace] = cvLoadImage(imgFilename, CV_LOAD_IMAGE_GRAYSCALE);

		if( !faceImgArr[iFace] )
		{
			fprintf(stderr, "Can\'t load image from %s\n", imgFilename);
			return 0;
		}
	}

	fclose(imgListFile);

	return nFaces;
}
// ----------------


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

// Código para recortar face

// Returns a new image that is a cropped version (rectangular cut-out)
// of the original image.
IplImage* cropImage(const IplImage *img, const CvRect region)
{
	IplImage *imageCropped;
	CvSize size;

	if (img->width <= 0 || img->height <= 0
		|| region.width <= 0 || region.height <= 0) {
		//cerr << "ERROR in cropImage(): invalid dimensions." << endl;
		exit(1);
	}

	if (img->depth != IPL_DEPTH_8U) {
		//cerr << "ERROR in cropImage(): image depth is not 8." << endl;
		exit(1);
	}

	// Set the desired region of interest.
	cvSetImageROI((IplImage*)img, region);
	// Copy region of interest into a new iplImage and return it.
	size.width = region.width;
	size.height = region.height;
	imageCropped = cvCreateImage(size, IPL_DEPTH_8U, img->nChannels);
	cvCopy(img, imageCropped);	// Copy just the region.

	return imageCropped;
}

// Código para redimensionar face
IplImage* resizeImage(const IplImage *origImg, int newWidth,
	int newHeight, bool keepAspectRatio)
{
	IplImage *outImg = 0;
	int origWidth;
	int origHeight;
	if (origImg) {
		origWidth = origImg->width;
		origHeight = origImg->height;
	}
	if (newWidth <= 0 || newHeight <= 0 || origImg == 0
		|| origWidth <= 0 || origHeight <= 0) {
		//cerr << "ERROR: Bad desired image size of " << newWidth
		//	<< "x" << newHeight << " in resizeImage().\n";
		exit(1);
	}

	if (keepAspectRatio) {
		// Resize the image without changing its aspect ratio,
		// by cropping off the edges and enlarging the middle section.
		CvRect r;
		// input aspect ratio
		float origAspect = (origWidth / (float)origHeight);
		// output aspect ratio
		float newAspect = (newWidth / (float)newHeight);
		// crop width to be origHeight * newAspect
		if (origAspect > newAspect) {
			int tw = (origHeight * newWidth) / newHeight;
			r = cvRect((origWidth - tw)/2, 0, tw, origHeight);
		}
		else {	// crop height to be origWidth / newAspect
			int th = (origWidth * newHeight) / newWidth;
			r = cvRect(0, (origHeight - th)/2, origWidth, th);
		}
		IplImage *croppedImg = cropImage(origImg, r);

		// Call this function again, with the new aspect ratio image.
		// Will do a scaled image resize with the correct aspect ratio.
		outImg = resizeImage(croppedImg, newWidth, newHeight, false);
		cvReleaseImage( &croppedImg );

	}
	else {

		// Scale the image to the new dimensions,
		// even if the aspect ratio will be changed.
		outImg = cvCreateImage(cvSize(newWidth, newHeight),
			origImg->depth, origImg->nChannels);
		if (newWidth > origImg->width && newHeight > origImg->height) {
			// Make the image larger
			cvResetImageROI((IplImage*)origImg);
			// CV_INTER_LINEAR: good at enlarging.
			// CV_INTER_CUBIC: good at enlarging.			
			cvResize(origImg, outImg, CV_INTER_LINEAR);
		}
		else {
			// Make the image smaller
			cvResetImageROI((IplImage*)origImg);
			// CV_INTER_AREA: good at shrinking (decimation) only.
			cvResize(origImg, outImg, CV_INTER_AREA);
		}

	}
	return outImg;
}

void doWebcam()
{
	IplImage *inputImg = cvLoadImage("C:\\imagemproc\\saida.bmp");
	//IplImage *inputImg = cvLoadImage("C:\\Users\\max\\Desktop\\EasyWebCam\\saida.bmp",CV_LOAD_IMAGE_GRAYSCALE);
	CvSeq * pFaceRectSeq;
	// Haar Cascade file, used for Face Detection.	
	// Modificado de haarcascade_frontalface_default para haarcascade_profileface
	char *faceCascadeFilename = "C:\\imagemproc\\WinFormCharpWebCam\\bin\\Release\\haarcascade_profileface.xml";
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

	//IplImage *imageCut;
	//imageCut = inputImg;

	if (i<pFaceRectSeq->total) 
	{
		for (i=0;i<=pFaceRectSeq->total;i++)
		{
			CvRect * r = (CvRect *)cvGetSeqElem(pFaceRectSeq,i);
			CvPoint pt1 = {r->x,r->y};
			CvPoint pt2 = {r->x +r->width  ,r->y+r->height};

			// Código para salvar imagem da face detectada
			//IplImage *imageCut;
			//imageCut = cropImage(inputImg, *r);
			//cvSaveImage("C:\\imagemproc\\saida_cut.bmp", imageCut);
			//cvReleaseImage(&imageCut);

			// Adiciona o retângulo na face
			cvRectangle(inputImg,pt1,pt2,CV_RGB(255,0,0),3,4,0);
		}
	}

	//cvNamedWindow( "Source", 1 );
	//cvShowImage( "Source", inputImg );
	//cvWaitKey(0);
	cvSaveImage("C:\\imagemproc\\saida2.bmp", inputImg);
	
	//Face Recognition
	// Either convert the image to greyscale, or use the existing greyscale image.
	/*IplImage *imageGrey;
	if (inputImg->nChannels == 3) {
		imageGrey = cvCreateImage( cvGetSize(inputImg), IPL_DEPTH_8U, 1 );
		// Convert from RGB (actually it is BGR) to Greyscale.
		cvCvtColor( inputImg, imageGrey, CV_BGR2GRAY );
	}
	else {
		// Just use the input image, since it is already Greyscale.
		imageGrey = inputImg;
	}*/

	// Resize the image to be a consistent size, even if the aspect ratio changes.
	//IplImage *imageProcessed;
	//imageProcessed = cvCreateImage(cvSize(inputImg->width, inputImg->height), IPL_DEPTH_8U, 1);
	// Make the image a fixed size.
	// CV_INTER_CUBIC or CV_INTER_LINEAR is good for enlarging, and
	// CV_INTER_AREA is good for shrinking / decimation, but bad at enlarging.
	//cvResize(imageGrey, imageProcessed, CV_INTER_LINEAR);

	// Give the image a standard brightness and contrast.
	//cvEqualizeHist(imageProcessed, imageProcessed);

	//.....  Use 'imageProcessed' for Face Recognition ....
	// teste
	//cvSaveImage("C:\\imagemproc\\saida3.bmp",imageGrey);
	//cvSaveImage("C:\\imagemproc\\saida4.bmp",imageProcessed);

	//if (imageGrey)
	//	cvReleaseImage(&imageGrey);
	//if (imageProcessed)
	//	cvReleaseImage(&imageProcessed);
	//---------------

	cvReleaseImage(&inputImg);
	if (pStorage) cvReleaseMemStorage(&pStorage);
	if(faceCascade) cvReleaseHaarClassifierCascade(&faceCascade);

	//Executado comandos do recognize
	//learn(); //Comentado o Recognize para testes
	//recognize();
}

void captureTest(int argn)
{
	IplImage *inputImg = cvLoadImage("C:\\imagemproc\\saida.bmp");
	CvSeq * pFaceRectSeq;
	char *faceCascadeFilename = "C:\\imagemproc\\WinFormCharpWebCam\\bin\\Release\\haarcascade_frontalface_default.xml";
	CvHaarClassifierCascade* faceCascade;
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

			//Código para salvar imagem da face detectada
			IplImage *imageCut;
			imageCut = cropImage(inputImg, *r);
			if(imageCut->width > 70 && imageCut->height > 70)
			{
				imageCut = resizeImage(imageCut, 115, 115, true);
				IplImage *imageGrey;
				if (imageCut->nChannels == 3) {
					imageGrey = cvCreateImage( cvGetSize(imageCut), IPL_DEPTH_8U, 1 );
					// Convert from RGB (actually it is BGR) to Greyscale.
					cvCvtColor( imageCut, imageGrey, CV_BGR2GRAY );
				}
				else {
					// Just use the input image, since it is already Greyscale.
					imageGrey = imageCut;
				}

				if(argn == 1)
				{
					cvSaveImage("C:\\imagemproc\\WinFormCharpWebCam\\bin\\Release\\test1_show.jpg", imageCut);
					cvSaveImage("C:\\imagemproc\\WinFormCharpWebCam\\bin\\Release\\test1.jpg", imageGrey);
				}else if(argn == 2)
				{
					cvSaveImage("C:\\imagemproc\\WinFormCharpWebCam\\bin\\Release\\test2_show.jpg", imageCut);
					cvSaveImage("C:\\imagemproc\\WinFormCharpWebCam\\bin\\Release\\test2.jpg", imageGrey);
				}

				cvReleaseImage(&imageGrey);
			}
			cvReleaseImage(&imageCut);
		}
	}

	cvReleaseImage(&inputImg);
	if (pStorage) cvReleaseMemStorage(&pStorage);
	if(faceCascade) cvReleaseHaarClassifierCascade(&faceCascade);
}

int main(int argc, char** argv)
{
	if(!strcmp(argv[1], "webcam"))
		doWebcam();
	else if(!strcmp(argv[1], "captureTest1"))
		captureTest(1);
	else if(!strcmp(argv[1], "captureTest2"))
		captureTest(2);
	else if(!strcmp(argv[1], "recognize"))
	{
		learn();
		recognize();
	}
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