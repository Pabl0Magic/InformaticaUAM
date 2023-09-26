#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "index.h"


typedef struct _idx_data
{
    int key;
    unsigned int nrec;
    unsigned long *records;
} idx_data;

struct index_
{
    idx_data *idx_datas;
	type_t type;
	char* path;
    unsigned int nidx; /* Number of indexes */
};


/*  The compare needs the type and it can't be passed through an argument.
    It needs a global variable taken as a temporary variable 
    
    NOTE: This is NOT thread-safe. Avoid using indexes with different types running 
    in the same program but in parallel (a.k.a. in different threads)
    To make the program thread safe, one way could be 
    giving every idx_data a "type_t" variable and use that one, 
    which would be a massive waste of memory.
    It's highly recommended to yoink a sort function and slap it
    here manually here. */
type_t tempType;
int idx_compare(const void * s1, const void * s2) {
    const idx_data* i1 = (const idx_data*) s1;
    const idx_data* i2 = (const idx_data*) s2;

    return (value_cmp(tempType, (void*) &i1->key, (void*) &i2->key));
}
void index_sort(index_t* idx) {
    tempType = idx->type;
    qsort(idx->idx_datas, idx->nidx, sizeof(idx_data), idx_compare);
}
/*********************
 * PUBLIC FUNCTIONS *
 ********************/
/* 
   Function: int index_create(char *path, int type)

   Creates a file for saving an empty index. The index is initialized
   to be of the specific type (in the basic version this is always INT)
   and to contain 0 entries.

   Parameters:
   path:  the file where the index is to be created
   type:  the type of the index (always INT in this version)

   Returns:
   1:   index created
   0:   parameter error or file creation problem. Index not created.
 */

int index_create(char *path, type_t type) {
	int zero = 0;
    FILE *f;
    if (!path) {
        return 0;
    }

    f = fopen(path, "wb+");
    if (!f) {
        return 0;
    }

    fwrite(&type, sizeof(int), 1, f);
    fwrite(&zero, sizeof(int), 1, f);

    fclose(f);
	return 1;
}

/* 
   Opens a previously created index: reads the contents of the index
   in an index_t structure that it allocates, and returns a pointer to
   it (or NULL if the files doesn't exist or there is an error). 

   NOTE: the index is stored in memory, so you can open and close the
   file in this function. However, when you are asked to save the
   index, you will not be given the path name again, so you must store
   in the structure either the FILE * (and in this case you must keep
   the file open) or the path (and in this case you will open the file
   again).

   Parameters:
   path:  the file where the index is 

   Returns:
   pt:   index opened
   NULL: parameter error or file opening problem. Index not opened.

 */
index_t *index_open(char *path) {
	unsigned int i, flag = 0;
	index_t* idx;
    FILE *pf;
    
	if(!path) return NULL;
	
	idx = (index_t*) malloc(sizeof(index_t));
	if (!idx) return NULL;
	
	pf = fopen(path, "rb+");
	if (!pf) {
		free(idx);
		return NULL;
	}
    
    /* We will save the path file so we will close it and open it again in index_save */
    idx->path = strdup(path);

    if (!idx->path) {
        fclose(pf);
        free(idx);
        return NULL;
    }

    if(!fread(&idx->type, sizeof(int), 1, pf)) {
        fclose(pf);
        free(idx->path);
        free(idx);
        return NULL;
    }
	/* Save the number of indexes */
    
	if(!fread(&idx->nidx, sizeof(int), 1, pf)) {
        fclose(pf);
        free(idx->path);
        free(idx);
        return NULL;
    }
    /* SPECIAL CASE. 0 keys in the index */
	if (idx->nidx == 0) {
        idx->idx_datas = NULL;
        fclose(pf);
        return idx;    
    }

    /* Allocate memory for the index in case there are indexes */
    idx->idx_datas = (idx_data*) malloc(idx->nidx * sizeof(idx_data));

    if (!idx->idx_datas) {
        fclose(pf);
        free(idx->path);
        free(idx);
        return NULL;
    }
    
    /* First read the keys, then the number of records in each index*/
    for (i = 0; i < idx->nidx; i++) {
        /* Read the key[i] */
		if(!fread(&(idx->idx_datas[i].key), sizeof(int), 1, pf)) {
            flag = 1;
            break;
        }
        /* Read the number of records for idx_data[i], which has the previous key */
        if(!fread(&(idx->idx_datas[i].nrec), sizeof(int), 1, pf)){
            flag = 1;
            break;
        }

        /* Alloc the memory for records, then read the records for each index*/
        idx->idx_datas[i].records = (unsigned long*) malloc(idx->idx_datas[i].nrec * sizeof(unsigned long));
        if(!idx->idx_datas[i].records) {
            flag = 1;
            break;
        }
        if(!fread(&(idx->idx_datas[i].records), sizeof(unsigned long), idx->idx_datas[i].nrec, pf)){
            flag = 1;
            break;
        }
	}
	
    if (flag) {
        for (i -= 1; i >= 0; i--){
            free(idx->idx_datas[i].records);
        }
        free(idx->idx_datas);
        fclose(pf);
        free(idx->path);
        free(idx);
        return NULL;
    }

    /* In case the index isn't sorted, sort it */
    index_sort(idx);
	return idx;
}

/* 
   int index_save(index_t* index);

   Saves the current state of index in the file it came from. Note
   that the name of the file in which the index is to be saved is not
   given.  See the NOTE to index_open.  

   Parameters:
   index:  the index the function operates upon

   Returns:
   1:  index saved
   0:  error saving the index (cound not open file)

*/
int index_save(index_t *idx) {
  	unsigned int i, flag = 0;
    FILE * pf;
    if (!idx) return 0;
    if (!idx->path || !idx->idx_datas) return 0;
    
    pf = fopen(idx->path, "wb");
    if (!pf) {
        return 0;
    }
    if(!fwrite(&idx->type, sizeof(int), 1, pf)) {
        fclose(pf);
        return 0;
    }
	/* Save the number of indexes */
	if(!fwrite(&idx->nidx, sizeof(int), 1, pf)) {
        fclose(pf);
        return 0;
    }
    
    /* First write the keys, then the number of records in each index*/
    for (i = 0; i < idx->nidx; i++) {
        /* Write the key[i] */
		if (!fwrite(&(idx->idx_datas[i].key), sizeof(int), 1, pf)) {
            flag = 1;
            break;
        }
        /* Write the number of records for idx_data[i], which has the previous key index */
        if (!fwrite(&(idx->idx_datas[i].nrec), sizeof(int), 1, pf)) {
            flag = 1;
            break;
        }

        /* Write the records for each index */
        if (!fwrite((idx->idx_datas[i].records), sizeof(unsigned long), idx->idx_datas[i].nrec, pf)) {
            flag = 1;
            break;
        }
	}

    if (flag) {
        fclose(pf);
        return 0;
    }
    fclose(pf);
    return 1;
}

/* 
   Function: int index_put(index_t *index, int key, long pos);

   Puts a pair key-position in the index. Note that the key may be
   present in the index or not... you must manage both situation. Also
   remember that the index must be kept ordered at all times.

   Parameters:
   index:  the index the function operates upon
   key: the key of the record to be indexed (may or may not be already
        present in the index)
   pos: the position of the corresponding record in the table
        file. This is the datum that we will want to recover when we
        search for the key.

   Return:
   n>0:  after insertion the file now contains n unique keys
   0:    error inserting the key

*/
int index_put(index_t *idx, int key, long pos) {
  	/* We're going to use the same variable many times to save some time */
    idx_data* idxTemp;
    int arrIdx;

    if (!idx || pos < 0) return 0;
    
    tempType = idx->type;
    idxTemp = bsearch(&key, idx->idx_datas, idx->nidx, sizeof(idx_data), idx_compare);
    /* If the key is found... */
    if (idxTemp) {
        arrIdx = (*idxTemp).nrec;
        (*idxTemp).records = (unsigned long *) realloc((*idxTemp).records, sizeof(unsigned long) * (arrIdx + 1));
        if(!(*idxTemp).records) {
            /* Check if the old array was saved */
            (*idxTemp).nrec--; 
            return 0;
        }
        else {
            fprintf(stderr, "FATAL ERROR: Close the current index before interacting with it.\n");
            return 0;
        }
        (*idxTemp).records[arrIdx] = (unsigned long) pos;
        (*idxTemp).nrec++;
        return idx->nidx;
    }
    arrIdx = idx->nidx;
    /* Case where there's no indexes, alloc for one */
    if(idx->idx_datas == NULL) {
        if(!(idx->idx_datas = (idx_data*) malloc(sizeof(idx_data))))
        {
            return 0;
        }
        idx->nidx++;
    } /* In the case there's idx_datas, do a whole another routine
       to realloc the idx_datas size to alloc for more memory */
    else {
        idx->nidx++;
        idx->idx_datas = (idx_data*) realloc(idx->idx_datas, sizeof(idx_data) * idx->nidx);
        if (!idx->idx_datas) {
            fprintf(stderr, "FATAL ERROR: The index will do a segmentation fault unless fully closed and reloaded.\n");
            idx->nidx--;
            return 0;
        }
    }
    /* Shared code between both "routines" for the new key part */
    idx->idx_datas[arrIdx].key = key;
    idx->idx_datas[arrIdx].records = (unsigned long *) malloc(sizeof(unsigned long));
    if(!idx->idx_datas[arrIdx].records) {
        return 0;
    }
    idx->idx_datas[arrIdx].records[0] = (unsigned long) pos;
    idx->idx_datas[arrIdx].nrec = 1;
    
    /* Sort the index since, anyways, we will have to use binary search for the index_put method again */
    index_sort(idx);
    return idx->nidx;
}

/* 
   Function: long *index_get(index_t *index, int key, int* nposs);

   Retrieves all the positions associated with the key in the index. 

   Parameters:
   index:  the index the function operates upon
   key: the key of the record to be searched
   nposs: output paramters: the number of positions associated to this key
   
   Returns:

   pos: an array of *nposs long integers with the positions associated
        to this key
   NULL: the key was not found   

   NOTE: the parameter nposs is not an array of integers: it is
   actually an integer variable that is passed by reference. In it you
   must store the number of elements in the array that you return,
   that is, the number of positions associated to the key. The call
   will be something like this:

   int n
   long **poss = index_get(index, key, &n);

   for (int i=0; i<n; i++) {
       Do something with poss[i]
   }

   ANOTHER NOTE: remember that the search for the key MUST BE DONE
   using binary search.

   FURTHER NOTE: the pointer returned belongs to this module. The
   caller guarantees that the values returned will not be changed.

*/
long *index_get(index_t *idx, int key, int *nposs) {
  	idx_data* keyFound;
      if (!idx || !nposs) return NULL;
    
    tempType = idx->type;
    keyFound = (idx_data*) bsearch(&key, idx->idx_datas, idx->nidx, sizeof(idx_data), idx_compare);
	if (!keyFound) {
        *nposs = 0;
        return NULL;
    }
    /* This should never happen but it's a security
    measure in case someone edits this value. */
    if(!(*keyFound).records) {
        *nposs = 0;
        return NULL;
    }
    *nposs = (*keyFound).nrec;
    return (*keyFound).records;
}

/* 
   Closes the index by freeing the allocated resources. No operation
   on the index will be possible after calling this function. 

   Parameters:
   index:  the index the function operates upon

   Returns:
   Nothing

   NOTE: This function does NOT save the index on the file: you will
   have to call the function index_save for this.
*/
void index_close(index_t *idx) {
  	int i;
    if (!idx) return;
    /* Check if there's the idx_datas array to properly free it.
    Its values have pointers that need some freeing, you know. */
    if (idx->idx_datas) { 
        for(i = 0; i < idx->nidx; i++){
            if(idx->idx_datas[i].records) free(idx->idx_datas[i].records);
        }
        free(idx->idx_datas);
    }
    if(idx->path) free(idx->path);
    free(idx);
	return;
}

/*
  Function: long **index_get_order(index_t *index, int n, int* nposs);

  Function useful for debugging but that should not be used otherwise:
  returns the nth record in the index. DO NOT USE EXCEPT FOR
  DEBUGGING. The test program uses it.

   Parameters:
   index:  the index the function operates upon
   n: number of the record to be returned
   key: output parameter: the key of the record
   nposs: output parameter: the number of positions associated to this key
   
   Returns:

   pos: an array of *nposs long integers with the positions associated
        to this key
   NULL: the key was not found   


   See index_get for explanation on nposs and pos: they are the same stuff
*/
long *index_get_order(index_t* idx, int n, int *key, int* nposs) {
  	if (!idx || !nposs) return NULL;
    if (n >= idx->nidx) { 
        return NULL;
    }

    *key = idx->idx_datas[n].key;
    *nposs = idx->idx_datas[n].nrec;
	return idx->idx_datas[n].records;
}