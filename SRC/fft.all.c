#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include  <math.h>


#pragma DATA_SECTION(Complex.real,"ADCDATA");
#define pi 3.141593 // floatС�����6λ
#define NL 4096  // NLΪ�ϳ��źŵ�������N��ֵ������һ�µģ���NL=N
    int N=NL;   //FFT����
struct Complex		// ���帴���ṹ��
{
   float real,imag;
};
struct Complex Wn;//������ת����
struct Complex Vn;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
struct Complex T;//�����ת������X(k+B)�ĳ˻�

//float Realin[NL]={0};// ���������ʵ��
float output[NL]={0};// �����FFT��ֵ��������ģ��
struct Complex Sample[NL];// ���������ʵ��ת��Ϊ����

struct Complex MUL(struct Complex a,struct Complex b)//���帴��
{
   struct Complex c;
   c.real=a.real*b.real-a.imag*b.imag;
   c.imag=a.real*b.imag+a.imag*b.real;
   return(c);
}

void MYFFT(struct Complex *xin,int N)//����Ϊ����ָ��*xin����N��FFT
{
   int L=0; // ���������
   int J=0; // ���������
   int K=0,KB=0; // ���������
   int M=1,Nn=0;// N=2^M
   float B=0; // �����������������ݼ��
   /* ������Ϊ�����½��ľֲ�����*/
   int LH=0,J2=0,N1=0,I,K2=0;
   struct Complex T;
   /*�����ǵ���*/
   LH=N/2; // LH=N/2
   J2=LH;
   N1=N-2;
   for(I=1;I<=N1;I++)
    {
     if(I<J2)
	 {
       T=xin[I];
       xin[I]=xin[J2];
       xin[J2]=T;
	 }
	 K2=LH;
	 while(J2>=K2)
	  {
        J2-=K2;
        K2=K2/2;// K2=K2/2
	  }
	  J2+=K2;
    }
   /* ����Ϊ�����M */
   Nn=N;
   while(Nn!=2)// �����N����2Ϊ��������M
   {
     M++;
	 Nn=Nn/2;
   }

   /* �������� */
   for(L=1;L<=M;L++)  // ����
	{
	  B=pow(2,(L-1));
      Vn.real=1;
	  Vn.imag=0;
      Wn.real=cos(pi/B);
      Wn.imag=-sin(pi/B);
	  for(J=0;J<B;J++)   // ����
	   {
		 for(K=J;K<N;K+=2*B)  // ������������
		  {
            KB=K+B;
            T=MUL(xin[KB],Vn);
            xin[KB].real=xin[K].real-T.real;//ԭַ���㣬�����������ԭ����������
            xin[KB].imag=xin[K].imag-T.imag;
             xin[K].real=xin[K].real+T.real;
             xin[K].imag=xin[K].imag+T.imag;
		  }
		  Vn=MUL(Wn,Vn);
		  // ��ת�����������൱��ָ����ӣ��õ��Ľ��
		  // ��J*2^��M-L����һ���ģ���Ϊ�ڵ�����������
		 // ����M��L���ǲ���ģ�Ψһ�仯���Ǽ��ڵ�J
		 // ����J����1Ϊ�����ģ���J*W��Ч��W+W+W...J��W���
		}
	 }
}


/*
void FilterDC(struct Complex *ADC,int N)//ȥ�������е�ֱ���ɷ֣�����ֱ���������ܴ�
{
   int i;
   float sum=0;
   for(i=0;i<N;i++)
    { sum+=ADC[i].real;}
   sum=sum/N;
   for(i=0;i<N;i++)
    { ADC[i].real-=sum;}
}*/

/********************************
���ܣ����㸴����ģ
�βΣ�*Sampleָ����Ҫȡģ�ĸ����ṹ��
      NΪȡģ����
	  *output���ȡģ����ֵ������
*********************************/
void ModelComplex(struct Complex *Sample,int N,float *output)
{
   int i;
   for(i=0;i<N;i++)
    {
     output[i]=Sample[i].real*Sample[i].real+Sample[i].imag*Sample[i].imag;
	}
}

void fft(int *input,float *output)
{
   Uint16 i=0;
   InitSysCtrl();
	 for(i=0;i<NL;i++)   //����ʵ���ź�ת��Ϊ����
	  {
         Sample[i].real=input[i];
		 Sample[i].imag=0;
	  }
	 MYFFT(Sample,NL);                //FFT
     ModelComplex(Sample,NL,output);  //��ģ
}
