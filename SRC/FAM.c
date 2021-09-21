#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
//#include "FFT.h"
#include "fftsg.h"
#include "string.h"
Uint16 *ExRamStart = (Uint16 *)0x100000;

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;
#define  BUF_SIZE   16384

#define	  AD7656_BASIC_1    (*((volatile  Uint16 *)0x200000))
#define	  AD7656_BASIC_2    (*((volatile  Uint16 *)0x200001))
//#define	  AD7656_rst      (*((volatile  Uint16 *)0x200008))
#define   AD_BUSY         GpioDataRegs.GPBDAT.bit.GPIO60
#define   SET_ADRST       GpioDataRegs.GPBSET.bit.GPIO61=1
#define   CLEAR_ADRST     GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define   SET_ADCLK       GpioDataRegs.GPASET.bit.GPIO25=1
#define   CLR_ADCLK       GpioDataRegs.GPACLEAR.bit.GPIO25=1

//#pragma CODE_SECTION(rdft,"ADCPROG");
#pragma DATA_SECTION(input2,"ADCDATA");
#pragma DATA_SECTION(sinput2,"ADCDATA");
#pragma DATA_SECTION(ad,"AD");
//#pragma DATA_SECTION(output,"ADCDATA");
//#pragma DATA_SECTION(w,"ADCDATA");
//#pragma DATA_SECTION(a,"ADCDATA");
#define NADC 2048
float sinput1[NADC];
float input1[NADC];
float input2[NADC];
float sinput2[NADC];
int ad[2];

float VE;//RSSI有效值
int sign=0,tab=0;
int ip[32];//length of ip >= 2+sqrt(n/2)
float w[NADC/2];
float output[NADC/2];
float a[NADC];
//int ad[6];//存放ad转换结果
//float output4[NADC];
Uint16 sampleCount=0;

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
	static int i;
    for(i=1;i<(NADC/2);i++)
    {
    	fftout[i-1]=fftin[2*i]*fftin[2*i]+fftin[2*i+1]*fftin[2*i+1];
     //if(i>128&&i<512&&output[i]>level)ok=1;
	}
    fftout[NADC/2-1]=fftin[1]*fftin[1];
}

void VEcalculation(float *RSSI)
{
	static int i;
	static float sum;
	sum=0;
    for(i=0;i<NADC;i++)
    {
    	sum+=RSSI[i];
    }
    VE=5*sum/NADC/32768;
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
	InitPieVectTable();
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TINT0 = &ISRTimer0;
   EDIS;    // This is needed to disable write to EALLOW protected registers
   InitCpuTimers();   // For this example, only initialize the Cpu Timers
   //ConfigCpuTimer(&CpuTimer0, 1, 1416); //在定时器内进行采样,采样率200KHz
   ConfigCpuTimer(&CpuTimer0, 1, 7285); //在定时器内进行采样,采样率153.6KHz
   	   	   	   	   	   	   	   	   	   //减小会导致拉伸，增大会导致重叠，据此判断最佳采样率
    IER |= M_INT1;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; 
    EnableInterrupts();
    EINT;
	ERTM;

	DMAInitialize();
	//DMADest   = (volatile Uint16 *)0xBC0A;              //Point DMA destination to the beginning of the array
	DMADest   = &ad[0];    //Point DMA destination to the beginning of the array
	DMASource = (volatile Uint16 *)0x200000;    //Point DMA source to ADC result register base
	DMACH1AddrConfig(DMADest,DMASource);
	/*DMACH1BurstConfig(6,1,1);
	DMACH1TransferConfig(0,0,0);
	DMACH1WrapConfig(0,0,6,1);*/

	DMACH1BurstConfig(2,1,1);
	DMACH1TransferConfig(0,0,0);
	DMACH1WrapConfig(0,0,2,0);

	DMACH1ModeConfig(11,PERINT_ENABLE,ONESHOT_DISABLE,CONT_ENABLE,SYNC_DISABLE,
					 SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,CHINT_END,CHINT_DISABLE);
	StartDMACH1();

	SET_ADRST;  
	DELAY_US(100000);
	CLEAR_ADRST; 
	StartCpuTimer0();
	CLR_ADCLK;   //启动转换信号
	SET_ADCLK;
	DELAY_US(1);
	ip[0]=0;
	while(1)
	{
		if(sign==0)
		    {
			if(tab==0)
				{
				tab=1;
			    rdft(NADC, 1, input1, ip, w);
			    ModelComplex(input1,output);
			    VEcalculation(input2);
				}
			else
				{
				tab=0;
			    rdft(NADC, 1, sinput1, ip, w);
			    ModelComplex(sinput1,output);
				VEcalculation(sinput2);
				}
			sign=1;
		    }
	}
}

interrupt void ISRTimer0(void)
{
    CpuTimer0Regs.TCR.bit.TIF=1; // 定时到了指定时间，标志位置位，清除标志
    CpuTimer0Regs.TCR.bit.TRB=1; // 重载Timer0的定时数据
	if(tab==0)
		{
		input1[sampleCount]=ad[0];
		input2[sampleCount]=ad[1];
		}
	else
		{
		sinput1[sampleCount]=ad[0];
		sinput2[sampleCount]=ad[1];
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
