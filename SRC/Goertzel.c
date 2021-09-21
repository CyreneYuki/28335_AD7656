#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "string.h"
#define res 3									//�任����
#define res_2 6									//2*�任����
float P[res],Q0[res],Q1[res],Q2[res],C[res],f[res],temp[res],k[res],data;
int i;

/*���㲢��ʼ������*/
void Goertzel_init(float interval, int N)//����Ϊ(Ƶ�ʼ������������)
{
	float PI=3.141593;							//floatС�����6λ
	float floatN;
	floatN = (float) N;							//��Nת��Ϊ���������������������
	for(i=0;i<res;i++)
	{
		f[i]=interval*(i+1);
		k[i] = (int) (0.5 + ((floatN * f[i]) / 3200));//������3200���辫ȷ
		temp[i]=(2*PI*k[i])/floatN;				//K=N*f/R
		C[i]=2*(cos(temp[i]));					//w=3.141593*2*K/N(����)
	}											//w=360*K/N=7.2*f/N(�Ƕ�)
	memset(Q0,0,res1);							//��������
	memset(P,0,res1);
}

/*��������*/
void goertzel_reset(void)
{
	memset(Q1,0,res1);
	memset(Q2,0,res1);
}

/*����*/
void goertzel_process(int S)					//����Ϊ���ݱ���
{
	data=S-32767;								//��ȡ���ݲ�תΪ�з�����
	for(i=0;i<res;i++)							//����Q0
	{
		Q0[i]=C[i]*Q1[i]-Q2[i]+data;
		//Q2[i] = Q1[i];
		//Q1[i] = Q0[i];
	}
	memcpy(Q2,Q1,res1);							//���ϴεļ�����������Q2��
	memcpy(Q1,Q0,res1);							//�����εļ�����������Q1��
}

/*���ݼ�����ϣ�������*/
void goertzel_output(void)
{
	for(i=0;i<res;i++)
	{
		P[i]=Q1[i]*Q1[i]+Q2[i]*Q2[i]-C[i]*Q1[i]*Q2[i];//�����ݹ������������������/ȡ����/����
	}
}
