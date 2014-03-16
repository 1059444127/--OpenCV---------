/*
 * plotImhist.cpp
 * author:李晓波
 * descriptin: to cut five areas and
 * processing them through calcHistogram.
 *
 *
 * have passed the test at 11/5/2012.
 * Tester : 李晓波
 * */

#include "opencvImageEnhanceHeader.h"
void plotImhist(IplImage *pImg,IplImage *sourceImg,char winName[])
{
	   //IplImage *sourceImg=cvLoadImage("sim_cyst.png", CV_LOAD_IMAGE_GRAYSCALE);
	   //IplImage *imhistImage=cvLoadImage("cyst.pgm", CV_LOAD_IMAGE_GRAYSCALE);
	    IplImage *imhistImage=pImg;
		//speckle area
		IplImage *speckle;
		//edge between speckle and hyper
		IplImage *edgeSH;
		//edge between speckle and cyst
		IplImage *edgeSC;
		//hyper area
		IplImage *hyper;
		//cyst
		IplImage *cyst;



		IplImage *speckleHist=NULL;
		IplImage *edgeSHHist=NULL;
		IplImage *edgeSCHist=NULL;
		IplImage *hyperHist=NULL;
		IplImage *cystHist=NULL;



		//裁剪speckle are
		cvSetImageROI(imhistImage,cvRect(217,124,15,15));//set the ROI area
		speckle=cvCreateImage(cvSize(15,15),IPL_DEPTH_8U,imhistImage->nChannels);
		cvCopy(imhistImage,speckle,0);//copy the image to the ROI area
		cvResetImageROI(imhistImage);//reset the ROI

		//裁剪edge between speckle and hyper
		cvSetImageROI(imhistImage,cvRect(149 ,225, 15, 15));
		edgeSH=cvCreateImage(cvSize(15,15),IPL_DEPTH_8U,imhistImage->nChannels);
		cvCopy(imhistImage,edgeSH,0);
		cvResetImageROI(imhistImage);

		//裁剪edge between speckle and cyst
		cvSetImageROI(imhistImage,cvRect(252 ,84, 15, 15));
		edgeSC=cvCreateImage(cvSize(15,15),IPL_DEPTH_8U,imhistImage->nChannels);
		cvCopy(imhistImage,edgeSC,0);
		cvResetImageROI(imhistImage);

		//裁剪hyper area
		cvSetImageROI(imhistImage,cvRect(162 ,162, 15, 15));
		hyper=cvCreateImage(cvSize(15,15),IPL_DEPTH_8U,imhistImage->nChannels);
		cvCopy(imhistImage,hyper,0);
		cvResetImageROI(imhistImage);

		//裁剪cyst
		cvSetImageROI(imhistImage,cvRect(260 ,163, 15, 15));
		cyst=cvCreateImage(cvSize(15,15),IPL_DEPTH_8U,imhistImage->nChannels);
		cvCopy(imhistImage,cyst,0);
		cvResetImageROI(imhistImage);



		/*cvNamedWindow("sourceImg",1);
		cvShowImage("sourceImg",sourceImg);
		cvWaitKey(0);
		cvReleaseImage(&sourceImg);
		cvDestroyWindow("sourceImg");*/

			/*cvNamedWindow("speckle",1);
			cvShowImage("speckle",speckle);
			cvNamedWindow("edgeSH",1);
			cvShowImage("edgeSH",edgeSH);
			cvNamedWindow("edgeSC",1);
			cvShowImage("edgeSC",edgeSC);
			cvNamedWindow("hyper",1);
			cvShowImage("hyper",hyper);
			cvNamedWindow("cyst",1);
			cvShowImage("cyst",cyst);
			cvWaitKey(0);
			cvReleaseImage(&speckle);
			cvDestroyWindow("speckle");
			cvReleaseImage(&edgeSH);
			cvDestroyWindow("edgeSH");
			cvReleaseImage(&edgeSC);
			cvDestroyWindow("edgeSC");
			cvReleaseImage(&hyper);
			cvDestroyWindow("hyper");
			cvReleaseImage(&cyst);
			cvDestroyWindow("cyst");*/


		speckleHist=calcHistogram(speckle);
		edgeSHHist=calcHistogram(edgeSH);
		edgeSCHist=calcHistogram(edgeSC);
		hyperHist=calcHistogram(hyper);
		cystHist=calcHistogram(cyst);

		//writing the title to the image.
		CvFont ImageEnhanceFont;
		cvInitFont(&ImageEnhanceFont,CV_FONT_HERSHEY_COMPLEX,0.5f,0.5f,0,1,8);
		cvPutText(sourceImg,"Source Image",cvPoint(0,15),&ImageEnhanceFont,CV_RGB(255,255,255));
		cvPutText(speckleHist,"AREA A",cvPoint(0,15),&ImageEnhanceFont,CV_RGB(0,0,0));
		cvPutText(edgeSHHist,"AREA B",cvPoint(0,15),&ImageEnhanceFont,CV_RGB(0,0,0));
		cvPutText(edgeSCHist,"AREA C",cvPoint(0,15),&ImageEnhanceFont,CV_RGB(0,0,0));
		cvPutText(hyperHist,"AREA D",cvPoint(0,15),&ImageEnhanceFont,CV_RGB(0,0,0));
		cvPutText(cystHist,"AREA E",cvPoint(0,15),&ImageEnhanceFont,CV_RGB(0,0,0));


		multiWin(7,winName,sourceImg,speckleHist,edgeSHHist,edgeSCHist,hyperHist,cystHist);
}
