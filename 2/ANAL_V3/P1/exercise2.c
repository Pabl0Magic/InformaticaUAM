/********************************************************/
/* Program: exeercise2      Date:                       */
/* Authors:                                             */
/*                                                      */
/* Program that generates random permutations           */
/*                                                      */
/* Input: Command line                                  */
/* -size: nomber of elements in each permutation        */
/* -numP: numero of permutations                        */
/* Output: 0: OK, -1: ERR                               */
/********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int num, size, j, k;
  int* perm = NULL;

  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -size <int> -numP <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -size : number of elements in each permutation.\n");
    fprintf(stderr, " -numP : number of permutations.\n");
    exit(-1);
  }

  printf("Practice number 1, section 2\n");
  printf("Done by: Pablo Almarza\n");
  printf("Group: Your group\n");

  /* check command line */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-size") == 0) {
      size = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
    }
  }

  /* print result */
  for(j = 0; j < num; j++) { 
    perm = generate_perm(size);
    if (perm == NULL) { /* error */
      printf("Error: Out of memory\n");
      exit(-1);
    } else {
      for(k = 0; k < size; k++) { /* print each element */
        printf("%d ", perm[k]);
      }
      printf("\n");
      free(perm); /* free permutations */
    }
  }

  return 0;
}

