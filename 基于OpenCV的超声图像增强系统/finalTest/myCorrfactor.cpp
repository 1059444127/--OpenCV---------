

#include "opencvImageEnhanceHeader.h"
void myCorrfactor(IplImage *pImg,int spkWindow,IplImage *corrIM,IplImage *factorIM)
{

    //just for  test...
	IplImage *test=cvCreateImage(cvGetSize(corrIM),IPL_DEPTH_8U,1);
	cvZero(test);

	IplImage *corrOrgImg=pImg;
	IplImage *subCorrImg=0;//stand for the several area cut from the corrOrgImg

	//a sub-area from the special area of the original image
	IplImage *speckleImg=0;
	CvHistogram *speckleHist=0;
	CvHistogram *subCorrHist;//某子区域的直方图
	int hdims = 32;     // 划分HIST的个数，越高越精确,灰度值范围。
	float hranges_arr[] = {0,255};//浮点数对，
	float* hranges = hranges_arr;

	double sum=0;

	double MaxValue=0.0,MinValue=0.0;


	double Beta=20*log(10)/(20*(0.5*15)*(0.5*15));
printf("Beta=%f\n",Beta);


	//设置ROI 兴趣区域 裁剪源图像中某个15X15区域 给speckleImg
	cvSetImageROI(corrOrgImg,cvRect(215,80,spkWindow,spkWindow));
	speckleImg=cvCreateImage(cvSize(spkWindow,spkWindow),IPL_DEPTH_8U,corrOrgImg->nChannels);
	cvCopy(corrOrgImg,speckleImg,0);
	cvResetImageROI(corrOrgImg);

/*cvNamedWindow("speckleImg",1);
cvShowImage("speckleImg",speckleImg);
cvWaitKey(0);
cvReleaseImage(&speckleImg);
cvDestroyWindow("speckleImg");
multiWin(1,calcHistogram(speckleImg));
*/


	//get the histogram information of the 15X15 area
	speckleHist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );
	cvCalcHist(&speckleImg,speckleHist,0,0);//calculate the histogram of speckleImg


	int m=corrOrgImg->height;//rows of the image（pix）.
	int n=corrOrgImg->width;//cols of the image(pix).


printf("m=%d\n",m);
printf("n=%d\n",n);


//processing each pixel

	for(int i=0;i<m;++i)
	{
		for(int j =0;j<n;++j)
		{
			if((i+spkWindow)<=m&&(j+spkWindow)<=n)
			{
				cvSetImageROI(corrOrgImg,cvRect(j,i,spkWindow,spkWindow));
				subCorrImg=cvCreateImage(cvSize(spkWindow,spkWindow),IPL_DEPTH_8U,corrOrgImg->nChannels);
				cvCopy(corrOrgImg,subCorrImg,0);
				cvResetImageROI(corrOrgImg);

/*cvNamedWindow("subCorrImg",1);
cvShowImage("subCorrImg",subCorrImg);
cvWaitKey(0);
cvReleaseImage(&subCorrImg);
cvDestroyWindow("subCorrImg");*/

				subCorrHist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );  // create直方图,1表示直方图包含得维数
				cvCalcHist(&subCorrImg,subCorrHist,0,0);//计算直方图

				sum=0;
				for(int k=0;k<hdims;++k)
				{

					double x=cvGetReal1D(speckleHist->bins,k)
							-cvGetReal1D(subCorrHist->bins,k);
//printf("x=%f\n",x);

					x=x*x;

						sum+=exp(-Beta*x);

//printf("-------sum=%f\n",sum);
				}

				sum=sum/hdims;
				CvScalar s=cvGet2D(corrIM,i+spkWindow/2,j+spkWindow/2);
									s.val[0]=sum;
//printf("s.val[0]=%f\n",s.val[0]);
									cvSet2D(corrIM,i+7,j+7,s);
			}
		}
	}

	cvMinMaxLoc(corrIM,&MinValue,&MaxValue,NULL,NULL);//获取图像中某像素的最大值
//printf("MinValue=%f   MaxValue=%f\n",MinValue,MaxValue);
	cvConvertScale(corrIM,test,255/(MaxValue-MinValue));

/*cvNamedWindow("corrIM",1);
cvShowImage("corrIM",test);
cvWaitKey(0);
cvReleaseImage(&test);
cvDestroyWindow("corrIM");*/


	double corrTH=0.75*MaxValue;

printf("MaxValue=%f\n",MaxValue);
printf("corrTH=%f\n",corrTH);

	double count=0;

	for(int x=0;x<m;++x)
	{
		for(int y=0;y<n;++y)
		{
			if((x>7&&x<m-7)&&(y>7&&y<n-7)&&cvGet2D(corrIM,x,y).val[0]<corrTH)
			{
				count=0;
				for(int a=-7;a<=7;++a)
				{
					for(int b=-7;b<=7;++b)
					{
						if(cvGet2D(corrIM,x+a,y+b).val[0]<corrTH)
							count=count+1;
					}

				}
//printf("count = %f\n",count);
				CvScalar s=cvGet2D(factorIM,x,y);
				s.val[0]=count/255;
/*printf("count = %f\n",count);
printf("s.val[0]=%f\n",s.val[0]);*/
				cvSet2D(factorIM,x,y,s);

//cvMinMaxLoc(factorIM,& MinValue,& MaxValue,& MinLocation,& MaxLocation);//获取图像中某像素的最大值

			}



		}


	}


	/*cvNamedWindow("factorIM",1);
	cvShowImage("factorIM",factorIM);
	cvWaitKey(0);
	cvReleaseImage(&factorIM);
	cvDestroyWindow("factorIM");*/


/*
printf("MaxValue    2=%f\n",MaxValue);
printf("MinValue    2=%f\n",MinValue);
*/
}
