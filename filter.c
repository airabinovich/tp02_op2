#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <time.h>

#include "inputSig.h"
#include "senial.h"

#define TamSignal 1250000
#define TamFilter 500
#define TamOutput (TamSignal + TamFilter -1)

int main(int argc, char *argv[]){
	int threads;
	double init, fin;
	float y[TamOutput];
	memset(y,0,(TamOutput)*sizeof(float));
	
	if(argc>1) threads = atoi(argv[1]);
	else threads = omp_get_num_procs();
	
	init = omp_get_wtime();
	
	#pragma omp parallel num_threads(threads)
	{
		int i,n;		
		#pragma omp for private(i,n)
		for(n=0;n<(TamOutput);n++){
			for(i=0;i<TamFilter;i++){
				if(n-i>=0 && (n-i) < TamSignal)
					y[n] += input[i] * rcvdSignal[n-i];
			}
		}
	}
	fin = omp_get_wtime();
	printf("Demoró %f segundos usando %d hilos\n",(fin-init),threads);
	
	FILE *dest, *reg;
	
	dest = fopen("resultado.h","w");
	if(dest == NULL){
		perror("error abriendo archivo");
		exit(1);
	}
	
	fprintf(dest,"output[%d] = {",TamOutput);
	int n;
	for(n=0;n<TamOutput;n++){
		fprintf(dest,"%f ",y[n]);
	}
	fprintf(dest,"};");
	fclose(dest);
	
	reg = fopen("registro.txt","a");
	if(reg == NULL){
		perror("error abriendo archivo");
		exit(1);
	}
	fprintf(reg,"tiempo: %f\thilos: %d\n",(fin-init),threads);
	
	return EXIT_SUCCESS;
}
