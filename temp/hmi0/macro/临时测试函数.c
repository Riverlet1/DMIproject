#include "macrotypedef.h"

#include "math.h"



#define qd_num 7
#define dc_num 6
#define xhj_num 1

#define HUI2XIN 2
#define XIN2HUI 1
#define XIN2ZHI 3
#define ZHI2XIN 4
#define XIN2WAN 5
#define WAN2XIN 6

#define ZUO2YOU_1 1
#define ZUO2YOU_2 2
#define ZUO2YOU_3 3
#define ZUO2YOU_4 4
#define ZUO2YOU_5  5
#define YOU2ZUO_1  6
#define YOU2ZUO_2 7
#define YOU2ZUO_3 8 
#define YOU2ZUO_4  9
#define YOU2ZUO_5  10

//struct definition
typedef struct{
	int id;
	int xinjing;
	int xinwei;
	int huijing;
	int huiwei;
	int zhijing;
	int zhiwei;
	int wanjing;
	int wanwei;
	int style;
}DC_struct;
typedef struct{
	int id;
	int jing;
	int wei;
	char proDirection;
}XHJ_struct;
typedef struct{
	int id;
	int zuojing;
	int zuowei;
	int youjing;
	int youwei;	
}QD_struct;

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
/*	int xianshikongzhi, cheRawXCur, cheRawYCur, cheRawXPrev, cheRawYPrev, chebianx, chebiany, btnVisiable, originx, originy, initControl, nowDrawOnce;
    float scaleCur, scaleLast;
	int curID, curDir, cheWeiXcur, cheWeiYcur, xiu_gai_zb;  
*/	//----------------------------------------------------------------------------

	DC_struct dcs[dc_num] = {
		{1001,	200,	200,	180,	180,	220,	220,	270,  190},
{1002,	800,	800,	820,	820,	780,	780,	790,	740},
{1003,	350,	350,	330,	330,	370,	370,	350,	410},
{1004,	350,	450,	370,	470,	330,	430,	350,	410},
{1005,	410	,410,	430,	430,	390,	390,	350,	410},
{1006,	310,	410,	290,	390,	330,	430,	350,	410}
	};
	XHJ_struct xhjs[xhj_num] = {
		{3001,	300,	300,	1}
	};
	QD_struct qds[qd_num] = {
        {2001,	0,	0,	180,180},
{2002,	220,	220	, 330,	 330},
{2003,	370,	370,	390,	390},
{2004,	430,	430, 780,	780},
{2005,	200,	300,	290,	390},
{2006,	270,	190,	790,	740},
{2007,	370,	470,	470,	570}
	};

int help_cur_id[19] = {2001, 1001,1001,   2002, 2002, 1003,1003 ,1004, 1004,  2007, 
2007, 2007, 1004, 1004, 1006, 1006, 2005, 2005, 2005};
int help_dir[19] = {5, HUI2XIN, XIN2ZHI, 2, 4, HUI2XIN, XIN2WAN, WAN2XIN, XIN2HUI, 1,
2, 9, HUI2XIN, XIN2ZHI,  ZHI2XIN, XIN2HUI, 6, 8, 9};

if( xiu_gai_zb == 18){
	curID = help_cur_id[xiu_gai_zb];
	curDir = help_dir[xiu_gai_zb];
	xiu_gai_zb = 0;
}else{
	curID = help_cur_id[xiu_gai_zb];
	curDir = help_dir[xiu_gai_zb];
	xiu_gai_zb++;
}

	//changing position of train
	cheRawXPrev = cheRawXCur; 	cheRawYPrev = cheRawXCur;
	
	if(curID < 1999 && curID > 1000){
		int Index = curID % 1000 - 1;
		//dao cha
		if(curDir == HUI2XIN){
			cheRawXCur = dcs[Index].xinjing;
			cheRawYCur = dcs[Index].xinwei;
			cheWeiXcur = dcs[Index].huijing;
			cheWeiYcur = dcs[Index].huiwei;
		}
		else if(curDir == XIN2HUI){
			cheRawXCur = dcs[Index].huijing;
			cheRawYCur = dcs[Index].huiwei;
			cheWeiXcur = dcs[Index].xinjing;
			cheWeiYcur = dcs[Index].xinwei;
		}
		else if(curDir == XIN2ZHI){
			cheRawXCur = dcs[Index].zhijing;
			cheRawYCur = dcs[Index].zhiwei;
			cheWeiXcur = dcs[Index].xinjing;
			cheWeiYcur = dcs[Index].xinwei;
		}
		else if(curDir == ZHI2XIN){
			cheRawXCur = dcs[Index].xinjing;
			cheRawYCur = dcs[Index].xinwei;
			cheWeiXcur = dcs[Index].zhijing;
			cheWeiYcur = dcs[Index].zhiwei;
		}
		else if(curDir == XIN2WAN){
			cheRawXCur = dcs[Index].wanjing;
			cheRawYCur = dcs[Index].wanwei;
			cheWeiXcur = dcs[Index].xinjing;
			cheWeiYcur = dcs[Index].xinwei;
		}
		else if(curDir == WAN2XIN){
			cheRawXCur = dcs[Index].xinjing;
			cheRawYCur = dcs[Index].xinwei;
			cheWeiXcur = dcs[Index].wanjing;
			cheWeiYcur = dcs[Index].wanwei;
		}
	}
	else if(curID >2000 && curID < 2999){
		//qu duan
		int index = curID % 2000 - 1;
		if(curDir >= ZUO2YOU_1 && curDir <= ZUO2YOU_5){
			int deltax = qds[index].youjing - qds[index].zuojing;
			int deltay = qds[index].youwei - qds[index].zuowei;
			cheRawXCur = qds[index].zuojing + (deltax) / 5 * curDir;
			cheRawYCur = qds[index].zuowei + (deltay) / 5 * curDir;
			cheWeiXcur = cheRawXCur - deltax / 5;
			cheWeiYcur = cheRawYCur - deltay / 5;
		}
		else 
		{
			int deltax = -(qds[index].youjing - qds[index].zuojing);
			int deltay = -(qds[index].youwei - qds[index].zuowei);
			curDir = curDir % 5;
			cheRawXCur = qds[index].youjing + deltax / 5 * curDir;
			cheRawYCur = qds[index].youwei + deltay / 5 * curDir;
			cheWeiXcur = cheRawXCur - deltax / 5;
			cheWeiYcur = cheRawYCur - deltay / 5;
		}		
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
	
	//nowDrawOnce = 0;

	return 0;
} 