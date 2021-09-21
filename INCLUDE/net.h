#define		RTL8019BASE		0x4900

#define		Reg00	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x00)))
#define		Reg01	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x01)))
#define		Reg02	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x02)))
#define		Reg03	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x03)))
#define		Reg04	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x04)))
#define		Reg05	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x05)))
#define		Reg06	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x06)))
#define		Reg07	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x07)))
#define		Reg08	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x08)))
#define		Reg09	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x09)))
#define		Reg0a	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0A)))
#define		Reg0b	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0B)))
#define		Reg0c	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0C)))
#define		Reg0d	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0D)))
#define		Reg0e	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0E)))
#define		Reg0f	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0F)))
#define		Reg10	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x10)))


#define MY_TCP_PORT    	     12345
#define MY_UDP_PORT  	     12345
#define REMOTE_UDP_PORT  	     12345

#define ETH_HEADER_START     0
#define IP_HEADER_START      7
#define ARP_HEADER_START     7
#define TCP_HEADER_START     17
#define UDP_HEADER_START     17
#define ICMP_HEADER_START    17
#define USER_DATA_START      27

#define RTL8019_HEADER_SIZE  2 
#define ETH_HEADER_SIZE      7
#define IP_HEADER_SIZE       10
#define TCP_HEADER_SIZE      10
#define UDP_HEADER_SIZE      4
#define ARP_FRAME_SIZE       14
#define ICMP_HEADER_SIZE     2
#define DUMMY_HEADER_SIZE    6
#define MY_MAX_SEG_SIZE      1460

#define Frame_ARP            0x0806
#define Frame_IP             0x0800
#define Ip_Edition           0x4500              //Ip 版本和IP首部长度
#define DEFUALT_TTL          128
#define ICMP_ECHO            8
#define ICMP_ECHO_REPLY      0
//ARP

#define HARDW_ETH            1
#define IP_HLEN_PLEN         0x0604
#define OP_ARP_REQUEST       1
#define OP_ARP_ANSWER        2

#define PROTOCOL_ICMP        1
#define PROTOCOL_TCP         6
#define PROTOCOL_UDP         17

/////TCP define

#define TCP_MAX_RE_TXDNUM    8

#define TCP_CODE_FIN         0x0001
#define TCP_CODE_SYN         0x0002
#define TCP_CODE_RST         0x0004
#define TCP_CODE_PSH         0x0008
#define TCP_CODE_ACK         0x0010
#define TCP_CODE_URG         0x0020

#define 	TCP_STATE_LISTEN        0
#define 	TCP_STATE_SYN_RCVD      1
#define 	TCP_STATE_SYN_SENT      2
#define 	TCP_STATE_ESTABLISHED   3
#define 	TCP_STATE_FIN_WAIT1     4
#define 	TCP_STATE_FIN_WAIT2     5
#define 	TCP_STATE_CLOSING       6
#define 	TCP_STATE_CLOSE_WAIT    7
#define 	TCP_STATE_LAST_ACK      8
#define 	TCP_STATE_CLOSED        9
#define 	TCP_STATE_TIME_WAIT     10
	
extern	void	SendFrame(Uint16	*buf,Uint16	len);
extern	Uint16	SwapWord(Uint16	data);

void	Init8019();
Uint16	RecFrame();
void 	ArpRequest();
void	ArpAnswer();
void	SendFrame(Uint16 *TxdNetBuff,Uint16 length);
void 	addinit();
void 	UDPinit(float *data,int length);
Uint16 CalcCheckSum();

//========================== end ==========================
