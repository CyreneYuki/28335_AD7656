/*
 * FFT.h
 *
 *  Created on: 2021年5月19日
 *      Author: Administrator
 */

#ifndef FFT_H_
#define FFT_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include <math.h>

//extern float pi;
//extern int Goertzel_sign=0;
extern float Sample1[];// 采样输入的实数转化为复数
extern float Sample2[];// 采样输入的实数转化为复数
void fftinit(void);
void fft(int *input,float *output);
//void Goertzel_init(void);
//void goertzel_reset(void);
//void goertzel_process(int S);
//void goertzel_output(void);


#endif /* FFT_H_ */
