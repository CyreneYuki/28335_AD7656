#include  <math.h>
#include  <string.h>
#include  <stdio.h>
#define N 64									         //���ݳ���
#define res 6									         //г������
#define res_2 12									     //2*г������
float P[res],Q0[res],Q1[res],Q2[res],C[res],f[res],temp[res],k[res],data;
float Q0_alone,Q1_alone,Q2_alone;
float P_alone1,P_alone2,P_alone3;//�������

int x[64];

/*�������*/
void data_set(void)
{
    int i;
    for(i=0;i<N;i++)
    {
        x[i]=220*sin(i*100*3.141593/3200);
    }
}

/*��ʼ������*/
void Goertzel_init(float interval)                       //����ΪƵ�ʼ��
{
    int i;
	float PI=3.141593;							         //floatС�����6λ
	float floatN;
	floatN = (float) N;							         //��Nת��Ϊ���������������������
	for(i=0;i<res;i++)
	{
		f[i]=interval*(i+1);
		k[i] = (int) (0.5 + ((floatN * f[i]) / 3200));   //������3200
		temp[i]=(2*PI*k[i])/floatN;				         //K=N*f/R
		C[i]=2*(cos(temp[i]));					         //w=3.141593*2*K/N(����)
	}											         //w=360*K/N=7.2*f/N(�Ƕ�)
}

/*����ȫ��г������*/
void goertzel_process_all(int* x)					     //����Ϊ����
{
	memset(Q1,0,res_2);
	memset(Q2,0,res_2);                                  //��������
    int i,j;
    for(j=0;j<N;j++)
	{
        data = (float)x[j];                              //int����Ϊfloat��
        for(i=0;i<res;i++)						    	 //����Q0
        {
            Q0[i]=C[i]*Q1[i]-Q2[i]+data;
            //Q2[i] = Q1[i];
            //Q1[i] = Q0[i];
        }
        memcpy(Q2,Q1,res_2);						  	 //���ϴεļ�����������Q2��
        memcpy(Q1,Q0,res_2);							 //�����εļ�����������Q1��
    }
    /*������ϣ�ȫ��г����ģ*/
	for(i=0;i<res;i++)
	{
		P[i]=Q1[i]*Q1[i]+Q2[i]*Q2[i]-C[i]*Q1[i]*Q2[i];   //�����ݹ������������������/ȡ����/����
	}
}

/*���㵥��г������*/
float Goertzel(int x[], int order)
{
	Q1_alone=Q2_alone=0;                                 //����
    int j;
    for(j=0;j<N;j++)
	{
        data = (float)x[j];                              //int����Ϊfloat��
        Q0_alone=C[order-1]*Q1_alone-Q2_alone+data;
        Q2_alone = Q1_alone;
        Q1_alone = Q0_alone;
    }
    /*������ϣ���ģ*/
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
		for(j=0;j<64;j++) /*��j��*/
		{
			fscanf(fp,"%d",&x[j]);  /*��һ������*/
		}
		/* �ر��ļ� */
		fclose(fp);
	}

    Goertzel_init(50);										 //����Ϊ50hz
    goertzel_process_all(x);                                 //����
    P_alone1=Goertzel(x, 1);
    P_alone2=Goertzel(x, 3);								 //����
    P_alone3=Goertzel(x, 5);
}
