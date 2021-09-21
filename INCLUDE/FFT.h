/*
 * FFT.h
 *
 *  Created on: 2021��5��19��
 *      Author: Administrator
 */

#ifndef FFT_H_
#define FFT_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include <math.h>

//extern float pi;
//extern int Goertzel_sign=0;
extern float Sample1[];// ���������ʵ��ת��Ϊ����
extern float Sample2[];// ���������ʵ��ת��Ϊ����
void fftinit(void);
void fft(int *input,float *output);
//void Goertzel_init(void);
//void goertzel_reset(void);
//void goertzel_process(int S);
//void goertzel_output(void);


#endif /* FFT_H_ */
