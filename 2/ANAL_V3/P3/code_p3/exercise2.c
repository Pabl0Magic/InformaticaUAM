/***********************************************************/
/* Program: exercise2 Date:                             */
/* Authors:                                                */
/*                                                         */
/* Program that writes in a file the average times         */
/* of the search algorithm                                 */
/*                                                         */
/* Input: Command line                                     */
/* -num_min: minimum number of elements in the table       */
/* -num_max: maximum number of elements in the table       */
/* -incr: increment                                       */
/* -fkeys: number of keys to search                        */
/* -numP: Introduce the number of permutations to average  */
/* -outputFile: Name of the output file                    */
/*                                                         */
/* Output: 0 if there was an error                         */
/*        -1 otherwise                                     */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"
#include "search.h"
#include "times.h"

int main(int argc, char** argv)
{
  int i, num_min,num_max,incr,n_times;
  char name[256];
  short ret;
 
  srand(time(NULL));

  if (argc != 11) {
    fprintf(stderr, "Error in the input parameters:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -n_keys <int> -n_times <int> -outputFile <string> \n");
    fprintf(stderr, "Where:\n");
    fprintf(stderr, "-num_min: minimum number of elements of the table\n");
    fprintf(stderr, "-num_max: maximum number of elements of the table\n");
    fprintf(stderr, "-incr: increment\n");
    fprintf(stderr, "-n_times: number of times each key is searched\n");
    fprintf(stderr, "-outputFile: Output file name\n");
    exit(-1);
  }

  printf("Practice number 3, section 2\n");
  printf("Done by: Pablo Almarza\n");
  printf("Group: Your group\n");

  /* check the command line */
  for(i = 1; i < argc ; i++) {
    if (strcmp(argv[i], "-num_min") == 0) {
      num_min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-num_max") == 0) {
      num_max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-incr") == 0) {
      incr = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-n_times") == 0) {
      n_times = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-outputFile") == 0) {
      strcpy(name, argv[++i]);
    } else {
      fprintf(stderr, "Parameter %s is invalid\n", argv[i]);
      exit(-1);
    }
  }

  /* calculamos los tiempos */
  ret = generate_search_times(lin_auto_search, potential_key_generator, NOT_SORTED, 
                                name, num_min, num_max, incr, n_times);
  if (ret == ERR) { 
    printf("Error in function generate_search_times\n");
    exit(-1);
  }

  printf("Correct output \n");

  return 0;
}

