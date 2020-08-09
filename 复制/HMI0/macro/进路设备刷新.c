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

#define leftbound1 172
#define rightbound1 588
#define lightbandy 396
#define drawwidth 416
#define reducetimes 4
#define fanSpdReduce 5
#define pixelspd 4
#define FanLimitLen 100
#define IniSpdLimit 40
#define DingSpd 50
#define FanSpd 35
#define MinNegOffset 15000
#define LeftBound 175
#define RightBound 580
#define y 394
#define cleary 170
#define clearwhid 226
#define CurveGrad 3/4
#define ZeroSpdPosit 380
#define MaxSpdLimit 50
#define FanSpdLimitHigh 240
#define OpenSpd 15
//声明各类pen
PenParam pennull={PS_NULL,1,RGB(0,0,0)};//无
PenParam penyellow={PS_SOLID,1,RGB(255,215,0)};//黄
PenParam penred={PS_SOLID,1,RGB(255,0,0)};//红
PenParam penblue={PS_SOLID,1,RGB(41,82,156)};//蓝
PenParam pengreen={PS_SOLID,1,RGB(0,255,0)};//绿
PenParam penwhite={PS_SOLID,1,RGB(255,255,255)};//白
						
//声明各类brush
BrushParam brhnull={BFS_NOBRUSH,RGB(41,82,156),RGB(41,82,156)};//无
BrushParam brhyellow={BFS_SOLID,RGB(255,215,0),RGB(255,215,0)};//黄
BrushParam brhred={BFS_SOLID,RGB(255,0,0),RGB(255,0,0)};//红
BrushParam brhblue={BFS_SOLID,RGB(41,82,156),RGB(41,82,156)};//蓝
BrushParam brhwhite={BFS_SOLID,RGB(255,255,255),RGB(255,255,255)};//白
BrushParam brhblack={BFS_SOLID,RGB(0,0,0),RGB(0,0,0)};//黑
BrushParam brhgreen={BFS_SOLID,RGB(0,255,0),RGB(0,255,0)};//绿

unsigned short min(unsigned short  a, unsigned short  b)
{
    if(a<b) return a;//a更小，返回a。
    return b;//b更小返回b。
}
unsigned short max(unsigned short  a, unsigned short  b)
{
    if(a>b) return a;//a更小，返回a。
    return b;//b更小返回b。
}

int MacroEntry()
{
	unsigned short i,height,ProStartPoint;
	//画一个黑色无边框矩形背景，清屏
	DrawRect(leftbound1, cleary, drawwidth, clearwhid, pennull, brhblack);
	//画黄色基准线
	DrawLine(leftbound1, 60, leftbound1, 428, penyellow);
	//画白光带
	//DrawRect(leftbound1, lightbandy, drawwidth, 5, pennull, brhblue);
	DrawRect(leftbound1, lightbandy, drawwidth, 5, pennull, brhwhite);
 
/*
	//带限速排序的阶梯限速
	unsigned short int indexoftrack, oldindexoftrack,EndTrackIndex,count= 0;
	int OpenSpdHigh = 380 - OpenSpd* pixelspd;

	for (i = 0;i<NumofEffectTrack;i++)
	{
		indexoftrack = LabelSort[i];
		ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[indexoftrack])*CurveGrad;
		//检查终止区段的防护限速值及防护点位置
		if (i != 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint>=leftbound1)&&(ProStartPoint<=NearOfTrack[indexoftrack])&&NearOfTrack[indexoftrack]<=rightbound1)  //防护1
		{
			oldindexoftrack =  LabelSort[i-1];
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[oldindexoftrack])*CurveGrad;
			SpdHighOFTrack[indexoftrack] = SpdHighOFTrack[oldindexoftrack];
			EndTrackIndex = oldindexoftrack;
			DrawLine(FarOfTrack[oldindexoftrack], SpdHighOFTrack[oldindexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[oldindexoftrack], penred);
			break;
		}
		else if (i != 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint<=leftbound1)&&NearOfTrack[indexoftrack]>=MinNegOffset)  //防护1
		{
			oldindexoftrack =  LabelSort[i-1];
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[oldindexoftrack])*CurveGrad;
			SpdHighOFTrack[indexoftrack] = SpdHighOFTrack[oldindexoftrack];
			EndTrackIndex = oldindexoftrack;
			DrawLine(FarOfTrack[oldindexoftrack], SpdHighOFTrack[oldindexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[oldindexoftrack], penred);
			break;
		}
		else if(i == 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint>=leftbound1)&&(ProStartPoint<=NearOfTrack[indexoftrack])&&NearOfTrack[indexoftrack]<=rightbound1)  //防护2
		{
			SpdHighOFTrack[indexoftrack] = FanSpdLimitHigh;
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[indexoftrack])*CurveGrad;
			EndTrackIndex = indexoftrack;
			DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[indexoftrack], penred);
			break;
		}
		else if(i == 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint>=leftbound1)&&NearOfTrack[indexoftrack]>=MinNegOffset)  //防护3
		{
			EndTrackIndex = indexoftrack;
			SpdLimit = (380-SpdHighOFTrack[indexoftrack])/pixelspd;
			DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[indexoftrack], penred);
			break;
		}
		else if(i == 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint<=leftbound1)&&(ProStartPoint<=NearOfTrack[indexoftrack])&&NearOfTrack[indexoftrack]<=rightbound1)  //防护4
		{
			//SpdHighOFTrack[indexoftrack] = FanSpdLimitHigh;
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[indexoftrack])*CurveGrad;
			EndTrackIndex = indexoftrack;
			DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], max(ProStartPoint,leftbound1), SpdHighOFTrack[indexoftrack], penred);
			break;
		}
		else if(i == 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint<=leftbound1)&&NearOfTrack[indexoftrack]>=MinNegOffset)  //防护5
		{
			//SpdHighOFTrack[indexoftrack] = FanSpdLimitHigh;
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[indexoftrack])*CurveGrad;
			EndTrackIndex = indexoftrack;
			break;
		}
		

//绘制阶梯限速曲线
		if ((FarOfTrack[indexoftrack]<=ProStartPoint)&&(ProStartPoint>=leftbound1)) //防护开始点未进入车头位置，远端小于防护开始点
		{
			
			if ((i==0)&&(i!=(NumofEffectTrack-1)))
			{
				DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], FarOfTrack[indexoftrack], SpdHighOFTrack[indexoftrack], penred);
				SpdLimit = (380-SpdHighOFTrack[indexoftrack])/pixelspd;
			}
			else if ((i>0)&&(i<(NumofEffectTrack-1))&&(NearOfTrack[indexoftrack]<rightbound1))
			{
				oldindexoftrack =  LabelSort[i-1];
				DrawLine(NearOfTrack[indexoftrack], SpdHighOFTrack[indexoftrack], FarOfTrack[indexoftrack], SpdHighOFTrack[indexoftrack], penred);
				DrawLine(FarOfTrack[oldindexoftrack], SpdHighOFTrack[oldindexoftrack], NearOfTrack[indexoftrack], SpdHighOFTrack[indexoftrack], penred);
			}
			else if ((i>0)&&(i<(NumofEffectTrack-1))&&(NearOfTrack[indexoftrack]>MinNegOffset))
			{
				oldindexoftrack =  LabelSort[i-1];
				DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], FarOfTrack[indexoftrack], SpdHighOFTrack[indexoftrack], penred);
			}
			else if ((i==0)&&(i==(NumofEffectTrack-1)))
			{
				EndTrackIndex = indexoftrack;
				DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[indexoftrack], penred);
				SpdLimit = (380-SpdHighOFTrack[indexoftrack])/pixelspd;
			}
			else if ((i!=0)&&(i==(NumofEffectTrack-1)))
			{
				oldindexoftrack =  LabelSort[i-1];
				EndTrackIndex = indexoftrack;
				DrawLine(NearOfTrack[indexoftrack], SpdHighOFTrack[indexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[indexoftrack], penred);
				DrawLine(FarOfTrack[oldindexoftrack], SpdHighOFTrack[oldindexoftrack], NearOfTrack[indexoftrack], SpdHighOFTrack[indexoftrack], penred);
			}
		}
		else if ((FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint>leftbound1))//防护开始点未进入车头位置，远端大于防护开始点
		{
			if ((i==0)&&(ProStartPoint>NearOfTrack[indexoftrack]))
			{
				DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[indexoftrack], penred);
				SpdLimit = (380-SpdHighOFTrack[indexoftrack])/pixelspd;
				EndTrackIndex = indexoftrack;
				break;
			}
			else if ((i>0)&&(ProStartPoint>NearOfTrack[indexoftrack]))
			{
				oldindexoftrack =  LabelSort[i-1];
				DrawLine(NearOfTrack[indexoftrack], SpdHighOFTrack[indexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[indexoftrack], penred);
				DrawLine(FarOfTrack[oldindexoftrack], SpdHighOFTrack[oldindexoftrack], NearOfTrack[indexoftrack], SpdHighOFTrack[indexoftrack], penred);
				EndTrackIndex = indexoftrack;
				break;
			}
		}
	}



	if (SpdHighOFTrack[EndTrackIndex]>=140&&SpdHighOFTrack[EndTrackIndex]<=380) //判断终点限速值是否合法
	{
		ProLimitSpd =(380-SpdHighOFTrack[EndTrackIndex])/pixelspd;
	}
	else  //不合法防护限速值置零
	{
		ProLimitSpd = 0;
		SpdLimit = 0;
	}
	if (EndPointOffset>=leftbound1&&ProStartPoint<=leftbound1)//防护曲线进入车头位置
	{
		SpdLimit = max((EndPointOffset-leftbound1)/3,OpenSpd);
		ProLimitSpd = SpdLimit;
	}
	else if (EndPointOffset>=MinNegOffset||EndPointOffset<=leftbound1+5)
	{
		ProLimitSpd = 0;
		SpdLimit = OpenSpd;
	}
	//画防护曲线
	if (EndPointOffset<rightbound1&&EndPointOffset>leftbound1)
	{
		int Protectwide = ProLimitSpd * pixelspd*CurveGrad*2;
		int Protecthigh = (ProLimitSpd  - OpenSpd)* pixelspd * 2+1;
		int Protectwidex = EndPointOffset-Protectwide;
		int Protectwidey = 380-ProLimitSpd*pixelspd;
		DrawArc(Protectwidex, Protectwidey, Protectwide, Protecthigh, 0, 90, penred);
		DrawLine(EndPointOffset, OpenSpdHigh, rightbound1, OpenSpdHigh, penred);
		if(EndPointOffset<=leftbound1+OpenSpd * pixelspd*CurveGrad+2)
		{
			DrawLine(leftbound1, OpenSpdHigh, EndPointOffset, OpenSpdHigh, penred);
		}
	}

	if(NumofEffectTrack == 0)
	{
		DrawLine(leftbound1, OpenSpdHigh, rightbound1, OpenSpdHigh, penred);
		SpdLimit = OpenSpd;
	}
*/
	//画信号机
	for(i=0;i<NumofLights;i++)
		{
			if(OffsetofLights[i]>LeftBound&&OffsetofLights[i]<RightBound)
				{
					if(StateofLights[i]==9||StateofLights[i]==10)//判断信号灯类型（颜色），设置灯显示高度
					{
						height = 90;
					}
					else if(StateofLights[i]>16)
					{
						height = 30;
					}
					else if(StateofLights[i]<9||(10<StateofLights[i]&&StateofLights[i]<=16))
					{
						height = 210;
					}
					else 
					{
						height = 210;
					}

					int x11=OffsetofLights[i],y11=y,x12=OffsetofLights[i],y12=y-height;
					int x21=OffsetofLights[i]-6,y21=y-height-13,w21=14,h21=14;
					DrawLine(x11, y11, x12, y12, penblue);//画立柱

					if (StateofLights[i]==1) //绿
					{
						DrawEclips(x21, y21, w21, h21, pengreen, brhgreen);	
					}
					else if (StateofLights[i]==2)//黄
					{
						DrawEclips(x21, y21, w21, h21, penyellow, brhyellow);
					}
					else if (StateofLights[i]==4)//双黄
					{
						DrawEclips(x21, y21, w21, h21, penyellow, brhyellow);
						DrawEclips(x21, y21+14, w21, h21, penyellow, brhyellow);
					}
					else if (StateofLights[i]==8)//红
					{
						DrawEclips(x21, y21, w21, h21, penred, brhred);	
					}
					else if (StateofLights[i]==9)//蓝
					{
						DrawEclips(x21, y21, w21, h21, penblue, brhblue);	
					}
					else if (StateofLights[i]==10)//白
					{
						DrawEclips(x21, y21, w21, h21, penwhite, brhwhite);	
					}
					else if (StateofLights[i]>=16)//反向信号机
					{
						DrawEclips(x21, y21, w21, h21, penblue, brhnull);	
					}
					
				}
		}
//画区段
	for(i=0;i<NumofTracks;i++)
		{
			if (NearOfTrack[i]>=leftbound1&&NearOfTrack[i]<rightbound1&&FarOfTrack[i]<MinNegOffset)
			{
				int x11=NearOfTrack[i],y11=396,x12=min(FarOfTrack[i],rightbound1)-NearOfTrack[i],y12=5;
				if(ColorofTracks[i]==1)//光带红
				{
					DrawRect( x11, y11, x12,y12, pennull, brhred);	
				}
				else if(ColorofTracks[i]==2)//光带白
				{
					DrawRect( x11, y11, x12,y12, pennull, brhwhite);	
				}
				else if(ColorofTracks[i]==3)//光带蓝
				{
					DrawRect( x11, y11, x12,y12, pennull, brhblue);	
				}
				else if(ColorofTracks[i]==0x0f)//光带有车
				{
					DrawRect( x11, y11, x12,y12, pennull, brhred);	
					DrawRect( NearOfTrack[i], 396-6, 40,6, pennull, brhblue);	
					DrawRect( NearOfTrack[i]+8, 396-12, 40-8,6, pennull, brhblue);	
					DrawLine(NearOfTrack[i]+8, 396-12+2, NearOfTrack[i]+2, 396-6, penblue);
				}
			}
			else if (NearOfTrack[i]>MinNegOffset&&FarOfTrack[i]<MinNegOffset)
			{
				int x11=leftbound1,y11=396,x12=min(FarOfTrack[i],rightbound1)-leftbound1,y12=5;
				if(ColorofTracks[i]==1)//光带红
				{
					DrawRect( x11, y11, x12,y12, pennull, brhred);	
				}
				else if(ColorofTracks[i]==2)//光带白
				{
					DrawRect( x11, y11, x12,y12, pennull, brhwhite);	
				}
				else if(ColorofTracks[i]==3)//光带蓝
				{
					DrawRect( x11, y11, x12,y12, pennull, brhblue);	
				}
				else if(ColorofTracks[i]==0x0f)//光带有车
				{
					DrawRect( x11, y11, x12,y12, pennull, brhred);	
					DrawRect( NearOfTrack[i], 396-6, 40,6, pennull, brhblue);	
					DrawRect( NearOfTrack[i]+8, 396-12, 40-8,6, pennull, brhblue);	
					DrawLine(NearOfTrack[i]+8, 396-12+2, NearOfTrack[i]+2, 396-6, penblue);
				}
			}
			

		}

	//画道岔
	for(i=0;i<NumofSwitchs;i++)
		{
			int HighofSwitch = 210;
			if(OffsetofSwitchs[i]>LeftBound&&OffsetofSwitchs[i]<RightBound)
			{
				DrawLine(OffsetofSwitchs[i], y-HighofSwitch,OffsetofSwitchs[i], y, penblue);//画立柱

			   if(StateofSwitchs[i]==1)  //定位
				{
					DrawLine(OffsetofSwitchs[i]-6, y-HighofSwitch, OffsetofSwitchs[i]+6, y-HighofSwitch-5, pengreen);
					DrawLine(OffsetofSwitchs[i]-6, y-HighofSwitch, OffsetofSwitchs[i]+6, y-HighofSwitch+5, pengreen);
				}
				else if(StateofSwitchs[i]==2) //反位
				{					
					DrawLine(OffsetofSwitchs[i]+6, y-HighofSwitch, OffsetofSwitchs[i]-6, y-HighofSwitch-5, penyellow);
					DrawLine(OffsetofSwitchs[i]+6, y-HighofSwitch, OffsetofSwitchs[i]-6, y-HighofSwitch+5, penyellow);
				}
				else if(StateofSwitchs[i]==3)  //故障
				{
					DrawLine(OffsetofSwitchs[i]-6, y-HighofSwitch-6, OffsetofSwitchs[i]+6, y-HighofSwitch+6, penred);
					DrawLine(OffsetofSwitchs[i]-6, y-HighofSwitch+6, OffsetofSwitchs[i]+6, y-HighofSwitch-6, penred);
				}
			}

		}
	//画特殊设备

	for(i=0;i<NumofSpes;i++)
		{
			int HighofSpe = 190;
			if(OffsetofSpes[i]>LeftBound&&OffsetofSpes[i]<RightBound)
			{
				DrawLine(OffsetofSpes[i], y-HighofSpe, OffsetofSpes[i]-10, y-HighofSpe-10, penred);
				DrawLine(OffsetofSpes[i], y-HighofSpe, OffsetofSpes[i]+10, y-HighofSpe-10,penred);
				DrawLine(OffsetofSpes[i]-10, y-HighofSpe-10, OffsetofSpes[i], y-HighofSpe-20, penred);
				DrawLine(OffsetofSpes[i]+10, y-HighofSpe-10, OffsetofSpes[i], y-HighofSpe-20, penred);
				DrawLine(OffsetofSpes[i], y-HighofSpe, OffsetofSpes[i], y, penblue);
			}
		}
		//开始标签匹配
	LabelMatch = 1;
	return 0;
} 