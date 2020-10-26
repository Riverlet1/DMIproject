#include "macrotypedef.h"
#include "math.h"
#include "string.h"

#define CycleTime  1200
#define Switch  0xA1
#define Light  0xA2
#define Track  0xA3
#define Spe  0xA4
#define TurnbackTip  0xA7
#define ShuntingList  0xB2
#define Liechezhuangtai  0xC0
#define OffsetOfTrain  172
#define IniSpdLimit 40
#define pixelspd 4
#define LeftBound 180
#define RightBound 580
#define ControlDrawLen  65
#define EqpArrayLen  20
#define MinNegOffset 15000
#define MapMultiple 9/10   
#define CurveGrad 4/3	
#define OpenSpd 15
#define CommSignIni 60*1000   
/*CycleTime      20200626 ???????*/
unsigned char message[8] = {0};

#define RS485_REC_BUFF_SIZE 64
#define RS485_SEND_BUFF_SIZE 64

unsigned char RS485_Rec_buff[RS485_REC_BUFF_SIZE] ;
unsigned char RS485_Send_buff[RS485_SEND_BUFF_SIZE] ;
unsigned int RS485_rec_counter = 0 ;

typedef struct
{
	unsigned char Fangxiang;
	unsigned char TypeOfData;
	unsigned char Gouxu;
	unsigned char Gudaohao;
	unsigned char Jishi;
	unsigned char Zuoyefangfa;
	unsigned char Liangshu;
	unsigned char Cheliangbianma[3];
} Diaochedan;
unsigned char framehead[3]={0,0,0};
int headp=0;
int handle;
//route dispatch variable
unsigned char NumofSpeShang = 0;
unsigned char LabelOfSwitchShang[EqpArrayLen] = {0};
unsigned char StateOfSwitchShang[EqpArrayLen] = {0};
unsigned short OffsetOfSwitchShang[EqpArrayLen] = {0};
unsigned char LabelOfLightShang[EqpArrayLen] = {0};
unsigned char StateOfLightShang[EqpArrayLen] = {0};
unsigned short OffsetOfLightShang[20] = {0};
unsigned char LabelOfTrackShang[20] = {0};
unsigned char ColorOfTrackShang[20] = {0};
unsigned short NearOfTrackShang[20] = {0};
unsigned short FarOfTrackShang[20] = {0};
unsigned char KindOfSpeShang[20] = {0};
unsigned short OffsetOfSpeShang[20] = {0};
unsigned char NumofSpeXia = 0;
unsigned char LabelOfSwitchXia[EqpArrayLen] = {0};
unsigned char StateOfSwitchXia[EqpArrayLen] = {0};
unsigned short OffsetOfSwitchXia[EqpArrayLen] = {0};
unsigned char LabelOfLightXia[EqpArrayLen] = {0};
unsigned char StateOfLightXia[EqpArrayLen] = {0};
unsigned short OffsetOfLightXia[20] = {0};
unsigned char LabelOfTrackXia[20] = {0};
unsigned char ColorOfTrackXia[20] = {0};
unsigned short NearOfTrackXia[20] = {0};
unsigned short FarOfTrackXia[20] = {0};
unsigned char KindOfSpeXia[20] = {0};
unsigned short OffsetOfSpeXia[20] = {0};
unsigned short TempOffset = 0;
int aaabbb=0;


//unsigned short EndPointOffset;
unsigned short OpenOffset;
unsigned short DangerOffset;
//unsigned short ProLimitSpd;
//unsigned short SpdLimit;
unsigned short FaultOrEnd[20] = {0};
unsigned short FaultOrderNum = 0;
unsigned char IsOpenTrack = 0;
unsigned short i,ii,boolsign,IndexofInsert;
unsigned short int j;
unsigned short int tempcount;
unsigned short int NormalMark; 
unsigned short Temp3Spd[3] = {0}; 
unsigned short int Spd3Index = 0; 
unsigned short int CurentEndOffset = 0;
unsigned short int OldEndOffset = 0;
unsigned short int CurentSpd = 0;
short int Acceleration = 0;
unsigned char NumOfEquip = 60;
unsigned char NumOfEquipinArray = 0;
unsigned char TypeOfEquip;
unsigned char LableOfEquip;
unsigned char StateOfEquip;
unsigned char OffsetOfEquipH;
unsigned char OffsetOfEquipL;
unsigned int EndSign;
unsigned char numofindex;
//shunt data dispatch variable
Diaochedan diaochedan;
unsigned short TempGouNum = 0;
unsigned char LiangS[41] = {0};
unsigned char FangX[41] = {0};
unsigned char ZuoYFF[41] = {0};
unsigned char GuDH[41] = {0};
unsigned short int CheLBM[41][2] = {0};
unsigned char JiS[41] = {0};
unsigned int cheliangbianma = 0;
unsigned int ShuntNum = 0;
unsigned int OldShuntNum = 0;
unsigned int Zonggoushu = 0;
unsigned short CommSign = 0;
unsigned short ArrayCheck(unsigned char templabel,unsigned char LabelArray[20])
{
	unsigned short index,sign;
	for(index = 0;index < 20;index ++)
	{
		if ((LabelArray[index] == templabel)||(LabelArray[index] == 0))
		{
			sign = 1;
			IndexofInsert = index;
			break;
		}
		else
		{
			sign = 0;
		}
	}
	return sign;
}
unsigned char NumofEqp(unsigned char LabelArray[])
{
	unsigned char num = 0;
	int index;
	for(index = 0;index < 20;index ++)
	{
		if(LabelArray[index] == 0)
		{
			num = num;
			break;
		}
		else
		{
			num = num + 1;
		}
	}
	return num;
}

unsigned char NumofArray(unsigned short Array[])
{
	unsigned char num = 0;
	int index;
	for(index = 0;index < 15;index ++)
	{
		if(Array[index] == 0)
		{
			num = num;
			break;
		}
		else
		{
			num = num + 1;
		}
	}
	return num;
}

int MacroEntry()
{
	//ColorofTracks[0] = 1;
	unsigned char EqpFangxiang  = 0;
	if(DimianData[0] == 0xa6 && DimianData[1]==0x00 && DimianData[2]==0x55 )
    { 
		for(i = 0; i < 8;i ++)
		{
			Yuyinzhen[i] = DimianData[i+16];
		}
		Xiansu = DimianData[41];
		Shangxiaxing = DimianData[25];
		SpdLimit= DimianData[41];
		if(DimianData[51] == 0x02||DimianData[51]==0x04)
		{Zhengxiangshoubing = DimianData[51];}
		for(i = 0; i < DimianData[52];i ++)
		{
			for(j= 0;j < 8;j++)
			{
				message[j] = DimianData[56+8*i+j];
			}
			TempOffset = (message[4]*16*16+message[3])*MapMultiple+OffsetOfTrain;
			switch(message[0])						
			{
				case Switch:
						boolsign = ArrayCheck(message[1],LabelOfSwitchShang);
						if (boolsign == 1)
						{	
							LabelOfSwitchShang[IndexofInsert] = message[1];
							StateOfSwitchShang[IndexofInsert] = message[2]&0x0f;
							OffsetOfSwitchShang[IndexofInsert] = TempOffset;
						}
					break;
				case Light:
					
						boolsign = ArrayCheck(message[1],LabelOfLightShang);
						if (boolsign == 1)
						{	
						LabelOfLightShang[IndexofInsert] = message[1];
							StateOfLightShang[IndexofInsert] = message[2];
							OffsetOfLightShang[IndexofInsert] = TempOffset;
						}
					break;
		
				case Track:
						boolsign = ArrayCheck(message[1],LabelOfTrackShang);
		
						if (boolsign == 1)
		
						{	
		
							LabelOfTrackShang[IndexofInsert] = message[1];
		
							ColorOfTrackShang[IndexofInsert] = message[7]&0x0f;
							NearOfTrackShang[IndexofInsert] = TempOffset;
							FarOfTrackShang[IndexofInsert] =  (message[6]*16*16+message[5])*MapMultiple+OffsetOfTrain;
						}
		
					break;
		
				case Spe: 
						KindOfSpeShang[NumofSpeShang] = message[1];
		
						OffsetOfSpeShang[NumofSpeShang] = TempOffset;
		
						NumofSpeShang++;
					break;
				case 0xc1:
						if(shoubing == Zhengxiangshoubing && (shoubing == 0x02 || shoubing == 0x04))
						{
							DangerSheBeiOffset = message[4]*16*16 +message[3];
							if(message[2]<4 && message[2]>0)
							{
								memset(&DangerSheBei[1],0,3);
								tempcount = message[2];
								DangerSheBei[tempcount] = message[1];
								
							}
						}
					break;
		
			}

			if(message[5] == 1 && message[0] == Light&&Zhengxiangshoubing == shoubing)
			{	
					NumofSwitchs = NumofEqp(LabelOfSwitchShang);
					NumofLights = NumofEqp(LabelOfLightShang);
					NumofTracks = NumofEqp(LabelOfTrackShang);
					NumofSpes = NumofSpeShang; 
					for(i = 0;i<20;i++)
					{
						OffsetofSwitchs[i] = OffsetOfSwitchShang[i];				
						StateofSwitchs[i] =StateOfSwitchShang[i];				
						LabelofSwitchs[i] =LabelOfSwitchShang[i];				
		
						OffsetofLights[i] = OffsetOfLightShang[i];				
		
						StateofLights[i] = StateOfLightShang[i];				
		
						LabelofLights[i] =LabelOfLightShang[i];								
		
						NearOfTrack[i] = NearOfTrackShang[i];				
		
						ColorofTracks[i] = ColorOfTrackShang[i];				
		
						FarOfTrack[i] = FarOfTrackShang[i];				
		
						KindofSpe[i] = KindOfSpeShang[i];		
		
						OffsetofSpes[i] = OffsetOfSpeShang[i];
		
						OffsetOfSwitchShang[i] = 0;
		
						StateOfSwitchShang[i] = 0;
		
						LabelOfSwitchShang[i] = 0;
		
						OffsetOfLightShang[i] = 0;
		
						StateOfLightShang[i] = 0;
		
						LabelOfLightShang[i] = 0;
		
						NearOfTrackShang[i] = 0; 
		
						ColorOfTrackShang[i] = 0;
		
						FarOfTrackShang[i] = 0;
		
						KindOfSpeShang[i] = 0;
		
						OffsetOfSpeShang[i] = 0;
		
						LabelOfTrackShang[i] = 0;
		
						OffsetOfSwitchXia[i] = 0;
		
						StateOfSwitchXia[i] = 0;
		
						LabelOfSwitchXia[i] = 0;
		
						OffsetOfLightXia[i] = 0;
		
						StateOfLightXia[i] = 0;
		
						LabelOfLightXia[i] = 0;
		
						NearOfTrackXia[i] = 0; 
		
						ColorOfTrackXia[i] = 0;
		
						FarOfTrackXia[i] = 0;
		
						KindOfSpeXia[i] = 0;
		
						OffsetOfSpeXia[i] = 0;
		
						LabelOfTrackXia[i] = 0;
		
					} 
		
					if(LB101==0&&LB102==0&&LB103==0&&LB104==0&&LB105==0)
		
					{LB100 = 1;}
		
					NumofSpeShang = 0;
		
					NumofSpeXia = 0;
		
			}
		}
		numofindex = 64+8*DimianData[52]+4;
		if(DimianData[numofindex-1]==0x02||DimianData[numofindex-1]==0x04)
		{Fanxiangshoubing = DimianData[numofindex-1];}
		for(i = 0; i < DimianData[numofindex];i ++)
		{
			for(j= 0;j < 8;j++)
			{
				message[j] = DimianData[numofindex+4+8*i+j];
			}
			TempOffset = (message[4]*16*16+message[3])*MapMultiple+OffsetOfTrain;
			switch(message[0])						
			{
				case Switch:
				
						boolsign = ArrayCheck(message[1],LabelOfSwitchXia);
						if (boolsign == 1)
						{	
							LabelOfSwitchXia[IndexofInsert] = message[1];
							StateOfSwitchXia[IndexofInsert] = message[2]&0x0f;
							OffsetOfSwitchXia[IndexofInsert] = TempOffset;
						}
					
					break;
				case Light:
					
						boolsign = ArrayCheck(message[1],LabelOfLightXia);
						if(message[2]&0x80)
						message[2] &= 0x7f;
						else
						message[2] |= 0x80;
						if (boolsign == 1)
						{	
		
							LabelOfLightXia[IndexofInsert] = message[1];
		
							StateOfLightXia[IndexofInsert] = message[2];
		
							OffsetOfLightXia[IndexofInsert] = TempOffset;
		
						}
		
					
		
					break;
		
				case Track:
		
				

						boolsign = ArrayCheck(message[1],LabelOfTrackXia);
		
						if (boolsign == 1)
		
						{	
		
							LabelOfTrackXia[IndexofInsert] = message[1];
		
							ColorOfTrackXia[IndexofInsert] = message[7];
		
							NearOfTrackXia[IndexofInsert] = TempOffset;
		
							FarOfTrackXia[IndexofInsert] =  (message[6]*16*16+message[5])*MapMultiple+OffsetOfTrain;
		
						}
		
					break;
		
				case Spe: 
		
						KindOfSpeXia[NumofSpeXia] = message[1];
		
						OffsetOfSpeXia[NumofSpeXia] = TempOffset;
		
						NumofSpeXia++;
		
					break;

				case 0xc1:
						if(shoubing != Zhengxiangshoubing &&(shoubing == 0x02 || shoubing == 0x04))
						{
							DangerSheBeiOffset = message[4]*16*16 +message[3];
							if(message[2]<4 && message[2]>0)
							{
								memset(&DangerSheBei[1],0,3);
								tempcount = message[2];
								DangerSheBei[tempcount] = message[1];
								
							}
						}
					break;
			}

			if(message[5] == 1 && message[0] == Light&&shoubing == Fanxiangshoubing)
			{	
					NumofSwitchs = NumofEqp(LabelOfSwitchXia);
		
					NumofLights = NumofEqp(LabelOfLightXia);
		
					NumofTracks = NumofEqp(LabelOfTrackXia);
		
					NumofSpes = NumofSpeXia;  
					for(i = 0;i<20;i++)
		
					{
		
						OffsetofSwitchs[i] = OffsetOfSwitchXia[i];				
		
						StateofSwitchs[i] =StateOfSwitchXia[i];				
		
						LabelofSwitchs[i] =LabelOfSwitchXia[i];				
		
						OffsetofLights[i] = OffsetOfLightXia[i];				
		
						StateofLights[i] = StateOfLightXia[i];				
		
						LabelofLights[i] =LabelOfLightXia[i];								
		
						NearOfTrack[i] = NearOfTrackXia[i];				
		
						ColorofTracks[i] = ColorOfTrackXia[i];				
		
						FarOfTrack[i] = FarOfTrackXia[i];				
		
						KindofSpe[i] = KindOfSpeXia[i];		
		
						OffsetofSpes[i] = OffsetOfSpeXia[i];
		
						OffsetOfSwitchShang[i] = 0;
		
						StateOfSwitchShang[i] = 0;
		
						LabelOfSwitchShang[i] = 0;
		
						OffsetOfLightShang[i] = 0;
		
						StateOfLightShang[i] = 0;
		
						LabelOfLightShang[i] = 0;
		
						NearOfTrackShang[i] = 0; 
		
						ColorOfTrackShang[i] = 0;
		
						FarOfTrackShang[i] = 0;
		
						KindOfSpeShang[i] = 0;
		
						OffsetOfSpeShang[i] = 0;
		
						LabelOfTrackShang[i] = 0;
		
						OffsetOfSwitchXia[i] = 0;
		
						StateOfSwitchXia[i] = 0;
		
						LabelOfSwitchXia[i] = 0;
		
						OffsetOfLightXia[i] = 0;
		
						StateOfLightXia[i] = 0;
		
						LabelOfLightXia[i] = 0;
		
						NearOfTrackXia[i] = 0; 
		
						ColorOfTrackXia[i] = 0;
		
						FarOfTrackXia[i] = 0;
		
						KindOfSpeXia[i] = 0;
		
						OffsetOfSpeXia[i] = 0;
		
						LabelOfTrackXia[i] = 0;
		
					} 
		
					if(LB101==0&&LB102==0&&LB103==0&&LB104==0&&LB105==0)
		
					{LB100 = 1;}
		
					NumofSpeShang = 0;
		
					NumofSpeXia = 0;
	
			}
		} 
	}

	else if(DimianData[0] == 0xa5&&DimianData[1]==0x00&&DimianData[2]==0x55)
    {

		for(ii = 0; ii < 32;ii ++)
		{
			for(j= 0;j < 8;j++)
			{
				message[j] = DimianData[8+8*ii+j];
			}
			if (message[0] == 0xbf)
			{
				Zonggoushu = (unsigned short )message[6];
				if(Zonggoushu == 0)
				{
					for(i = 0;i < 40;i++)
					{
						Gudaohaos[i] = 0;
						Fangxiangs[i] = 0;
						Zuoyefangfas[i] = 0;
						Liangshus[i] = 0;
						Cheliangbianmas[i] = 0;
						Cheliangbianmas[i+40] = 0;
						Jishis[i] = 0;
					}
				}
				else
				{
					LW8302 = message[5];
					LW8306 = message[6];
					LW8303 = message[7];
					ShuntNum = message[3]*65536+message[2]*256+message[1];
					LW8304 = ShuntNum / 10000;
					LW8305 = ShuntNum % 10000;
					for(i = Zonggoushu;i < 40;i++)
					{
						Gudaohaos[i] = 0;
						Fangxiangs[i] = 0;
						Zuoyefangfas[i] = 0;
						Liangshus[i] = 0;
						Cheliangbianmas[i] = 0;
						Cheliangbianmas[i+40] = 0;
						Jishis[i] = 0;
					}
				}
			}
			else if(message[0] == 0xC7)
			{
				if (message[2] == 0&&message[3] == 0)
					message[2] = 0x20;
				if (message[4] == 0&&message[5] == 0)
					message[4] = 0x20;
				if (message[6] == 0&&message[7] == 0)
					message[6] = 0x20;
				i = (message[1]&0x0f)*3;
				memcpy(&TipMsg[i],&message[2],6);
			}
			else if(message[0]>=0xb0 &&message[0]<0xbe )
			{

				//memcpy(&diaochedan,&message[0],8);
				cheliangbianma = message[7]*pow(16.0,4.0)+message[6]*pow(16.0,2.0)+message[5];
				diaochedan.Gouxu =  message[1];
				Gudaohaos[diaochedan.Gouxu-1] = message[2];
				Fangxiangs[diaochedan.Gouxu-1] =  message[0]&0x0f;
				Zuoyefangfas[diaochedan.Gouxu-1] = message[3]/0xc0;
				Liangshus[diaochedan.Gouxu-1] =  message[4];
				Cheliangbianmas[(diaochedan.Gouxu-1)*2] = cheliangbianma/10000;
				Cheliangbianmas[(diaochedan.Gouxu-1)*2+1] = cheliangbianma%10000;
				Jishis[diaochedan.Gouxu-1] =  message[3]&0x3f;
			}
			else if(message[0] == 0xc2)
			{
				Dangqiangou = message[7];
				LB89 = 1;
			}
					
       }
    }
	return 0;
}
 