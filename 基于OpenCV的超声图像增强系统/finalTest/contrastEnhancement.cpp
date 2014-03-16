#include "opencvImageEnhanceHeader.h"

void contrastEnhancement(IplImage *orgIM,IplImage *corrIM,IplImage *factorIM,IplImage *processedIM)
{

	int m=orgIM->height;
	int n=orgIM->width;
	//CvScalar s;
	int *p;
	CvMat SE;
	double corrTH=0.93;

	double MaxValue=0.0,MinValue=0.0;

	IplImage *enhancedIM=cvCreateImage(cvSize(orgIM->width,orgIM->height),IPL_DEPTH_64F,1);
	cvZero(enhancedIM);

	IplImage *A=cvCreateImage(cvSize(n,m),IPL_DEPTH_64F,1);
	cvZero(A);

	IplImage *resultIM=cvCreateImage(cvSize(n,m),IPL_DEPTH_8U,1);
	cvZero(resultIM);

	//A./3
	IplImage *AScale=cvCreateImage(cvSize(n,m),IPL_DEPTH_64F,1);
	cvZero(AScale);
	//uint(A./3)
	IplImage *AInt=cvCreateImage(cvSize(n,m),IPL_DEPTH_8U,1);
	cvZero(AInt);//

			for(int i=5;i<=9;i=i+2)
			{
				if(NULL==(p=(int*)malloc(i*i*sizeof(int))))
					printf("malloc error!\n");
				for(int j=0;j<i*i;++j)
				{
					p[j]=1.0;//用于创建矩阵的数组
//printf("p[%d]=%d\n",j,p[j]);
				}
				SE=cvMat(i,i,CV_32SC1,p);//创建全一矩阵

	/*for(int r=0;r<i;++r)
		{
			for(int q=0;q<i;++q)
				printf("%d    %d   %d\n",r,q,(int)cvGet2D(&SE,r,q).val[0]);
		}*/


				enhancedIM=myTophat(orgIM,corrIM,factorIM,&SE,corrTH);

				/*for(int a =0;a<m;a++)
				{
					for(int b=0;b<n;b++)
					{
						s.val[0]=0.5*cvGet2D(enhancedIM,a,b).val[0]
						         +cvGet2D(A,a,b).val[0];
						cvSet2D(A,a,b,s);
					}

				}*/
				cvAddWeighted(A,1,enhancedIM,0.5,0,A);


/*cvNamedWindow("A",1);
cvShowImage("A",A);
cvWaitKey(0);*/


				free(p);
			}

cvMinMaxLoc(A,&MinValue,&MaxValue,NULL,NULL);
printf("A---MinValue=%f,MaxValue=%f\n",MinValue,MaxValue);
			cvConvertScale(A,AScale,1.0/3);

cvMinMaxLoc(AScale,&MinValue,&MaxValue,NULL,NULL);
printf("AScale---MinValue=%f,MaxValue=%f\n",MinValue,MaxValue);
			cvConvertScale(AScale,AInt,255/(MaxValue-MinValue));

cvMinMaxLoc(AInt,&MinValue,&MaxValue,NULL,NULL);
printf("AInt---MinValue=%f,MaxValue=%f\n",MinValue,MaxValue);
			cvAddWeighted(orgIM,1,AInt,1,0,resultIM);

			cvCopy(resultIM,processedIM);
			//processedIM=resultIM;

/*cvNamedWindow("processedIM",1);
cvShowImage("processedIM",processedIM);
cvWaitKey(0);
cvDestroyWindow("processedIM");*/



			//writing the title to the image.
					CvFont ImageEnhanceFont;
					cvInitFont(&ImageEnhanceFont,CV_FONT_HERSHEY_COMPLEX,0.5f,0.5f,0,1,8);
					cvPutText(orgIM,"Source Image",cvPoint(0,15),&ImageEnhanceFont,CV_RGB(0,0,0));
					cvPutText(resultIM,"resultIM",cvPoint(0,15),&ImageEnhanceFont,CV_RGB(0,0,0));
					char winName[]="Enhancement";

					IplImage *EqualizeIM=cvCreateImage(cvGetSize(orgIM),IPL_DEPTH_8U,1);
					cvEqualizeHist(orgIM,EqualizeIM);
					cvPutText(EqualizeIM,"EqualizeIM",cvPoint(0,15),&ImageEnhanceFont,CV_RGB(0,0,0));


					multiWin(4,winName,orgIM,resultIM,EqualizeIM);


			/*cvNamedWindow("A",1);
			cvShowImage("A",A);
			cvWaitKey(0);
			cvNamedWindow("AScale",1);
			cvShowImage("AScale",AScale);
			cvWaitKey(0);
			cvNamedWindow("AInt",1);
			cvShowImage("AInt",AInt);
			cvWaitKey(0);
			cvNamedWindow("resultIM",1);
			cvShowImage("resultIM",resultIM);
			cvWaitKey(0);
			cvReleaseImage(&A);
			cvDestroyWindow("A");
			cvReleaseImage(&AScale);
			cvDestroyWindow("AScale");
			cvReleaseImage(&AInt);
			cvDestroyWindow("AInt");
			cvReleaseImage(&resultIM);
			cvDestroyWindow("resultIM");*/
			//multiWinContrastEnhancement(6,orgIM,A,AScale,AInt,resultIM,factorIM);

}
