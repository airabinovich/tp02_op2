#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <time.h>

#include "inputSig.h"
#include "senial.h"
#define threads 4
#define iter 500

#define TAM 500
float *senial = rcvdSignal;

int main(int argc, char *argv[]){
	int i,n;
	time_t init,fin;
	init = time(&init);
	float y[TAM];
	memset(y,0,TAM*sizeof(float));
	for(n=0;n<iter;n++){
		for(i=0;i<=n;i++){
			y[n] += input[n-i] * senial[i];
		}
	}
	printf("y = { ");
	for(n=0;n<iter;n++){
			printf("%f,",y[n]);
	}
	printf("}\n");
	fin = time(&fin);
	printf("Demoró %f segundos\n",difftime(fin,init));
	return EXIT_SUCCESS;
}
