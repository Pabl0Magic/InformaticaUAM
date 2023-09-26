/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "permutations.h"

/***************************************************/
/* Function: average_sorting_time Date: 26-09-2021 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort method, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  int* unsortedArray;
  int ret, i, totalOBs = 0;
  clock_t timeBefore, timeAfter;
  ptime->N = N;
  ptime->time = 0;
  if (n_perms < 0) {
    printf(" Number of perms is less or equal than 0");
    return ERR;
  }
  for(i = 0; i < n_perms; i++) {
    /* Generate a permutation */
    unsortedArray = generate_perm(N);
    if(!unsortedArray) return ERR;
    
    /* Check the time before the method is run */
    timeBefore = clock();
    if (timeBefore == -1) {
      return ERR;
    }
    ret = method(unsortedArray, 0, N-1);
    /* Fetch the time after the method is run */
    timeAfter = clock();

    /* Safely add the time without interfering with the execution time of the sorting algorithm */
    ptime->time += ((double) (timeAfter - timeBefore) / (double) CLOCKS_PER_SEC);
    free(unsortedArray);
    
    /* Check if there was an error */
    if(ret == ERR) return ERR;
    totalOBs += ret;
    
    /* Check if the returned count of OB's is a maximum, a minimum or both */
    if(i == 0){
      ptime->max_ob = ret;
      ptime->min_ob = ret;
    }
    else {
      if(ret > ptime->max_ob) ptime->max_ob = ret;
      if(ret < ptime->min_ob) ptime->min_ob = ret;
    }
  }

  ptime->average_ob = (double) totalOBs / (double) n_perms;
  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:17/10/2020*/
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{  
  int N, n_time = 0, n_times = (num_max - num_min + 1) / incr;
  PTIME_AA timeArray;
  timeArray = (PTIME_AA) malloc(sizeof(TIME_AA) * num_max);

  for (N = num_min; N <= num_max; N += incr, n_time++) {
    if(average_sorting_time(method, n_perms, N, &timeArray[n_time]) == ERR) {
      free(timeArray);
      return ERR;
    } 
  }

  if(save_time_table(file, timeArray, n_times) == ERR) {
    free(timeArray);
    return ERR;
  }
  free(timeArray);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date: 17/10/2020      */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *pf;
  int i;

  pf = fopen (file, "w");
    if (pf == NULL) return ERR;

  fprintf(pf, "Size\t Time\t Avg.\t Max.\t Min.\t ");

  for(i = 0; i < n_times; i++) {
    fprintf(pf, "\n%d\t%e\t%e\t%d\t%d\t\n",
    ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
  }

  fclose(pf);
  return OK;
}

short generate_search_times(pfunc_search method, pfunc_key_generator generator, 
                                int order, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_times) 
{
  PTIME_AA ptime = NULL;
  int n = 0, i = 0, j = 0;

  if(!method || !generator || !file || incr <= 0 || num_min > num_max || num_min < 0 || (order != NOT_SORTED && order != SORTED) || n_times <= 0){
    return ERR;
  }

  n = ((num_max-num_min)/incr)+1;

  ptime = malloc(sizeof(TIME_AA) * n);
  if(!ptime) return ERR;



  for(i = num_min, j = 0; i <= num_max ; i += incr, j++){
    if(average_search_time(method, generator, order, i, n_times, &ptime[j]) == ERR){
      free(ptime);
      return ERR;
    }  
  }
  
  if(save_time_table(file, ptime, n) == ERR){
    free(ptime);
    return ERR;
  }
  
  free(ptime);
  return OK;

}

short average_search_time(pfunc_search metodo, pfunc_key_generator generator,
                              int order,
                              int N, 
                              int n_times,
                              PTIME_AA ptime)
{
  int i = 0, *perm = NULL, *keys=NULL, ppos = 0, aux = 0, n_ob = 0;
  clock_t begin, end;
  PDICT pdict=NULL;

  if(!metodo|| !generator || !ptime || N <= 0 || n_times < 0 || (order != NOT_SORTED && order != SORTED)) return ERR;

  if(metodo == bin_search && order == NOT_SORTED) {
    printf("Binary search must be sorted\n");
    return ERR;
  }
  
  ptime->average_ob = 0;
  ptime->max_ob = 0;
  ptime->min_ob = 0;
  ptime->time = 0;

  pdict = init_dictionary(N, order);
  if(!pdict) {
    return ERR;
  }

  perm = generate_perm(N);
  if(!perm){
    free_dictionary(pdict);
    return ERR;
  }

  if(massive_insertion_dictionary(pdict, perm, N) == ERR){
    free_dictionary(pdict);
    free(perm);
    return ERR;
  }


  keys = (int*)malloc(sizeof(int) * N * n_times); 
  if(!keys){
    free_dictionary(pdict);
    free(perm);
    return ERR;
  }
  generator(keys, n_times * N, N);
  

  begin=clock();
  for(i = 0; i < N * n_times; i++){
    aux = search_dictionary(pdict, keys[i], &ppos, metodo);
    if(aux == ERR || ppos == NOT_FOUND){
      free_dictionary(pdict);
      free(perm);
      free(keys);
      return ERR;
    }
    
    n_ob += aux;

    if(aux < ptime->min_ob || ptime->min_ob == 0) {
      ptime->min_ob = aux;
    }
    
    if(aux>ptime->max_ob || ptime->max_ob == 0) {
      ptime->max_ob = aux;
    }

    
  }
  end=clock();

  
  

  ptime->time = (double)(end - begin)/(double)CLOCKS_PER_SEC;
  ptime->average_ob = (double)(n_ob)/(N*n_times);
  ptime->N = N;
  ptime->n_elems = N * n_times;

  free_dictionary(pdict);
  free(perm);
  free(keys);
  
  return OK;
}