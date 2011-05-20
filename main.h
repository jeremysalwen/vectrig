#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>

//#define CLOCK
#define SIZE (int)(1024*3.14159)

#define FLTEND(x) x##f
#define FLTTYPE float
#define QUARTPI  FLTEND(0.785398163)
#define HALFPI  FLTEND(1.570796327)
#define PI FLTEND(3.141592653589793238462643)
#define ROOT2O2  FLTEND(0.707106781)

void sinsuperseries7(float* __restrict__ arr,int len);
void sinsuperseries9(float* __restrict__ arr,int len);
void bestseries9div3(float * __restrict__ arr,int len);
void minimaxseries7(float* __restrict__ arr, int len);
void minimaxseries9(float* __restrict__ arr, int len);
void minimaxseries11(float* __restrict__ arr, int len);
void minimaxseries13(float* __restrict__ arr, int len);
void minimaxseries15(float* __restrict__ arr, int len);
void sinseries0o13(float* __restrict__ arr, int len);
void sinseries0o11(float* __restrict__ arr, int len);
void sinseries0o9(float* __restrict__ arr, int len);
void sinseries0o7(float* __restrict__ arr, int len);
void vecsin(float* arr, int size);
void gnuseries(float* __restrict__ arr, int len);
void b7series(float* __restrict__ arr, int len);
void b9series(float* __restrict__ arr, int len);
void b11series(float* __restrict__ arr, int len);

