/**
 *
 * Descripcion: Heather for functions for permutations generation
 *
 * Fichero: permutationes.h
 * Autor: Carlos Aguirre 
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#ifndef PERMUTACIONES_H
#define PERMUTACIONES_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

int random_num(int inf, int sup);
int* generate_perm(int N);
int** generate_permutations(int n_perms, int N);

#endif
