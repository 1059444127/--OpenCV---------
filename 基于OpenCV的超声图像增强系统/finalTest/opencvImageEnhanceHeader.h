#include "cxcore.h"
#include "highgui.h"
#include "cv.h"
#include <stdarg.h>  //VA_LIST 可变参数需要用到



//相关函数申明
IplImage *calcHistogram(IplImage *);
void multiWin(int ,char winName[],IplImage *,...);
void plotImhist(IplImage *,IplImage *,char []);
void myCorrfactor(IplImage *,int ,IplImage *,IplImage *);
IplImage * myTophat(IplImage *,IplImage *,IplImage *,CvMat *,double);
void contrastEnhancement(IplImage *,IplImage *,IplImage *,IplImage*);


