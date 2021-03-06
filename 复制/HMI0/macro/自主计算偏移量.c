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
	short int i ,drawflag, OffsetChange= 0;
   double tempOffsetChange;
   tempOffsetChange =v*3.6+a/2;      							//计算偏移量减少量，v为当前速度
   OffsetChange = (short int)tempOffsetChange;
	//v = v+a;																			   //根据加速度更新当前速度
	for(i=0;i<NumofLights;i++)											//更新当前需要绘制的设备偏移量
		{
			OffsetofLights[i] -= OffsetChange;
			if(StateofLights[i] == 9 && OffsetofLights[i] <= 180)
				{
					drawflag = 0;
					v = 0;
				}
			else
				{
					drawflag = 1;
				}
		}
	for(i=0;i<NumofSwitchs;i++)
		{
			OffsetofSwitchs[i] -= OffsetChange;
		}
	for(i=0;i<NumofTracks;i++)
		{
			NearOfTrack[i] -= OffsetChange;
			FarOfTrack[i] -= OffsetChange;
		}
	if(drawflag == 1)
	{
		LB100 = 1;	
	}																		//开启画图
	return 0;
}
 