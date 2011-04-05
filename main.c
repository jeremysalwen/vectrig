#include "main.h"

//RODP=right of decimal place, in scientific notation.

//we split the first 32 binary digits (RODP) of pi into two 15 bit numbers.
// we choose 32 digits of pi because if we multiply this many digits by
// MAX(float), we want there still to be 23 digits of precision (RODP)
// (the number of digits precision in a float).  The max float is 1.111..*2^(127)
// Thus the max multiple of pi we want is ~2^127.  This means that we must have 127+23
// binary digits of pi to get the correct answer. that would be 150 digits of PI.
// We can split them up into elements of size 
//PI = 1.100100100001111*2^1 + 1.101101010100010*10^-14 + the rest of the binary digits.
static inline void bringtorange(float* __restrict__ arr, int len) {
	for(int i=0; i<len; i++) {
		arr[i]-=((int)(arr[i]/PI))*PI;
	}
	for(int i=0; i<len; i++) {
          arr[i]=(arr[i]>HALFPI)?(PI-arr[i]):arr[i];
	}
	for(int i=0; i<len; i++) {
	  arr[i]=(arr[i]<-HALFPI)?-PI-arr[i]:arr[i];
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


#define SUP9ORD9  FLTEND(2.606554478313565595882074411479941465e-6)
#define SUP9ORD7  FLTEND(-0.0001980958020645666255913004592493451013630)
#define SUP9ORD5  FLTEND(0.008333058557743530894880100811013104093447)
#define SUP9ORD3  FLTEND(-0.1666665877741693726311023404936793615961)

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

#define SS03 FLTEND(-0.1666666666666666)
#define SS05 FLTEND(0.00833333333333333)
#define SS07 FLTEND(-0.00019841269841269841269841)
#define SS09 FLTEND(2.75573192239858906525573e-6)
#define SS011 FLTEND(-2.50521083854417187750e-8)
#define SS013 FLTEND(1.605904383682161459e-10)

void sinseries0o13(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
   FLTTYPE sqr;
    for(int i=0; i<len; i++) {
      sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(SS03+sqr*(SS05 +sqr*(SS07 +sqr*(SS09+sqr*(SS011+sqr*SS013)))));
    }
}

void sinseries0o11(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
   FLTTYPE sqr;
    for(int i=0; i<len; i++) {
      sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(SS03+sqr*(SS05 +sqr*(SS07 +sqr*(SS09+sqr*SS011))));
    }
}
void sinseries0o9(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
   FLTTYPE sqr;
    for(int i=0; i<len; i++) {
      sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(SS03+sqr*(SS05 +sqr*(SS07 +sqr*SS09)));
    }
}
void sinseries0o7(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
   FLTTYPE sqr;
    for(int i=0; i<len; i++) {
      sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(SS03+sqr*(SS05 +sqr*SS07));
    }
}

void vecsin(float* arr, int size) {
   for(int i=0; i<size; i++) {
     arr[i]=sin(arr[i]);
   }
}


FLTTYPE GNUS1  = FLTEND(-1.6666667163e-01);
FLTTYPE GNUS2  = FLTEND( 8.3333337680e-03);
FLTTYPE GNUS3  = FLTEND(-1.9841270114e-04);
FLTTYPE GNUS4  = FLTEND( 2.7557314297e-06);
FLTTYPE GNUS5  = FLTEND(-2.5050759689e-08);
FLTTYPE GNUS6  = FLTEND( 1.5896910177e-10);

void gnuseries(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
   FLTTYPE sqr;
    for(int i=0; i<len; i++) {
      sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(GNUS1+sqr*(GNUS2 +sqr*(GNUS3 +sqr*(GNUS4+sqr*(GNUS5+sqr*GNUS6)))));
    }
}
FLTTYPE B91  = FLTEND(-1.6666658777408987333e-1);
FLTTYPE B92  = FLTEND(8.3330585579660222884e-3);
FLTTYPE B93  = FLTEND(-1.9809580202098392708e-4);
FLTTYPE B94  = FLTEND( 2.6065544878032086552e-6);

void b9series(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
   FLTTYPE sqr;
    for(int i=0; i<len; i++) {
      sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(B91+sqr*(B92 +sqr*(B93 +sqr*B94)));
    }
}
FLTTYPE B111  = FLTEND(-1.6666666621113970589e-1);
FLTTYPE B112  = FLTEND(8.3333309585278954692e-3);
FLTTYPE B113  = FLTEND(-1.9840861674155877174e-4);
FLTTYPE B114  = FLTEND(2.7525172542458407497e-6);
FLTTYPE B115  = FLTEND(-2.3897606931720883012e-8);

void b11series(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
   FLTTYPE sqr;
    for(int i=0; i<len; i++) {
      sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(B111+sqr*(B112 +sqr*(B113 +sqr*(B114+sqr*B115))));
    }
}
