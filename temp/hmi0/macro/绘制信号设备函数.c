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

#define qd_num 79

#define dc_num 100

#define xhj_num 142

#define DOUXIAOYU 2
#define YIDAYIXIAO 1
#define DOUDAYU 3

#define PENWIDTH 2

#define FANGZUO 1
#define FANGYOU 0

#define XHJLEN 12

//信号设备状态
#define ZHANYONG 1
#define SUOBI 2
#define KONGXIAN 3
#define XHJGUANBI 4
#define XHJKAIFANG 5
#define XHJMIEDENG 6
#define DCDINGWEI 7
#define DCFANWEI 8
#define DCSIKAI 9

//带参数宏定义

//#define DC_JT(n) dc_jt_data_0 # n



//struct definition
typedef struct{
	short id;
	short xinjing;
	short xinwei;
	short huijing;
	short huiwei;
	short zhijing;
	short zhiwei;
	short wanjing;
	short wanwei;
	short style;

	//动态信息
	short zhuangtai;
}DC_struct;
typedef struct{
	short id;
	short type;
	short jing;
	short wei;
	short zuo_you;

	//动态信息
	short zhuangtai;
}XHJ_struct;
typedef struct{
	short id;
	short zuojing;
	short zuowei;
	short youjing;
	short youwei;

	//动态信息
	short zhuangtai;	
}QD_struct;

//��������pen

PenParam pennull={PS_NULL,PENWIDTH,RGB(0,0,0)};//��

PenParam penyellow={PS_SOLID,PENWIDTH,RGB(255,215,0)};//��

PenParam penred={PS_SOLID,PENWIDTH,RGB(255,0,0)};//��

PenParam penblue={PS_SOLID,PENWIDTH,RGB(41,82,156)};//��

PenParam pengreen={PS_SOLID,PENWIDTH,RGB(0,255,0)};//��

PenParam penwhite={PS_SOLID,PENWIDTH,RGB(255,255,255)};//��
PenParam penblack={PS_SOLID,PENWIDTH+2,RGB(1,1,1)};

						

//��������brush

BrushParam brhnull={BFS_NOBRUSH,RGB(41,82,156),RGB(41,82,156)};//��

BrushParam brhyellow={BFS_SOLID,RGB(255,215,0),RGB(255,215,0)};//��

BrushParam brhred={BFS_SOLID,RGB(255,0,0),RGB(255,0,0)};//��

BrushParam brhblue={BFS_SOLID,RGB(41,82,156),RGB(41,82,156)};//��

BrushParam brhwhite={BFS_SOLID,RGB(255,255,255),RGB(255,255,255)};//��

BrushParam brhblack={BFS_SOLID,RGB(1,1,1),RGB(1,1,1)};//��

BrushParam brhgreen={BFS_SOLID,RGB(0,255,0),RGB(0,255,0)};//��

BrushParam brhback ={BFS_SOLID,RGB(1, 1, 1),RGB(1, 1, 1)};//��

//判断连线是在top的哪一ce
int TopDetect(int x1, int y1, int x2, int y2){
	int ret = 3;
	int p1x,p1y,p2x,p2y;

	if(y1 <= TOP_BOUND && y2 <= TOP_BOUND){
		ret = DOUXIAOYU;
	}
	else if(y1 <= TOP_BOUND && y2 > TOP_BOUND){
		ret = YIDAYIXIAO;
	}
	else if(y1 > TOP_BOUND && y2 <= TOP_BOUND){
		ret = YIDAYIXIAO;
	}

	return ret;
}

void ConvertPoint(short *x1, short *y1, short *x2, short *y2){
	int y_level = TOP_BOUND - 3;
	if((*y1) > (*y2)){
		//(*x2) = (*x1) - ((*y1) - y_level)*((*x1) - (*x2))/((*y1) - (*y2));
		//(*y2) = y_level;
	}else{
		//(*x1) = (*x2) - ((*y2) - y_level) * ((*x2) - (*x1)) / ((*y2) - (*y1));
		//(*y1) = y_level;
	}
}

void ShortenDC(short *x1, short *y1, short *x2, short *y2)
{
	short px1 = *x1, py1 = *y1, px2 = *x2, py2 = *y2;

	short xmid, ymid;

	if(py1 > py2)
	{
		ymid = py1 - 5;
	}
	else
	{
		ymid = py1 + 5;
	}
	xmid = (px2 - px1) / (py2 - py1) * (ymid - py1) + px1;

	(*x1) = px1; (*y1) = py1; (*x2) = px2; (*y2) = py2;
} 


int MacroEntry()

{  //------ji cun qi she zhi liang
	//  int chetoux, chetouy, cheweix, cheweiy; short qd_jt_data[700]; short dc_jt_data_01[1000];  short xhj_jt_data[1000];
//----------------------------------------------------------------------------------------------------------
	
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
	QD_struct qds[qd_num];

	unsigned short i, j, k;

	short zuox,zuoy,youx,youy, xinx, xiny, huix, huiy, zhix, zhiy, wanx, wany, xhjx, xhjy, dcwanx, dcwany, ifOutScreen, xhj_zuoyou;
	short dc_zhuangtai = ZHANYONG, qd_zhuangtai = SUOBI, xhj_zhuangtai = XHJGUANBI, dc_dfw = DCFANWEI, xhjdx, xhjdy;

   int xinhaowidth = 10, xinhaoheight = 10;

	//经纬度-》屏幕坐标

	DrawRect(LEFT_BOUND, TOP_BOUND, RIGHT_BOUND-LEFT_BOUND, BOTTOM_BOUND-TOP_BOUND, pennull, brhback);

	//----------------------------------------------------------------------------------------DrawRect(LEFT_BOUND, TOP_BOUND, RIGHT_BOUND-LEFT_BOUND, BOTTOM_BOUND-TOP_BOUND, pennull, brhback);
	//车的绘制
//to do get chedian

	int toux = (cheRawXCur - originx) * scaleCur;

   int touy = (cheRawYCur - originy) * scaleCur;

   int weix = (cheweix - originx) * scaleCur;

   int weiy = (cheweiy - originy) * scaleCur;

	int bian_y = weiy > weix ? 10 : -10;

   weix = toux + (weix - toux) / (weiy - touy) * bian_y;

   weiy = touy + bian_y;

	if(toux - weix == 0){

		bian_y = 0;

   	}else{

		bian_y = (weiy -touy) / (toux - weix);

	}

	Point pts[4] = {

		{toux, touy},

		{weix + 10, weiy + bian_y * 10},

   		{weix, weiy},

		{weix - 10, weiy - bian_y * 10 }

	};

	// (weiy - touy) / (toux - weix) * 10 + weiy

	if(touy > TOP_BOUND && weiy > TOP_BOUND){

		DrawPolyg(pts, 4, penyellow, brhwhite);

	}

//===========================================================================================================

	//根据动态信息改变颜色
	PenParam pentemp = penblue;
	BrushParam brhtemp = brhblue;

	//������

	for(i = 0; i < qd_num*7; i=i+7){
		zuox = qd_jt_data[i]; 
		zuoy = qd_jt_data[i+1];
		youx = qd_jt_data[i+2];
		youy = qd_jt_data[i+3]; 
		 		
		zuox -= originx; zuoy -= originy;
		youx -= originx; youy -= originy;

		zuox *= scaleCur; zuoy *= scaleCur;
		youx *= scaleCur; youy *= scaleCur;

//dong tai xin xi gai bian
		if(qd_zhuangtai == KONGXIAN)
		{
			pentemp = penblue;
		}
		else if(qd_zhuangtai == SUOBI)
		{
			pentemp = penwhite;
		}
		else if(qd_zhuangtai == ZHANYONG)
		{
			pentemp = penred;
		}
		else
		{
			pentemp = penred;
		}
		

		ifOutScreen = TopDetect(zuox, zuoy, youx, youy);
		if(ifOutScreen == DOUXIAOYU) continue;
		if(ifOutScreen == YIDAYIXIAO){
			ConvertPoint(&zuox, &zuoy, &youx, &youy);
		}		
		DrawLine(zuox, zuoy, youx, youy, pentemp);

	}

	//������

	for(j = 0; j < dc_num*12; j = j + 12){

		int index = 0;
		if(j < 600){
			i = j;
			index = 1;
			xinx = dc_jt_data_01[i]; xiny = dc_jt_data_01[i+1];
			huix = xinx + dc_jt_data_01[i+2]; huiy = xiny + dc_jt_data_01[i+3];
			zhix = xinx + dc_jt_data_01[i+4]; zhiy = xiny + dc_jt_data_01[i+5];
			wanx = xinx + dc_jt_data_01[i+6]; wany = xiny + dc_jt_data_01[i+7];
		}else if( j >= 600 && j < 1200){
			i = j - 600;
			index = 2;
			xinx = dc_jt_data_02[i]; xiny = dc_jt_data_02[i+1];
			huix = xinx + dc_jt_data_02[i+2]; huiy = xiny + dc_jt_data_02[i+3];
			zhix = xinx + dc_jt_data_02[i+4]; zhiy = xiny + dc_jt_data_02[i+5];
			wanx = xinx + dc_jt_data_02[i+6]; wany = xiny + dc_jt_data_02[i+7];
		}else
		{
			i = j - 1200;
			index = 3;
			xinx = dc_jt_data_03[i]; xiny = dc_jt_data_03[i+1];
			huix = xinx + dc_jt_data_03[i+2]; huiy = xiny + dc_jt_data_03[i+3];
			zhix = xinx + dc_jt_data_03[i+4]; zhiy = xiny + dc_jt_data_03[i+5];
			wanx = xinx + dc_jt_data_03[i+6]; wany = xiny + dc_jt_data_03[i+7];
		}
		//xinx = DC_JT(index, 0); xiny = DC_JT(index, 1);
		//huix = xinx + DC_JT(index, 2); huiy = xiny + DC_JT(index, 3);
		//zhix = xinx + DC_JT(index, 4); zhiy = xiny + DC_JT(index, 5);
		//wanx = xinx + DC_JT(index, 6); wany = xiny + DC_JT(index, 7);
		

		xinx -= originx; xiny -=originy;
		huix -= originx; huiy -= originy;
		zhix -= originx; zhiy -= originy; 
		wanx -= originx; wany -= originy; 

		xinx *= scaleCur; xiny *= scaleCur;
		huix *= scaleCur; huiy *= scaleCur;
		zhix *= scaleCur; zhiy *= scaleCur;
		wanx *= scaleCur; wany *= scaleCur;

//dong tai xin xi gai bian
		if(dc_zhuangtai == KONGXIAN)
		{
			pentemp = penblue;
		}
		else if(dc_zhuangtai == SUOBI)
		{
			pentemp = penwhite;
		}
		else if(dc_zhuangtai == ZHANYONG)
		{
			pentemp = penred;
		}
		else
		{
			pentemp = penred;
		}

		ifOutScreen = TopDetect(xinx, xiny, huix, huiy);
		if(ifOutScreen != DOUXIAOYU){
			DrawLine(xinx, xiny,  huix, huiy, pentemp);
		}
	    ifOutScreen = TopDetect(xinx, xiny, zhix,  zhiy);
		if(ifOutScreen != DOUXIAOYU){
			DrawLine(xinx, xiny,  zhix,  zhiy, pentemp);
		}
		ifOutScreen = TopDetect(xinx, xiny,  wanx, wany);
		if(ifOutScreen != DOUXIAOYU){
			DrawLine(xinx, xiny, wanx,  wany, pentemp);
		}

		if(dc_dfw == DCDINGWEI)
		{
			short dx = xinx + (wanx - xinx) / 4;
			short dy = xiny + (wany - xiny) / 4;
			ifOutScreen = TopDetect(xinx, xiny,  dx, dy);
			if(ifOutScreen != DOUXIAOYU){				
				DrawLine(xinx, xiny, dx, dy, penblack);
				DrawLine(xinx, xiny, zhix, zhiy, pentemp);
			}
		}
		else if(dc_dfw == DCFANWEI)
		{
			short dx = xinx + (zhix - xinx) / 4;
			short dy = xiny + (zhiy - xiny) / 4;
			ifOutScreen = TopDetect(xinx, xiny,  dx, dy);
			if(ifOutScreen != DOUXIAOYU){			
				DrawLine(xinx, xiny, dx, dy, penblack);
				DrawLine(xinx, xiny, wanx, wany, pentemp);
			}
		}
		else
		{
		
		}

	}

	// //���źŻ�

	for(j = 0; j < xhj_num * 9; j = j + 9){

		//������

		if(j < 900){
			i = j;
			xhjx = xhj_jt_data_01[i+0];
			xhjy = xhj_jt_data_01[i+1];
			xhj_zuoyou = xhj_jt_data_01[i+2];			
		}else if( j >= 900 && j < 1800){
			i = j - 900;
			xhjx = xhj_jt_data_02[i+0];
			xhjy = xhj_jt_data_02[i+1];
			xhj_zuoyou = xhj_jt_data_02[i+2];
		}

		xhjx -= originx; xhjy -=originy;

		xhjx *= scaleCur; xhjy *= scaleCur;

//dong tai xin xi gai bian
		if(xhj_zhuangtai == XHJKAIFANG)
		{
			pentemp = penwhite;
			brhtemp = brhwhite;
		}
		else if(xhj_zhuangtai == XHJGUANBI)
		{
			pentemp = penblue;
			brhtemp = brhblue;
		}
		else
		{
			pentemp = penblue;
			brhtemp = brhblue;
		}
		
		xinhaowidth = 15 * scaleCur, xinhaoheight = 15 * scaleCur;
		xhjdx = 15 * scaleCur; xhjdy = 10 * scaleCur;	
		if(xhjx > LEFT_BOUND && xhjy > TOP_BOUND && xhjx < RIGHT_BOUND && xhjy < BOTTOM_BOUND)
		{
					
			if(xhj_zuoyou == FANGZUO){
				DrawLine(xhjx, xhjy, xhjx, xhjy-xhjdy*2, pentemp);
				DrawEclips(xhjx-xhjdx, xhjy-xhjdy, xinhaowidth, xinhaoheight, pentemp, brhtemp);
			}else if(xhj_zuoyou == FANGYOU){
				DrawLine(xhjx, xhjy, xhjx, xhjy+xhjdy*2, pentemp);
				DrawEclips(xhjx, xhjy-xhjdy, xinhaowidth, xinhaoheight, pentemp, brhtemp);
			}
		}
	}

	nowDrawStr2 = 0;

	//�������豸
	return 0;

} 