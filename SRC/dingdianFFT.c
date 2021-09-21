#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include  <math.h>
#include  <string.h>


float pi=3.141593; // floatС�����6λ
#define NL 1024  // NLΪ�ϳ��źŵ�������N��ֵ������һ�µģ���NL=N
int Vn1;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
int Vn2;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
int T1;//�����ת������X(k+B)�ĳ˻�
int T2;//�����ת������X(k+B)�ĳ˻�
int LH,N1;
int Wn1[11]={0,-32768,0,23171,30274,32139,32610,32729,32758,32766,32767};
int Wn2[11]={0,0,-32767,-23171,-12540,-6393,-3212,-1608,-804,-402,-201};//������ת���Ӳ���ǰ������ֵ������Ϊfft������2��ָ��
int Sample1[NL];// ���������ʵ��ת��Ϊ����
int Sample2[NL];// ���������ʵ��ת��Ϊ����
//float level=10000000000000;
int ok=0;
int ffttable[NL];

void fftinit(void)		//��ʼ������
{
	LH=NL/2;
	N1=NL-2;
	//����Ϊ���������

}

void MYFFT(int *xin1,int *xin2)//����Ϊ����ָ��*xin����N��FFT
{
   int L=0; // ���������
   int J=0; // ���������
   int K=0,KB=0; // ���������
   int B=0; // �����������������ݼ��
   long temp1;
   /* ������Ϊ�����½��ľֲ�����*/
   int J2=0,I,K2=0;
   long T1;
   long T2;
   /*�����ǵ���*/
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

   /* �������� */
   for(L=1;L<=10;L++)  // ����
	{
	  B=2<<(L-2);
	  if(L==1)B=1;
      Vn1=32767;
	  Vn2=0;
	  for(J=0;J<B;J++)   // ����
	   {
		 for(K=J;K<NL;K+=2*B)  // ������������
		  {
            KB=K+B;
            T1=(xin1[KB]*Vn1-xin2[KB]*Vn2)/32768;
            T2=(xin1[KB]*Vn2+xin2[KB]*Vn1)/32768;//����
            xin1[KB]=xin1[K]-T1;//ԭַ���㣬�����������ԭ����������
            xin2[KB]=xin2[K]-T2;
             xin1[K]+=T1;
             xin2[K]+=T2;
		  }
		  temp1=(Wn1[L]*Vn1-Wn2[L]*Vn2)/32768;
		  Vn2=(Wn1[L]*Vn2+Wn2[L]*Vn1)/32768;//����
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
     ModelComplex(input,Sample2,output);  //��ģ
     //if(ok==1)while(1);
}
