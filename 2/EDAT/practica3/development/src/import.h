/*
    Project: EDAT Lab 3 test program
    File:    import.h
    Author:  Simone Santini
    Rev.     1.0
    Date:    10/02/2019 
    
    This file contains functions that import data from a file and prepares 
    them in a structre ready to be inserted in the table. Note that these
    functions load the whole file in menory, after which some other program
    will insert the data in the table. This is, in general, not a very 
    rational thing to do: much more efficient would it be to read the record
    one by one and, as soon as they are read, store them in the table.
    
    Keep in mind, however, that this file is part of a test suite, and having 
    the data in memory simplifies the task of checking whether they have been
    stored and retrieved correctly in the table.
    
    The functions return a structure with the following fields:
    
    n_rec:   THe number of records in the file.
    n_col:   The number of columns.
    types:   An array of n_cols t_type entries with the type of each columns.
    record:  of type void ***, the element record[i] (0<=i<n_rec) is a 
             pointer to the i-th record; the element record[i][j] 
             (0<=j<n_cols) is a pointer to the value of the jth column of
             the ith record. The value can be recovered depending on the type.
             If INT:
                int q = *((int *) record[i][j]
            if STR:
                char *q = (char *) record[i][j]
    
    This structure is abstract: suitable functions will allow access to its 
    members.
*/
#ifndef ___IMPORT__INCLUDED___
#define ___IMPORT__INCLUDED___

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "type.h"

/*
    Structure that contains the results of the reading
*/

typedef struct _filedata filedata;


/*
    Public Function:  filedata *f_read(char *fname)
    
    Opens the file fname and reads its contents in a filedata structure.
    The file has the following format:
    
    <TYPE1>, <TYPE2>,..., <TYPEN>
    <VAL11>, <VAL12>, ..., <VAL1N>
    <VAL21>, <VAL22>, ..., <VAL2N>
    .
    .
    .
    <VALM1>, <VALM2>, ..., <VALMN>

    where <TYPEi> is the type of the ith column and <VALki> is the value
    of the ith column of the kth record. The numbr of columns (N) and of 
    records (M) are detected during reading.


    The function returns a poiter to a newly allocated filedata structure
    (to be release by calling teh function f_free). Returns NULL if 
    there is an error.
*/
filedata *f_read(char *fname);


/*  
    Function: void f_free(filedata *f);
    
    Releases the space allocated for a filedata structure
*/ 
void f_free(filedata *f); 

/*
    Funciont: int f_records(filedata *fd)
    
    Returns the number of records in the data 
*/
int f_records(filedata *fd);


/*
    Funciont: int f_columns(filedata *fd)
    
    Returns the number of columns in the data 
*/
int f_columns(filedata *fd);

/*
    Function: type_t *f_types(filedata *fd)
    
    Returns an array with the types of the columns of the data.

    WARNING: the array is NOT a copy, it is a pointer to the actual array
    contained in the filedata structure. The caller should not change
    it in any way.
*/
type_t *f_types(filedata *fd);


/*
    Function void **f_vals(filedata *fd, int n)
    
    Returns the values of the nth record read from the file. 
    If 
    
    void **val = f_vals(fd, n);
    
    then vals[i] is a pointer to the value in the ith column of the nth
    record. What this value actually is (int or string) depends on the 
    type of the ith column, which can be obtained by calling f_types

    The function returns NULL if n is greater than the number of records.

    WARNING: the array is NOT a copy, it is a pointer to the actual array
    contained in the filedata structure. The caller should not change
    it in any way.
*/
void **f_vals(filedata *fd, int n);

#endif