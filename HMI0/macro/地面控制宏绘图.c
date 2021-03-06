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
unsigned short int RGBchart[13][3]={
	{0,0,0},
	{0,0,0},				//1 black
	{255,255,255},	//2 white
	{255,0,0},			//3 red
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,255,0},			//7 green
	{0,0,0},
	{0,0,0},
	{255,215,0},		//10 yellow
	{0,0,0},
	{41,82,156}				//12 blue
};  

int MacroEntry()
{
	int i;
	for (i = 0;i < numofline;i++)
	{
		PenParam pen={PS_SOLID,1,RGB(RGBchart[Line[6*i+5]][0],RGBchart[Line[6*i+5]][1],RGBchart[Line[6*i+5]][2])};
		DrawLine(Line[6*i+0], Line[6*i+1],Line[6*i+2], Line[6*i+3], pen);
	}
	for (i = 0;i <numofrect;i++)
	{
		PenParam pen={PS_NULL,1,RGB(0,0,0)};
		BrushParam brh={BFS_SOLID,RGB(RGBchart[Rect[6*i+5]][0],RGBchart[Rect[6*i+5]][1],RGBchart[Rect[6*i+5]][2]),RGB(RGBchart[Rect[6*i+5]][0],RGBchart[Rect[6*i+5]][1],RGBchart[Rect[6*i+5]][2])};
		DrawRect(Rect[6*i+0], Rect[6*i+1],Rect[6*i+2], Rect[6*i+3], pen, brh);
	}
	for (i = 0;i < numofecilps;i++)
	{
		PenParam pen={PS_SOLID,1,RGB(RGBchart[Ecilps[6*i+4]][0],RGBchart[Ecilps[6*i+4]][1],RGBchart[Ecilps[6*i+4]][2])};
		BrushParam brh={BFS_SOLID,RGB(RGBchart[Ecilps[6*i+5]][0],RGBchart[Ecilps[6*i+5]][1],RGBchart[Ecilps[6*i+5]][2]),RGB(RGBchart[Ecilps[6*i+5]][0],RGBchart[Ecilps[6*i+5]][1],RGBchart[Ecilps[6*i+5]][2])};
		DrawEclips(Ecilps[6*i+0], Ecilps[6*i+1],Ecilps[6*i+2], Ecilps[6*i+3], pen, brh);	
	}
	for (i = 0;i < numofarc;i++)
	{
		PenParam pen={PS_SOLID,1,RGB(RGBchart[Arc[6*i+5]][0],RGBchart[Arc[6*i+5]][1],RGBchart[Arc[6*i+5]][2])};
		DrawArc(Arc[6*i+0], Arc[6*i+1], Arc[6*i+2], Arc[6*i+3], 0, Arc[6*i+4]*6,pen);
	}
	return 0;
}
 