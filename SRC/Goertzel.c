#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "string.h"
#define res 3									//变换点数
#define res_2 6									//2*变换点数
float P[res],Q0[res],Q1[res],Q2[res],C[res],f[res],temp[res],k[res],data;
int i;

/*计算并初始化参数*/
void Goertzel_init(float interval, int N)//参数为(频率间隔，采样点数)
{
	float PI=3.141593;							//float小数点后6位
	float floatN;
	floatN = (float) N;							//将N转化为浮点数方便进行四舍五入
	for(i=0;i<res;i++)
	{
		f[i]=interval*(i+1);
		k[i] = (int) (0.5 + ((floatN * f[i]) / 3200));//采样率3200，需精确
		temp[i]=(2*PI*k[i])/floatN;				//K=N*f/R
		C[i]=2*(cos(temp[i]));					//w=3.141593*2*K/N(弧度)
	}											//w=360*K/N=7.2*f/N(角度)
	memset(Q0,0,res1);							//序列清零
	memset(P,0,res1);
}

/*序列清零*/
void goertzel_reset(void)
{
	memset(Q1,0,res1);
	memset(Q2,0,res1);
}

/*计算*/
void goertzel_process(int S)					//参数为数据变量
{
	data=S-32767;								//读取数据并转为有符号数
	for(i=0;i<res;i++)							//计算Q0
	{
		Q0[i]=C[i]*Q1[i]-Q2[i]+data;
		//Q2[i] = Q1[i];
		//Q1[i] = Q0[i];
	}
	memcpy(Q2,Q1,res1);							//将上次的计算结果保存在Q2中
	memcpy(Q1,Q0,res1);							//将本次的计算结果保存在Q1中
}

/*数据计算完毕，输出结果*/
void goertzel_output(void)
{
	for(i=0;i<res;i++)
	{
		P[i]=Q1[i]*Q1[i]+Q2[i]*Q2[i]-C[i]*Q1[i]*Q2[i];//若数据过大容易溢出，开根号/取对数/右移
	}
}
