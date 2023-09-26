#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "arqo4.h"

int main(int argc, char const *argv[])
{
	float *A=NULL, *B=NULL;
	long long k=0;
	struct timeval fin,ini;
	double sum=0;
	if (argc < 3) {
		fprintf(stderr, "Usage: %s <size_of_array> <num_threads>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	long long size = atoll(argv[1]);
	A = generateVectorOne(size);
	B = generateVectorOne(size);
	if ( !A || !B )
	{
		printf("Error when allocationg matrix\n");
		freeVector(A);
		freeVector(B);
		return -1;
	}
	
    omp_set_num_threads(2*atoi(argv[2]));
    
	gettimeofday(&ini,NULL);
	/* Bloque de computo */
	sum = 0;
	#pragma omp parallel for reduction(+:sum) if(size>80000)
	for(k=0;k<size;k++)
	{
		sum = sum + A[k]*B[k];
	}
	/* Fin del computo */
	gettimeofday(&fin,NULL);

	printf("Tiempo: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
	freeVector(A);
	freeVector(B);

	return 0;
}
