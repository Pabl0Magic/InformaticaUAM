/**
 *
 * Description: Header files for permutation generation
 *
 * File: permutations.h
 * Author: Javier Sanz-Cruzado, Rocío Cañamares 
 * Version: 1.0
 * Data: 20-09-2019
 *
 */

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

int random_num(int inf, int sup);
int* generate_perm(int N);
int** generate_permutations(int n_perms, int N);

#endif
