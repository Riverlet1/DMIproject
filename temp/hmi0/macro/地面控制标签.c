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
#define OffsetOfTrain 173

int MacroEntry()
{
	int i;
	for (i = 0 ;i < 20;i++) 
	{
		SignalLabel[i*3] = 0;
		SwitchLabel[i*3] = 0;
	}
	for (i = 0;i < NumOfSignalLab;i++)
	{
		SignalLab[i*3] = SignalLabelDraw[i*2];
		SignalLab[i*3+1] = SignalLabelDraw[i*2+1]-OffsetOfTrain;
	}
	for (i ;i < 20;i++) 
	{
		SignalLab[i*3] = 0;
	}

	for (i = 0;i < NumOfSwitchLab;i++)
	{
		SwitchLab[i*3] = SwitchLabelDraw[i*2];
		SwitchLab[i*3+1] = SwitchLabelDraw[i*2+1]-OffsetOfTrain;
	}
	for (i ;i < 20;i++) 
	{
		SwitchLab[i*3] = 0;
	}

	return 0;
}
 