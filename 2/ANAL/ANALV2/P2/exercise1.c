/***********************************************/
/* Programa: ejercicio1     Date:             */
/* Authors:                                    */
/*                                             */
/* Program that generates random numbers	   */
/* between two given numbers                   */
/*                                             */
/* Input: Command line                 		   */
/* -infLim: inferior limit                     */
/* -supLim: superior limit                     */
/* -numN: amount of numbers	                   */
/* Output: 0: OK, -1: ERR                      */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int inf, sup, num, j;

  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Error in the input parameters:\n\n");
    fprintf(stderr, "%s -infLim <int> -supLim <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -infLim: inferior limit.\n");
    fprintf(stderr, " -supLim: superior limit.\n");
    fprintf(stderr, " -numN: amount of numbers to generate.\n");
    exit(-1);
  }
  printf("Assigment number 1, part 1\n");
  printf("Made by: Miguel Arnaiz & Pablo Almarza\n");
  printf("Group: 1292\n");

  /* check command line*/
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-infLim") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-supLim") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parameter %s is incorrect\n", argv[i]);
    }
  }

  /* print data */
  for(j = 0; j < num; j++) { 
    printf("%d\n", random_num(inf, sup));
  }

  return 0;
}

