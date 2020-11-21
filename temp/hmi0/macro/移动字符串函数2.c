#include "macrotypedef.h"
#include "math.h"

#define LEFT_BOUND 0

#define RIGHT_BOUND 640

#define TOP_BOUND 83

#define BOTTOM_BOUND 480

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
	int xhj_num = 5;

int i, j,k, xhjx, xhjy;
k = 0;
	for(j = 0; j < xhj_num * 9; j = j + 9){
		if(j < 900){
			i = j;
			xhjx = xhj_jt_data_01[i+4];
			xhjy = xhj_jt_data_01[i+5];		
		}else if( j >= 900 && j < 1800){
			i = j - 900;
			xhjx = xhj_jt_data_02[i+4];
			xhjy = xhj_jt_data_02[i+5];
		}
	
		xhjx -= originx; xhjy -=originy;
		xhjx *= scale; xhjy *= scale;

		k = k + 3;
		if(xhjx > LEFT_BOUND && xhjy > TOP_BOUND && xhjx < RIGHT_BOUND && xhjy < BOTTOM_BOUND)
		{
			textCtrl[k] = 3;
			textCtrl[k+1] = xhjx+1;
			textCtrl[k+2] = xhjy+1;
		}
	}

	return 0;
}
 