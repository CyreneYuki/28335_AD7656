#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "fft8g.h"
#include "net.h"
#include "string.h"
Uint16 *ExRamStart = (Uint16 *)0x180000;

Uint16  FrameLenth;
Uint16  RxSuccessFlag;

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

#define	  AD7656_BASIC    (*((volatile  Uint16 *)0x200000))
//#define	  AD7656_rst      (*((volatile  Uint16 *)0x200008))
#define   AD_BUSY         GpioDataRegs.GPBDAT.bit.GPIO60
#define   SET_ADRST       GpioDataRegs.GPBSET.bit.GPIO61=1
#define   CLEAR_ADRST     GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define   SET_ADCLK       GpioDataRegs.GPASET.bit.GPIO25=1
#define   CLR_ADCLK       GpioDataRegs.GPACLEAR.bit.GPIO25=1

#pragma DATA_SECTION(input1,"ADCDATA");
#pragma DATA_SECTION(sinput1,"ADCDATA");
#pragma DATA_SECTION(input2,"ADCDATA");
#pragma DATA_SECTION(sinput2,"ADCDATA");
#pragma DATA_SECTION(input3,"ADCDATA");
#pragma DATA_SECTION(sinput3,"ADCDATA");
#pragma DATA_SECTION(input4,"ADCDATA");
#pragma DATA_SECTION(sinput4,"ADCDATA");
#pragma DATA_SECTION(input5,"ADCDATA");
#pragma DATA_SECTION(sinput5,"ADCDATA");
#pragma DATA_SECTION(input6,"ADCDATA");
#pragma DATA_SECTION(sinput6,"ADCDATA");
#pragma DATA_SECTION(ad,"AD");
//#pragma DATA_SECTION(check,"ADCDATA");
#define NADC 4096
int input1[NADC],sinput1[NADC],input2[NADC],sinput2[NADC],input3[NADC],sinput3[NADC],
	input4[NADC],sinput4[NADC],input5[NADC],sinput5[NADC],input6[NADC],sinput6[NADC];
int sign=0,tab=0,i=0;
int ip[49];//length of ip >= 2+sqrt(n/2)
float w[NADC/2];
float output[NADC/2];
//float a[NADC];
int ad[6];
//int check[NADC/2];
float level=10000000000000;
Uint16 sampleCount=0;

Uint16	RxEthnetFrameBuffer[1500/2];
Uint16	TxEthnetFrameBuffer[1500/2];
#pragma DATA_SECTION(RxEthnetFrameBuffer,"R8019");
#pragma DATA_SECTION(TxEthnetFrameBuffer,"R8019");

interrupt void ISRTimer0(void);
void InitXintf(void);

/*adc工作方式选择 */
void ADInit(void)
{
	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO25=0;
	GpioCtrlRegs.GPADIR.bit.GPIO25=1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;  // XWE0
	GpioCtrlRegs.GPBDIR.bit.GPIO61=1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO60=0; //ADBUSY
	GpioCtrlRegs.GPBDIR.bit.GPIO60=0;//INPUT
	GpioCtrlRegs.GPBQSEL2.bit.GPIO60= 0;
	EDIS;
}

void ModelComplex(float *fftin,float *fftout)
{
	static int j;
    for(j=1;j<(NADC/2);j++)
    {
    	fftout[j-1]=fftin[2*j]*fftin[2*j]+fftin[2*j+1]*fftin[2*j+1];
     /*if(i>1750&&i<2048&&output[i]>level)					//事件监测
    	 {
    	 check[i]=1;
    	 }*/
	}
    fftout[NADC/2-1]=fftin[1]*fftin[1];
}

/*主函数*/
void main(void)
{
	InitSysCtrl();
	InitXintf();
	InitXintf16Gpio();
	ADInit();
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
    EINT;
	ERTM;

	SET_ADRST;
	DELAY_US(100000);
	CLEAR_ADRST;
	StartCpuTimer0();
	CLR_ADCLK;   //启动转换信号
	SET_ADCLK;
	DELAY_US(1);
	ip[0]=0;
	LedReg = 0xFF;
	Init8019();//网口通信初始化
	ArpRequest();
	for(i=0;i<750;i++)
	{
		TxEthnetFrameBuffer[i]=i;
	}
	while(1)
	{
		SendFrame(TxEthnetFrameBuffer,750);
		if(sign==0)
		    {
				switch(tab)
				{
				case 0:
					tab=1;
					/*for(i=0;i<4096;i++)
					{
						a[i]=input4[i];
					}
					rdft(NADC, 1, a, ip, w);*/
					//memset(check,0,NADC/2);//事件监测初始化
					//ModelComplex(a,output);
					//memcpy(TxEthnetFrameBuffer+21,input4,727);
					//ArpRequest();
					SendFrame(TxEthnetFrameBuffer,750);
					break;
				case 1:
					tab=0;
					/*for(i=0;i<4096;i++)
					{
						a[i]=sinput4[i];
					}
					rdft(NADC, 1, a, ip, w);*/
					//memset(check,0,NADC/2);//事件监测初始化
					//ModelComplex(a,output);
					//memcpy(TxEthnetFrameBuffer+21,sinput4,727);
					//ArpRequest();
					SendFrame(TxEthnetFrameBuffer,750);
					break;
				default:
					break;
				}
				sign=1;
		    }
	}
}

interrupt void ISRTimer0(void)
{
	switch(tab)
	{
		case 0:
			input1[sampleCount]=ad[0];
			input2[sampleCount]=ad[1];
			input3[sampleCount]=ad[2];
			input4[sampleCount]=ad[3];
			input5[sampleCount]=ad[4];
			input6[sampleCount]=ad[5];
			break;
		case 1:
			sinput1[sampleCount]=ad[0];
			sinput2[sampleCount]=ad[1];
			sinput3[sampleCount]=ad[2];
			sinput4[sampleCount]=ad[3];
			sinput5[sampleCount]=ad[4];
			sinput6[sampleCount]=ad[5];
			break;
		default:break;
	}
	sampleCount++;
	if(sampleCount >= NADC)
		{
		sampleCount=0;
		sign=0;
		}
	CLR_ADCLK;   //启动转换信号
	SET_ADCLK;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
