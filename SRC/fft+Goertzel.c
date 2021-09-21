#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include  <math.h>
#include  <string.h>

#define pi 3.141593 // float小数点后6位
#define NL 2048  // NL为合成信号点数，与N的值必须是一致的，即NL=N
float Vn1;//每一级第一个旋转因子虚部为0，实部为1
float Vn2;//每一级第一个旋转因子虚部为0，实部为1
float T1;//存放旋转因子与X(k+B)的乘积
float T2;//存放旋转因子与X(k+B)的乘积
int LH,N1;
float Wn1[12],Wn2[12];//定义旋转因子并提前计算数值，长度为fft点数对2的指数+1
float Sample1[NL];// 采样输入的实数转化为复数
float Sample2[NL];// 采样输入的实数转化为复数
float level;//阈值
int ok=0;
int ffttable[NL];

//float P,Q0,Q1,Q2,C,f,temp,k,N;
/*计算并初始化参数*/
/*void Goertzel_init(void)//参数为(频率间隔，采样点数)
{
		f=50;
		N=40960/f;
		k=10;
		temp=(2*pi*k)/30720;				//K=N*f/R
		C=2*(cos(temp));					//w=3.141593*2*K/N(弧度)
												//w=360*K/N=7.2*f/N(角度)
}*/
/*序列清零*/
/*void goertzel_reset(void)
{
	Q1=Q2=0;
}*/
/*计算（每次采样进行一次）*/
/*void goertzel_process(int S)					//参数为数据变量
{
		Q0 = C*Q1-Q2+S;
		Q2 = Q1;
		Q1 = Q0;
}*/
/*数据计算完毕，输出结果*/
/*void goertzel_output(void)
{
		P=Q1*Q1+Q2*Q2-C*Q1*Q2;
		Q1=Q2=0;
}
*/

//#pragma DATA_SECTION(Sample1,"ADCDATA1");
//#pragma DATA_SECTION(Sample2,"ADCDATA1");
void fftinit(void)		//初始化参数
{
	//以下为建立旋转因子表
	int temp;
	int B1;
	LH=NL/2;
	N1=NL-2;
	for(temp=1;temp<=11;temp++)
	{
		B1=(float)(2<<(temp-2));
		if(temp==1)B1=1;
		Wn1[temp]=cos(pi/B1);
		Wn2[temp]=-sin(pi/B1);
	}
		Wn1[2]=0;	//浮点数用很小的小数表示0，故直接赋值0
		Wn2[1]=0;
}
void daoxu(void)
{
//以下为建立倒序表
int LH=0,J2=0,N1=0,I,K2=0,N=2048,T1;
LH=N/2; // LH=N/2
J2=LH;
N1=N-2;
for(I=0;I<N;I++)
{
	ffttable[I]=I;
}
for(I=1;I<=N1;I++)
{
	if(I<J2)
	{
		T1=ffttable[I];
		ffttable[I]=ffttable[J2];
		ffttable[J2]=T1;
	}
	K2=LH;
	while(J2>=K2)
	{
		J2-=K2;
		K2=K2/2;// K2=K2/2
	}
	J2+=K2;
}
}
void MYFFT(float *xin1,float *xin2)//输入为复数指针*xin，做N点FFT
{
   int L=0; // 级间运算层
   int J=0; // 级内运算层
   int K=0,KB=0; // 蝶形运算层
   int B=0; // 蝶形运算两输入数据间隔
   float temp1;

   /* 蝶形运算 */
   for(L=1;L<=11;L++)  // 级间
	{
	  B=2<<(L-2);
	  if(L==1)B=1;
      Vn1=1;
	  Vn2=0;
	  for(J=0;J<B;J++)   // 级内
	   {
		 for(K=J;K<NL;K+=2*B)  // 蝶形因子运算
		  {
            KB=K+B;
            T1=xin1[KB]*Vn1-xin2[KB]*Vn2;
            T2=xin1[KB]*Vn2+xin2[KB]*Vn1;//复乘
            xin1[KB]=xin1[K]-T1;//原址运算，计算结果存放在原来的数组中
            xin2[KB]=xin2[K]-T2;
             xin1[K]+=T1;
             xin2[K]+=T2;
		  }
		  temp1=Wn1[L]*Vn1-Wn2[L]*Vn2;
		  Vn2=Wn1[L]*Vn2+Wn2[L]*Vn1;//复乘
		  Vn1=temp1;
		}
	 }
}

void ModelComplex(float *Sample1,float *Sample2,float *output)
{
	Uint16 i=0;
   for(i=0;i<NL;i++)
    {
	   output[i]=Sample1[i]*Sample1[i]+Sample2[i]*Sample2[i];
     Sample2[i]=0;
     //if(i>128&&i<512&&output[i]>level)ok=1;
	}
}

void fft(short *input,float *output)
{
	daoxu();
	fftinit();
   Uint16 i=0,j=0;
	 for(i=0;i<NL;i++)   //输入实数信号转换为复数
	  {
		 j=ffttable[i];
         Sample1[i]=input[j];
	  }
	 MYFFT(Sample1,Sample2);                //FFT
     ModelComplex(Sample1,Sample2,output);  //求模
     //if(ok==1)while(1);
}
