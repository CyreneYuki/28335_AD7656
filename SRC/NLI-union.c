#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
//#include "FFT.h"
#include "fft8g_union.h"
#include "string.h"
Uint16 *ExRamStart = (Uint16 *)0x180000;


volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

#define	  AD7656_BASIC    (*((volatile  Uint16 *)0x200000))
//#define	  AD7656_rst      (*((volatile  Uint16 *)0x200008))
#define   AD_BUSY         GpioDataRegs.GPBDAT.bit.GPIO60
#define   SET_ADRST       GpioDataRegs.GPBSET.bit.GPIO61=1
#define   CLEAR_ADRST     GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define   SET_ADCLK       GpioDataRegs.GPASET.bit.GPIO25=1
#define   CLR_ADCLK       GpioDataRegs.GPACLEAR.bit.GPIO25=1

#pragma DATA_SECTION(input4,"ADCDATA");
#pragma DATA_SECTION(sinput4,"ADCDATA");
//#pragma DATA_SECTION(output,"ADCDATA");
//#pragma DATA_SECTION(w,"ADCDATA");
#define NADC 4096
int sign=0,tab=0;
int ip[50];//length of ip >= 2+sqrt(n/2)
float output[NADC/2];
//float a[NADC];
union ADDATA input4[NADC];
union ADDATA sinput4[NADC];
union ADDATA w[NADC/2];
Uint16 sampleCount=0;
int i;
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

void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
	 while(SourceAddr < SourceEndAddr)
	    {
	       *DestAddr++ = *SourceAddr++;
	    }
	    return;
}

void ModelComplex(union ADDATA *fftin,float *fftout)
{
	static int i;
    for(i=1;i<(NADC/2);i++)
    {
    	fftout[i-1]=fftin[2*i].f*fftin[2*i].f+fftin[2*i+1].f*fftin[2*i+1].f;
     //if(i>128&&i<512&&output[i]>level)ok=1;
	}
    fftout[NADC/2-1]=fftin[1].f*fftin[1].f;
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
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	InitFlash();
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TINT0 = &ISRTimer0;
   EDIS;    // This is needed to disable write to EALLOW protected registers
   InitCpuTimers();   // For this example, only initialize the Cpu Timers
   //ConfigCpuTimer(&CpuTimer0, 1, 1416); //在定时器内进行采样,采样率200KHz
   ConfigCpuTimer(&CpuTimer0, 1, 694); //在定时器内进行采样,采样率153.6KHz
   	   	   	   	   	   	   	   	   	   //减小会导致拉伸，增大会导致重叠，据此判断最佳采样率
    IER |= M_INT1;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; 
    EnableInterrupts();
    EINT;
	ERTM;

	DMAInitialize();
	//DMADest   = (volatile Uint16 *)0x1C1000;              //Point DMA destination to the beginning of the array
	DMADest   = &sinput4[0].u;    //Point DMA destination to the beginning of the array
	DMASource = (volatile Uint16 *)0x200000;    //Point DMA source to ADC result register base
	DMACH1AddrConfig(DMADest,DMASource);
	/*DMACH1BurstConfig(6,1,1);
	DMACH1TransferConfig(0,0,0);
	DMACH1WrapConfig(0,0,6,1);*/

	DMACH1BurstConfig(1,0,2);
	DMACH1TransferConfig(2*NADC-1,0,0);
	DMACH1WrapConfig(2*NADC-1,0,2*NADC-1,0);

	DMACH1ModeConfig(11,PERINT_ENABLE,ONESHOT_DISABLE,CONT_ENABLE,SYNC_DISABLE,
					 SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,CHINT_BEGIN,CHINT_DISABLE);
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
		    	//DMADest = &sinput4[0].u;
		    	//DMACH1AddrConfig(DMADest,DMASource);
				static int co;
				for(co=0;co<NADC;co++)
				{
					input4[co].f=(float)input4[co].i;
				}
			    rdft(NADC, 1, input4, ip, w);
			    ModelComplex(input4,output);
				tab=1;
				}
			else
				{
		    	//DMADest = &input4[0].u;
		    	//DMACH1AddrConfig(DMADest,DMASource);
				static int co;
				for(co=0;co<NADC;co++)
				{
					sinput4[co].f=(float)sinput4[co].i;
				}
			    rdft(NADC, 1, sinput4, ip, w);
			    ModelComplex(sinput4,output);
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
    /*for(i=0;i<6;i++)
	{
        ad[i]=AD7656_BASIC; //读取6路AD通道数据
	}*/
    /*if(tab==0)
    {
    	input4[sampleCount].i=AD7656_BASIC;
    }
    if(tab==1)
    {
    	sinput4[sampleCount].i=AD7656_BASIC;
    }*/
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
