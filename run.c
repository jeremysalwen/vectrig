#include "main.h"

static void evaluateFunction(const char* name, void (*func)(float*,int) ) {
   float arr[SIZE];
   float  vecsinarr[SIZE];
   for(int i=0; i<SIZE; i++) {
     arr[i]=(float)i/2048;
     vecsinarr[i]=arr[i];
   }
   vecsin(vecsinarr,SIZE);
#ifdef CLOCK
   clock_t endwait=clock();
   for(int i=0; i<100000; i++) {
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
     if(arr[i]!=vecsinarr[i]) {
        off++;
      }
     float err=fabs(arr[i]-sin((float)i/2048));
     if(err >maxerr) {
       maxerr=err;
     }
     if(arr[i]!=0 && fabs(err/arr[i]) >maxrelerr) {
       maxrelerr=fabs(err/arr[i]);
     }
     unsigned int x= abs((*((unsigned int*)&arr[i])) - (*((unsigned int*)&vecsinarr[i])));
     if(x>ulpsoff) {
	ulpsoff=x;
	//printf("%u: %u, %u, %f, %f\n",bitsoff,*((unsigned int*)&arr[i]),*((unsigned int*)&vecsinarr[i]),arr[i],vecsinarr[i]);
     }
   }
   printf("Evaluation for %s: off:%d ulpsoff: %u maxerr:%10.10fe-7 maxrelerr:%10.10fe-7\n",name,off,ulpsoff, maxerr*10e7, maxrelerr*10e7);
}


int main() {
evaluateFunction("vecsin",&vecsin);
evaluateFunction("sinseries0",&sinseries0);
evaluateFunction("sinseries05",&sinseries05);
evaluateFunction("supersin7",&sinsuperseries7);
evaluateFunction("supersin9",&sinsuperseries9);
evaluateFunction("best9div3",&bestseries9div3);
evaluateFunction("minimaxseries7",&minimaxseries7);
evaluateFunction("minimaxseries9",&minimaxseries9);
evaluateFunction("minimaxseries11",&minimaxseries11);
evaluateFunction("minimaxseries13",&minimaxseries13);
evaluateFunction("minimaxseries15",&minimaxseries15);
}
