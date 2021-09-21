/*
 * fftsg.h
 *
 *  Created on: 2021Äê6ÔÂ18ÈÕ
 *      Author: Administrator
 */

#ifndef FFTSG_H_
#define FFTSG_H_

union ADDATA
{
	long l;
	int i;
	float f;
	unsigned int u;
};
void rdft(int, int, union ADDATA*, int *, union ADDATA *);
//void rdft(int, int, float *, int *, float *);
    void rdftinit(void);




#endif /* FFTSG_H_ */
