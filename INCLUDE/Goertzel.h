/*
 * Goertzel.h
 *
 *  Created on: 2021年6月11日
 *      Author: Administrator
 */
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include <math.h>

#ifndef GOERTZEL_H_
#define GOERTZEL_H_
#define res 7		//转换点数
extern int i;
extern float P[res],Q0[res],Q1[res],Q2[res],C[res],f[res],temp[res],k[res],data;
void Goertzel_init(float interval,unsigned int N);
void goertzel_reset(void);
void goertzel_process(unsigned int S);
void goertzel_output(void);


#endif /* GOERTZEL_H_ */
