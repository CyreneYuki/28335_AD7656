#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "Goertzel.h"
#include "fft.h"
#include "string.h"

#define NADC 4096						//采样点数

Uint16 *ExRamStart = (Uint16 *)0x100000;

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;
#define  BUF_SIZE   6
#define	 AD7656_BASIC    (*((volatile  Uint16 *)0x200000))
//#define	  AD7656_rst      (*((volatile  Uint16 *)0x200008))
#define  AD_BUSY         GpioDataRegs.GPBDAT.bit.GPIO60
#define  SET_ADRST       GpioDataRegs.GPBSET.bit.GPIO61=1
#define  CLEAR_ADRST     GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define  SET_ADCLK       GpioDataRegs.GPASET.bit.GPIO25=1
#define  CLR_ADCLK       GpioDataRegs.GPACLEAR.bit.GPIO25=1

Uint16 sampleCount=0;
Uint16 sign=0;
Uint16 fftsign=0;
Uint16 ad[6];//存放ad转换结果
float input4[NADC];

//#pragma DATA_SECTION(testSample1,"ADCDATA");//（例）数组存放在外部SRAM中

void InitXintf(void);
interrupt void ISRTimer0(void);

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
   ConfigCpuTimer(&CpuTimer0, 1, 715); //在定时器内进行采样,采样率100650*2hz
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
	DMADest   = &ad[0];              //Point DMA destination to the beginning of the array
	DMASource = (volatile  Uint16 *)0x200000;    //Point DMA source to ADC result register base
	DMACH1AddrConfig(DMADest,DMASource);
	DMACH1BurstConfig(6,1,1);
	DMACH1TransferConfig(0,0,0);
	DMACH1WrapConfig(0,0,6,1);

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
	Goertzel_init(1000,NADC);//初始化goertzel参数
	while(1)
	{/*
		if(sign==0)
		{
			goertzel_process(ad[0]);
			if(sampleCount >= NADC)
			{
				goertzel_output();
				goertzel_reset();
				sampleCount=0;
			}
			sign=1;
		}*/
		if(sign==0)
		{
				memcpy(Sample1,input4,2048);
				fft(output4);
				fftsign=1;
				memcpy(Sample1,input4+(unsigned int)2048,2048);
				fft(output4);
		}
	}
}

interrupt void ISRTimer0(void)
{
    CpuTimer0Regs.TCR.bit.TIF=1; // 定时到了指定时间，标志位置位，清除标志
    CpuTimer0Regs.TCR.bit.TRB=1;  // 重载Timer0的定时数据
	input4[sampleCount]=ad[0]-32768;
	sampleCount++;
	if(sampleCount >= NADC)
	{
		sampleCount=0;
		if(sign==1)sign=0;
	}
	CLR_ADCLK;   //启动转换信号
	SET_ADCLK;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
