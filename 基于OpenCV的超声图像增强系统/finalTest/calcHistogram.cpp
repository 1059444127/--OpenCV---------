#include "opencvImageEnhanceHeader.h"
IplImage *calcHistogram(IplImage *pImg)//计算灰度直方图  ,pImg已经是 单通道图片了.
{

	    //IplImage *src = pImg;
	    IplImage *histImage=0;//灰度直方图
	    CvHistogram *hist = 0;

	    int hdims = 32;     // 划分HIST的个数，越高越精确,灰度值范围。
	    float hranges_arr[] = {0,255};//浮点数对，
	    float* hranges = hranges_arr;
	    double bin_w;//bin_w 为直方图条的宽度

	    float max_val;//直方图的最大值
	    int i,j;
	    double histBins=0;

	    hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );  // create直方图

	    cvCalcHist(&pImg,hist,0,0);// 计算直方图

	    cvGetMinMaxHistValue( hist, 0, &max_val, NULL, NULL );  // 只找最大值

	    printf("max_val = %f\n",max_val);

	    //为了方便显示，直方图的大小和源图像的大小一样，203*279 pix

	    histImage = cvCreateImage(
	   	      cvSize(203,279),
	   	      IPL_DEPTH_8U,
	   	      3
	   	    );      //直方图

	    cvZero(histImage);

	   /* cvConvertScale( hist->bins,
	    		hist->bins, max_val ? 255. / max_val : 0., 0 ); // 缩放 bin 到区间 [0,255]*/


	   	    cvSet(histImage,cvScalarAll(255),0);//图片背景 设置为 白色

	   	    bin_w = (double)histImage->width/hdims;//条的宽度。


	   	    //获取BIN 的 总数


	   	 for(j=0;j<hdims;j++)
	   	 {
	   		histBins+=cvGetReal1D(hist->bins,j);

	   	 }


	    // 画直方图
	    for( i = 0; i < hdims; i++ )
	    {
	    	 double percent = (cvGetReal1D(hist->bins,i)/histBins);//某一个灰度值的像素点的比值

	    	 //直方图中i点的高度,*3是为了将每个条的高度扩大3倍，以便观察直方图。
	        double val = (percent *histImage->height )*3;

	        CvScalar color = CV_RGB(255,0,0);
	        CvPoint px=cvPoint(i*bin_w,histImage->height);//x点坐标

	        //对角线y点坐标,此处 减去2 是为了给每个直方图 之间留出 2pix 的 空隙
	        CvPoint py=cvPoint((i+1)*bin_w-2,(histImage->height-val));
	        cvRectangle( histImage, px,py,color, CV_FILLED, 8, 0 );
	    }



	    /*cvNamedWindow("Histogram",1);
	    cvShowImage( "Histogram", histImage );
	    cvWaitKey(0);
	    cvDestroyWindow("Histogram");
	    cvReleaseImage( &histImage );*/
	    return histImage;

}

