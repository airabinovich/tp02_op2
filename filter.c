#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <time.h>

#include "inputSig.h"
#include "senial.h"
#define threads 4

#define TAM 500
#define iter 500
float *senial = rcvdSignal;

int main(int argc, char *argv[]){
	//~ omp_set_num_threads(4);
	//~ #pragma omp parallel
	//~ {
		//~ 
	//~ }
	int i,n;
	time_t init, fin;
	init = time(&init);
	float y[TAM];
	memset(y,0,TAM*sizeof(float));
	printf("y[n] = { ");
	for(i=0;i<TAM;i++){
		printf("%.2f,",y[i]);
	}
	printf("\b}\n");
	
	#pragma omp parallel num_threads(threads)
	{
		#pragma omp for
		for(n=0;n<iter;n++){
			for(i=0;i<=n;i++){
				#pragma omp atomic
				y[n] += input[n-i] * senial[i];
			}
		}
	}
	printf("y[n] = { ");
	for(n=0;n<iter;n++){
			printf("%f,",y[n]);
	}
	printf("\b }\n");
	fin = time(&fin);
	
	printf("Demoró %f segundos\n",difftime(fin,init));
	return EXIT_SUCCESS;
}
