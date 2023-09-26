/***********************************************/
/* Program: exercise1     Date:             */
/* Authors:                                    */
/*                                             */
/* Program that checks the correct behaviour of*/
/* linear search                               */
/*                                             */
/* Input: Command line                         */
/*   -size: number of elements in the dictionary */
/*   -key:  key to search                      */
/*                                             */
/* Output: 0: OK, -1: ERR                      */
/***********************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#include "permutations.h"
#include "search.h"

int main(int argc, char** argv)
{
  int i, nob, pos;
  unsigned int key, size;
  PDICT pdict;
  int *perm;

  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error in the input parameters:\n\n");
    fprintf(stderr, "%s -size <int> -key <int>\n", argv[0]);
    fprintf(stderr, "where:\n");
    fprintf(stderr, " -size : number of elements in the table.\n");
    fprintf(stderr, " -key : key to search.\n");
    exit(-1);
  }

  printf("Pratice number 3, section 1\n");
  printf("Done by: Pablo Almarza\n");
  printf("Group: Your group\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-size") == 0) {
      size = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-key") == 0) {
      key = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parameter %s is invalid\n", argv[i]);
    }
  }

  pdict = init_dictionary(size,SORTED);

  if (pdict == NULL) {
    /* error */
    printf("Error: Dictionary could not be initialized\n");
    exit(-1);
  }

  perm = generate_perm(size);

  if (perm == NULL) {
    /* error */
    printf("Error: No hay memoria\n");
    free_dictionary(pdict);
    exit(-1);
  }

  nob = massive_insertion_dictionary(pdict, perm, size);

  if (nob == ERR) {
    /* error */
    printf("Error: Dictionary could not be created\n");
    free(perm);
    free_dictionary(pdict);
    exit(-1);
  }

  nob = search_dictionary(pdict,key,&pos,bin_search);

  if(nob >= 0) {
    printf("Key %d found in position %d in %d basic op.\n",key,pos,nob);
  } else if (nob==NOT_FOUND) {
    printf("Key %d not found in table\n",key);
  } else {
    printf("Error when searching the key %d\n",key);
  }

  free(perm);
  free_dictionary(pdict);

  return 0;
}

