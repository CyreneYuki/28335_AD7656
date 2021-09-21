#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "fft8g.h"
#include "net.h"
#include "string.h"
#include  <stdio.h>
Uint16 *ExRamStart = (Uint16 *)0x180000;					//外扩sram起始地址

volatile Uint16 *DMADest;									//DMA指针
volatile Uint16 *DMASource;

#define NADC 4096											//采样与FFT点数

#define	  AD7656_BASIC    (*((volatile  Uint16 *)0x200000))	//AD7656寄存器
//#define	  AD7656_rst      (*((volatile  Uint16 *)0x200008))
#define   AD_BUSY         GpioDataRegs.GPBDAT.bit.GPIO60
#define   SET_ADRST       GpioDataRegs.GPBSET.bit.GPIO61=1
#define   CLEAR_ADRST     GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define   SET_ADCLK       GpioDataRegs.GPASET.bit.GPIO25=1
#define   CLR_ADCLK       GpioDataRegs.GPACLEAR.bit.GPIO25=1

#pragma DATA_SECTION(input1,"ADCDATA");						//将大数组定义到外部sram
#pragma DATA_SECTION(sinput1,"ADCDATA");
#pragma DATA_SECTION(input2,"ADCDATA");
#pragma DATA_SECTION(sinput2,"ADCDATA");
#pragma DATA_SECTION(powerall,"ADCDATA");
#pragma DATA_SECTION(test,"ADCDATA");

#pragma DATA_SECTION(ad,"AD");								//高频使用的数组，定义到内部ram
#pragma DATA_SECTION(sampleCount,"AD");
#pragma DATA_SECTION(tab,"AD");

int input1[NADC],sinput1[NADC],input2[NADC],sinput2[NADC];
int sign=0,tab=0,i=0,har=0,funda,temp,sampleCount=0;
int ip[49],ad[6],test[248];//length of ip >= 2+sqrt(n/2)
float w[NADC/2],output[NADC/2],a[NADC];
extern Uint16 identification;

float level=10000000000,level50hz;							//投切检测灵敏度

float proportion=0.000152587890625;							//用于功率分解
float dproportion=0.000000023283064365386962890625;

Uint16	RxEthnetFrameBuffer[1500/2];						//定义网卡发送与接收缓冲区
Uint16	TxEthnetFrameBuffer[1500/2];
#pragma DATA_SECTION(RxEthnetFrameBuffer,"ADCDATA");
#pragma DATA_SECTION(TxEthnetFrameBuffer,"ADCDATA");

#pragma CODE_SECTION(ModelComplex,"ramfuncs");				//烧写时使用，将函数复制到ram运行
#pragma CODE_SECTION(ISRTimer0,"ramfuncs");
#pragma CODE_SECTION(ang,"ramfuncs");
#pragma CODE_SECTION(p,"ramfuncs");
#pragma CODE_SECTION(maintask,"ramfuncs");

interrupt void ISRTimer0(void);
void InitXintf(void);

/*将程序复制到ram中运行*/
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    {
       *DestAddr++ = *SourceAddr++;
    }
    return;
}

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

/*求模函数 */
void ModelComplex(float *fftin,float *fftout)
{
	static int j;
	har=funda=0;
    for(j=1;j<(NADC/2);j++)
    {
    	 fftout[j-1]=fftin[2*j]*fftin[2*j]+fftin[2*j+1]*fftin[2*j+1];
    	 if(i>1800)										//高频分量信号突变检测
    	 {
    		 if(output[i]>level)
    		 {
    			 har=1;
    			 test[i-1800]=1;
    		 }
    		 else
    		 {
    			 test[i-1800]=0;
    		 }
    	 }
	}
    if(output[0]>level50hz)								//基波分量信号突变检测
		 {
    	 funda=1;
		 }
    fftout[NADC/2-1]=fftin[1]*fftin[1];
}

/*求功率因数角*/
struct angle{
	float c,s;
}angle1,angle2;
struct angle ang(int *Iin)
{
	struct angle an;
	static int j;
	static int k=0;
	if(Iin[1]>=0)k=1;
	switch(k)
	{
		case 0:
			for(j=1;j<NADC;j++)
			    {
			     if(Iin[j]>=0)
			    	 {
			    	 break;
			    	 }
				}
			an.c=cos(3.141593*(j-1)/2048);
			an.s=sin(3.141593*(j-1)/2048);
			break;
		case 1:
	    	for(j=NADC;j>0;j--)
	    	    {
	    	     if(Iin[j]<=0)
	    	    	 {
	    	    	 break;
	    	    	 }
	    		}
	        an.c=cos(3.141593*(j+1-NADC)/2048);
	        an.s=sin(3.141593*(j+1-NADC)/2048);
	    	if(Iin[0]<=0)
	    	{
	    		j=1;
	    		an.c=cos(3.141593*(j)/2048);
	    		an.s=-sin(3.141593*(j)/2048);
	    	}
			break;
		default:
			break;
	}
    return(an);
}

/*功率分解*/
struct power{
	float a,ra;
}powerall[NADC],padd;
struct power p(int input1,int input2,struct angle ang)	//功率分解
{
	struct power po;
	po.a=(float)input1*(float)input2*ang.c;
	po.ra=(float)input1*(float)input2*ang.s;
    return(po);
}
struct power p_add(void)//求和
{
	struct power poa;
	static int i;
	poa.a=0;
	poa.ra=0;
	for(i=0;i<NADC;i++)
	{
		poa.a+=powerall[i].a;
		poa.ra+=powerall[i].ra;
	}
	poa.a=dproportion*poa.a/(NADC);
	poa.ra=dproportion*poa.ra/(NADC);
    return(poa);
}

/*主程序，输入分别为电压、电流*/
void maintask(int* voltage,int* current)
{
	for(i=0;i<NADC;i++)
	{
		//powerall[i]=p(voltage[i],current[i],angle1);	//功率分解
		a[i]=voltage[i];								//将ad采集的数据提升为float类型
	}
	rdft(NADC, 1, a, ip, w);							//fft
	ModelComplex(a,output);								//求模运算
	//padd=p_add();										//功率分解求和

	/*网口传输*/
	/*
    *(TxEthnetFrameBuffer+21)=funda;				//低频突变标志
    *(TxEthnetFrameBuffer+22)=har;					//高频突变标志
	memcpy(TxEthnetFrameBuffer+23,&padd,4);			//功率分解结果
	memcpy(TxEthnetFrameBuffer+27,&padd,248);		//投切发生频段
	SendFrame(TxEthnetFrameBuffer,275);
	*/
	UDPinit(output,730);
	UDPinit(output+365,730);
	UDPinit(output+730,730);
	UDPinit(output+1095,730);
	UDPinit(output+1460,730);
	UDPinit(output+1825,446);
	identification=0;
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
	//MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd,&RamfuncsRunStart);//烧写到flash，在ram中运行
	InitFlash();
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TINT0 = &ISRTimer0;
   EDIS;    // This is needed to disable write to EALLOW protected registers
   InitCpuTimers();   // For this example, only initialize the Cpu Timers
   ConfigCpuTimer(&CpuTimer0, 1, 731); //在定时器内进行采样,采样率204800Hz

    IER |= M_INT1;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; 
    EnableInterrupts();
    EINT;
	ERTM;

	/*DMA*/
	DMAInitialize();
	//DMADest   = (volatile Uint16 *)0x1C1000;
	DMADest   = &ad[0];    //Point DMA destination to the beginning of the array
	DMASource = (volatile Uint16 *)0x200000;    //Point DMA source to ADC result register base
	DMACH1AddrConfig(DMADest,DMASource);
	DMACH1BurstConfig(6,1,1);
	DMACH1TransferConfig(0,0,0);
	DMACH1WrapConfig(0,0,6,1);
	/*DMACH1BurstConfig(1,0,1);
	DMACH1TransferConfig(NADC-1,0,0);
	DMACH1WrapConfig(NADC-1,0,NADC-1,0);*/
	DMACH1ModeConfig(11,PERINT_ENABLE,ONESHOT_DISABLE,CONT_ENABLE,SYNC_DISABLE,
					 SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,CHINT_BEGIN,CHINT_DISABLE);
	StartDMACH1();

	SET_ADRST;  
	DELAY_US(100000);
	CLEAR_ADRST; 
	StartCpuTimer0();
	CLR_ADCLK;  	 //启动转换信号
	SET_ADCLK;
	DELAY_US(1);
	ip[0]=0;		 //生成旋转因子
	LedReg = 0xFF;
 	Init8019();		 //网口通信初始化
	addinit();	 //地址获取成功后继续
	DELAY_US(10000);
	while(1)
	{
		if(sign==0)
		    {
				switch(tab)
				{
				case 0:
					tab=1;

					if(input1[4095]>0)		//过零检测(处理起始相位逐渐减小的情况）
							{
							sampleCount++;
							sinput1[0]=input1[4095];
							sinput2[0]=input2[4095];
							}

					angle1=ang(input2);		//求功率因数角,每两周期重新计算一次
					maintask(input1,input2);
					break;
				case 1:
					tab=0;
					maintask(sinput1,sinput2);
					break;
				default:
					break;
				}
				sign=1;
		    }
		//此处可添加故障检测程序
		//若使用软件过零检测，不可测量1khz以上的连续信号
	}
}

interrupt void ISRTimer0(void)
{
	switch(tab)
	{
		case 0:
			input1[sampleCount]=ad[0];
			input2[sampleCount]=ad[1];

			if(sampleCount==1)
			{
				if((input1[0]<0)&&(input1[1]<0))
					{
					input1[0]=input1[1];			//过零检测(处理起始相位逐渐增加的情况）
					sampleCount=0;
					}
			}

			break;
		case 1:
			sinput1[sampleCount]=ad[0];
			sinput2[sampleCount]=ad[1];
			break;
		default:break;
	}
	CLR_ADCLK;   //启动转换信号
	SET_ADCLK;
	sampleCount++;
	if(sampleCount >= NADC)
		{
		sampleCount=0;
		sign=0;
		}
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
