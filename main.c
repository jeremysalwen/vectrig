#include "main.h"

static inline void bringtorange(float* __restrict__ arr, int len) {
	for(int i=0; i<len; i++) {
		arr[i]-=((int)(arr[i]/HALFPI))*HALFPI;
	}
}
#define SUP7ORD3 FLTEND(-0.16665168108677)
#define SUP7ORD5  FLTEND(0.0083095170074559)
#define SUP7ORD7  FLTEND(-1.8447222287032252e-4)

void sinsuperseries7(float* __restrict__ arr,int len) {
   bringtorange(arr,len);
   for(int i=0; i<len; i++) {
      FLTTYPE tmp=arr[i]*arr[i];
      arr[i]+=arr[i]*tmp*(SUP7ORD3 + tmp*(SUP7ORD5+tmp*SUP7ORD7));
   }
}


#define SUP9ORD9  FLTEND(2.5984422633634844e-6)
#define SUP9ORD7  FLTEND(-1.9804930374010013e-4)
#define SUP9ORD5  FLTEND(0.0083329670804495)
#define SUP9ORD3  FLTEND(-0.1666665171729)
#define SUP9ORD1  FLTEND(0.99999998312198)

void sinsuperseries9(float* __restrict__ arr,int len) {
   bringtorange(arr,len);
   for(int i=0; i<len; i++) {
      FLTTYPE sqr=arr[i]*arr[i];
      arr[i]+=sqr*arr[i]*(SUP9ORD3+sqr*(SUP9ORD5+sqr*(SUP9ORD7+sqr*SUP9ORD9)));
   }
}

#define PIO6  FLTEND(0.523598776)

#define SA5  FLTEND(2.74201854577e-06)
#define SA4  FLTEND(-1.98410347969e-04)
#define SA3  FLTEND(8.33333320429e-03)
#define SA2  FLTEND(-1.66666666666e-01)

void bestseries9div3(float * __restrict__ arr,int len) {
   bringtorange(arr,len);
   for(int i=0; i<len; i++) {
      FLTTYPE or=arr[i];
      if(or>PIO6) {
        arr[i]/=3;
      }
      FLTTYPE sqr=arr[i]*arr[i];
      arr[i]+=arr[i]*sqr*(SA2+sqr*(SA3+sqr*(SA4+SA5*sqr))); 
     arr[i]+=(or>PIO6)*arr[i]*(2-4*arr[i]*arr[i]);
   }
}

#define MMS77  FLTEND(-0.00018684148083603963091)
#define MMS75  FLTEND(0.0083191783483393336376)
#define MMS73  FLTEND(-0.16666231326215784070)

void minimaxseries7(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
  for(int i=0; i<len; i++) {
    FLTTYPE sqr=arr[i]*arr[i];
    arr[i]+=sqr*arr[i]*(MMS73 + sqr*(MMS75 + sqr* MMS77));
  }
}

#define MMS99  FLTEND(2.6199025197195120855e-6)
#define MMS97  FLTEND(-0.00019816322019412579628)
#define MMS95  FLTEND(0.0083331628953425015333)
#define MMS93  FLTEND(-0.16666663516396446563)

void minimaxseries9(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
  for(int i=0; i<len; i++) {
    FLTTYPE sqr=arr[i]*arr[i];
    arr[i]+=sqr*arr[i]*(MMS93 + sqr*(MMS95 + sqr* (MMS97 + sqr*MMS99)));
  }
}

#define MMS1111  FLTEND(-2.3984563163388346477e-8)
#define MMS119  FLTEND(2.7531152930120359229e-6)
#define MMS117  FLTEND(-0.00019840988242599135899)
#define MMS115  FLTEND(0.0083333320944743463687)
#define MMS113  FLTEND(-0.16666666651391896548)

void minimaxseries11(float* __restrict__ arr, int len) {
  bringtorange(arr,len);
  for(int i=0; i<len; i++) {
    FLTTYPE sqr=arr[i]*arr[i];
    arr[i]+=sqr*arr[i]*(MMS113 + sqr*(MMS115 + sqr* (MMS117 + sqr*(MMS119+sqr*MMS1111))));
  }
}

#define MMS1313  FLTEND(1.5456812420974751789e-10)
#define MMS1311  FLTEND(-2.5033643691216283785e-8)
#define MMS139  FLTEND(2.7557046632657704673e-6)
#define MMS137  FLTEND(-0.00019841267882522861091)
#define MMS135  FLTEND(0.0083333333272969841645)
#define MMS133  FLTEND(-0.16666666666613490804)

void minimaxseries13(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
  for(int i=0; i<len; i++) {
    int x=(int)(arr[i]/HALFPI);
    arr[i]-=x*HALFPI;
    FLTTYPE sqr=arr[i]*arr[i];
    arr[i]+=sqr*arr[i]*(MMS133 + sqr*(MMS135 + sqr* (MMS137 + sqr*(MMS139 + sqr*(MMS1311 + sqr * MMS1313)))));
  }
}
#define MMS1515  FLTEND(7.3912059649841211983e-13)
#define MMS1513  FLTEND(1.6049620931934533410e-10)
#define MMS1511  FLTEND(-2.5051931236723817451e-8)
#define MMS159  FLTEND(2.7557317438440821200e-6)
#define MMS157  FLTEND(-0.00019841269832025835003)
#define MMS155  FLTEND(0.0083333333333122242661)
#define MMS153  FLTEND(-0.16666666666666527182)

void minimaxseries15(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
  for(int i=0; i<len; i++) {
    FLTTYPE sqr=arr[i]*arr[i];
     arr[i]+=sqr*arr[i]*(MMS133 + sqr*(MMS135 + sqr* (MMS137 + sqr*(MMS139 + sqr*(MMS1311 + sqr * (MMS1313+sqr*MMS1515))))));
  }
}
 void sinseries05(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
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
 void sinseries0(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
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
 void vecsin(float* arr, int size) {
   for(int i=0; i<size; i++) {
     arr[i]=sin(arr[i]);
   }
}
