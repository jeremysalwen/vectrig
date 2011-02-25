#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>

//#define CLOCK
#define SIZE (int)(512*3.14159)

#define QUARTPI 0.785398163
#define HALFPI 1.570796327

#define ROOT2O2 0.707106781

#define SUP7ORD1 0.99999748721912
#define SUP7ORD3 -0.16665168108677
#define SUP7ORD5 0.0083095170074559
#define SUP7ORD7 -1.8447222287032252e-4

static void sinsuperseries7(float* __restrict__ arr,int len) {
   for(int i=0; i<len; i++) {
      float tmp=arr[i]*arr[i];
      arr[i]=arr[i]*SUP7ORD1+arr[i]*tmp*SUP7ORD3 +arr[i]*tmp*tmp*SUP7ORD5+arr[i]*tmp*tmp*tmp*SUP7ORD7;
   }
}


#define SUP9ORD9 2.5984422633634844e-6
#define SUP9ORD7 -1.9804930374010013e-4
#define SUP9ORD5 0.0083329670804495
#define SUP9ORD3 -0.1666665171729
#define SUP9ORD1 0.99999998312198

static void sinsuperseries9(float* __restrict__ arr,int len) {
   for(int i=0; i<len; i++) {
      float sqr=arr[i]*arr[i];
      arr[i]+=sqr*arr[i]*(SUP9ORD3+sqr*(SUP9ORD5+sqr*(SUP9ORD7+sqr*SUP9ORD9)));
   }
}

#define PIO6f 0.523598776f

#define SA5f 2.74201854577e-06f
#define SA4f -1.98410347969e-04f
#define SA3f 8.33333320429e-03f
#define SA2f -1.66666666666e-01f

static void bestseries9div3(float * __restrict__ arr,int len) {
   for(int i=0; i<len; i++) {
      float or=arr[i];
      if(or>PIO6f) {
        arr[i]/=3;
      }
      float sqr=arr[i]*arr[i];
      arr[i]+=arr[i]*sqr*(SA2f+sqr*(SA3f+sqr*(SA4f+SA5f*sqr))); 
     arr[i]+=(or>PIO6f)*arr[i]*(2-4*arr[i]*arr[i]);
   }
}
#define MMS99f 2.6199025197195120855e-6f
#define MMS97f -0.00019816322019412579628f
#define MMS95f 0.0083331628953425015333f
#define MMS93f -0.16666663516396446563f

static void minimaxseries9(float* __restrict__ arr, int len) {
  for(int i=0; i<len; i++) {
    float sqr=arr[i]*arr[i];
    arr[i]+=sqr*arr[i]*(MMS93f + sqr*(MMS95f + sqr* (MMS97f + sqr*MMS99f)));
  }
}
#define MMS1111f -2.3984563163388346477e-8f
#define MMS119f 2.7531152930120359229e-6f
#define MMS117f -0.00019840988242599135899f
#define MMS115f 0.0083333320944743463687f
#define MMS113f -0.16666666651391896548f

static void minimaxseries11(float* __restrict__ arr, int len) {
  for(int i=0; i<len; i++) {
    float sqr=arr[i]*arr[i];
    arr[i]+=sqr*arr[i]*(MMS113f + sqr*(MMS115f + sqr* (MMS117f + sqr*(MMS119f+sqr*MMS1111f))));
  }
}
static void sinseries05(float* __restrict__ arr, int len) {
    float  orig[len];
    float  tmp[len];
    float lol;
    for(int i=0; i<len; i++) {
      orig[i]=arr[i]-QUARTPI;
      tmp[i]=orig[i]*ROOT2O2;
      arr[i]=ROOT2O2;
    }
   for(int i=0; i<len; i++) {
      arr[i]+=tmp[i];
    }
   for(int i=0; i<len; i++) {
      tmp[i]=tmp[i]*tmp[i]*ROOT2O2;
      arr[i]-=tmp[i];
   }
   for(int i=0; i<len; i++) {
     tmp[i]*=orig[i]/3;
     arr[i]-=tmp[i];
   }
   for(int i=0; i<len; i++) {
     tmp[i]*=orig[i]/4;
     arr[i]+=tmp[i];
   }
   for(int i=0; i<len; i++) {
     tmp[i]*=orig[i]/5;
     arr[i]+=tmp[i];
   }
   for(int i=0; i<len; i++) {
     tmp[i]*=orig[i]/6;
     arr[i]-=tmp[i];
   }
   for(int i=0; i<len; i++) {
     tmp[i]*=orig[i]/7;
     arr[i]-=tmp[i];
   }
}
static void sinseries0(float* __restrict__ arr, int len) {
    float  orig[len];
    float  tmp[len];
    float lol;
    for(int i=0; i<len; i++) {
      orig[i]=arr[i];
      tmp[i]=orig[i];
    }
    for(int i=0; i<len; i++) {
      orig[i]=orig[i]*orig[i];
    }
    for(int i=0; i<len; i++) {
      tmp[i]*=orig[i]/6;
      arr[i]-=tmp[i];
    }
    for(int i=0; i<len; i++) {
      tmp[i]*=orig[i]/20;
      arr[i]+=tmp[i];
    }
    for(int i=0; i<len; i++) {
      tmp[i]*=orig[i]/42;
      arr[i]-=tmp[i];
    }
    for(int i=0; i<len; i++) {
      tmp[i]*=orig[i]/72;
      arr[i]+=tmp[i];
    }
/*    for(int i=0; i<len; i++) {
      tmp[i]*=orig[i]*orig[i]/110;
      arr[i]-=tmp[i];
    }
    for(int i=0; i<SIZE; i++) {
      tmp[i]*=orig[i]*orig[i]/1560;
      arr[i]+=tmp[i];
    }*/
}
static void vecsin(float* arr, int size) {
   for(int i=0; i<size; i++) {
     arr[i]=sin(arr[i]);
   }
}
int main() {
   float sinarr[SIZE];
   float sin0arr[SIZE];
   float sin05arr[SIZE];
   float supsin7arr[SIZE];
   float supsin9arr[SIZE];
   float bestseries9div3arr[SIZE];
   float mms9arr[SIZE];
   float mms11arr[SIZE];
   for(int i=0; i<SIZE; i++) {
     sinarr[i]=(float)i/1024;
     sin0arr[i]=sinarr[i];
     sin05arr[i]=sinarr[i];
     supsin7arr[i]=sinarr[i];
     supsin9arr[i]=sinarr[i];
     bestseries9div3arr[i]=sinarr[i];
     mms9arr[i]=sinarr[i];
     mms11arr[i]=sinarr[i];
   }
#ifdef CLOCK
   clock_t endwait=clock();
   for(int i=0; i<100000; i++) {
#endif
      sinseries0(sin0arr,SIZE);
#ifdef CLOCK
   }

  printf("diff sin0: %d\n",clock()-endwait);
   endwait=clock();
   for(int i=0; i<100000; i++) {
#endif
     vecsin(sinarr,SIZE);
#ifdef CLOCK
   }
  printf("diff vecsin: %d\n",clock()-endwait);

    endwait=clock();
   for(int i=0; i<100000; i++) {
#endif

     sinseries05(sin05arr,SIZE);
#ifdef CLOCK

   }
  printf("diff sin05: %d\n",clock()-endwait);

    endwait=clock();
   for(int i=0; i<100000; i++) {
#endif
     sinsuperseries7(supsin7arr,SIZE);
#ifdef CLOCK

   }
  printf("diff supsin7: %d\n",clock()-endwait);
    endwait=clock();
   for(int i=0; i<100000; i++) {
#endif
     sinsuperseries9(supsin9arr,SIZE);
#ifdef CLOCK
   }
  printf("diff supsin9: %d\n",clock()-endwait);
  endwait=clock();
  for(int i=0; i<100000; i++) {
#endif
     bestseries9div3(bestseries9div3arr,SIZE);
#ifdef CLOCK
  }
  printf("diff bestseries9div3: %d\n",clock()-endwait);
  endwait=clock();
  for(int i=0; i<100000; i++) {
#endif
     minimaxseries9(mms9arr,SIZE);
#ifdef CLOCK
  }
  printf("diff mms9: %d\n",clock()-endwait);
  endwait=clock();
  for(int i=0; i<100000; i++) {
#endif
     minimaxseries11(mms11arr,SIZE);
#ifdef CLOCK
  }
  printf("diff mms11: %d\n",clock()-endwait);
#endif
  printf("#\tX\tSIN\tSIN0\tSIN05\tSUPSIN7\tSUPSIN9\tBESTSERIES\n"); 
  for(int i=0; i<SIZE; i++) {
    printf("%f %f %f %f %f %f %f %f %d\n",(float)i/1024,sinarr[i],sin0arr[i],supsin7arr[i],supsin9arr[i],bestseries9div3arr[i],mms9arr[i],mms11arr[i],mms11arr[i]==sinarr[i]);
  }
}
