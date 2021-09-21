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
Uint16 IpEdition;                                //IP版本
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
**函数原型：    void  page(uchar pagenumber)
**入口参数:   	Uint16	pagenumber: 要切换的页
**出口参数:		无
**返 回 值：	无      
**说    明：	选择页,可选择0,1,2三页,第四页ne000兼容芯片保留 
************************************************************************/
void	page(Uint16 pagenumber)
		{
			Uint16	temp;
			temp = Reg00;				//command register
			temp = temp&0x3B ; 			//注意txp位不能要
			pagenumber=pagenumber <<6;
			temp=temp | pagenumber;
			Reg00=temp;
		}


/**********************************************************************
**函数原型:     void 	Init8019()
**入口参数:		无
**出口参数:		无
**返 回 值:		无              
**说    明:		对芯片的工作寄存器进行设置,各个寄存器的用法可参考文档和
**				络芯片的数据手册
************************************************************************/
void	Init8019()
		{
			DELAY_US(10000);
/**********************************************************************

1.Reg00命令寄存器: CR,命令寄存器,地址偏移量00H,为一个字节
  位:  7   6   5   4   3   2   1   0 
名字: PS1 PS0 RD2 RD1 RD0 TXP STA STP 
//============================================
2.
RD2,RD1,RD0: 这3个位代表要执行的功能。
 0   0   1 : 读网卡内存
 0   1   0 : 写网卡内存
 0   1   1 : 发送网卡数据包
 1   *   * : 完成或结束DMA的读写操作
//============================================
3.TXP位置1时发送数据包，发完自动清零
//============================================
4.
STA,STP:	这两个位用来启动命令或停止命令
 1   0 		启动命令
 0   1 		停止命令
//============================================
********************************************************/
			Reg00=0x21;   //使芯片处于停止模式,这时进行寄存器设置

			DELAY_US(10000); //延时10毫秒,确保芯片进入停止模式
			page(0);
			Reg0a=0x00;   //清rbcr0
			DELAY_US(5);
			Reg0b=0x00;   //清rbcr1
			DELAY_US(5);
			Reg0c= 0xe0;  //RCR,监视模式,不接收数据包          
			DELAY_US(5);
			Reg0d= 0xe2;  //TCR,loop back模式
			DELAY_US(5);

			Reg01=0x4c;
			DELAY_US(5);
			Reg02=0x80;
			DELAY_US(5);
			Reg03=0x4c;
			DELAY_US(5);
			Reg04=0x40;  //TPSR,发送起始页寄存器
			DELAY_US(5);
			Reg07=0xff;  //清除所有中断标志位，中断状态寄存器
			DELAY_US(5);
			Reg0f=0x00;  //中断屏蔽寄存器清0，禁止中断
			DELAY_US(5);

			Reg0e=0xC9;  // 数据配置寄存器，16位dma方式
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
			Reg0c=0xce;  //将芯片设置成正常模式,跟外部网络连接
			DELAY_US(5);
			Reg0d=0xe0;  // 发送配置寄存器TCR，设置为启用crc自动生成和校验，正常模式工作
			DELAY_US(5);
			Reg00=0x22;  //启动芯片开始工作
			DELAY_US(5);
//-----------------------------------
			Reg07=0xff;  //清除所有中断标志位
			DELAY_US(5);
		}

Uint16 CalcCheckSum(Uint16 *Start, Uint16 Count, Uint16 IsTCP, Uint16 IsUDP)
{
    Uint32 Sum;
  
    Sum = 0;
    if ((IsTCP)||(IsUDP)) //计算伪首部校验值
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
**函数原型：    void 		SendFrame(Uint16 *TxdNetBuff,Uint16  length)
**入口参数:		Uint16    	*TxdNetBuff	:指向发送缓冲区
**              uint length					:发送数据包的长度
**出口参数:		无
**返 回 值：	无              
**说    明：	发送数据包,以太网底层驱动程序,所有的数据发送都要通过该程序
************************************************************************/
void	SendFrame(Uint16 *TxdNetBuff,Uint16 length)
		{


			Uint16	i,ii;
		   	/*if(length<46/2)//以太网帧最小数据长度为46字节，不足的用0填充
       			{
          			for(i=length;i<60/2;i++)	TxdNetBuff[i]=0;
          			length=60/2;
       			}*/
			
			page(0);
			DELAY_US(5);					//切换至第0页
			length = length <<1;
			TxBufFlag=!TxBufFlag;			//设置两个发缓区,提高发送效率
			if(TxBufFlag)
				{Reg09=0x40 ;}				//设置发送页地址
			else
				{Reg09=0x46 ;}				//设置发送页地址
    		DELAY_US(5);
			Reg08=0x00; 					//read page address low
			DELAY_US(5);
			Reg0b = length >>8;				//写发送长度高位
			DELAY_US(5);
			Reg0a = length & 0x00ff;        //写发送长度低位  
			DELAY_US(5);
			Reg00=0x12;						//write dma, page0
			DELAY_US(5);

			for(i=0;i<length/2;i++)
				{
					Reg10 = TxdNetBuff[i];
   				}
/***************************************/
//以下为终止DMA操作
			Reg0b=0x00; 
			DELAY_US(5);
			Reg0a=0x00;
			DELAY_US(5);
			Reg00=0x22;			//结束或放弃DMA操作
/***************************************/

			for(i=0;i<6;i++)	//最多重发6次
				{
					for(ii=0;ii<1000;ii++)
    					{//检查CR寄存器的txp位是否为低,为1说明正在发送,为0说明发完或出错放弃
        					if((Reg00&0x04)==0)  
        						{ break; }
        				}
					if((Reg04&0x01)!=0)//表示发送成功,判断发送状态寄存器TSR，决定是否出错
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
**函数原型：    Uint16        Rec_NewPacket()
**入口参数:		无
**出口参数:		无
**返 回 值：	0          没有新数据包
**              1          接收到新数据包
**说    明：	查询是否有新数据包并接收进缓冲区
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
			bnry = Reg03;				//bnry page have read 读页指针
			bnry = bnry & 0x00FF;
			page(1);
			DELAY_US(15);
			curr = Reg07;				//curr writepoint 8019写页指针
			curr = curr & 0x00FF;
			page(0);
			if((curr==0))return(0);	//读的过程出错
			bnry++;
			if(bnry>0x7f)	bnry=0x4c;
			if(bnry!=curr)			//此时表示有新的数据包在缓冲区里
    			{					//在任何操作都最好返回page0
     				page(0);
     //=======================================
					DELAY_US(15);
     				Reg09=bnry;		//读页地址的高字节
					DELAY_US(5);
     				Reg08=0x00; 	//读页地址的低字节
					DELAY_US(5);
     				Reg0b=0x00;		//读取字节计数高字节
					DELAY_US(5);
     				Reg0a=18;       //读取字节计数高字节
					DELAY_US(5);
     				Reg00=0x0a;     //启动Remote DMA读操作
					DELAY_US(5);
	 
	 
     				for(i=0;i<9;i++)	//读取一包的前18个字节:4字节的8019头部,6字节目的地址,6字节原地址,2字节协议
                    	{
                       		RxEthnetFrameBuffer[i]=Reg10;
                      	}
 //=======================================中止DMA操作
					DELAY_US(5);
     				Reg0b=0x00;	//
					DELAY_US(5);
     				Reg0a=0x00;	//
					DELAY_US(5);
     				Reg00=0x22;	//结束或放弃DMA操作
					DELAY_US(5);
 //=======================================
					
					d.total = RxEthnetFrameBuffer[0];
					length = RxEthnetFrameBuffer[1];
     				if(((d.e.high & 0x01)==0)||(d.e.low > 0x7f) || (d.e.low < 0x4c)||( length > 1517))
    					{//接收状态错误或下一数据包的起始页地址错误或接收的数据包长度>1500字节
       						page(1);
							DELAY_US(15);
							curr=Reg07; 	//page1
							DELAY_US(5);
							page(0);		//切换回page0
							DELAY_US(15);
        					bnry = curr -1;
        					if(bnry < 0x4c) 	bnry =0x7f;
        					Reg03=bnry; 	//write to bnry     
							DELAY_US(15);
        					Reg07=0xff;
							return(0);
              			}
//=============================================
            
     				else//表示数据包是完好的.读取剩下的数据
     					{
     						Temp = SwapWord(RxEthnetFrameBuffer[8]);		
        					if((Temp == Frame_IP)||(Temp == Frame_ARP))
								{ //协议为IP或ARP才接收
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
                        			//================终止DMA操作
                        			Reg0b=0x00;			//read count high   
									DELAY_US(5);
                        			Reg0a=0x00;			//read count low;
									DELAY_US(5);
                        			Reg00=0x22;			//结束或放弃DMA
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
	*(TxEthnetFrameBuffer + ETH_HEADER_START +2) = 0xFFFF;//目的mac
	 
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+3),&MyMAC,3);//源mac
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_ARP);//ARP
    *(TxEthnetFrameBuffer+ARP_HEADER_START+0)=SwapWord(HARDW_ETH);//硬件类型:以太网
    *(TxEthnetFrameBuffer+ARP_HEADER_START+1)=SwapWord(Frame_IP);//协议类型：IP
    *(TxEthnetFrameBuffer+ARP_HEADER_START+2)=SwapWord(IP_HLEN_PLEN);//硬件长度+协议长度
    *(TxEthnetFrameBuffer+ARP_HEADER_START+3)=SwapWord(OP_ARP_REQUEST);//操作：arp请求
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+4),&MyMAC,3);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+7),&MyIP,2);
	*(TxEthnetFrameBuffer + ARP_HEADER_START+9) = 0xFFFF;
	*(TxEthnetFrameBuffer + ARP_HEADER_START+10) = 0xFFFF;
	*(TxEthnetFrameBuffer + ARP_HEADER_START+11) = 0xFFFF;//目的mac
    
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
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_IP);//帧类型：IP
    *(TxEthnetFrameBuffer+IP_HEADER_START+0)=SwapWord(Ip_Edition);//Ip 版本和IP首部长度
    *(TxEthnetFrameBuffer+IP_HEADER_START+1)=SwapWord(2*(length+21-IP_HEADER_START));//IP包长度
    *(TxEthnetFrameBuffer+IP_HEADER_START+2)=SwapWord(identification);//标识
    *(TxEthnetFrameBuffer+IP_HEADER_START+3)=SwapWord(0x0000);//不分段
    *(TxEthnetFrameBuffer+IP_HEADER_START+4)=SwapWord(0x2011);//TTL=32,协议为UDP
    memcpy((TxEthnetFrameBuffer+IP_HEADER_START+6),&MyIP,2);
    memcpy((TxEthnetFrameBuffer+IP_HEADER_START+8),&RemoteIP,2);
    *(TxEthnetFrameBuffer+UDP_HEADER_START+0)=SwapWord(MY_UDP_PORT);
    *(TxEthnetFrameBuffer+UDP_HEADER_START+1)=SwapWord(REMOTE_UDP_PORT);
    *(TxEthnetFrameBuffer+UDP_HEADER_START+2)=SwapWord(2*(21+length-UDP_HEADER_START));//UDP包长度
    *(TxEthnetFrameBuffer+UDP_HEADER_START+3)=0;//校验和清零
    *(TxEthnetFrameBuffer+IP_HEADER_START+5)=0;//校验和清零
    /*UDP校验和怎么都算不对，不算了*/
    //*(TxEthnetFrameBuffer+UDP_HEADER_START+3)=CalcCheckSum(TxEthnetFrameBuffer+UDP_HEADER_START,UDP_HEADER_SIZE+length,0,1);//UDP头校验和
    *(TxEthnetFrameBuffer+IP_HEADER_START+5)=CalcCheckSum(TxEthnetFrameBuffer+IP_HEADER_START,IP_HEADER_SIZE,0,0);//IP头校验和
    //*(TxEthnetFrameBuffer+length+21)=0;//最后一个字节设为0
    SendFrame(TxEthnetFrameBuffer,length+21);
}

//======================= END ===============================
