/***********************************************/
/* Program: exercise1     Date:                */
/* Authors:                                    */
/*                                             */
/* Program that generates two random nunmbers  */
/* between two given numbers                   */
/*                                             */
/* Input: Command Line                         */
/* -limInf: lower limit                        */
/* -limSup: upper limit                        */
/* -numN: ammount of numbers                   */
/* Output: 0: OK, -1: ERR                      */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

/*************************/
/* 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 */
/*************************/

int generate_data(int* v, int inf, int sup, int num) {
  FILE *fp;
  int i, j, k;

  if (!v || inf > sup) {
    return ERR;
  }

  fp = fopen("data.txt", "w");
  for(i = inf; i <= sup; i++) {
    k = 0;
    for(j = 0; j < num; j++) {
      if (i == v[j]) {
        k++;
      }
    }

    fprintf(fp, "%d\t%d\n", i, k);
  }
  fclose(fp);

  return OK;
  
}

int main(int argc, char** argv)
{
  int i, a, k;
  unsigned int inf, sup, num, j;
  int *v;


  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Input parameter error:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -limInf : Lower limit.\n");
    fprintf(stderr, " -limSup : Upper limit.\n");
    fprintf(stderr, " -numN : ammout of mumbers to generate.\n");
    exit(-1);
  }
  printf("Practice no 1, Section 1\n");
  printf("Done by: Pablo Almarza\n");
  printf("Grupo: 129\n");

  /* check command line */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-limInf") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-limSup") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong Parameter %s \n", argv[i]);
    }
  }

  v = (int*)malloc(num*sizeof(int));
  if (!v) {
    return ERR;
  }

  /* print data */
  for(j = 0, k = 0; j < num; j++, k++) { 
    a = random_num(inf, sup);
    printf("%d\n", a);

    v[k] = a;
  }

  if (generate_data(v, inf, sup, num) == ERR) {
    fprintf(stderr, "Error generating the histogram file\n");
    free(v);
    return -1; 
  }

  free(v);

  return 0;
}

