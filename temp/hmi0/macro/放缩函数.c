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
	
	//update the scale and change origin point
	scaleLast = scaleCur;
	if(scaleCur == 1.0){
		scaleCur = 1.5;
	}
	else if(scaleCur == 1.5)
	{
		scaleCur = 0.6;
	}
	else{
		scaleCur = 1.0;
	}
	originx = cheRawXCur + (originx - cheRawXCur) * scaleLast / scaleCur;
	originy = cheRawYCur + (originy - cheRawYCur) * scaleLast / scaleCur;
	
	nowDrawOnce = 0;

	return 0;
}
 