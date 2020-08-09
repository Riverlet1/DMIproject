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
int MacroEntry()
{
int i,j;
DanH = DanHgao*10000+DanHdi;
for (i = 0;i<8;i++)
{
	if (Dangqianye == i)
	{
		for (j = 0;j<5;j++)
		{
			YeGouXu[j] = i*5+j+1;
			YeGdh[j] = Gdh[i*5+j];
			YeZyff[j] =Zyff[i*5+j];
			YeJs[j] = Js[i*5+j];
			YeLs[j] = LiangS[i*5+j];
			YeFx[j] = Fs[i*5+j];
			YeClbm[j] = Clbm[i*5*2+j*2]*10000+Clbm[i*5*2+j*2+1];
		}
	}
}
if (Dangqianye == 8)
{	
	Dangqianye = 0;
	LB88 = 1;
}
CurentXuanze = CurentChar+Dangqianye*5+1;
	return 0;
}
 