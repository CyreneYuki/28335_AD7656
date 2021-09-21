#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include  <math.h>
#include  <string.h>


#define pi 3.141593 // float小数点后6位
#define NL 1024  // NL为合成信号点数，与N的值必须是一致的，即NL=N
    int N=NL;   //FFT点数
    long Wn1;//定义旋转因子
    long Wn2;//定义旋转因子
    long Vn1;//每一级第一个旋转因子虚部为0，实部为1
    long Vn2;//每一级第一个旋转因子虚部为0，实部为1
    long T1;//存放旋转因子与X(k+B)的乘积
    long T2;//存放旋转因子与X(k+B)的乘积
    long Sample1[NL];// 采样输入的实数转化为复数
    long Sample2[NL];// 采样输入的实数转化为复数

void MYFFT(long *xin1,long *xin2,int N)//输入为复数指针*xin，做N点FFT
{
   int L=0; // 级间运算层
   int J=0; // 级内运算层
   int K=0,KB=0; // 蝶形运算层
   float B=0; // 蝶形运算两输入数据间隔
   /* 以下是为倒序新建的局部变量*/
   int LH=0,J2=0,N1=0,I,K2=0;
   long T1;
   long T2;
   /*以下是倒序*/
   LH=N/2; // LH=N/2
   J2=LH;
   N1=N-2;
   for(I=1;I<=N1;I++)
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
	   float temp1,temp2;
	  B=pow(2,(L-1));
      Vn1=pow(2,15);
	  Vn2=0;

      temp1=cos(pi/B);
      temp2=-sin(pi/B);
      Wn1=(long)temp1;
      Wn2=(long)temp2;
      Wn1=Wn1<<15;
      Wn2=Wn2<<15;
	  for(J=0;J<B;J++)   // 级内
	   {
		 for(K=J;K<N;K+=2*B)  // 蝶形因子运算
		  {
            KB=K+B;
            T1=(xin1[KB]*Vn1-xin2[KB]*Vn2)>>15;
            T2=(xin1[KB]*Vn2+xin2[KB]*Vn1)>>15;//蝶形运算
            xin1[KB]=xin1[K]-T1;//原址运算，计算结果存放在原来的数组中
            xin2[KB]=xin2[K]-T2;
             xin1[K]=xin1[K]+T1;
             xin2[K]=xin2[K]+T2;
		  }
		  Vn1=(Wn1*Vn1-Wn2*Vn2)>>15;
		  Vn2=(Wn1*Vn2+Wn2*Vn1)>>15;//蝶形运算
		}
	 }
}

void ModelComplex(long *Sample1,long *Sample2,int N,long *output)
{
   int i;
   for(i=0;i<N;i++)
    {
     output[i]=Sample1[i]*Sample1[i]+Sample2[i]*Sample2[i];
	}
}

void fft(int *input,long *output)
{
   Uint16 i=0;
	 for(i=0;i<NL;i++)   //输入实数信号转换为复数
	  {
         Sample1[i]=input[i];
	  }
	 memset(Sample2,0,2*NL);
	 MYFFT(Sample1,Sample2,NL);                //FFT
     ModelComplex(Sample1,Sample2,NL,output);  //求模
}
