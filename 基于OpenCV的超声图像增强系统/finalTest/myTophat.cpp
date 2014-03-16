#include "opencvImageEnhanceHeader.h"
#include<math.h>

IplImage * myTophat(IplImage *orgIM,IplImage *corrIM,IplImage *factorIM,CvMat *SE,double Threshold)
{
	int m=orgIM->height;//图像的行数（像素）
	int n=orgIM->width;//图像的列数(像素)
	int se_m=cvGetSize(SE).height;//获取矩阵的行(像素)
	int se_n=cvGetSize(SE).width;//获取矩阵的列（像素）
	int se_r=ceil(se_m/2);
	double s_t=Threshold;

	int k=0;
	double MinValue=0;
	double MaxValue=0;

	CvScalar s;


//printf("-----se_r=%d\n----------",se_r);

/*IplImage *test=cvCreateImage(cvSize(n,m),8,1);
printf("---m=%d  ,   n=%d\n",m,n);
printf("---se_m=%d  ,se_n=%d\n",se_m,se_n);
printf("----s_t=%f\n-----",s_t);*/
/*cvMinMaxLoc(corrIM,&MinValue,&MaxValue,NULL,NULL);
printf("AScale---MinValue=%f,MaxValue=%f\n",MinValue,MaxValue);
cvConvertScale(corrIM,test,255);
cvNamedWindow("corrIMtest",1);
cvShowImage("corrIMtest",test);
cvWaitKey(0);
//cvReleaseImage(&test);
cvDestroyWindow("corrIMtest");*/

/*printf("+++++++++++++++++++++++++++\n");
for(int r=0;r<se_m;++r)
		{
			for(int q=0;q<se_n;++q)
				printf("%d    %d   %d\n",r,q,(int)cvGet2D(SE,r,q).val[0]);
				//printf("r=%d  q=%d\n",r,q);
		}

printf("---------------------------------------------------\n");*/

	/*
	 * tophat----step1->erode image	 *
	 * */



	IplImage *erodeIM=cvCreateImage(cvSize(n,m),8,1);
	cvZero(erodeIM);

	IplImage *temp=cvCreateImage(cvSize(se_m*se_n,1),8,1);
	cvZero(temp);

	for(int x=0;x<m;++x)
	{
		for(int y=0;y<n;++y)
		{

			if((x>se_r && x<m-se_r) && (y>se_r && y<n-se_r) &&(cvGet2D(corrIM,x,y).val[0]<s_t))
			{


				/*printf("---x=%d  ,y=%d  ,s_t=%f\n",x,y,s_t);
				printf("---cvGet2D(corrIM,x,y).val[0]=%f\n---",cvGet2D(corrIM,x,y).val[0]);
*/
				k=0;
				for(int i=-se_r;i<=se_r;++i)
				{
					for(int j=-se_r;j<=se_r;++j)
					{

						//printf("i=%d,j=%d,x+i=%d,y+j=%d\n",i,j,x+i,y+j);
						s=cvGet2D(orgIM,x+i,y+j);
						//printf("k=%d ,s.val=%f in step1\n",k,s.val[0]);
						cvSet2D(temp,0,k,s);
						k=k+1;
					}
				}

				cvMinMaxLoc(temp,& MinValue,NULL,NULL,NULL);//获取图像中某像素的最小值
				s.val[0]=MinValue;
//printf("MinValue=%f\n",MinValue);
				cvSet2D(erodeIM,x,y,s);
			}
			else
				cvSet2D(erodeIM,x,y,cvGet2D(orgIM,x,y));
		}

	}


printf("+++++++++after step1+++++++++++++\n");
	/*
	 * tophat---step2->dilate the eroded image
	 * */


	IplImage *dilateIM=cvCreateImage(cvSize(n,m),IPL_DEPTH_8U,1);
	cvZero(temp);

	for(int x=0;x<m;++x)
	{
			for(int y=0;y<n;++y)
			{
				if((x>se_r && x<m-se_r) && (y>se_r && y<n-se_r) &&(cvGet2D(corrIM,x,y).val[0]<s_t))
				{
					k=0;

					for(int i=-se_r;i<=se_r;++i)
					{
						for(int j=-se_r;j<=se_r;++j)
						{
							s=cvGet2D(erodeIM,x+i,y+j);
//printf("k=%d ,s.val=%f\n",k,s.val[0]);
							cvSet2D(temp,0,k,s);
							k=k+1;
						}
					}
					cvMinMaxLoc(temp,NULL,&MaxValue,NULL,NULL);//获取图像中某像素的最小值
					s.val[0]=MaxValue;
//printf("s.val==%f\n",MaxValue);
					cvSet2D(dilateIM,x,y,s);
				}
				else
					cvSet2D(dilateIM,x,y,cvGet2D(erodeIM,x,y));
			}
	}

printf("-------------after step2....-------------------\n");
	IplImage *openingIM=dilateIM;
	IplImage *whiteTophatIM=cvCreateImage(cvSize(n,m),IPL_DEPTH_64F,1);


/*cvNamedWindow("dilateIM",1);
cvShowImage("dilateIM",dilateIM);
cvWaitKey(0);
cvReleaseImage(&dilateIM);
cvDestroyWindow("dilateIM");
cvNamedWindow("openingIM",1);
cvShowImage("openingIM",openingIM);
cvWaitKey(0);
cvReleaseImage(&openingIM);
cvDestroyWindow("openingIM");*/


	for(int a=0;a<m;++a)
	{
		for(int b=0;b<n;++b)
		{
			s.val[0]=(cvGet2D(orgIM,a,b).val[0]-cvGet2D(openingIM,a,b).val[0])
					*cvGet2D(factorIM,a,b).val[0];

			cvSet2D(whiteTophatIM,a,b,s);
		}

	}

/*cvNamedWindow("whiteTophatIM",0);
cvShowImage("whiteTophatIM",openingIM);
cvWaitKey(0);
//cvReleaseImage(&whiteTophatIM);
cvDestroyWindow("whiteTophatIM");*/

	return  whiteTophatIM;


}
