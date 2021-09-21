#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include  <math.h>
#include  <string.h>


#define pi 3.141593 // floatС�����6λ
#define NL 1024  // NLΪ�ϳ��źŵ�������N��ֵ������һ�µģ���NL=N
    int N=NL;   //FFT����
    long Wn1;//������ת����
    long Wn2;//������ת����
    long Vn1;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
    long Vn2;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
    long T1;//�����ת������X(k+B)�ĳ˻�
    long T2;//�����ת������X(k+B)�ĳ˻�
    long Sample1[NL];// ���������ʵ��ת��Ϊ����
    long Sample2[NL];// ���������ʵ��ת��Ϊ����

void MYFFT(long *xin1,long *xin2,int N)//����Ϊ����ָ��*xin����N��FFT
{
   int L=0; // ���������
   int J=0; // ���������
   int K=0,KB=0; // ���������
   float B=0; // �����������������ݼ��
   /* ������Ϊ�����½��ľֲ�����*/
   int LH=0,J2=0,N1=0,I,K2=0;
   long T1;
   long T2;
   /*�����ǵ���*/
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

   /* �������� */
   for(L=1;L<=10;L++)  // ����
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
	  for(J=0;J<B;J++)   // ����
	   {
		 for(K=J;K<N;K+=2*B)  // ������������
		  {
            KB=K+B;
            T1=(xin1[KB]*Vn1-xin2[KB]*Vn2)>>15;
            T2=(xin1[KB]*Vn2+xin2[KB]*Vn1)>>15;//��������
            xin1[KB]=xin1[K]-T1;//ԭַ���㣬�����������ԭ����������
            xin2[KB]=xin2[K]-T2;
             xin1[K]=xin1[K]+T1;
             xin2[K]=xin2[K]+T2;
		  }
		  Vn1=(Wn1*Vn1-Wn2*Vn2)>>15;
		  Vn2=(Wn1*Vn2+Wn2*Vn1)>>15;//��������
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
	 for(i=0;i<NL;i++)   //����ʵ���ź�ת��Ϊ����
	  {
         Sample1[i]=input[i];
	  }
	 memset(Sample2,0,2*NL);
	 MYFFT(Sample1,Sample2,NL);                //FFT
     ModelComplex(Sample1,Sample2,NL,output);  //��ģ
}
