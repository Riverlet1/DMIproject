#include "macrotypedef.h"

#include "math.h"



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

//��ͼ����λ��

#define LEFT_BOUND 0

#define RIGHT_BOUND 640

#define TOP_BOUND 83

#define BOTTOM_BOUND 480

#define qd_num 7

#define dc_num 6

#define xhj_num 1

#define DOUXIAOYU 2
#define YIDAYIXIAO 1
#define DOUDAYU 3

#define PENWIDTH 2

#define FANGZUO 1
#define FANGYOU 2

#define XHJLEN 12

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

//��������pen

PenParam pennull={PS_NULL,PENWIDTH,RGB(0,0,0)};//��

PenParam penyellow={PS_SOLID,PENWIDTH,RGB(255,215,0)};//��

PenParam penred={PS_SOLID,PENWIDTH,RGB(255,0,0)};//��

PenParam penblue={PS_SOLID,PENWIDTH,RGB(41,82,156)};//��

PenParam pengreen={PS_SOLID,PENWIDTH,RGB(0,255,0)};//��

PenParam penwhite={PS_SOLID,PENWIDTH,RGB(255,255,255)};//��

						

//��������brush

BrushParam brhnull={BFS_NOBRUSH,RGB(41,82,156),RGB(41,82,156)};//��

BrushParam brhyellow={BFS_SOLID,RGB(255,215,0),RGB(255,215,0)};//��

BrushParam brhred={BFS_SOLID,RGB(255,0,0),RGB(255,0,0)};//��

BrushParam brhblue={BFS_SOLID,RGB(41,82,156),RGB(41,82,156)};//��

BrushParam brhwhite={BFS_SOLID,RGB(255,255,255),RGB(255,255,255)};//��

BrushParam brhblack={BFS_SOLID,RGB(0,0,0),RGB(0,0,0)};//��

BrushParam brhgreen={BFS_SOLID,RGB(0,255,0),RGB(0,255,0)};//��

//判断连线是在top的哪一ce
int TopDetect(int *x1, int *y1, int *x2, int *y2){
	int ret = 0;
	int p1x,p1y,p2x,p2y;

	if(*y1 < TOP_BOUND && *y2 > TOP_BOUND){
		p1x = (*x1); p1y = (*y1); p2x = (*x2); p2y = (*y2);
		p1x = (p2x-p1x)*(TOP_BOUND-p1y)/(p2y-p1y)+p1x;
		(*x1) = p1x;
		(*y1) = TOP_BOUND;
		ret = YIDAYIXIAO;		
	}
	else if(*y2 < TOP_BOUND && *y1 > TOP_BOUND){
		p1x = (*x2); p1y = (*y2); p2x = (*x1); p2y = (*y1);
		p1x = (p2x-p1x)*(TOP_BOUND-p1y)/(p2y-p1y)+p1x;
		(*x2) = p1x;
		*y2 = TOP_BOUND;
		ret = YIDAYIXIAO;
	}
	else if(*y1 <= TOP_BOUND && *y2 <= TOP_BOUND){
		ret = DOUXIAOYU;
	}
	else if(*y1 > TOP_BOUND && *y2 > TOP_BOUND){
		ret = DOUDAYU;
	}
	return ret;
}


int MacroEntry()

{
	
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
        {2001,	0,	0,	300	,300},
{2002,	300,	300	,400,	400},
{2003,	400,	400,	500,	500},
{2004,	500,	500	,600,	600},
{2005,	600,	600,	1000,	1000},
{2006,	270,	190,	790,	740},
{2007,	200,	300,	510,	610}
	};



if(btnVisiable==0){

	unsigned short i;

	int zuox,zuoy,youx,youy, xinx, xiny, huix, huiy, zhix, zhiy, wanx, wany, xhjx, xhjy, dcwanx, dcwany;

   int xinhaowidth = 10, xinhaoheight = 10;

	//经纬度-》屏幕坐标

	//������

	
    if(initControl == 1){
		
}else if(initControl == 0)
	{
	initControl = 1;
   scale = 1;
	originx = 0, originy = 0;
	cheRawXCur = 330; cheRawYCur = 330;
	cheRawXPrev = 330; cheRawYPrev = 330;
		xinhaowidth = 10, xinhaoheight = 10;

	}

	//����ɫ��������

	DrawRect(LEFT_BOUND, TOP_BOUND, RIGHT_BOUND-LEFT_BOUND, BOTTOM_BOUND-TOP_BOUND, pennull, brhblack);
	//车的绘制
//to do get chedian
	int trainx = cheRawXCur - originx;
   int trainy = cheRawYCur - originy;
	trainx *= scale;
	trainy *= scale;
	Point pts[4] = {
	{trainx,trainy},
	{trainx-15,trainy-10},
   {trainx-10,trainy-10},
	{trainx-10,trainy-15}
};
	DrawPolyg(pts, 4, penyellow, brhwhite);

	//��v0

	//������

	for(i = 0; i < qd_num; i++){

		zuox = qds[i].zuojing; zuoy = qds[i].zuowei;
		youx = qds[i].youjing; youy = qds[i].youwei;
		
		zuox -= originx; zuoy -= originy;
		youx -= originx; youy -= originy;

		zuox *= scale; zuoy *= scale;
		youx *= scale; youy *= scale;

		int state = TopDetect(&zuox, &zuoy, &youx, &youy);
		if(state == DOUXIAOYU) continue;		
		DrawLine(zuox, zuoy, youx, youy, penblue);

	}

	//������

	for(i = 0; i < dc_num; i++){

		xinx = dcs[i].xinjing; xiny = dcs[i].xinwei;
		huix = dcs[i].huijing; huiy = dcs[i].huiwei;
		zhix = dcs[i].zhijing; zhiy = dcs[i].zhiwei;
		wanx = dcs[i].wanjing; wany = dcs[i].wanwei;

		xinx -= originx; xiny -=originy;
		huix -= originx; huiy -= originy;
		zhix -= originx; zhiy -= originy; 
		wanx -= originx; wany -= originy; 

		xinx *= scale; xiny *= scale;
		huix *= scale; huiy *= scale;
		zhix *= scale; zhiy *= scale;
		wanx *= scale; wany *= scale;

		int state = TopDetect(&xinx, &xiny, &huix, &huiy);
		if(state != DOUXIAOYU){
			DrawLine(xinx, xiny, huix, huiy, penblue);
		}
	    state = TopDetect(&xinx, &xiny, &zhix, &zhiy);
		if(state != DOUXIAOYU){
			DrawLine(xinx, xiny, zhix, zhiy, penblue);
		}
		state = TopDetect(&xinx, &xiny, &wanx, &wany);
		if(state != DOUXIAOYU){
			DrawLine(xinx, xiny, wanx, wany, penblue);
		}

	}

	//���źŻ�

	for(i = 0; i < xhj_num; i++){

		//������

		//��Բ

		xhjx = xhjs[i].jing; xhjy = xhjs[i].wei;
		xhjx -= originx; xhjy -= originy; 
		xhjx *= scale; xhjy *= scale;

		if(xhjx > LEFT_BOUND && xhjy > TOP_BOUND && xhjx < RIGHT_BOUND && xhjy < BOTTOM_BOUND)
		{
			xinhaowidth = 20, xinhaoheight = 20;			
			if(xhjs[i].proDirection == FANGZUO){
				DrawLine(xhjx, xhjy, xhjx-XHJLEN, xhjy+XHJLEN, penblue);
				DrawEclips(xhjx-30, xhjy, xinhaowidth, xinhaoheight, penred, brhred);
			}else{
				DrawLine(xhjx, xhjy, xhjx+XHJLEN, xhjy-XHJLEN, penblue);
				DrawEclips(xhjx-30, xhjy, xinhaowidth, xinhaoheight, penred, brhred);
			}
		}
		

	}

	//�������豸
}
	return 0;

}


 