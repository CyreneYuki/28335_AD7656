/*
 * fft8g.h
 *
 *  Created on: 2021Äê6ÔÂ18ÈÕ
 *      Author: Administrator
 */

#ifndef FFT8G_H_
#define FFT8G_H_

union ADDATA
{
	long l;
	int i;
	float f;
	unsigned int u;
};
void rdft(int n, int isgn, float *a, int *ip, float *w);
//void rdft(int, int, float *, int *, float *);
    void rdftinit(void);




#endif /* FFT8G_H_ */
