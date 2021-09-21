#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "fft8g.h"
#include "net.h"
#include "string.h"
#include  <stdio.h>
Uint16 *ExRamStart = (Uint16 *)0x180000;					//����sram��ʼ��ַ

volatile Uint16 *DMADest;									//DMAָ��
volatile Uint16 *DMASource;

#define NADC 4096											//������FFT����

#define	  AD7656_BASIC    (*((volatile  Uint16 *)0x200000))	//AD7656�Ĵ���
//#define	  AD7656_rst      (*((volatile  Uint16 *)0x200008))
#define   AD_BUSY         GpioDataRegs.GPBDAT.bit.GPIO60
#define   SET_ADRST       GpioDataRegs.GPBSET.bit.GPIO61=1
#define   CLEAR_ADRST     GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define   SET_ADCLK       GpioDataRegs.GPASET.bit.GPIO25=1
#define   CLR_ADCLK       GpioDataRegs.GPACLEAR.bit.GPIO25=1

#pragma DATA_SECTION(input1,"ADCDATA");						//�������鶨�嵽�ⲿsram
#pragma DATA_SECTION(sinput1,"ADCDATA");
#pragma DATA_SECTION(input2,"ADCDATA");
#pragma DATA_SECTION(sinput2,"ADCDATA");
#pragma DATA_SECTION(powerall,"ADCDATA");
#pragma DATA_SECTION(test,"ADCDATA");

#pragma DATA_SECTION(ad,"AD");								//��Ƶʹ�õ����飬���嵽�ڲ�ram
#pragma DATA_SECTION(sampleCount,"AD");
#pragma DATA_SECTION(tab,"AD");

int input1[NADC],sinput1[NADC],input2[NADC],sinput2[NADC];
int sign=0,tab=0,i=0,har=0,funda,temp,sampleCount=0;
int ip[49],ad[6],test[248];//length of ip >= 2+sqrt(n/2)
float w[NADC/2],output[NADC/2],a[NADC];
extern Uint16 identification;

float level=10000000000,level50hz;							//Ͷ�м��������

float proportion=0.000152587890625;							//���ڹ��ʷֽ�
float dproportion=0.000000023283064365386962890625;

Uint16	RxEthnetFrameBuffer[1500/2];						//����������������ջ�����
Uint16	TxEthnetFrameBuffer[1500/2];
#pragma DATA_SECTION(RxEthnetFrameBuffer,"ADCDATA");
#pragma DATA_SECTION(TxEthnetFrameBuffer,"ADCDATA");

#pragma CODE_SECTION(ModelComplex,"ramfuncs");				//��дʱʹ�ã����������Ƶ�ram����
#pragma CODE_SECTION(ISRTimer0,"ramfuncs");
#pragma CODE_SECTION(ang,"ramfuncs");
#pragma CODE_SECTION(p,"ramfuncs");
#pragma CODE_SECTION(maintask,"ramfuncs");

interrupt void ISRTimer0(void);
void InitXintf(void);

/*�������Ƶ�ram������*/
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    {
       *DestAddr++ = *SourceAddr++;
    }
    return;
}

/*adc������ʽѡ�� */
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

/*��ģ���� */
void ModelComplex(float *fftin,float *fftout)
{
	static int j;
	har=funda=0;
    for(j=1;j<(NADC/2);j++)
    {
    	 fftout[j-1]=fftin[2*j]*fftin[2*j]+fftin[2*j+1]*fftin[2*j+1];
    	 if(i>1800)										//��Ƶ�����ź�ͻ����
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
    if(output[0]>level50hz)								//���������ź�ͻ����
		 {
    	 funda=1;
		 }
    fftout[NADC/2-1]=fftin[1]*fftin[1];
}

/*����������*/
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

/*���ʷֽ�*/
struct power{
	float a,ra;
}powerall[NADC],padd;
struct power p(int input1,int input2,struct angle ang)	//���ʷֽ�
{
	struct power po;
	po.a=(float)input1*(float)input2*ang.c;
	po.ra=(float)input1*(float)input2*ang.s;
    return(po);
}
struct power p_add(void)//���
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

/*����������ֱ�Ϊ��ѹ������*/
void maintask(int* voltage,int* current)
{
	for(i=0;i<NADC;i++)
	{
		//powerall[i]=p(voltage[i],current[i],angle1);	//���ʷֽ�
		a[i]=voltage[i];								//��ad�ɼ�����������Ϊfloat����
	}
	rdft(NADC, 1, a, ip, w);							//fft
	ModelComplex(a,output);								//��ģ����
	//padd=p_add();										//���ʷֽ����

	/*���ڴ���*/
	/*
    *(TxEthnetFrameBuffer+21)=funda;				//��Ƶͻ���־
    *(TxEthnetFrameBuffer+22)=har;					//��Ƶͻ���־
	memcpy(TxEthnetFrameBuffer+23,&padd,4);			//���ʷֽ���
	memcpy(TxEthnetFrameBuffer+27,&padd,248);		//Ͷ�з���Ƶ��
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

/*������*/
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
	//MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd,&RamfuncsRunStart);//��д��flash����ram������
	InitFlash();
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TINT0 = &ISRTimer0;
   EDIS;    // This is needed to disable write to EALLOW protected registers
   InitCpuTimers();   // For this example, only initialize the Cpu Timers
   ConfigCpuTimer(&CpuTimer0, 1, 731); //�ڶ�ʱ���ڽ��в���,������204800Hz

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
	CLR_ADCLK;  	 //����ת���ź�
	SET_ADCLK;
	DELAY_US(1);
	ip[0]=0;		 //������ת����
	LedReg = 0xFF;
 	Init8019();		 //����ͨ�ų�ʼ��
	addinit();	 //��ַ��ȡ�ɹ������
	DELAY_US(10000);
	while(1)
	{
		if(sign==0)
		    {
				switch(tab)
				{
				case 0:
					tab=1;

					if(input1[4095]>0)		//������(������ʼ��λ�𽥼�С�������
							{
							sampleCount++;
							sinput1[0]=input1[4095];
							sinput2[0]=input2[4095];
							}

					angle1=ang(input2);		//����������,ÿ���������¼���һ��
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
		//�˴�����ӹ��ϼ�����
		//��ʹ����������⣬���ɲ���1khz���ϵ������ź�
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
					input1[0]=input1[1];			//������(������ʼ��λ�����ӵ������
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
	CLR_ADCLK;   //����ת���ź�
	SET_ADCLK;
	sampleCount++;
	if(sampleCount >= NADC)
		{
		sampleCount=0;
		sign=0;
		}
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
