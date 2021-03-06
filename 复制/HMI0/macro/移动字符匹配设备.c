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

#define LeftBound 180
#define RightBound 580
#define leftbound1 173

int MacroEntry()
{
   unsigned short i = 0;
	unsigned short j = 0;
	unsigned short k = 0;
	for(i = 0;i<20;i++)
	{
		SignalLab[i*3] = 0;
		SwitchLab[i*3] = 0;
	}

	for(i = 0;i<20;i++)
	{
		
		if (OffsetofSwitchs[i]>LeftBound&&OffsetofSwitchs[i]<RightBound)
			{
				SwitchLabel[j*3] = LabelOfSwitchs[i];
				SwitchLabel[j*3+1] = OffsetofSwitchs[i]-leftbound1;
				j = j+1;
				
			}
	}
	for (j;j<20;j++)
	{
		SwitchLabel[j*3] = 0; 
	}

	for(i = 0;i<19;i++)
	{
		if (OffsetofLights[i]>LeftBound&&OffsetofLights[i]<RightBound&&OffsetofLights[i]!=OffsetofLights[i+1])
			{
				SignalLabel[k*3] = LabelOfLights[i];
				SignalLabel[k*3+1] = OffsetofLights[i]-leftbound1;
				k = k+1;
			}
	}

	for (k;k<20;k++)
	{
		SignalLabel[k*3] = 0; 
	}

	return 0;
}
 