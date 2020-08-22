#include "macrotypedef.h"

#include "math.h"



#define qd_num 3

#define dc_num 3

#define xhj_num 3

/*

	Read,Write Local address function:

  	int ReadLocal( const char *type, int addr, int nRegs, void *buf, int flag  );

	int WriteLocal( const char *type, int addr, int nRegs, void *buf , int flag );



	Parameter:     type     is the string of "LW","LB" etc;

								address is the Operation address ;

 								nRegs    is the length of read or write ;

								buf        is the buffer which store the reading or writing data;

 								flag       is 0,then codetype is BIN,is 1  then codetype is BCD;

	return value : 1  ,Operation success

 								0,  Operation fail.



 	eg: read the value of local lw200 and write it to the lw202,with the codetype BIN,

		The code is :



    	short buf[2] = {0};

		ReadLocal("LW", 200, 2, (void*)buf, 0);

		WriteLocal("LW", 202, 2, (void*)buf, 0);

*/

int MacroEntry()

{
	//显示寄存器已经定义的变量，实际运行时下面需注释
	//int xianshikongzhi, cheRawXCur, cheRawYCur, cheRawXPrev, cheRawYPrev, chebianx, chebiany, btnVisiable, originx, originy, initControl, nowDrawOnce;
    //float scaleCur, scaleLast;

	//changing position of train
	cheRawXPrev = cheRawXCur; 	cheRawYPrev = cheRawXCur;

	cheRawXCur = cheRawXCur + 40;	cheRawYCur = cheRawYCur + 30;
	
	if(cheRawXCur >= 900 && cheRawYCur >= 900){
		cheRawXCur = 200;	cheRawYCur = 200;
	}

	//get the variation of the train, if > threshold
	int variationTrainX, variationTrainY;
	int refreshTrainThreshold = 10;
	variationTrainX = cheRawXCur - cheRawXPrev;
	variationTrainY = cheRawYCur - cheRawYPrev;
	
		//originx += variationTrainX;		originy += variationTrainY;
		originx = cheRawXCur - 350/scaleCur;
		originy = cheRawYCur - 350/scaleCur;
		nowDrawOnce = 0;

	return 0;
} 