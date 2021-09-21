#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include  <math.h>
#include  <string.h>

#define pi 3.141593 // floatС�����6λ
#define NL 2048  // NLΪ�ϳ��źŵ�������N��ֵ������һ�µģ���NL=N
float Vn1;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
float Vn2;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
float T1;//�����ת������X(k+B)�ĳ˻�
float T2;//�����ת������X(k+B)�ĳ˻�
int LH,N1;
float Wn1[12],Wn2[12];//������ת���Ӳ���ǰ������ֵ������Ϊfft������2��ָ��+1
float Sample1[NL];// ���������ʵ��ת��Ϊ����
float Sample2[NL];// ���������ʵ��ת��Ϊ����
float level;//��ֵ
int ok=0;
int ffttable[NL];

//float P,Q0,Q1,Q2,C,f,temp,k,N;
/*���㲢��ʼ������*/
/*void Goertzel_init(void)//����Ϊ(Ƶ�ʼ������������)
{
		f=50;
		N=40960/f;
		k=10;
		temp=(2*pi*k)/30720;				//K=N*f/R
		C=2*(cos(temp));					//w=3.141593*2*K/N(����)
												//w=360*K/N=7.2*f/N(�Ƕ�)
}*/
/*��������*/
/*void goertzel_reset(void)
{
	Q1=Q2=0;
}*/
/*���㣨ÿ�β�������һ�Σ�*/
/*void goertzel_process(int S)					//����Ϊ���ݱ���
{
		Q0 = C*Q1-Q2+S;
		Q2 = Q1;
		Q1 = Q0;
}*/
/*���ݼ�����ϣ�������*/
/*void goertzel_output(void)
{
		P=Q1*Q1+Q2*Q2-C*Q1*Q2;
		Q1=Q2=0;
}
*/

//#pragma DATA_SECTION(Sample1,"ADCDATA1");
//#pragma DATA_SECTION(Sample2,"ADCDATA1");
void fftinit(void)		//��ʼ������
{
	//����Ϊ������ת���ӱ�
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
		Wn1[2]=0;	//�������ú�С��С����ʾ0����ֱ�Ӹ�ֵ0
		Wn2[1]=0;
}
void daoxu(void)
{
//����Ϊ���������
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
void MYFFT(float *xin1,float *xin2)//����Ϊ����ָ��*xin����N��FFT
{
   int L=0; // ���������
   int J=0; // ���������
   int K=0,KB=0; // ���������
   int B=0; // �����������������ݼ��
   float temp1;

   /* �������� */
   for(L=1;L<=11;L++)  // ����
	{
	  B=2<<(L-2);
	  if(L==1)B=1;
      Vn1=1;
	  Vn2=0;
	  for(J=0;J<B;J++)   // ����
	   {
		 for(K=J;K<NL;K+=2*B)  // ������������
		  {
            KB=K+B;
            T1=xin1[KB]*Vn1-xin2[KB]*Vn2;
            T2=xin1[KB]*Vn2+xin2[KB]*Vn1;//����
            xin1[KB]=xin1[K]-T1;//ԭַ���㣬�����������ԭ����������
            xin2[KB]=xin2[K]-T2;
             xin1[K]+=T1;
             xin2[K]+=T2;
		  }
		  temp1=Wn1[L]*Vn1-Wn2[L]*Vn2;
		  Vn2=Wn1[L]*Vn2+Wn2[L]*Vn1;//����
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
	 for(i=0;i<NL;i++)   //����ʵ���ź�ת��Ϊ����
	  {
		 j=ffttable[i];
         Sample1[i]=input[j];
	  }
	 MYFFT(Sample1,Sample2);                //FFT
     ModelComplex(Sample1,Sample2,output);  //��ģ
     //if(ok==1)while(1);
}
