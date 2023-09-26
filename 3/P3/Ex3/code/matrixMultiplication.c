#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

void transpose_to_out(tipo **matrix, tipo **out, int n) {
	int i, j;
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			out[j][i] = matrix[i][j];
		}
	}
}

int main(int argc, char const *argv[]) {
	int register i = 0;
	int j, k;
	tipo **m1 = NULL, **m2 = NULL, **result = NULL, **m2_trans = NULL, sum = 0.0;
	struct timeval fin,ini;
	int N = 0;
	bool transposed = false, debug = false;
	if (argc < 2) {
		printUsageAndExit(-1, argv);
	}
	N = atoi(argv[1]);
	/* Parse parameters after size */
	for(i = 2; i < argc; i++) {
		if (strncmp("-t", argv[i], 2) == 0 || strncmp("--transposed", argv[i], 12) == 0) {
			transposed = true;
		} else if (strncmp("-d", argv[i], 2) == 0 || strncmp("--debug", argv[i], 2) == 0) {
			debug = true;
		} else {
			printUsageAndExit(i, argv);
		}
	}

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
	if(debug) {
		printMatrix("Matrix 1", m1, N);
		printMatrix("Matrix 2", m2, N);
	}
	/* Matrix multiplication */
	if(!transposed) {
        gettimeofday(&ini,NULL);
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				sum = 0;
				for(k = 0; k < N; k++) {
					sum += m1[i][k] * m2[k][j];
				}
				result[i][j] = sum;
			}
		}
		gettimeofday(&fin,NULL);
	} else { /* Multiplication of B transposed */
		m2_trans = generateEmptyMatrix(N);
		if(!m2_trans) { 
			free(m1);
			free(m2);
			free(result);
			return -1;
		}
		gettimeofday(&ini,NULL);
		transpose_to_out(m2, m2_trans, N);
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				sum = 0;
				for(k = 0; k < N; k++) {
					sum += m1[i][k] * m2_trans[j][k];
				}
				result[i][j] = sum;
			}
		}
		gettimeofday(&fin,NULL);
	}
	
	printf("Execution time: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
	if (debug) printMatrix("Result", result, N);

    free(m1);
    free(m2);
    free(result);
    free(m2_trans);
	return 0;
}
