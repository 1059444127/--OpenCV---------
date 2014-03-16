/*multiWin.cpp
 * Author:李晓波
 * Description:to show several image through ROI method.
 *
 * have passed the test at 11/5/2012.
 * Testor:李晓波
 *
 * */


#include "opencvImageEnhanceHeader.h"


    void multiWin( int nArgs,char winName[],IplImage *sourceImg, ...)
    {
    	//used for writing words.
    	/*CvFont ImageEnhanceFont;
    	cvInitFont(&ImageEnhanceFont,CV_FONT_HERSHEY_COMPLEX,0.5f,0.5f,0,1,8);*/


       // img - Used for getting the arguments
       IplImage *img;
       //used for the convert...
       IplImage *img2;

       // DispImage - the image in which input images are to be copied
       IplImage *DispImage;

       //size  just  to  define the size of a  image which was shown in the window
       int sizeW=sourceImg->width;//the size which refer to the width of the image
       int sizeH=sourceImg->height;//the size which refer to the heigth of the image
       int i;
       int m=0, n=0;//locate the position at the Histogram window.


       //w - Maximum number of images in a row
       //h - Maximum number of images in a column
       int w, h;

       // If the number of arguments is lesser than 0 or greater than 12
       // return without displaying
       if(nArgs-1 <= 0) {
          printf("Number of arguments too small....\n");
          return;
          }
       else if(nArgs-1 > 12) {
          printf("Number of arguments too large....\n");
          return;
          }

       // Determine the size of the image,
       // and the number of rows/cols
       // from number of arguments
       else if ((nArgs-1) == 1) {
          w = h = 1;
         }
       else if ((nArgs-1) == 2) {
          w = 2; h = 1;
         }
       else if ((nArgs-1)== 3 || (nArgs-1) == 4) {
          w = 2; h = 2;
         }
       else if ((nArgs-1) == 5 || (nArgs-1) == 6) {
          w = 3; h = 2;
         }
       else if ((nArgs-1) == 7 || (nArgs-1) == 8) {
          w = 4; h = 2;
         }
       else {
          w = 4; h = 3;
         }

       cvNamedWindow(winName,1);
       //resize the window base on the image size...
       //the space of every two images are 5 pix
       cvResizeWindow(winName,-5+w*(sizeW+5),-5+h*(sizeH+5));

printf("----sizeW=%d-----sizeH=%d\n-----",sizeW,sizeH);

       // Create a new 3 channel image
       DispImage = cvCreateImage( cvSize(-5+w*(sizeW+5),-5+h*(sizeH+5)), 8, 3 );

       //assign the first image to the DispImage
       // Set the image ROI to display the current image
       cvSetImageROI(DispImage, cvRect(0, 0, sizeW, sizeH));

       img2=cvCreateImage(cvGetSize(sourceImg),8,3);

	 if(1==sourceImg->nChannels){
	  cvCvtColor(sourceImg,img2,CV_GRAY2RGB);
	  cvCopy(img2, DispImage);
	  cvReleaseImage(&img2);
	 }else{
		  cvCopy(sourceImg,DispImage);
	 }
	 cvReleaseImage(&sourceImg);
     cvResetImageROI(DispImage);


     cvShowImage(winName, DispImage);
     cvWaitKey(0);



       // Used to get the arguments
       //C语言中的可变参数
       va_list args;
       va_start(args, sourceImg);

       // Loop for nArgs number of arguments

       for (i = 0; i < nArgs-2; i++) {

          // Get the Pointer to the IplImage
          img = va_arg(args, IplImage*);

          // Check whether it is NULL or not
          // If it is NULL, release the image, and return
          if(img == 0) {
             printf("Invalid arguments");
             cvReleaseImage(&DispImage);
             return;
          }

/*cvNamedWindow("test",1);
cvShowImage("test",img);
cvWaitKey(0);
printf("x=%d,y=%d\n",x,y);
printf("img->nChannerl=%d\n",img->nChannels);*/

          // Used to align the images.Locate the position.
          if((nArgs-1) == 5 || (nArgs-1) == 6){
			  if(3>i+1)
			  {
				  m = 5*(i>0?i+1:1)+sizeW * ((i+1) % w);
				  n = sizeH * ((i+1) / w);
			  }else if(2==i){
				  m=sizeW*((i+1) % w);
				  n=5+ sizeH * ((i+1) / w);
			  }else{
				  m = 5*((i-3)>0?(i-3)+1:1)+sizeW * ((i+1) % w);
				  n = 5+sizeH * ((i+1) / w);
			  }
          }else if((nArgs-1)== 3 || (nArgs-1) == 4){
        	  if(0==i)
        	  {
        		  m=5+sizeW;
        		  n=0;
        	  }else{
        		  m=5*(i-1)+sizeW*(i-1);
        		  n=5+sizeH;
        	  }
          }

          // Set the image ROI to display the current image
          cvSetImageROI(DispImage, cvRect(m, n, sizeW, sizeH));

          // Resize the input image and copy the it to the Single Big Image
          img2=cvCreateImage(cvGetSize(img),img->depth,3);


          //if this is a 1-channel image,then  covert to 3-channel image.
          if(1==img->nChannels){
        	  cvCvtColor(img,img2,CV_GRAY2RGB);
        	  cvResize(img2, DispImage);
//printf("resize successful...\n");
        	  cvReleaseImage(&img2);
          }else{
        	  //if this is the 3-channel image ,then resize it to the ROI area on the Histogram window.
        		  cvResize(img,DispImage);
//printf("resize successful!!!\n");
          }
          cvReleaseImage(&img);


          // Reset the ROI in order to display the next image
          cvResetImageROI(DispImage);

          //show image every once,when hit the keyboard.
          cvShowImage( winName, DispImage);
          cvWaitKey(0);
       }

       // And show the Single Big Image
		 cvShowImage( winName, DispImage);
		 cvWaitKey(0);

       // End the number of arguments
       va_end(args);


       // Release the Image Memory
       /*cvReleaseImage(&img);
       cvReleaseImage(&DispImage);
       cvDestroyWindow(winName);*/

    }
