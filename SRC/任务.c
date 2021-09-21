#include  <math.h>
#include  <string.h>
#include  <stdio.h>
#define N 64									         //数据长度
#define res 6									         //谐波次数
#define res_2 12									     //2*谐波次数
float P[res],Q0[res],Q1[res],Q2[res],C[res],f[res],temp[res],k[res],data;
float Q0_alone,Q1_alone,Q2_alone;
float P_alone1,P_alone2,P_alone3;//输出测试

int x[64];

/*获得数据*/
void data_set(void)
{
    int i;
    for(i=0;i<N;i++)
    {
        x[i]=220*sin(i*100*3.141593/3200);
    }
}

/*初始化参数*/
void Goertzel_init(float interval)                       //输入为频率间隔
{
    int i;
	float PI=3.141593;							         //float小数点后6位
	float floatN;
	floatN = (float) N;							         //将N转化为浮点数方便进行四舍五入
	for(i=0;i<res;i++)
	{
		f[i]=interval*(i+1);
		k[i] = (int) (0.5 + ((floatN * f[i]) / 3200));   //采样率3200
		temp[i]=(2*PI*k[i])/floatN;				         //K=N*f/R
		C[i]=2*(cos(temp[i]));					         //w=3.141593*2*K/N(弧度)
	}											         //w=360*K/N=7.2*f/N(角度)
}

/*计算全部谐波向量*/
void goertzel_process_all(int* x)					     //参数为输入
{
	memset(Q1,0,res_2);
	memset(Q2,0,res_2);                                  //序列清零
    int i,j;
    for(j=0;j<N;j++)
	{
        data = (float)x[j];                              //int提升为float；
        for(i=0;i<res;i++)						    	 //计算Q0
        {
            Q0[i]=C[i]*Q1[i]-Q2[i]+data;
            //Q2[i] = Q1[i];
            //Q1[i] = Q0[i];
        }
        memcpy(Q2,Q1,res_2);						  	 //将上次的计算结果保存在Q2中
        memcpy(Q1,Q0,res_2);							 //将本次的计算结果保存在Q1中
    }
    /*计算完毕，全部谐波求模*/
	for(i=0;i<res;i++)
	{
		P[i]=Q1[i]*Q1[i]+Q2[i]*Q2[i]-C[i]*Q1[i]*Q2[i];   //若数据过大容易溢出，开根号/取对数/右移
	}
}

/*计算单个谐波向量*/
float Goertzel(int x[], int order)
{
	Q1_alone=Q2_alone=0;                                 //清零
    int j;
    for(j=0;j<N;j++)
	{
        data = (float)x[j];                              //int提升为float；
        Q0_alone=C[order-1]*Q1_alone-Q2_alone+data;
        Q2_alone = Q1_alone;
        Q1_alone = Q0_alone;
    }
    /*计算完毕，求模*/
    float P1;
	P1=Q1_alone*Q1_alone+Q2_alone*Q2_alone-C[order-1]*Q1_alone*Q2_alone;
    return(P1);
}

void main(void)
{

	//data_set();

	{
		int j;
		FILE* fp = fopen("d:\\data\\led_arc1.txt","r");
		for(j=0;j<64;j++) /*读j行*/
		{
			fscanf(fp,"%d",&x[j]);  /*读一个数据*/
		}
		/* 关闭文件 */
		fclose(fp);
	}

    Goertzel_init(50);										 //基波为50hz
    goertzel_process_all(x);                                 //测试
    P_alone1=Goertzel(x, 1);
    P_alone2=Goertzel(x, 3);								 //测试
    P_alone3=Goertzel(x, 5);
}
