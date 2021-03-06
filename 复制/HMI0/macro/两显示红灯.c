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
int y=330;
int x11=OffsetofRedLights,y11=y,x12=OffsetofRedLights,y12=y-40;
PenParam pen11={PS_SOLID,1.5,RGB(30,144,255)};
DrawLine(x11, y11, x12, y12, pen11);
int x21=OffsetofRedLights-10,y21=y-50,w21=20,h21=20;
PenParam pen21={PS_DASH,0,RGB(30,144,255)};
BrushParam brh={BFS_SOLID,RGB(255,0,0),RGB(255,0,0)};
DrawEclips(x21, y21, w21, h21, pen21, brh);	
return 0;
}
 