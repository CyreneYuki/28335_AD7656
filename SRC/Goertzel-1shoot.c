#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "string.h"
float P,Q0,Q1,Q2,C,f,temp,k;

/*���㲢��ʼ������*/
void Goertzel_init(float interval)//����Ϊ(Ƶ�ʼ������������)
{
		f=50;
		k= (int) (0.5 + (f / 153600));//������200000���辫ȷ
		temp=(2*pi*k);				//K=N*f/R
		C=2*(cos(temp));					//w=3.141593*2*K/N(����)
												//w=360*K/N=7.2*f/N(�Ƕ�)
}

/*��������*/
void goertzel_reset(void)
{
	Q1=Q2=0;
}

/*���㣨ÿ�β�������һ�Σ�*/
void goertzel_process(int S)					//����Ϊ���ݱ���
{
		Q0 = C*Q1-Q2+S;
		Q2 = Q1;
		Q1 = Q0;
}

/*���ݼ�����ϣ�������*/
void goertzel_output(void)
{
		P=Q1*Q1+Q2*Q2-C*Q1*Q2;
}
