#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <immintrin.h>

#define ARRAY_SIZE 2048
#define NUMBER_OF_TRIALS 100000

/*
 * Statically allocate our arrays.  Compilers can
 * align them correctly.
 */
static double a[ARRAY_SIZE], b[ARRAY_SIZE], c;

float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

int main(int argc, char *argv[]) {
    int i,t,j,number_of_trials;
    struct timeval start;
    struct timeval end;
    FILE *pf;

    pf = fopen("trials.txt", "w");

    double m = 1.0001;
    __m256d ii={0.0,1.0,2.0,3.0};
    __m256d jj={1.0,2.0,3.0,4.0};
    /* Populate A and B arrays */
    for (i=0; i < ARRAY_SIZE; i++) {
        b[i] = i;
        a[i] = i+1;
    }
    /*for (i=0;i<ARRAY_SIZE;i+=4){
        _mm256_storeu_pd(&a[i], ii);
        _mm256_storeu_pd(&b[i], jj);
    }*/

    /* Declare variables */
    __m256d mm = {1.0001, 1.0001, 1.0001, 1.0001};
    __m256d sum = {0.0, 0.0, 0.0, 0.0}; // to hold partial sums

    /* Perform an operation a number of times */
    number_of_trials = NUMBER_OF_TRIALS;
    while (number_of_trials <= 1000000) {
        gettimeofday(&start, NULL);
        for (t=0; t < number_of_trials; t++) {
            for (i=0; i < ARRAY_SIZE; i+=4) {
                /* Load */
                __m256d va = _mm256_loadu_pd(&a[i]);
                __m256d vb = _mm256_loadu_pd(&b[i]);

                /* m*a+b */
                __m256d tmp = _mm256_fmadd_pd (mm, va, vb);

                /* Sum */
                sum = _mm256_add_pd (tmp, sum);
            }
        }
        gettimeofday(&end, NULL);
        fprintf(pf, "Number trials %d\t Execution time %0.8f\n", number_of_trials, time_diff(&start, &end));
        number_of_trials += 100000;
    }
    c = 0.0;
    for (j = 0; j < 4; j++) {
        c += sum[j];
    }

    fclose(pf);

    return 0;
}
