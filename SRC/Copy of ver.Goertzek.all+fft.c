#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include  <math.h>
#include "FFT.h"
#include "string.h"
Uint16 *ExRamStart = (Uint16 *)0x100000;

#pragma DATA_SECTION(input4,"ADCDATA");
#pragma DATA_SECTION(output4,"ADCDATA");
int input4[2048]={88.0,84.0,84.0,85.0,88.0,87.0,82.0,85.0,85.0,87.0,87.0,90.0,92.0,89.0,92.0,84.0,89.0,88.0,87.0,88.0,90.0,88.0,88.0,87.0,90.0,88.0,90.0,89.0,90.0,91.0,89.0,88.0,90.0,90.0,91.0,92.0,89.0,91.0,90.0,90.0,90.0,90.0,88.0,92.0,91.0,89.0,89.0,90.0,88.0,90.0,90.0,92.0,89.0,89.0,90.0,91.0,88.0,88.0,89.0,89.0,91.0,85.0,89.0,88.0,88.0,92.0,89.0,90.0,88.0,88.0,90.0,90.0,91.0,92.0,90.0,90.0,90.0,86.0,89.0,92.0,90.0,90.0,85.0,90.0,90.0,90.0,-106.0,-121.0,-126.0,-123.0,-122.0,-122.0,-122.0,-122.0,-120.0,-120.0,-122.0,-121.0,-122.0,-120.0,-121.0,-122.0,-121.0,-121.0,-121.0,-120.0,-121.0,-122.0,-120.0,-120.0,-122.0,-122.0,-121.0,-120.0,-122.0,-120.0,-120.0,-119.0,-120.0,-121.0,-122.0,-120.0,-120.0,-122.0,-119.0,-120.0,-120.0,-120.0,-121.0,-120.0,-123.0,-120.0,-122.0,-121.0,-118.0,-118.0,-121.0,-121.0,-121.0,-120.0,-120.0,-120.0,-122.0,-120.0,-120.0,-121.0,-122.0,-119.0,-122.0,-122.0,-122.0,-121.0,-119.0,-122.0,-122.0,-120.0,-121.0,-120.0,-121.0,-121.0,-120.0,-122.0,-120.0,-123.0,-121.0,-120.0,-119.0,-120.0,-120.0,-122.0,-121.0,-122.0,-121.0,-121.0,-121.0,-120.0,-121.0,-119.0,-118.0,-122.0,-136.0,-128.0,-128.0,-125.0,-126.0,-128.0,-129.0,-126.0,-128.0,-124.0,-122.0,-128.0,-126.0,-121.0,-124.0,-118.0,-122.0,-123.0,-128.0,-125.0,-119.0,-122.0,-124.0,-129.0,-128.0,-124.0,-122.0,-131.0,-128.0,-122.0,-122.0,-122.0,-122.0,-128.0,-122.0,-119.0,-121.0,-118.0,-120.0,-121.0,-121.0,-120.0,-121.0,-122.0,-120.0,-120.0,-122.0,-123.0,-122.0,-120.0,-119.0,-122.0,-122.0,-122.0,-123.0,-121.0,-120.0,-118.0,-120.0,-118.0,-123.0,-123.0,-122.0,-120.0,-122.0,-120.0,-121.0,-120.0,-124.0,-121.0,-121.0,-120.0,-128.0,-122.0,-127.0,-122.0,-120.0,-124.0,-120.0,-120.0,-120.0,-118.0,-120.0,-119.0,-120.0,-122.0,-120.0,-123.0,-120.0,-120.0,-120.0,-120.0,-120.0,-122.0,-120.0,-122.0,-120.0,-121.0,-122.0,-120.0,-121.0,-123.0,-121.0,-120.0,-120.0,-119.0,-122.0,-121.0,-122.0,-120.0,-120.0,88.0,93.0,87.0,86.0,90.0,88.0,88.0,91.0,90.0,90.0,92.0,91.0,88.0,89.0,92.0,85.0,86.0,89.0,88.0,89.0,90.0,88.0,88.0,83.0,89.0,90.0,90.0,87.0,89.0,85.0,89.0,90.0,90.0,90.0,88.0,90.0,89.0,89.0,90.0,89.0,88.0,89.0,88.0,88.0,88.0,88.0,90.0,90.0,88.0,88.0,89.0,88.0,89.0,91.0,91.0,89.0,89.0,90.0,89.0,89.0,90.0,89.0,93.0,91.0,91.0,94.0,82.0,88.0,89.0,90.0,94.0,90.0,89.0,90.0,88.0,90.0,86.0,88.0,88.0,88.0,90.0,88.0,88.0,88.0,88.0,90.0,88.0,90.0,92.0,85.0,80.0,80.0,85.0,84.0,80.0,89.0,88.0,84.0,81.0,88.0,83.0,74.0,84.0,77.0,82.0,86.0,86.0,88.0,85.0,83.0,82.0,82.0,84.0,84.0,81.0,82.0,85.0,83.0,84.0,86.0,86.0,87.0,88.0,86.0,85.0,88.0,88.0,88.0,89.0,93.0,88.0,90.0,92.0,87.0,89.0,90.0,89.0,89.0,88.0,90.0,90.0,91.0,88.0,88.0,88.0,88.0,87.0,89.0,88.0,87.0,89.0,89.0,90.0,89.0,90.0,90.0,90.0,91.0,88.0,90.0,90.0,85.0,88.0,87.0,84.0,88.0,92.0,87.0,85.0,86.0,89.0,91.0,90.0,91.0,90.0,90.0,88.0,92.0,90.0,88.0,90.0,90.0,89.0,89.0,91.0,89.0,89.0,88.0,89.0,90.0,89.0,90.0,90.0,90.0,91.0,89.0,88.0,89.0,88.0,90.0,89.0,89.0,91.0,88.0,87.0,-122.0,-120.0,-127.0,-124.0,-120.0,-118.0,-120.0,-119.0,-122.0,-120.0,-119.0,-122.0,-121.0,-122.0,-120.0,-122.0,-121.0,-120.0,-119.0,-120.0,-120.0,-123.0,-123.0,-120.0,-122.0,-121.0,-121.0,-120.0,-120.0,-118.0,-120.0,-122.0,-125.0,-121.0,-120.0,-123.0,-124.0,-122.0,-122.0,-123.0,-121.0,-120.0,-121.0,-120.0,-120.0,-121.0,-121.0,-122.0,-122.0,-119.0,-120.0,-122.0,-120.0,-124.0,-123.0,-122.0,-122.0,-120.0,-124.0,-122.0,-120.0,-122.0,-119.0,-124.0,-122.0,-120.0,-121.0,-122.0,-118.0,-122.0,-122.0,-120.0,-120.0,-120.0,-121.0,-123.0,-120.0,-123.0,-123.0,-123.0,-121.0,-120.0,-121.0,-120.0,-120.0,-121.0,-121.0,-120.0,-117.0,-116.0,-124.0,-120.0,-123.0,-124.0,-126.0,-124.0,-124.0,-124.0,-126.0,-125.0,-136.0,-126.0,-120.0,-124.0,-122.0,-122.0,-134.0,-124.0,-124.0,-127.0,-122.0,-125.0,-122.0,-120.0,-120.0,-127.0,-123.0,-123.0,-124.0,-128.0,-125.0,-128.0,-130.0,-120.0,-121.0,-122.0,-124.0,-122.0,-119.0,-116.0,-123.0,-120.0,-118.0,-124.0,-123.0,-124.0,-126.0,-122.0,-123.0,-123.0,-123.0,-120.0,-123.0,-122.0,-120.0,-122.0,-122.0,-118.0,-122.0,-120.0,-121.0,-121.0,-124.0,-123.0,-121.0,-119.0,-120.0,-121.0,-124.0,-120.0,-120.0,-120.0,-118.0,-120.0,-120.0,-120.0,-121.0,-120.0,-120.0,-123.0,-122.0,-119.0,-122.0,-120.0,-120.0,-122.0,-122.0,-120.0,-120.0,-123.0,-120.0,-122.0,-122.0,-121.0,-120.0,-122.0,-120.0,-124.0,-124.0,-122.0,-123.0,-121.0,-121.0,-122.0,-122.0,-122.0,-123.0,-120.0,-122.0,-124.0,-122.0,-122.0,-122.0,-122.0,-14.0,90.0,88.0,91.0,90.0,90.0,88.0,88.0,86.0,90.0,90.0,87.0,90.0,89.0,88.0,89.0,91.0,90.0,90.0,90.0,89.0,87.0,88.0,86.0,89.0,91.0,89.0,91.0,92.0,89.0,91.0,88.0,89.0,88.0,87.0,92.0,88.0,90.0,87.0,91.0,88.0,92.0,87.0,90.0,90.0,87.0,90.0,86.0,86.0,88.0,89.0,90.0,86.0,89.0,92.0,88.0,92.0,89.0,89.0,88.0,89.0,90.0,90.0,89.0,87.0,88.0,89.0,85.0,88.0,90.0,90.0,87.0,89.0,88.0,89.0,88.0,90.0,89.0,82.0,88.0,88.0,88.0,89.0,89.0,88.0,88.0,90.0,88.0,92.0,92.0,92.0,88.0,81.0,85.0,85.0,76.0,82.0,84.0,83.0,86.0,88.0,85.0,87.0,86.0,88.0,85.0,86.0,90.0,90.0,85.0,83.0,84.0,87.0,90.0,86.0,85.0,86.0,88.0,88.0,86.0,86.0,80.0,92.0,91.0,88.0,90.0,86.0,90.0,86.0,82.0,88.0,92.0,87.0,88.0,89.0,90.0,91.0,90.0,88.0,89.0,89.0,91.0,92.0,88.0,86.0,86.0,88.0,86.0,89.0,89.0,91.0,88.0,88.0,90.0,88.0,88.0,88.0,88.0,86.0,90.0,88.0,89.0,89.0,86.0,90.0,88.0,89.0,92.0,88.0,89.0,92.0,89.0,90.0,89.0,89.0,90.0,92.0,89.0,88.0,89.0,90.0,88.0,90.0,89.0,91.0,92.0,90.0,91.0,89.0,88.0,90.0,88.0,90.0,90.0,88.0,88.0,88.0,90.0,89.0,86.0,89.0,90.0,90.0,90.0,89.0,-118.0,-122.0,-121.0,-122.0,-122.0,-121.0,-122.0,-121.0,-121.0,-122.0,-122.0,-122.0,-122.0,-123.0,-122.0,-121.0,-120.0,-120.0,-121.0,-120.0,-122.0,-123.0,-122.0,-122.0,-120.0,-122.0,-122.0,-121.0,-121.0,-120.0,-120.0,-120.0,-120.0,-120.0,-122.0,-120.0,-123.0,-120.0,-124.0,-121.0,-121.0,-120.0,-123.0,-122.0,-124.0,-125.0,-120.0,-122.0,-122.0,-121.0,-123.0,-121.0,-119.0,-120.0,-120.0,-122.0,-121.0,-120.0,-122.0,-121.0,-122.0,-120.0,-122.0,-120.0,-123.0,-116.0,-120.0,-119.0,-121.0,-123.0,-121.0,-121.0,-124.0,-125.0,-124.0,-122.0,-122.0,-122.0,-123.0,-123.0,-124.0,-120.0,-122.0,-121.0,-120.0,-120.0,-121.0,-123.0,-120.0,-126.0,-121.0,-117.0,-122.0,-125.0,-128.0,-124.0,-122.0,-123.0,-120.0,-128.0,-133.0,-122.0,-126.0,-127.0,-124.0,-124.0,-124.0,-126.0,-136.0,-127.0,-128.0,-120.0,-122.0,-125.0,-119.0,-123.0,-122.0,-124.0,-123.0,-124.0,-120.0,-126.0,-125.0,-122.0,-128.0,-124.0,-127.0,-120.0,-124.0,-122.0,-120.0,-120.0,-123.0,-119.0,-121.0,-123.0,-120.0,-123.0,-122.0,-122.0,-121.0,-122.0,-123.0,-122.0,-121.0,-120.0,-122.0,-120.0,-124.0,-120.0,-122.0,-120.0,-121.0,-123.0,-120.0,-122.0,-122.0,-119.0,-122.0,-121.0,-123.0,-125.0,-128.0,-125.0,-124.0,-120.0,-120.0,-120.0,-119.0,-121.0,-123.0,-120.0,-120.0,-122.0,-122.0,-121.0,-120.0,-121.0,-118.0,-122.0,-121.0,-120.0,-121.0,-120.0,-122.0,-122.0,-120.0,-122.0,-122.0,-123.0,-122.0,-125.0,-124.0,-121.0,-121.0,-121.0,-120.0,-120.0,-121.0,-121.0,-121.0,-122.0,-122.0,-124.0,-121.0,88.0,90.0,91.0,88.0,89.0,89.0,89.0,90.0,92.0,90.0,92.0,89.0,91.0,90.0,90.0,92.0,89.0,89.0,90.0,89.0,88.0,88.0,89.0,88.0,86.0,88.0,87.0,89.0,89.0,88.0,89.0,90.0,88.0,89.0,89.0,90.0,88.0,88.0,91.0,89.0,89.0,85.0,88.0,90.0,90.0,90.0,89.0,90.0,90.0,88.0,90.0,90.0,88.0,88.0,89.0,89.0,89.0,88.0,90.0,90.0,89.0,90.0,85.0,89.0,89.0,90.0,92.0,91.0,90.0,88.0,88.0,90.0,89.0,88.0,89.0,90.0,89.0,86.0,88.0,90.0,88.0,88.0,88.0,90.0,89.0,87.0,90.0,89.0,92.0,88.0,92.0,86.0,82.0,81.0,86.0,90.0,88.0,88.0,81.0,76.0,83.0,86.0,84.0,90.0,89.0,89.0,85.0,84.0,85.0,78.0,83.0,88.0,83.0,82.0,84.0,87.0,85.0,82.0,86.0,86.0,80.0,88.0,81.0,83.0,79.0,88.0,86.0,84.0,84.0,88.0,88.0,89.0,91.0,93.0,90.0,88.0,88.0,84.0,90.0,89.0,89.0,89.0,88.0,85.0,87.0,89.0,90.0,90.0,88.0,92.0,91.0,90.0,90.0,89.0,90.0,90.0,88.0,89.0,90.0,90.0,90.0,90.0,90.0,91.0,90.0,90.0,88.0,90.0,89.0,88.0,88.0,90.0,87.0,90.0,88.0,89.0,91.0,88.0,90.0,88.0,88.0,84.0,88.0,85.0,89.0,92.0,87.0,90.0,89.0,88.0,89.0,90.0,91.0,88.0,88.0,90.0,88.0,92.0,88.0,90.0,89.0,88.0,92.0,86.0,89.0,-122.0,-123.0,-122.0,-120.0,-122.0,-119.0,-125.0,-121.0,-120.0,-123.0,-120.0,-121.0,-122.0,-123.0,-122.0,-120.0,-120.0,-120.0,-120.0,-120.0,-121.0,-120.0,-124.0,-122.0,-120.0,-121.0,-120.0,-122.0,-121.0,-122.0,-123.0,-121.0,-122.0,-121.0,-120.0,-123.0,-124.0,-120.0,-122.0,-120.0,-120.0,-120.0,-120.0,-122.0,-122.0,-119.0,-121.0,-120.0,-121.0,-122.0,-120.0,-122.0,-120.0,-123.0,-121.0,-121.0,-121.0,-120.0,-120.0,-122.0,-123.0,-121.0,-122.0,-120.0,-122.0,-121.0,-121.0,-122.0,-122.0,-122.0,-123.0,-122.0,-120.0,-124.0,-122.0,-121.0,-120.0,-123.0,-122.0,-120.0,-121.0,-120.0,-120.0,-118.0,-120.0,-120.0,-120.0,-122.0,-121.0,-121.0,-122.0,-119.0,-131.0,-122.0,-120.0,-120.0,-127.0,-124.0,-120.0,-121.0,-119.0,-131.0,-127.0,-122.0,-128.0,-128.0,-123.0,-125.0,-122.0,-122.0,-124.0,-124.0,-128.0,-124.0,-127.0,-123.0,-127.0,-124.0,-129.0,-125.0,-125.0,-127.0,-125.0,-122.0,-129.0,-124.0,-123.0,-120.0,-120.0,-122.0,-120.0,-119.0,-117.0,-121.0,-122.0,-122.0,-123.0,-121.0,-119.0,-120.0,-120.0,-122.0,-120.0,-120.0,-120.0,-122.0,-122.0,-120.0,-120.0,-124.0,-122.0,-121.0,-120.0,-118.0,-122.0,-122.0,-120.0,-119.0,-121.0,-124.0,-123.0,-120.0,-121.0,-123.0,-125.0,-122.0,-120.0,-120.0,-120.0,-118.0,-123.0,-121.0,-120.0,-122.0,-119.0,-122.0,-121.0,-120.0,-122.0,-120.0,-125.0,-123.0,-120.0,-122.0,-121.0,-120.0,-124.0,-121.0,-122.0,-122.0,-121.0,-120.0,-120.0,-120.0,-119.0,-120.0,-122.0,-120.0,-122.0,-121.0,-118.0,-121.0,-122.0,-121.0,86.0,88.0,91.0,88.0,88.0,88.0,86.0,86.0,87.0,87.0,92.0,89.0,89.0,89.0,89.0,89.0,89.0,88.0,86.0,87.0,91.0,89.0,88.0,90.0,89.0,91.0,88.0,88.0,90.0,87.0,90.0,91.0,89.0,90.0,89.0,89.0,90.0,90.0,89.0,89.0,90.0,90.0,88.0,90.0,89.0,89.0,89.0,88.0,89.0,90.0,90.0,90.0,88.0,88.0,90.0,87.0,90.0,90.0,85.0,88.0,89.0,89.0,90.0,88.0,89.0,92.0,88.0,90.0,89.0,86.0,89.0,89.0,88.0,88.0,92.0,90.0,89.0,87.0,89.0,88.0,88.0,91.0,88.0,90.0,90.0,87.0,89.0,86.0,86.0,92.0,92.0,93.0,86.0,84.0,82.0,84.0,83.0,84.0,85.0,80.0,82.0,88.0,88.0,85.0,87.0,87.0,88.0,88.0,86.0,88.0,89.0,89.0,88.0,83.0,89.0,89.0,90.0,79.0,88.0,85.0,88.0,84.0,84.0,88.0,84.0,85.0,85.0,79.0,83.0,88.0,88.0,94.0,93.0,89.0,89.0,92.0,91.0,89.0,88.0,88.0,88.0,88.0,87.0,90.0,90.0,88.0,91.0,91.0,89.0,88.0,87.0,89.0,92.0,89.0,90.0,89.0,90.0,90.0,87.0,89.0,90.0,90.0,88.0,88.0,90.0,89.0,88.0,89.0,92.0,89.0,92.0,88.0,89.0,90.0,90.0,89.0,91.0,90.0,89.0,91.0,90.0,91.0,90.0,90.0,89.0,86.0,89.0,88.0,89.0,90.0,92.0,89.0,88.0,88.0,89.0,88.0,89.0,90.0,90.0,90.0,88.0,88.0,89.0,86.0,90.0,-120.0,-118.0,-125.0,-124.0,-123.0,-118.0,-122.0,-121.0,-120.0,-120.0,-121.0,-125.0,-121.0,-119.0,-122.0,-120.0,-119.0,-121.0,-120.0,-121.0,-121.0,-119.0,-122.0,-123.0,-121.0,-120.0,-120.0,-123.0,-121.0,-122.0,-122.0,-119.0,-121.0,-120.0,-120.0,-122.0,-120.0,-120.0,-121.0,-120.0,-122.0,-122.0,-122.0,-121.0,-120.0,-126.0,-120.0,-120.0,-121.0,-120.0,-120.0,-121.0,-124.0,-122.0,-122.0,-119.0,-121.0,-120.0,-120.0,-120.0,-119.0,-122.0,-122.0,-120.0,-124.0,-120.0,-122.0,-123.0,-120.0,-120.0,-123.0,-120.0,-123.0,-120.0,-120.0,-122.0,-120.0,-122.0,-122.0,-120.0,-121.0,-121.0,-121.0,-120.0,-120.0,-125.0,-124.0,-120.0,-122.0,-120.0,-123.0,-124.0,-126.0,-133.0,-126.0,-126.0,-128.0,-126.0,-122.0,-123.0,-124.0,-128.0,-124.0,-130.0,-124.0,-132.0,-125.0,-128.0,-121.0,-122.0,-122.0,-126.0,-122.0,-124.0,-123.0,-125.0,-125.0,-122.0,-122.0,-123.0,-128.0,-124.0,-125.0,-127.0,-125.0,-123.0,-127.0,-124.0,-122.0,-118.0,-123.0,-118.0,-121.0,-121.0,-120.0,-120.0,-119.0,-120.0,-121.0,-123.0,-122.0,-120.0,-120.0,-120.0,-120.0,-120.0,-120.0,-118.0,-121.0,-119.0,-120.0,-121.0,-120.0,-121.0,-120.0,-122.0,-121.0,-120.0,-123.0,-124.0,-124.0,-126.0,-126.0,-121.0,-122.0,-122.0,-122.0,-121.0,-122.0,-122.0,-120.0,-121.0,-123.0,-120.0,-120.0,-123.0,-120.0,-122.0,-120.0,-120.0,-122.0,-120.0,-120.0,-123.0,-122.0,-120.0,-123.0,-120.0,-122.0,-118.0,-120.0,-121.0,-120.0,-121.0,-119.0,-119.0,-121.0,-120.0,-120.0,-122.0,-122.0,-122.0,-121.0,-120.0,-120.0,89.0,90.0,89.0,90.0,88.0,89.0,88.0,88.0,88.0,89.0,90.0,89.0,89.0,89.0,89.0,87.0,90.0,88.0,86.0,87.0,89.0,88.0,88.0,89.0,91.0,90.0,92.0,89.0,88.0,92.0,89.0,88.0,86.0,89.0,84.0,88.0,89.0,89.0,88.0,88.0,89.0,90.0,90.0,90.0,89.0,92.0,89.0,89.0,89.0,88.0,92.0,90.0,88.0,90.0,81.0,88.0,88.0,88.0,90.0,86.0,88.0,90.0,88.0,90.0,90.0,90.0,90.0,88.0,90.0,90.0,88.0,89.0,89.0,90.0,90.0,88.0,89.0,89.0,89.0,89.0,89.0,88.0,88.0,90.0,89.0,91.0,92.0,92.0,89.0,90.0,92.0,91.0,87.0,84.0,86.0,84.0,88.0,83.0,86.0,86.0,85.0,87.0,87.0,79.0,86.0,90.0,89.0,85.0,88.0,85.0,87.0,88.0,85.0,89.0,89.0,87.0,85.0,84.0,82.0};

/*������*/
float output4[2048];
void main(void)
{
	fft(input4,output4);
}
