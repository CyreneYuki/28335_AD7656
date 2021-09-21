#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "net.h"
#pragma CODE_SECTION(SendFrame,"ramfuncs");

Uint16  RxSuccessFlag;
extern	Uint16	TxEthnetFrameBuffer[1518/2];
extern	Uint16	RxEthnetFrameBuffer[1518/2];

const Uint16 MyMAC[] = 
{0xE002,0xA04C,0x7A7E};

const Uint16 MyIP[] =
{0xA8C0,0xE601};

const Uint16 RemoteIP[] =
{0xA8C0,0x0E01};

const Uint16 SubnetMask[] =
{0xFFFF,0x00FF};

const Uint16 GatewayIP[] = 
{0xA8C0,0x0101};

Uint16 count[] = {0,0};

Uint16 identification=0;

Uint16	TxBufFlag;
Uint16	bnry,curr;
Uint16 UDPUserDataLenth; 
Uint16 IpEdition;                                //IP�汾
Uint16 IpServiceType;
Uint16 IpIdent;
Uint16 MyUdpPort;

Uint16 RemoteMAC[3];                             // 48 bit MAC
Uint16 RecdFrameMAC[3];
Uint16 RecdFrameIP[2];
Uint16 RecdIpFrameLenth;
Uint16 TxFrameSize;
Uint16 ARPAnswerSuccessFlag;

/**********************************************************************
**����ԭ�ͣ�    void  page(uchar pagenumber)
**��ڲ���:   	Uint16	pagenumber: Ҫ�л���ҳ
**���ڲ���:		��
**�� �� ֵ��	��      
**˵    ����	ѡ��ҳ,��ѡ��0,1,2��ҳ,����ҳne000����оƬ���� 
************************************************************************/
void	page(Uint16 pagenumber)
		{
			Uint16	temp;
			temp = Reg00;				//command register
			temp = temp&0x3B ; 			//ע��txpλ����Ҫ
			pagenumber=pagenumber <<6;
			temp=temp | pagenumber;
			Reg00=temp;
		}


/**********************************************************************
**����ԭ��:     void 	Init8019()
**��ڲ���:		��
**���ڲ���:		��
**�� �� ֵ:		��              
**˵    ��:		��оƬ�Ĺ����Ĵ�����������,�����Ĵ������÷��ɲο��ĵ���
**				��оƬ�������ֲ�
************************************************************************/
void	Init8019()
		{
			DELAY_US(10000);
/**********************************************************************

1.Reg00����Ĵ���: CR,����Ĵ���,��ַƫ����00H,Ϊһ���ֽ�
  λ:  7   6   5   4   3   2   1   0 
����: PS1 PS0 RD2 RD1 RD0 TXP STA STP 
//============================================
2.
RD2,RD1,RD0: ��3��λ����Ҫִ�еĹ��ܡ�
 0   0   1 : �������ڴ�
 0   1   0 : д�����ڴ�
 0   1   1 : �����������ݰ�
 1   *   * : ��ɻ����DMA�Ķ�д����
//============================================
3.TXPλ��1ʱ�������ݰ��������Զ�����
//============================================
4.
STA,STP:	������λ�������������ֹͣ����
 1   0 		��������
 0   1 		ֹͣ����
//============================================
********************************************************/
			Reg00=0x21;   //ʹоƬ����ֹͣģʽ,��ʱ���мĴ�������

			DELAY_US(10000); //��ʱ10����,ȷ��оƬ����ֹͣģʽ
			page(0);
			Reg0a=0x00;   //��rbcr0
			DELAY_US(5);
			Reg0b=0x00;   //��rbcr1
			DELAY_US(5);
			Reg0c= 0xe0;  //RCR,����ģʽ,���������ݰ�          
			DELAY_US(5);
			Reg0d= 0xe2;  //TCR,loop backģʽ
			DELAY_US(5);

			Reg01=0x4c;
			DELAY_US(5);
			Reg02=0x80;
			DELAY_US(5);
			Reg03=0x4c;
			DELAY_US(5);
			Reg04=0x40;  //TPSR,������ʼҳ�Ĵ���
			DELAY_US(5);
			Reg07=0xff;  //��������жϱ�־λ���ж�״̬�Ĵ���
			DELAY_US(5);
			Reg0f=0x00;  //�ж����μĴ�����0����ֹ�ж�
			DELAY_US(5);

			Reg0e=0xC9;  // �������üĴ�����16λdma��ʽ
			DELAY_US(5);
			page(1);
			DELAY_US(15);
			Reg07=0x4d;
			DELAY_US(5);
			Reg08=0x00;
			DELAY_US(5);
			Reg09=0x00;
			DELAY_US(5);
			Reg0a=0x00;
			DELAY_US(5);
			Reg0b=0x00;
			DELAY_US(5);
			Reg0c=0x00;
			DELAY_US(5);
			Reg0d=0x00;
			DELAY_US(5);
			Reg0e=0x00;
			DELAY_US(5);
			Reg0f=0x00;
			DELAY_US(5);

    		Reg01=0x02;
			DELAY_US(5);
    		Reg02=0xE0;
			DELAY_US(5);
    		Reg03=0x4C;
			DELAY_US(5);
    		Reg04=0xA0;
			DELAY_US(5);
    		Reg05=0x7E;
			DELAY_US(5);
    		Reg06=0x7A;
			DELAY_US(5);

			page(0);
			DELAY_US(15);
			Reg0c=0xce;  //��оƬ���ó�����ģʽ,���ⲿ��������
			DELAY_US(5);
			Reg0d=0xe0;  // �������üĴ���TCR������Ϊ����crc�Զ����ɺ�У�飬����ģʽ����
			DELAY_US(5);
			Reg00=0x22;  //����оƬ��ʼ����
			DELAY_US(5);
//-----------------------------------
			Reg07=0xff;  //��������жϱ�־λ
			DELAY_US(5);
		}

Uint16 CalcCheckSum(Uint16 *Start, Uint16 Count, Uint16 IsTCP, Uint16 IsUDP)
{
    Uint32 Sum;
  
    Sum = 0;
    if ((IsTCP)||(IsUDP)) //����α�ײ�У��ֵ
    {
        Sum += MyIP[0];
        Sum += MyIP[1];
        Sum += RemoteIP[0];
        Sum += RemoteIP[1];
        Sum += SwapWord(Count*2);
        if(IsTCP)
             Sum += SwapWord(PROTOCOL_TCP);
        else
             Sum += SwapWord(PROTOCOL_UDP);
    }
    while (Count > 0) 
    {
        Sum += *Start;
        Start ++;
        Count --;
    }
    Sum = (Sum & 0xFFFF) + ((Sum >> 16)&0xFFFF);
    if(Sum&0xFFFF0000)
        Sum++;
    return((Uint16)((~Sum)&0xFFFF));
}

//=============================================================================
/**********************************************************************
**����ԭ�ͣ�    void 		SendFrame(Uint16 *TxdNetBuff,Uint16  length)
**��ڲ���:		Uint16    	*TxdNetBuff	:ָ���ͻ�����
**              uint length					:�������ݰ��ĳ���
**���ڲ���:		��
**�� �� ֵ��	��              
**˵    ����	�������ݰ�,��̫���ײ���������,���е����ݷ��Ͷ�Ҫͨ���ó���
************************************************************************/
void	SendFrame(Uint16 *TxdNetBuff,Uint16 length)
		{


			Uint16	i,ii;
		   	/*if(length<46/2)//��̫��֡��С���ݳ���Ϊ46�ֽڣ��������0���
       			{
          			for(i=length;i<60/2;i++)	TxdNetBuff[i]=0;
          			length=60/2;
       			}*/
			
			page(0);
			DELAY_US(5);					//�л�����0ҳ
			length = length <<1;
			TxBufFlag=!TxBufFlag;			//��������������,��߷���Ч��
			if(TxBufFlag)
				{Reg09=0x40 ;}				//���÷���ҳ��ַ
			else
				{Reg09=0x46 ;}				//���÷���ҳ��ַ
    		DELAY_US(5);
			Reg08=0x00; 					//read page address low
			DELAY_US(5);
			Reg0b = length >>8;				//д���ͳ��ȸ�λ
			DELAY_US(5);
			Reg0a = length & 0x00ff;        //д���ͳ��ȵ�λ  
			DELAY_US(5);
			Reg00=0x12;						//write dma, page0
			DELAY_US(5);

			for(i=0;i<length/2;i++)
				{
					Reg10 = TxdNetBuff[i];
   				}
/***************************************/
//����Ϊ��ֹDMA����
			Reg0b=0x00; 
			DELAY_US(5);
			Reg0a=0x00;
			DELAY_US(5);
			Reg00=0x22;			//���������DMA����
/***************************************/

			for(i=0;i<6;i++)	//����ط�6��
				{
					for(ii=0;ii<1000;ii++)
    					{//���CR�Ĵ�����txpλ�Ƿ�Ϊ��,Ϊ1˵�����ڷ���,Ϊ0˵�������������
        					if((Reg00&0x04)==0)  
        						{ break; }
        				}
					if((Reg04&0x01)!=0)//��ʾ���ͳɹ�,�жϷ���״̬�Ĵ���TSR�������Ƿ����
						{break;};
					Reg00=0x3e;
				}

			Reg07=0xff;
			DELAY_US(5);
			if(TxBufFlag)
				{
  					Reg04=0x40;   //txd packet start;
  				}
			else
				{
     				Reg04=0x46;  //txd packet start;
    			}
			DELAY_US(5);
			Reg06=length>>8;  //high byte counter
			DELAY_US(5);
			Reg05=length&0xff;//low byte counter
			DELAY_US(5);
			Reg07=0xff;
			DELAY_US(5);
			Reg00=0x3e;       //to sendpacket;
			DELAY_US(5);
	}

/**********************************************************************
**����ԭ�ͣ�    Uint16        Rec_NewPacket()
**��ڲ���:		��
**���ڲ���:		��
**�� �� ֵ��	0          û�������ݰ�
**              1          ���յ������ݰ�
**˵    ����	��ѯ�Ƿ��������ݰ������ս�������
************************************************************************/
Uint16	RecFrame()
		{
			Uint16	i,ii;
			Uint16	Temp,length;
			union{
					Uint16	total;	
					struct{
							Uint16	high:8;
							Uint16	low:8;
						  }e;
				 }d;
				 		  		
			page(0);
			DELAY_US(15);
			bnry = Reg03;				//bnry page have read ��ҳָ��
			bnry = bnry & 0x00FF;
			page(1);
			DELAY_US(15);
			curr = Reg07;				//curr writepoint 8019дҳָ��
			curr = curr & 0x00FF;
			page(0);
			if((curr==0))return(0);	//���Ĺ��̳���
			bnry++;
			if(bnry>0x7f)	bnry=0x4c;
			if(bnry!=curr)			//��ʱ��ʾ���µ����ݰ��ڻ�������
    			{					//���κβ�������÷���page0
     				page(0);
     //=======================================
					DELAY_US(15);
     				Reg09=bnry;		//��ҳ��ַ�ĸ��ֽ�
					DELAY_US(5);
     				Reg08=0x00; 	//��ҳ��ַ�ĵ��ֽ�
					DELAY_US(5);
     				Reg0b=0x00;		//��ȡ�ֽڼ������ֽ�
					DELAY_US(5);
     				Reg0a=18;       //��ȡ�ֽڼ������ֽ�
					DELAY_US(5);
     				Reg00=0x0a;     //����Remote DMA������
					DELAY_US(5);
	 
	 
     				for(i=0;i<9;i++)	//��ȡһ����ǰ18���ֽ�:4�ֽڵ�8019ͷ��,6�ֽ�Ŀ�ĵ�ַ,6�ֽ�ԭ��ַ,2�ֽ�Э��
                    	{
                       		RxEthnetFrameBuffer[i]=Reg10;
                      	}
 //=======================================��ֹDMA����
					DELAY_US(5);
     				Reg0b=0x00;	//
					DELAY_US(5);
     				Reg0a=0x00;	//
					DELAY_US(5);
     				Reg00=0x22;	//���������DMA����
					DELAY_US(5);
 //=======================================
					
					d.total = RxEthnetFrameBuffer[0];
					length = RxEthnetFrameBuffer[1];
     				if(((d.e.high & 0x01)==0)||(d.e.low > 0x7f) || (d.e.low < 0x4c)||( length > 1517))
    					{//����״̬�������һ���ݰ�����ʼҳ��ַ�������յ����ݰ�����>1500�ֽ�
       						page(1);
							DELAY_US(15);
							curr=Reg07; 	//page1
							DELAY_US(5);
							page(0);		//�л���page0
							DELAY_US(15);
        					bnry = curr -1;
        					if(bnry < 0x4c) 	bnry =0x7f;
        					Reg03=bnry; 	//write to bnry     
							DELAY_US(15);
        					Reg07=0xff;
							return(0);
              			}
//=============================================
            
     				else//��ʾ���ݰ�����õ�.��ȡʣ�µ�����
     					{
     						Temp = SwapWord(RxEthnetFrameBuffer[8]);		
        					if((Temp == Frame_IP)||(Temp == Frame_ARP))
								{ //Э��ΪIP��ARP�Ž���
                					Reg09 = bnry;   				//read page address high
									DELAY_US(5);
                					Reg08 = 4;      				//read page address low
									DELAY_US(5);
                					Reg0b = length>>8;  //read count high
									DELAY_US(5);
                					Reg0a = length & 0xff;//read count low;
									DELAY_US(5);
                					
                					Reg00=0x0a;                             //read dma
									DELAY_US(5);
						        	length=(length+1)/2;
                					for(ii=2;ii<length+2;ii++)
                						{
                							RxEthnetFrameBuffer[ii]=Reg10;
                						}
                        			//================��ֹDMA����
                        			Reg0b=0x00;			//read count high   
									DELAY_US(5);
                        			Reg0a=0x00;			//read count low;
									DELAY_US(5);
                        			Reg00=0x22;			//���������DMA
									DELAY_US(5);
                        			//============================
                        		}
                        		//=========================================
                        	d.total = RxEthnetFrameBuffer[0];
                        	bnry = d.e.low - 1;	
                			if(bnry<0x4c)	bnry=0x7f;
	        				Reg03=bnry;      //write to bnry
							DELAY_US(5);
	               			Reg07=0xff;
							DELAY_US(5);
//--------------------------------------                			
                			RxSuccessFlag=1;
//--------------------------------------                			
                			return(1);   //have new packet
               			}
   				}
			else{	
					return(0);
				}	
		}

Uint16 SwapWord(Uint16 Data)
{
    return((Data>>8)|(Data<<8));
}

void WriteDWord(Uint16 *Address,Uint32 Data)
{
    Uint16 Temp;
    Temp=(Uint16)(Data>>16);
    *Address=SwapWord(Temp);
    Temp=(Uint16)(Data&0x0000FFFF);
    *(Address+1)=SwapWord(Temp);
}

void CopyFrameFromBE(Uint16 Offset,Uint16 Size)
{
    Uint16 i,Temp;
    for(i=0;i<Size;i++)
    {
         Temp=*(RxEthnetFrameBuffer+Offset+i);
         *(RxEthnetFrameBuffer+Offset+i)=SwapWord(Temp);
    }
}

//============================================================
//======================== ARP ================================
void ArpRequest(void)
{
	*(TxEthnetFrameBuffer + ETH_HEADER_START +0) = 0xFFFF;
	*(TxEthnetFrameBuffer + ETH_HEADER_START +1) = 0xFFFF;
	*(TxEthnetFrameBuffer + ETH_HEADER_START +2) = 0xFFFF;//Ŀ��mac
	 
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+3),&MyMAC,3);//Դmac
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_ARP);//ARP
    *(TxEthnetFrameBuffer+ARP_HEADER_START+0)=SwapWord(HARDW_ETH);//Ӳ������:��̫��
    *(TxEthnetFrameBuffer+ARP_HEADER_START+1)=SwapWord(Frame_IP);//Э�����ͣ�IP
    *(TxEthnetFrameBuffer+ARP_HEADER_START+2)=SwapWord(IP_HLEN_PLEN);//Ӳ������+Э�鳤��
    *(TxEthnetFrameBuffer+ARP_HEADER_START+3)=SwapWord(OP_ARP_REQUEST);//������arp����
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+4),&MyMAC,3);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+7),&MyIP,2);
	*(TxEthnetFrameBuffer + ARP_HEADER_START+9) = 0xFFFF;
	*(TxEthnetFrameBuffer + ARP_HEADER_START+10) = 0xFFFF;
	*(TxEthnetFrameBuffer + ARP_HEADER_START+11) = 0xFFFF;//Ŀ��mac
    
    //if(((RemoteIP[0]^MyIP[0])&SubnetMask[0])||((RemoteIP[1]^MyIP[1])&SubnetMask[1]))
    //     memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+12),&GatewayIP,2);
    //else
         memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+12),&RemoteIP,2);

    TxFrameSize=750;
    SendFrame(TxEthnetFrameBuffer,TxFrameSize);
}

void ArpAnswer(void)
{
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+0),&RecdFrameMAC,3);
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+3),&MyMAC,3);
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_ARP);
//ARP    
    *(TxEthnetFrameBuffer+ARP_HEADER_START+0)=SwapWord(HARDW_ETH);
    *(TxEthnetFrameBuffer+ARP_HEADER_START+1)=SwapWord(Frame_IP);
    *(TxEthnetFrameBuffer+ARP_HEADER_START+2)=SwapWord(IP_HLEN_PLEN);
    *(TxEthnetFrameBuffer+ARP_HEADER_START+3)=SwapWord(OP_ARP_ANSWER);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+4),&MyMAC,3);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+7),&MyIP,2);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+9),&RecdFrameMAC,3);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+12),&RecdFrameIP,2);
    TxFrameSize=30;
}

void addinit()
{
	ArpRequest();
	while(!RecFrame())
	{
	    SendFrame(TxEthnetFrameBuffer,TxFrameSize);
	}
	memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+0),RxEthnetFrameBuffer+ETH_HEADER_START+5,3);
}

//============================================================
//======================== UDP ================================
#pragma CODE_SECTION(UDPinit,"ramfuncs");
void UDPinit(float *data,int length)
{
	identification++;
	memcpy(TxEthnetFrameBuffer+21,data,length);
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_IP);//֡���ͣ�IP
    *(TxEthnetFrameBuffer+IP_HEADER_START+0)=SwapWord(Ip_Edition);//Ip �汾��IP�ײ�����
    *(TxEthnetFrameBuffer+IP_HEADER_START+1)=SwapWord(2*(length+21-IP_HEADER_START));//IP������
    *(TxEthnetFrameBuffer+IP_HEADER_START+2)=SwapWord(identification);//��ʶ
    *(TxEthnetFrameBuffer+IP_HEADER_START+3)=SwapWord(0x0000);//���ֶ�
    *(TxEthnetFrameBuffer+IP_HEADER_START+4)=SwapWord(0x2011);//TTL=32,Э��ΪUDP
    memcpy((TxEthnetFrameBuffer+IP_HEADER_START+6),&MyIP,2);
    memcpy((TxEthnetFrameBuffer+IP_HEADER_START+8),&RemoteIP,2);
    *(TxEthnetFrameBuffer+UDP_HEADER_START+0)=SwapWord(MY_UDP_PORT);
    *(TxEthnetFrameBuffer+UDP_HEADER_START+1)=SwapWord(REMOTE_UDP_PORT);
    *(TxEthnetFrameBuffer+UDP_HEADER_START+2)=SwapWord(2*(21+length-UDP_HEADER_START));//UDP������
    *(TxEthnetFrameBuffer+UDP_HEADER_START+3)=0;//У�������
    *(TxEthnetFrameBuffer+IP_HEADER_START+5)=0;//У�������
    /*UDPУ�����ô���㲻�ԣ�������*/
    //*(TxEthnetFrameBuffer+UDP_HEADER_START+3)=CalcCheckSum(TxEthnetFrameBuffer+UDP_HEADER_START,UDP_HEADER_SIZE+length,0,1);//UDPͷУ���
    *(TxEthnetFrameBuffer+IP_HEADER_START+5)=CalcCheckSum(TxEthnetFrameBuffer+IP_HEADER_START,IP_HEADER_SIZE,0,0);//IPͷУ���
    //*(TxEthnetFrameBuffer+length+21)=0;//���һ���ֽ���Ϊ0
    SendFrame(TxEthnetFrameBuffer,length+21);
}

//======================= END ===============================
