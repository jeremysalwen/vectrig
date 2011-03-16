#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "main.h"

int getFailings(float coefficients[4],int len, float arr[len],float output[len]) {
    float copy[len];
    memcpy(copy,arr,sizeof(arr));
	vecsin(copy,len);
	for(int i=0; i<len; i++) {
		float sqr=arr[i]*arr[i];
		arr[i]+=arr[i]*sqr*(coefficients[0]+sqr*(coefficients[1]+sqr*(coefficients[2]+sqr*coefficients[3])));
	}
	int off=0;
	for(int i=0; i<len; i++) {
		if(arr[i]!=copy[i]) {
			off++;
		}
	}
	return off;
}

float maxErr(float coefficients[4],int len, float arr[len]) {
    float copy[len];
	float output[len];
	memcpy(copy,arr,len*sizeof(float));
	vecsin(copy,len);
	for(int i=0; i<len; i++) {
		float sqr=arr[i]*arr[i];
		output[i]=arr[i]*(1+sqr*(coefficients[0]+sqr*(coefficients[1]+sqr*(coefficients[2]+sqr*coefficients[3]))));
	}
	float max=0;
	for(int i=0; i<len; i++) {
		if(fabs(output[i]-copy[i])>max) {
			//printf("lol %f %f %f\n",arr[i],output[i],copy[i]);
			max=fabs(output[i]-copy[i]);
		}
	}
	return max;
}

float randf() {
	float f= (float)rand()/RAND_MAX;
	return f;
}
float randgaus() {
  // from http://www.taygeta.com/random/gaussian.html
  // Algorithm by Dr. Everett (Skip) Carter, Jr.

         float x1, x2, w;
 
         do {
                 x1 = 2.0 * randf() - 1.0;
                 x2 = 2.0 * randf() - 1.0;
                 w = x1 * x1 + x2 * x2;
         } while ( w >= 1.0 );

         w = sqrt( (-2.0 * log( w ) ) / w );
         return x1 * w;
}

#define POP 10
void mutate(float pop[POP][4],double prob,double amount) {

}
void mate(float par1[4],float par2[4],float child[4]) {
	for(int i=0; i<4; i++) {
		child[i]=(par1[i]+par2[i])/2;
	}
}

#define NUMTEST 1024

static inline int random(int i) {
	return rand()%i;
}
void GA() {
	srand(time(0));
	float population[POP][4];
	float poptmp[POP][4];
	for(int i=0; i<POP; i++) {
		for(int j=0; j<4; j++) {
			population[i][j]=randf()*4-2;
		}
	}
	for(int i=0; i<10001; i++) {
		//printf("Round %d\n",i);
		float test[NUMTEST];
		for(int j=0; j<NUMTEST; j++) {
			test[j]=(float)j/NUMTEST*HALFPI;
		}
		float best=10000;
		int bestindex=0;
		for(int j=0; j<POP; j++) {
			float off=maxErr(population[j],NUMTEST,test);
			if(off<best) {
				best=off;
				bestindex=j;
			}
			if(i%100==0) {
				//printf("Individual %d, %f %f %f %f: %f\n",j,population[j][0],population[j][1],population[j][2],population[j][3],off);
			}
			int mate1=random (POP);
			int mate2=random (POP);
			if(maxErr(population[mate1],NUMTEST,test)<maxErr(population[mate2],NUMTEST,test)) {
				mate(population[j],population[mate1],poptmp[j]);
			} else {
				mate(population[j],population[mate2],poptmp[j]);
			}
			for(int k=0; k<4; k++) {
				if(randf()<0.01) {
					population[j][k]+=1000*population[j][k]*off*randgaus();
				}
			}
		}
		printf("best: %f\n",best);
		memcpy(population,poptmp,sizeof(poptmp));
		for(int j=0; j<POP; j++) {
			for(int k=0; k<4; k++) {
				population[j][k]=population[bestindex][k];
			}
		}
	}
}

int main(char** argv, int argc) {
	srand(time(0));
	float value[4];
	float best[4];
	float neighbor[4];
	float test[NUMTEST];
	for(int j=0; j<NUMTEST; j++) {
		test[j]=(float)j*HALFPI/NUMTEST;
	}
	for(int i=0; i<4; i++) {
		value[i]=randf();
	}
	value[0]=2.6199025197195120855e-6f;
    value[1]=-0.00019816322019412579628f;
    value[2]=0.0083331628953425015333f;
    value[3]=-0.16666663516396446563f;
	float score,bestscore;
	bestscore=100000000;
	score=maxErr(value,NUMTEST,test);
#define ITERATIONS 10000
	for(int n=0; n<ITERATIONS; n++) {
		for(int i=0; i<4; i++) {
			float rand=randgaus()*0.1;
			//printf("LOLRAND %f\n",rand);
			neighbor[i]=value[i]+rand;
		}
		float newscore=maxErr(neighbor,NUMTEST,test);
		float temp=((float)n/ITERATIONS);
		if(newscore<score || (exp((newscore-score) / (1-temp)) < randf())) {
			memcpy(value,neighbor,sizeof(neighbor));
			score=bestscore;
		}
		if(newscore<bestscore) {
			memcpy(best,neighbor,sizeof(neighbor));
			bestscore=newscore;
		}
		printf("bestscore %8.8f %8.8f %8.8f %8.8f:%8.8f\n",best[0],best[1],best[2],best[3],bestscore);
	}
}
