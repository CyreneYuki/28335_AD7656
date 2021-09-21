#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "FFT.h"
#include "string.h"
Uint16 *ExRamStart = (Uint16 *)0x100000;

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;
#define  BUF_SIZE   16384

#define	  AD7656_BASIC    (*((volatile  Uint16 *)0x200000))
//#define	  AD7656_rst      (*((volatile  Uint16 *)0x200008))
#define   AD_BUSY         GpioDataRegs.GPBDAT.bit.GPIO60
#define   SET_ADRST       GpioDataRegs.GPBSET.bit.GPIO61=1
#define   CLEAR_ADRST     GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define   SET_ADCLK       GpioDataRegs.GPASET.bit.GPIO25=1
#define   CLR_ADCLK       GpioDataRegs.GPACLEAR.bit.GPIO25=1

//#pragma DATA_SECTION(input4,"ADCDATA");
//#pragma DATA_SECTION(sinput4,"ADCDATA");
//#pragma DATA_SECTION(output4,"ADCDATA1");
#define NADC 1024
int input4[NADC],sinput4[NADC];
int sign=0,tab=0;
int ad[6];//存放ad转换结果
int i,j;
float output4[NADC];
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

#define res 2
float P[res],Q0[res],Q1[res],Q2[res],C[res],f[res],temp[res];
int k[res];
void Goertzel_init(float *freq,int interval)
{
	float PI=3.141593;
	float floatN;
	floatN = (float) NADC;
	for(i=0;i<res;i++)
	{
		freq[i]=interval*(i+1);
		k[i] = (int) (0.5 + ((floatN * freq[i]) / 204800));
		temp[i]=(2*PI*k[i])/floatN;
		C[i]=2*(cos(temp[i]));
	}
}

void goertzel_reset(void)
{
	memset(Q0,0,res);
	memset(Q1,0,res);
	//memset(Q2,0,res);
}
void goertzel_process(Uint16 *S)
{
	Uint16 j;
	for(j=0;j<NADC;j++)
	{
		for(i=0;i<res;i++)
		{
		Q1[i]=Q0[i];
		Q0[i]=C[i]*Q0[i]-Q1[i]+S[j]-32768;
		}
	}
}
void goertzel_output(void)
{
	for(i=0;i<res;i++)
	{
		P[i]=log10(Q0[i]*Q0[i]+Q1[i]*Q1[i]-C[i]*Q0[i]*Q1[i]);
	}
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
   ConfigCpuTimer(&CpuTimer0, 1, 947); //在定时器内进行采样,采样率200KHz
   	   	   	   	   	   	   	   	   	   //减小会导致拉伸，增大会导致重叠，据此判断最佳采样率
    IER |= M_INT1;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; 
    EnableInterrupts();
    EINT;
	ERTM;

	DMAInitialize();
	for (i=0; i<BUF_SIZE; i++)
	{
	ad[i] = 0;
	}
	DMADest   = (volatile Uint16 *)0xD080;              //Point DMA destination to the beginning of the array
	DMASource = (volatile Uint16 *)0x200000;    //Point DMA source to ADC result register base
	DMACH1AddrConfig(DMADest,DMASource);
	/*DMACH1BurstConfig(6,1,1);
	DMACH1TransferConfig(0,0,0);
	DMACH1WrapConfig(0,0,6,1);*/

	DMACH1BurstConfig(1,0,1);
	DMACH1TransferConfig(2047,0,0);
	DMACH1WrapConfig(2047,0,2047,0);

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
	Goertzel_init(f,10000);
	memset(sinput4,0,2*NADC);
	memset(input4,0,2*NADC);
	fftinit();
	while(1)
	{
		if(sign==0)
		    {
			if(tab==0)
				{
				fft(input4,output4);
				tab=1;
				}
			else
				{
				fft(sinput4,output4);
				tab=0;
				}
			sign=1;
		    }
	}
}

interrupt void ISRTimer0(void)
{
    CpuTimer0Regs.TCR.bit.TIF=1; // 定时到了指定时间，标志位置位，清除标志
    CpuTimer0Regs.TCR.bit.TRB=1; // 重载Timer0的定时数据
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
