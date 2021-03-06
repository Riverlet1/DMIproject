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
{int y=330;
int x11=x,y11=y-100,x12=x,y12=y;
PenParam pen1={PS_SOLID,1.5,RGB(30,144,255)};
DrawLine(x11, y11, x12, y12, pen1);
int x21=x+5,y21=y-100,x22=x-5,y22=y-105;
PenParam pen2={PS_SOLID,1.5,RGB(30,144,255)};
DrawLine(x21, y21, x22, y22, pen2);
int x31=x+5,y31=y-100,x32=x-5,y32=y-95;
PenParam pen3={PS_SOLID,1.5,RGB(30,144,255)};
DrawLine(x31, y31, x32, y32, pen3);
	return 0;
}
 