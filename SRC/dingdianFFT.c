#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include  <math.h>
#include  <string.h>


float pi=3.141593; // float小数点后6位
#define NL 1024  // NL为合成信号点数，与N的值必须是一致的，即NL=N
int Vn1;//每一级第一个旋转因子虚部为0，实部为1
int Vn2;//每一级第一个旋转因子虚部为0，实部为1
int T1;//存放旋转因子与X(k+B)的乘积
int T2;//存放旋转因子与X(k+B)的乘积
int LH,N1;
int Wn1[11]={0,-32768,0,23171,30274,32139,32610,32729,32758,32766,32767};
int Wn2[11]={0,0,-32767,-23171,-12540,-6393,-3212,-1608,-804,-402,-201};//定义旋转因子并提前计算数值，长度为fft点数对2的指数
int Sample1[NL];// 采样输入的实数转化为复数
int Sample2[NL];// 采样输入的实数转化为复数
//float level=10000000000000;
int ok=0;
int ffttable[NL];

void fftinit(void)		//初始化参数
{
	LH=NL/2;
	N1=NL-2;
	//以下为建立倒序表

}

void MYFFT(int *xin1,int *xin2)//输入为复数指针*xin，做N点FFT
{
   int L=0; // 级间运算层
   int J=0; // 级内运算层
   int K=0,KB=0; // 蝶形运算层
   int B=0; // 蝶形运算两输入数据间隔
   long temp1;
   /* 以下是为倒序新建的局部变量*/
   int J2=0,I,K2=0;
   long T1;
   long T2;
   /*以下是倒序*/
   J2=LH;
   for(I=1;I<=1022;I++)
    {
     if(I<J2)
	 {
       T1=xin1[I];
       xin1[I]=xin1[J2];
       xin1[J2]=T1;
	 }
	 K2=LH;
	 while(J2>=K2)
	  {
        J2-=K2;
        K2=K2/2;// K2=K2/2
	  }
	  J2+=K2;
    }

   /* 蝶形运算 */
   for(L=1;L<=10;L++)  // 级间
	{
	  B=2<<(L-2);
	  if(L==1)B=1;
      Vn1=32767;
	  Vn2=0;
	  for(J=0;J<B;J++)   // 级内
	   {
		 for(K=J;K<NL;K+=2*B)  // 蝶形因子运算
		  {
            KB=K+B;
            T1=(xin1[KB]*Vn1-xin2[KB]*Vn2)/32768;
            T2=(xin1[KB]*Vn2+xin2[KB]*Vn1)/32768;//复乘
            xin1[KB]=xin1[K]-T1;//原址运算，计算结果存放在原来的数组中
            xin2[KB]=xin2[K]-T2;
             xin1[K]+=T1;
             xin2[K]+=T2;
		  }
		  temp1=(Wn1[L]*Vn1-Wn2[L]*Vn2)/32768;
		  Vn2=(Wn1[L]*Vn2+Wn2[L]*Vn1)/32768;//复乘
		  Vn1=temp1;
		}
	 }

}

void ModelComplex(int *Sample1,int *Sample2,int *output)
{
	Uint16 i=0;
	int temp1,temp2;
   for(i=0;i<NL;i++)
    {
	   temp1=(Sample1[i]*Sample1[i])/32768;
	   temp2=(Sample2[i]*Sample2[i])/32768;
     output[i]=temp1+temp2;
     Sample2[i]=0;
     //if(i>128&&i<512&&output[i]>level)ok=1;
		memset(Sample1,0,NL);
	}
}

void fft(int *input,int *output)
{
	 MYFFT(input,Sample2);                //FFT
     ModelComplex(input,Sample2,output);  //求模
     //if(ok==1)while(1);
}
