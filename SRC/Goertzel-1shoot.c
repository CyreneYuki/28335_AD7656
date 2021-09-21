#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "string.h"
float P,Q0,Q1,Q2,C,f,temp,k;

/*计算并初始化参数*/
void Goertzel_init(float interval)//参数为(频率间隔，采样点数)
{
		f=50;
		k= (int) (0.5 + (f / 153600));//采样率200000，需精确
		temp=(2*pi*k);				//K=N*f/R
		C=2*(cos(temp));					//w=3.141593*2*K/N(弧度)
												//w=360*K/N=7.2*f/N(角度)
}

/*序列清零*/
void goertzel_reset(void)
{
	Q1=Q2=0;
}

/*计算（每次采样进行一次）*/
void goertzel_process(int S)					//参数为数据变量
{
		Q0 = C*Q1-Q2+S;
		Q2 = Q1;
		Q1 = Q0;
}

/*数据计算完毕，输出结果*/
void goertzel_output(void)
{
		P=Q1*Q1+Q2*Q2-C*Q1*Q2;
}
