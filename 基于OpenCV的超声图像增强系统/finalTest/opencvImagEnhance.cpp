/*
 * Description:
 * 		Local contrast enhancement using:
 * 		A.morphological top hat transformation
 * 		B.histogram matching
 * */
#include "opencvImageEnhanceHeader.h"
int main( int argc, char** argv )
{
		IplImage *orgIM=cvLoadImage("cyst.pgm", CV_LOAD_IMAGE_GRAYSCALE);

		IplImage *corrIM=cvCreateImage(cvSize(orgIM->width,orgIM->height),IPL_DEPTH_64F,1);
		cvZero(corrIM);

		IplImage *factorIM=cvCreateImage(cvSize(orgIM->width,orgIM->height),IPL_DEPTH_64F,1);
		cvZero(factorIM);

		IplImage *processedIM=cvCreateImage(cvGetSize(orgIM),IPL_DEPTH_8U,1);
		cvZero(processedIM);

		IplImage *afterProcessedIM=cvLoadImage("afterProcessedIM.png",CV_LOAD_IMAGE_GRAYSCALE);
		IplImage *beforeProcessedIM=cvLoadImage("beforeProcessedIM.png",CV_LOAD_IMAGE_GRAYSCALE);

		char sourceIMWinName[]="sourceIM";
		char processedWinName[]="processedIM";


		plotImhist(orgIM,beforeProcessedIM,sourceIMWinName);
		myCorrfactor(orgIM,15,corrIM,factorIM);

		contrastEnhancement(orgIM,corrIM,factorIM,processedIM);
		plotImhist(processedIM,afterProcessedIM,processedWinName);


//kidney

		IplImage *kidney=cvLoadImage("kidney.pgm",CV_LOAD_IMAGE_GRAYSCALE);
		IplImage *corrIMKidney=cvCreateImage(cvSize(kidney->width,kidney->height),IPL_DEPTH_64F,1);
		cvZero(corrIMKidney);

		IplImage *factorIMKidney=cvCreateImage(cvSize(kidney->width,kidney->height),IPL_DEPTH_64F,1);
		cvZero(factorIMKidney);

		IplImage *processedIMKidney=cvCreateImage(cvGetSize(kidney),IPL_DEPTH_8U,1);
		cvZero(processedIMKidney);
		myCorrfactor(kidney,15,corrIMKidney,factorIMKidney);
		contrastEnhancement(kidney,corrIMKidney,factorIMKidney,processedIMKidney);
//neck
		IplImage *neck=cvLoadImage("neck.pgm",CV_LOAD_IMAGE_GRAYSCALE);
		IplImage *corrIMNeck=cvCreateImage(cvSize(neck->width,neck->height),IPL_DEPTH_64F,1);
		cvZero(corrIMNeck);

		IplImage *factorIMNeck=cvCreateImage(cvSize(neck->width,neck->height),IPL_DEPTH_64F,1);
		cvZero(factorIMNeck);

		IplImage *processedIMNeck=cvCreateImage(cvGetSize(neck),IPL_DEPTH_8U,1);
		cvZero(processedIMNeck);
		myCorrfactor(neck,15,corrIMNeck,factorIMNeck);
		contrastEnhancement(neck,corrIMNeck,factorIMNeck,processedIMNeck);



		/*cvNamedWindow("processedIM",1);
		cvShowImage("processedIM",processedIM);
		cvWaitKey(0);
		cvReleaseImage(&processedIM);
		cvDestroyWindow("processedIM");*/




}
