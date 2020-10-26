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
//��������pen
PenParam pennull={PS_NULL,1,RGB(0,0,0)};//��
PenParam penyellow={PS_SOLID,1,RGB(255,215,0)};//��
PenParam penred={PS_SOLID,1,RGB(255,0,0)};//��
PenParam penblue={PS_SOLID,1,RGB(41,82,156)};//��
PenParam pengreen={PS_SOLID,1,RGB(0,255,0)};//��
PenParam penwhite={PS_SOLID,1,RGB(255,255,255)};//��
						
//��������brush
BrushParam brhnull={BFS_NOBRUSH,RGB(41,82,156),RGB(41,82,156)};//��
BrushParam brhyellow={BFS_SOLID,RGB(255,215,0),RGB(255,215,0)};//��
BrushParam brhred={BFS_SOLID,RGB(255,0,0),RGB(255,0,0)};//��
BrushParam brhblue={BFS_SOLID,RGB(41,82,156),RGB(41,82,156)};//��
BrushParam brhwhite={BFS_SOLID,RGB(255,255,255),RGB(255,255,255)};//��
BrushParam brhblack={BFS_SOLID,RGB(0,0,0),RGB(0,0,0)};//��
BrushParam brhgreen={BFS_SOLID,RGB(0,255,0),RGB(0,255,0)};//��

unsigned short min(unsigned short  a, unsigned short  b)
{
    if(a<b) return a;//a��С������a��
    return b;//b��С����b��
}
unsigned short max(unsigned short  a, unsigned short  b)
{
    if(a>b) return a;//a��С������a��
    return b;//b��С����b��
}

int MacroEntry()
{
	unsigned short i,height,ProStartPoint;
	//��һ����ɫ�ޱ߿���α���������
	DrawRect(leftbound1, cleary, drawwidth, clearwhid, pennull, brhblack);
	//����ɫ��׼��
	DrawLine(leftbound1, 60, leftbound1, 428, penyellow);
	//���׹��
	//DrawRect(leftbound1, lightbandy, drawwidth, 5, pennull, brhblue);
	DrawRect(leftbound1, lightbandy, drawwidth, 5, pennull, brhwhite);
 
/*
	//����������Ľ�������
	unsigned short int indexoftrack, oldindexoftrack,EndTrackIndex,count= 0;
	int OpenSpdHigh = 380 - OpenSpd* pixelspd;

	for (i = 0;i<NumofEffectTrack;i++)
	{
		indexoftrack = LabelSort[i];
		ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[indexoftrack])*CurveGrad;
		//�����ֹ���εķ�������ֵ��������λ��
		if (i != 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint>=leftbound1)&&(ProStartPoint<=NearOfTrack[indexoftrack])&&NearOfTrack[indexoftrack]<=rightbound1)  //����1
		{
			oldindexoftrack =  LabelSort[i-1];
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[oldindexoftrack])*CurveGrad;
			SpdHighOFTrack[indexoftrack] = SpdHighOFTrack[oldindexoftrack];
			EndTrackIndex = oldindexoftrack;
			DrawLine(FarOfTrack[oldindexoftrack], SpdHighOFTrack[oldindexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[oldindexoftrack], penred);
			break;
		}
		else if (i != 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint<=leftbound1)&&NearOfTrack[indexoftrack]>=MinNegOffset)  //����1
		{
			oldindexoftrack =  LabelSort[i-1];
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[oldindexoftrack])*CurveGrad;
			SpdHighOFTrack[indexoftrack] = SpdHighOFTrack[oldindexoftrack];
			EndTrackIndex = oldindexoftrack;
			DrawLine(FarOfTrack[oldindexoftrack], SpdHighOFTrack[oldindexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[oldindexoftrack], penred);
			break;
		}
		else if(i == 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint>=leftbound1)&&(ProStartPoint<=NearOfTrack[indexoftrack])&&NearOfTrack[indexoftrack]<=rightbound1)  //����2
		{
			SpdHighOFTrack[indexoftrack] = FanSpdLimitHigh;
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[indexoftrack])*CurveGrad;
			EndTrackIndex = indexoftrack;
			DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[indexoftrack], penred);
			break;
		}
		else if(i == 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint>=leftbound1)&&NearOfTrack[indexoftrack]>=MinNegOffset)  //����3
		{
			EndTrackIndex = indexoftrack;
			SpdLimit = (380-SpdHighOFTrack[indexoftrack])/pixelspd;
			DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], min(ProStartPoint,rightbound1), SpdHighOFTrack[indexoftrack], penred);
			break;
		}
		else if(i == 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint<=leftbound1)&&(ProStartPoint<=NearOfTrack[indexoftrack])&&NearOfTrack[indexoftrack]<=rightbound1)  //����4
		{
			//SpdHighOFTrack[indexoftrack] = FanSpdLimitHigh;
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[indexoftrack])*CurveGrad;
			EndTrackIndex = indexoftrack;
			DrawLine(leftbound1, SpdHighOFTrack[indexoftrack], max(ProStartPoint,leftbound1), SpdHighOFTrack[indexoftrack], penred);
			break;
		}
		else if(i == 0&&(FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint<=leftbound1)&&NearOfTrack[indexoftrack]>=MinNegOffset)  //����5
		{
			//SpdHighOFTrack[indexoftrack] = FanSpdLimitHigh;
			ProStartPoint = EndPointOffset-(380-SpdHighOFTrack[indexoftrack])*CurveGrad;
			EndTrackIndex = indexoftrack;
			break;
		}
		

//���ƽ�����������
		if ((FarOfTrack[indexoftrack]<=ProStartPoint)&&(ProStartPoint>=leftbound1)) //������ʼ��δ���복ͷλ�ã�Զ��С�ڷ�����ʼ��
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
		else if ((FarOfTrack[indexoftrack]>=ProStartPoint)&&(ProStartPoint>leftbound1))//������ʼ��δ���복ͷλ�ã�Զ�˴��ڷ�����ʼ��
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



	if (SpdHighOFTrack[EndTrackIndex]>=140&&SpdHighOFTrack[EndTrackIndex]<=380) //�ж��յ�����ֵ�Ƿ�Ϸ�
	{
		ProLimitSpd =(380-SpdHighOFTrack[EndTrackIndex])/pixelspd;
	}
	else  //���Ϸ���������ֵ����
	{
		ProLimitSpd = 0;
		SpdLimit = 0;
	}
	if (EndPointOffset>=leftbound1&&ProStartPoint<=leftbound1)//�������߽��복ͷλ��
	{
		SpdLimit = max((EndPointOffset-leftbound1)/3,OpenSpd);
		ProLimitSpd = SpdLimit;
	}
	else if (EndPointOffset>=MinNegOffset||EndPointOffset<=leftbound1+5)
	{
		ProLimitSpd = 0;
		SpdLimit = OpenSpd;
	}
	//����������
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
	//���źŻ�
	for(i=0;i<NumofLights;i++)
		{
			if(OffsetofLights[i]>LeftBound&&OffsetofLights[i]<RightBound)
				{
					if(StateofLights[i]==9||StateofLights[i]==10)//�ж��źŵ����ͣ���ɫ�������õ���ʾ�߶�
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
					DrawLine(x11, y11, x12, y12, penblue);//������

					if (StateofLights[i]==1) //��
					{
						DrawEclips(x21, y21, w21, h21, pengreen, brhgreen);	
					}
					else if (StateofLights[i]==2)//��
					{
						DrawEclips(x21, y21, w21, h21, penyellow, brhyellow);
					}
					else if (StateofLights[i]==4)//˫��
					{
						DrawEclips(x21, y21, w21, h21, penyellow, brhyellow);
						DrawEclips(x21, y21+14, w21, h21, penyellow, brhyellow);
					}
					else if (StateofLights[i]==8)//��
					{
						DrawEclips(x21, y21, w21, h21, penred, brhred);	
					}
					else if (StateofLights[i]==9)//��
					{
						DrawEclips(x21, y21, w21, h21, penblue, brhblue);	
					}
					else if (StateofLights[i]==10)//��
					{
						DrawEclips(x21, y21, w21, h21, penwhite, brhwhite);	
					}
					else if (StateofLights[i]>=16)//�����źŻ�
					{
						DrawEclips(x21, y21, w21, h21, penblue, brhnull);	
					}
					
				}
		}
//������
	for(i=0;i<NumofTracks;i++)
		{
			if (NearOfTrack[i]>=leftbound1&&NearOfTrack[i]<rightbound1&&FarOfTrack[i]<MinNegOffset)
			{
				int x11=NearOfTrack[i],y11=396,x12=min(FarOfTrack[i],rightbound1)-NearOfTrack[i],y12=5;
				if(ColorofTracks[i]==1)//�����
				{
					DrawRect( x11, y11, x12,y12, pennull, brhred);	
				}
				else if(ColorofTracks[i]==2)//�����
				{
					DrawRect( x11, y11, x12,y12, pennull, brhwhite);	
				}
				else if(ColorofTracks[i]==3)//�����
				{
					DrawRect( x11, y11, x12,y12, pennull, brhblue);	
				}
				else if(ColorofTracks[i]==0x0f)//����г�
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
				if(ColorofTracks[i]==1)//�����
				{
					DrawRect( x11, y11, x12,y12, pennull, brhred);	
				}
				else if(ColorofTracks[i]==2)//�����
				{
					DrawRect( x11, y11, x12,y12, pennull, brhwhite);	
				}
				else if(ColorofTracks[i]==3)//�����
				{
					DrawRect( x11, y11, x12,y12, pennull, brhblue);	
				}
				else if(ColorofTracks[i]==0x0f)//����г�
				{
					DrawRect( x11, y11, x12,y12, pennull, brhred);	
					DrawRect( NearOfTrack[i], 396-6, 40,6, pennull, brhblue);	
					DrawRect( NearOfTrack[i]+8, 396-12, 40-8,6, pennull, brhblue);	
					DrawLine(NearOfTrack[i]+8, 396-12+2, NearOfTrack[i]+2, 396-6, penblue);
				}
			}
			

		}

	//������
	for(i=0;i<NumofSwitchs;i++)
		{
			int HighofSwitch = 210;
			if(OffsetofSwitchs[i]>LeftBound&&OffsetofSwitchs[i]<RightBound)
			{
				DrawLine(OffsetofSwitchs[i], y-HighofSwitch,OffsetofSwitchs[i], y, penblue);//������

			   if(StateofSwitchs[i]==1)  //��λ
				{
					DrawLine(OffsetofSwitchs[i]-6, y-HighofSwitch, OffsetofSwitchs[i]+6, y-HighofSwitch-5, pengreen);
					DrawLine(OffsetofSwitchs[i]-6, y-HighofSwitch, OffsetofSwitchs[i]+6, y-HighofSwitch+5, pengreen);
				}
				else if(StateofSwitchs[i]==2) //��λ
				{					
					DrawLine(OffsetofSwitchs[i]+6, y-HighofSwitch, OffsetofSwitchs[i]-6, y-HighofSwitch-5, penyellow);
					DrawLine(OffsetofSwitchs[i]+6, y-HighofSwitch, OffsetofSwitchs[i]-6, y-HighofSwitch+5, penyellow);
				}
				else if(StateofSwitchs[i]==3)  //����
				{
					DrawLine(OffsetofSwitchs[i]-6, y-HighofSwitch-6, OffsetofSwitchs[i]+6, y-HighofSwitch+6, penred);
					DrawLine(OffsetofSwitchs[i]-6, y-HighofSwitch+6, OffsetofSwitchs[i]+6, y-HighofSwitch-6, penred);
				}
			}

		}
	//�������豸

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
		//��ʼ��ǩƥ��
	LabelMatch = 1;
	return 0;
} 