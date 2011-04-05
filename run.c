#include "main.h"

#define SIZE (int)(4096*3.14159)

static void evaluateFunction(const char* name, void (*func)(float*,int) ) {
   float arr[SIZE];
   for(int i=0; i<SIZE; i++) {
     arr[i]=(float)i/8192;
   }
#ifdef CLOCK
   clock_t endwait=clock();
   for(int i=0; i<10000; i++) {
#endif
      func(arr,SIZE);
#ifdef CLOCK
   }
   printf("time for %s: %d\n",name,clock()-endwait);
#endif
   unsigned int off=0;
   float maxerr=0;
   float maxrelerr=0;
   unsigned int ulpsoff=0;
   for(int i=0; i<SIZE; i++) {
     float val=sin((float)i/8192);
     if(arr[i]!=val) {
        off++;
      }
     float err=fabs(arr[i]-val);
     if(err >maxerr) {
       maxerr=err;
     }
     if(arr[i]!=0 && fabs(err/val) >maxrelerr) {
       maxrelerr=fabs(err/val);
     }
     unsigned int x= abs((*((unsigned int*)&arr[i])) - (*((unsigned int*)&val)));
     if(x>ulpsoff) {
	ulpsoff=x;
	//printf("%u: %u, %u, %f, %f\n",bitsoff,*((unsigned int*)&arr[i]),*((unsigned int*)&vecsinarr[i]),arr[i],vecsinarr[i]);
     }
   }
   printf("Evaluation for %s: off:%d ulpsoff: %u maxerr:%10.10fe-7 maxrelerr:%10.10fe-7\n",name,off,ulpsoff, maxerr*10e7, maxrelerr*10e7);
}


int main() {
evaluateFunction("vecsin",&vecsin);
evaluateFunction("gnuseries",&gnuseries);
evaluateFunction("sinseries0o7",&sinseries0o7);
evaluateFunction("sinseries0o9",&sinseries0o9);
evaluateFunction("sinseries0o11",&sinseries0o11);
evaluateFunction("sinseries0o13",&sinseries0o13);
evaluateFunction("supersin7",&sinsuperseries7);
evaluateFunction("supersin9",&sinsuperseries9);
evaluateFunction("best9div3",&bestseries9div3);
evaluateFunction("minimaxseries7",&minimaxseries7);
evaluateFunction("minimaxseries9",&minimaxseries9);
evaluateFunction("minimaxseries11",&minimaxseries11);
evaluateFunction("minimaxseries13",&minimaxseries13);
evaluateFunction("minimaxseries15",&minimaxseries15);
evaluateFunction("b9series",&b9series);
evaluateFunction("b11series",&b11series);
}
