/**************************************************/
/* Program: exercise3       Date: 17/10/2020      */
/* Authors: Pablo Almarza & Miguel Arnaiz         */
/*                                                */
/* Program that generates N random permutations   */
/* with M elementos each                          */
/*                                                */
/* Input: Command line                            */
/* -size: nomber of elements in each permutation  */
/* -numP: numero of permutations                  */
/* Output: 0: OK, -1: ERR                         */
/**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int n_perms, tamanio, j, k;
  int** perms = NULL;

  srand(time(NULL));
  
  if (argc != 5) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -size <int> -numP <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -size : number of elements in each permutation.\n");
    fprintf(stderr, " -numP : number of permutations.\n");
    exit(-1);
  }

  printf("Practice number 1, section 3\n");
  printf("Done by: Pablo Almarza & Miguel Arnaiz \n");
  printf("Group: 03\n");


  /* check command line la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-size") == 0) {
      tamanio = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      n_perms = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
    }
  }

  perms = generate_permutations(n_perms, tamanio);

  if (perms == NULL) { /* error */
    printf("Error: Out of memory\n");
    exit(-1);
  } else {
    for(j = 0; j < n_perms; j++) { /* for each permutation */
      for(k = 0; k < tamanio; k++) {
        printf("%d ", perms[j][k]); /* print each element */
      }
      printf("\n");
      free(perms[j]); /* free permutation */
    }

    free(perms); /* free permutations array */
  }

  return 0;
}

