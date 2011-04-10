#include "main.h"

//all of this work is assuming IEEE floating point formats.
//2/PI =
//0.010100010111110011000001101101110010011100100010000010101001010011111110000100111010101111101000111110101001101001101110111000000110110110110001010010101100110010011110001000011100100000100000
//   |a---------------------------||b---------------------------||c---------------------------| |d---------------------------||e---------------------------||f---------------------------|
// The float which is closest to a multiple of PI/2 is close to within 29 binary digits.  I.E |x-M*PI| > 2^(-29)
// Let 2^N be an upper bound on X.  Any digit of 1/PI <2^(-N-29-23-1) will be beyond the precision of a float representing the smallest possible number.
//  a+b+c will give us 91 digits of 1/PI. Thus it is guaranteed to be accurate for 91=N+29+23+1,91=N+53, N=38.
// THUS THIS A,B,AND C WILL BE INNACURATE FOR EXPONENTS >=2^38, and will be psueduorandom for exponenents > 2^61.
// If we wanted N=128, we would require  bits=128+29+23+1=181 bits.  THUS a,b,c,d,e,f (accurate to 186 bits) is enough for all arguments!

//We only use 23 bits of the double to hold our float argument, therefore, we can pack 29 bits into a,b,c,etc, and the multiplication will
// go out to 29+23=52 bits, which is contained in a double, thus our multiplications are bit-exact.


static const double A=0xA2F9836Cp-33;
static const double B=0x93910548p-63;
static const double C=0x9FC2757Cp-93;

static const double D=0x8FA9A6ECp-124;
static const double E=0x81B6C528p-154;
static const double F=0xCC9E21C8p-184;

//This only works for numbers that fit into the signed int range.
static inline void bringtorange(float* __restrict__ arr, int len) {
//	 double tmp[len];
//	 double tot[len];
	 for(int i=0; i<len; i++) {
		double d=arr[i];
		double tot=d*A;
		tot-=(int)(tot);
		tot+=d*B;
		tot-=(int)(tot);
		tot+=d*C;
		tot-=(int)(tot);
		arr[i]=tot*PI;
	}
	for(int i=0; i<len; i++) {
          arr[i]=(arr[i]>HALFPI)?(PI-arr[i]):arr[i];
	}
	for(int i=0; i<len; i++) {
	  arr[i]=(arr[i]<-HALFPI)?-PI-arr[i]:arr[i];
	}
}
//The sup7 and sup9 series were created by projecting sin(x) onto [x,x^3...] in the L^2 norm, and then changing the X coefficient to 1.
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


#define SUP9ORD9  FLTEND(2.598541769316398e-6)
#define SUP9ORD7  FLTEND(1.980468790634404e-4)
#define SUP9ORD5  FLTEND(8.332968616969083e-3)
#define SUP9ORD3  FLTEND(1.666665142764146e-1)

void sinsuperseries9(float* __restrict__ arr,int len) {
   bringtorange(arr,len);
   for(int i=0; i<len; i++) {
      FLTTYPE sqr=arr[i]*arr[i];
      arr[i]+=sqr*arr[i]*(SUP9ORD3+sqr*(SUP9ORD5+sqr*(SUP9ORD7+sqr*SUP9ORD9)));
   }
}


//This one (including the series) comes from an article about the implementation of sine on some platform
//It is supposedly the minmax series on -PI/6,PI/6
#define PIO6  FLTEND(0.523598776)

#define SA5  FLTEND(2.74201854577e-06)
#define SA4  FLTEND(-1.98410347969e-04)
#define SA3  FLTEND(8.33333320429e-03)
#define SA2  FLTEND(-1.66666666666e-01)

void bestseries9div3(float * __restrict__ arr,int len) {
   bringtorange(arr,len);
   for(int i=0; i<len; i++) {
      FLTTYPE or=arr[i];
//      if(or>PIO6) {
        arr[i]/=3;
//      }
      FLTTYPE sqr=arr[i]*arr[i];
      arr[i]+=arr[i]*sqr*(SA2+sqr*(SA3+sqr*(SA4+SA5*sqr))); 
     // arr[i]+=(or>PIO6)*arr[i]*(2-4*arr[i]*arr[i]);
      arr[i]=arr[i]*3-4*arr[i]*arr[i]*arr[i];
   }
}

#define MMS77  FLTEND(-0.00018684148083603963091)
#define MMS75  FLTEND(0.0083191783483393336376)
#define MMS73  FLTEND(-0.16666231326215784070)

//The following are minimax series on -PI/2,PI/2
//(with the x term set to 1.)
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

//simple taylor series.
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

//use the native sin() function
void vecsin(float* arr, int size) {
   for(int i=0; i<size; i++) {
     arr[i]=sin(arr[i]);
   }
}

//This is taken from eglibc's software implementation of sine.(I think from fdlibm?)
#define GNUS1  FLTEND(-1.6666667163e-01)
#define GNUS2  FLTEND( 8.3333337680e-03)
#define GNUS3  FLTEND(-1.9841270114e-04)
#define GNUS4  FLTEND( 2.7557314297e-06)
#define GNUS5  FLTEND(-2.5050759689e-08)
#define GNUS6  FLTEND( 1.5896910177e-10)

void gnuseries(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
   FLTTYPE sqr;
    for(int i=0; i<len; i++) {
      sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(GNUS1+sqr*(GNUS2 +sqr*(GNUS3 +sqr*(GNUS4+sqr*(GNUS5+sqr*GNUS6)))));
    }
}
//Taken by projecting sin(x)-x onto [x^3,x^5,...]
#define B91  FLTEND(-1.6666658777408987333e-1)
#define B92  FLTEND(8.3330585579660222884e-3)
#define B93  FLTEND(-1.9809580202098392708e-4)
#define B94  FLTEND( 2.6065544878032086552e-6)

void b9series(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
   for(int i=0; i<len; i++) {
      FLTTYPE sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(B91+sqr*(B92 +sqr*(B93 +sqr*B94)));
    }
}
#define B111 FLTEND(-1.6666666621113970589e-1)
#define B112 FLTEND(8.3333309585278954692e-3)
#define B113 FLTEND(-1.9840861674155877174e-4)
#define B114 FLTEND(2.7525172542458407497e-6)
#define B115 FLTEND(-2.3897606931720883012e-8)

void b11series(float* __restrict__ arr, int len) {
   bringtorange(arr,len);
    for(int i=0; i<len; i++) {
  	  FLTTYPE sqr=arr[i]*arr[i];
      arr[i]+= arr[i]*sqr*(B111+sqr*(B112 +sqr*(B113 +sqr*(B114+sqr*B115))));
    }
}
