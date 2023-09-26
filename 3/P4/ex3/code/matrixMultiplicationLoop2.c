#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>
#include <sys/time.h>
#include "arqo3.h"

/*
	Authors: Jorge González and Pablo Almarza Marques
	Instead of doing two programs, we decided it was easier to handle everything
	through the same main function
*/

void printUsageAndExit(int argError, char const *argv[]) {
	fprintf(stderr, "Usage: %s <size> [--transposed | -t] [--debug | -d]\n", argv[0]);
	if(argError > 0) {
		fprintf(stderr, "Invalid parameter: %s\n", argv[argError]);
	}
	exit(-1);
}

void printMatrix(const char* title, tipo **matrix, int n) {
	int i=0, j=0;
	printf("%s:\n", title);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			#if __x86_64__
				printf("%.2lf\t", matrix[i][j]);
			#else
				printf("%.2f\t", matrix[i][j]);
			#endif
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[]) {
	int register i = 0;
	int j, k;
	tipo **m1 = NULL, **m2 = NULL, **result = NULL, sum = 0.0;
	struct timeval fin,ini;
	int N = 0, n_threads = 0;
	if (argc < 2) {
		printUsageAndExit(-1, argv);
	}
    n_threads = atoi(argv[1]);
	N = atoi(argv[2]);

	m1 = generateMatrix(N);
	if(!m1) {
		return -1;
	}

	m2 = generateMatrix(N);
	if(!m2) {
		free(m1);
		return -1;
	}

	result = generateEmptyMatrix(N);
	if(!result) {
		free(m1);
		free(m2);
		return -1;
	}

	/* Matrix multiplication */
    gettimeofday(&ini,NULL);
	for(i = 0; i < N; i++) {
        #pragma omp parallel for private(j, k) firstprivate(i) shared(result) num_threads(n_threads)
		for(j = 0; j < N; j++) {
			sum = 0;
			for(k = 0; k < N; k++) {
				sum += m1[i][k] * m2[k][j];
			}
			result[i][j] = sum;
		}
	}
	gettimeofday(&fin,NULL);

	printf("Execution time: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);

    free(m1);
    free(m2);
    free(result);
	return 0;
}
