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
	int flag = 0;
if(flag == 0){
	originx -= 10000; originy += 0;
}
if(flag == 1){
	if(scale_label == 1){
		scale01 = 0.007;
		scale_label = 2;
	}else if(scale_label == 2){
		scale01 = 0.007;
		scale_label = 3;
	}else if(scale_label == 3){
		scale01 = 0.007;
		scale_label = 4;
	}else{
		scale01 = 0.007;
		scale_label = 1;
	}
}

	//int zoomCur;

	float scale  = 1.4;

   int i, zuox,zuoy,youx,youy,xinx,xiny,huix,huiy,zhix,zhiy,wanx,wany,xhjx,xhjy;
   
   //坐标移动
   chebianx = 15; chebiany = 0;

if(bangTuKongZhi == 30){
bangTuKongZhi = 75;}
else{
bangTuKongZhi = 30;}

	if(zoomCur == 0){
		zoomCur = 1;
		//�����߻���

		for(i = 0; i < qd_num; i++){

			zuox = zuojing[i] * scale; zuoy = zuowei[i] * scale;

			youx = youjing[i] * scale; youy = youwei[i] * scale;

			zuojing[i] = zuox; zuowei[i] = zuoy;

			youjing[i] = youx; youwei[i] = youy;

		}

		//����	

		for(i = 0; i < dc_num; i++){

			xinx = xinjing[i] * scale; xiny = xinwei[i] * scale;

			huix = huijing[i] * scale; huiy = huiwei[i] * scale;

			zhix = zhijing[i] * scale; zhiy = zhiwei[i] * scale;

			wanx = wanjing[i] * scale; wany = wanwei[i] * scale;

			xinjing[i] = xinx; xinwei[i] = xiny;

			huijing[i] = huix; huiwei[i] = huiy;

			zhijing[i] = zhix; zhiwei[i] = zhiy;

			wanjing[i] = wanx; wanwei[i] = wany;

		}

		//�źŻ�

		for(i = 0; i < xhj_num; i++){

			xinhaojing[i] = xinhaojing[i] * scale; xinhaowei[i] = xinhaowei[i] * scale;

			xinhaowidth = xinhaowidth * scale; xinhaoheight = xinhaoheight * scale;		

		}

	}

	else{

		zoomCur = 0;

		//�����߻���

		for(i = 0; i < qd_num; i++){

			zuox = zuojing[i] / scale; zuoy = zuowei[i] / scale;

			youx = youjing[i] / scale; youy = youwei[i] / scale;

			zuojing[i] = zuox; zuowei[i] = zuoy;

			youjing[i] = youx; youwei[i] = youy;

		}

		//����	

		for(i = 0; i < dc_num; i++){

			xinx = xinjing[i] / scale; xiny = xinwei[i] / scale;

			huix = huijing[i] / scale; huiy = huiwei[i] / scale;

			zhix = zhijing[i] / scale; zhiy = zhiwei[i] / scale;

			wanx = wanjing[i] / scale; wany = wanwei[i] / scale;

			xinjing[i] = xinx; xinwei[i] = xiny;

			huijing[i] = huix; huiwei[i] = huiy;

			zhijing[i] = zhix; zhiwei[i] = zhiy;

			wanjing[i] = wanx; wanwei[i] = wany;

		}

		//�źŻ�

		for(i = 0; i < xhj_num; i++){

			xhjx = xinhaojing[i] / scale; xhjy = xinhaowei[i] / scale;

			xinhaojing[i] = xhjx; xinhaowei[i] = xhjy;

			//xinhaowidth = xinhaowidth / scale; xinhaoheight = xinhaoheight / scale;		

		}
	}

	return 0;

} 