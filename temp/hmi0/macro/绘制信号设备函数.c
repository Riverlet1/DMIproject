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

#define qd_num 1

#define dc_num 11

#define xhj_num 5

#define DOUXIAOYU 2
#define YIDAYIXIAO 1
#define DOUDAYU 3

#define PENWIDTH 2

//结构体定义
typedef struct{
	int xinjing;
	int xinwei;
	int huijing;
	int huiwei;
	int zhijing;
	int zhiwei;
	int wanjing;
	int wanwei;
}DC_struct;
typedef struct{
	int jing;
	int wei;
}XHJ_struct;
typedef struct{
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
		{22391780,	85096960,	22350731,	85112721,	22402285,	85093904,	22401016,	85091848},
{22410224,	85086830,	22438096,	85075828,	22399740,	85089790,	22401016,	85091848},
{22390069,	85094118,	22348189,	85108640,	22399740,	85089790,	22401016,	85091848},
{22411976,	85089619,	22440637,	85079922,	22402285,	85093904,	22401016,	85091848},
{22426417,	85075793,	22391139,	85087938,	22466257,	85060520,	22438477,	85073235},
{22448408,	85071317,	22477098,	85061640,	22438096,	85075828,	22438477,	85073235},
{22362595,	85097659,	22391139,	85087938,	22325756,	85111844,	22348404,	85100728},
{22321356,	85107242,	22348404,	85100728,	22310479,	85110806,	22300084,	85110237},
{22543395,	85041615,	22572005,	85031873,	22493486,	85060659,	22532126,	85043935},
{22322748,	85123647,	22350731,	85112721,	22312394,	85126736,	22313630,	85128788},
{22319596,	85118435,	22348189,	85108640,	22306777,	85123781,	22306671,	85121096}
	};
	XHJ_struct xhjs[xhj_num] = {
		{22350731	, 85112721},
{22348189,	85108640},
{22440637,	85079922},
{22391139,	85087938},
{22493486,	85060659}
	};
	QD_struct qds[qd_num] = {
        {22440637,	85079922,	22493486,	85060659}
	};



if(btnVisiable==0){

	unsigned short i;

	int zuox,zuoy,youx,youy;

	int xinx, xiny, huix, huiy, zhix, zhiy, wanx, wany, xhjx, xhjy;

   xinhaowidth = 10, xinhaoheight = 10;

	//经纬度-》屏幕坐标

	//������

	

    int loadflag = 0;

	if(loadflag == 0)

	{

   scale = 0.005;
	originx = dcs[0].huijing, originy = dcs[0].huiwei;
   originx -= 20000; originy += 20000;

		chebianx = 0, chebiany = 0;

		xinhaowidth = 10, xinhaoheight = 10;

		i = 0;

		//��duan	

		zuojing[i] = 100; zuowei[i] = -20;

		youjing[i] = 200; youwei[i] = 200;

		i = 1;

		zuojing[i] = 270; zuowei[i] = 270;

		youjing[i] = 300; youwei[i] = 300;

		i = 2;

		zuojing[i] = 280; zuowei[i] = 290;

		youjing[i] = 380; youwei[i] = 390;

		//����

		i=0;

		xinjing[i] = 220; xinwei[i] = 220;

		huijing[i] = 240; huiwei[i] = 240;

		zhijing[i] = 200; zhiwei[i] = 200;

		wanjing[i] = 210; wanwei[i] = 190;

		i = 1;

		xinjing[i] = 260; xinwei[i] = 260;

		huijing[i] = 240; huiwei[i] = 240;

		zhijing[i] = 270; zhiwei[i] = 270;

		wanjing[i] = 280; wanwei[i] = 290;

		i = 2;

		xinjing[i] = 160; xinwei[i] = 140;

		huijing[i] = 210; huiwei[i] = 190;

		zhijing[i] = 130; zhiwei[i] = 110;

		wanjing[i] = 130; wanwei[i] = 100;

		//xhj

		i = 0;

		xinhaojing[i] = 240; xinhaowei[i] = 240;		

		i = 1;

		xinhaojing[i] = 280; xinhaowei[i] = 280;

	}



    //�����������

	//����	

	for(i = 0; i < qd_num; i++){

		zuox = zuojing[i] + chebianx; zuoy = zuowei[i] + chebiany;

		youx = youjing[i] + chebianx; youy = youwei[i] + chebiany;

		zuojing[i] = zuox; zuowei[i] = zuoy;

		youjing[i] = youx; youwei[i] = youy;

	}

	//����	

	for(i = 0; i < dc_num; i++){

		xinx = xinjing[i] + chebianx; xiny = xinwei[i] + chebiany;

		huix = huijing[i] + chebianx ; huiy = huiwei[i] + chebiany;

		zhix = zhijing[i] + chebianx; zhiy = zhiwei[i] + chebiany;

		wanx = wanjing[i] + chebianx; wany = wanwei[i] + chebiany;

		xinjing[i] = xinx; xinwei[i] = xiny;

		huijing[i] = huix; huiwei[i] = huiy;

		zhijing[i] = zhix; zhiwei[i] = zhiy;

		wanjing[i] = wanx; wanwei[i] = wany;

	}

	//�źŻ�

	for(i = 0; i < xhj_num; i++){

		//������

		//��Բ

		xinhaojing[i] += chebianx; xinhaowei[i] += chebiany;

	}

	//����ɫ��������

	DrawRect(LEFT_BOUND, TOP_BOUND, RIGHT_BOUND-LEFT_BOUND, BOTTOM_BOUND-TOP_BOUND, pennull, brhblack);
	//车的绘制
//to do get chedian
	Point pts[4] = {
	{250,255},
	{260,235},
   {250,240},
	{240,235}
};
	DrawPolyg(pts, 4, penyellow, brhwhite);

	//��v0

	//������

	for(i = 0; i < qd_num; i++){

		zuox = qds[i].zuojing; zuoy = qds[i].zuowei;
		youx = qds[i].youjing; youy = qds[i].youwei;
		
		zuox -= originx; zuoy -= originy, zuoy = -zuoy;
		youx -= originx; youy -= originy, youy = -youy;

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

		xinx -= originx; xiny -=originy; xiny = -xiny;
		huix -= originx; huiy -= originy; huiy = -huiy;
		zhix -= originx; zhiy -= originy;  zhiy = -zhiy;
		wanx -= originx; wany -= originy; wany = -wany;

		xinx *= scale; xiny *= scale;
		huix *= scale; huiy *= scale;
		zhix *= scale; zhiy *= scale;
		wanx *= scale; wany *= scale;

		int state = TopDetect(&xinx, &xiny, &huix, &huiy);
		if(state != DOUXIAOYU)
		DrawLine(xinx, xiny, huix, huiy, penblue);
		state = TopDetect(&xinx, &xiny, &zhix, &zhiy);
		if(state != DOUXIAOYU)
		DrawLine(xinx, xiny, zhix, zhiy, penblue);
		state = TopDetect(&xinx, &xiny, &wanx, &wany);
		if(state != DOUXIAOYU)
		DrawLine(xinx, xiny, wanx, wany, penblue);

	}

	//���źŻ�

	for(i = 0; i < xhj_num; i++){

		//������

		//��Բ

		xhjx = xhjs[i].jing; xhjy = xhjs[i].wei;
		xhjx -= originx; xhjy -= originy; xhjy = -xhjy;
		xhjx *= scale; xhjy *= scale;

		if(xhjx > LEFT_BOUND && xhjy > TOP_BOUND && xhjx < RIGHT_BOUND && xhjy < BOTTOM_BOUND)
			{DrawEclips(xhjx, xhjy, xinhaowidth, xinhaoheight, penred, brhred);}

	}

	//�������豸



	//xianshikongzhi = 1;
}
	return 0;

}


 