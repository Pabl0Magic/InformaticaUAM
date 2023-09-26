/*
    Project: EDAT Lab 3 test program
    File:    import.c
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
    n_cols:  The number of columns.
    types:   An array of n_cols t_type entries with the type of each columns.
    records: of type void ***, the element records[i] (0<=i<n_rec) is a 
             pointer to the i-th record; the element records[i][j] 
             (0<=j<n_cols) is a pointer to the value of the jth column of
             the ith record. The value can be recovered depending on the type.
             If INT:
                int q = *((int *) records[i][j]
            if STR:
                char *q = (char *) records[i][j]
    
    This structure is abstract: suitable functions will allow access to its 
    members.
*/
#include "import.h"
#include <ctype.h>

/*
    Structure that contains the results of the reading
*/

struct _filedata {
    int n_rec;
    int n_col;
    type_t *type;
    void ***record;
};


/***********************************************************************
 *   
 *     AUXILIARY FUNCTIONS 
 * 
 ***********************************************************************/
 

/*
    Internal function:  char **_tokenize(char *str)
    
    Tokenizes a string: returns a series of pointers to the individual
    words in the string.
    
    Several things to notice: the string is modified, so the function 
    doesn't function with a constant parameter. The array of pointers is 
    constituted by pointers that point to parts of the original string,
    so they should not be released individually. For example:
    
    char **ptr = _tokenize(str);
    
    To release the pointers and the string, simply do 
    
    free(ptr[0]);  // this releases str 
    free(ptr);     // this releases ptr
    
    The function returns the array ptr with an extra pointer at the end set to 
    NULL to mark the end of the tokens. That is, the following works:
    
    for (char **p = ptr; *p; p**)
        printf("%s\n", *p);
        
    The tokens must be separated by a comma and an arbitrary number of spaces
    (0 is allowed)

*/
static char **_tokenize(char *str) {
    int n_tok = 1;
    
    while (*str && isspace(*str))
        str++;                     // remove leading blanks
    if (!*str) return NULL;
    
    for (char *q=str; *q; q++) {   // Count the number of tokens
        if (*q == ',') n_tok++;
    }
    n_tok++;
    char **ptr = (char **) malloc(n_tok*sizeof(char *));
    
    int idx = 0;
    ptr[idx++] = str;
    if (n_tok == 1) return ptr;

    for (char *q=str; *q; q++) {
        if (*q == ',') {
            *q++ = 0;
            while (*q && isspace(*q)) 
                *q++ = 0;
            if (*q) ptr[idx++] = q;
        }
//        else if (isspace(*q)) {
//            *q = 0;
//        }
    }
    ptr[idx] = NULL;
    return ptr;
}


/*
    Function: void **_value_parse(char *vline, type_t *type, int n_cols)
    
    Receives a line taken from the text file, the list of types of the table
    and the number of columns. Allocates and returns a list of n_cols pointers
    to the values defined in the line. If the line is inconsistent with the 
    types and n_cols, or if there is some other problem, returns NULL.
    
    The pointers muct be released independently by the caller executing:
    
    void **val = _value_parse(vline, types, n_cols);
    
    for (int i=0; i<n_cols; i++)
        free(val[i]);
    free(val);
*/
static void **_value_parse(char *vline, type_t *type, int n_cols) {
    if (!vline || strlen(vline) < 2)
        return NULL;
    if (vline[strlen(vline)-1]=='\n') vline[strlen(vline)-1] = 0;

    char **svals = _tokenize(strdup(vline));
    
    int n=0;
    for (char **p = svals; *p; p++, n++)
        ;
    if (n != n_cols) {
        fprintf(stdout, "Fatal error in line <<%s>>\nIncorrect numer of columns: is %d, should be %d\n", 
            vline, n, n_cols);
        return NULL;
    }
    
    void **vals = (void **) malloc(n_cols*sizeof(void *));
    for (int i=0; i<n_cols; i++) {
        vals[i] = value_parse(type[i], svals[i]);
    }
    free(svals[0]);
    free(svals);
    return vals;
}


/*
    Function: type_t *_type_parse(char *line, int *ncol)
    
    Parses the line that defines the types of the columns of the table. 
    Returns a newly allocated type array and, in the output parameter ncol,
    the number of columns of the table. 
    
    If there is an error in the line, prints a message and returns NULL.
*/
type_t *_type_parse(char *line, int *ncol) {
   if (!line || strlen(line) < 2) {
        fprintf(stdout, "Error: can't find the types line\n");
        return NULL;
    }
    if (line[strlen(line)-1]=='\n') line[strlen(line)-1] = 0;
    
    char **tp = _tokenize(line);
 
    *ncol = 0;
    for (char **p = tp; *p; p++, (*ncol)++)
        ;
    if (*ncol == 0) {
        fprintf(stdout, "No columns specified\n");
        return NULL;
    }
    
    type_t *type = (type_t *) malloc((*ncol)*sizeof(type_t));
    for (int i=0; i<*ncol; i++) {
        type[i] = type_parse(tp[i]);
        if (type[i] < 0) {
            fprintf(stdout, "Illegal type %s\n", tp[i]);
            free(tp);
            return NULL;
        }            
    }   
    free(tp);
    return type;
}

/***********************************************************************
 *   
 *     PUBLIC FUNCTIONS 
 * 
 ***********************************************************************/

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
filedata *f_read(char *fname) {
    FILE *f = fopen(fname, "r");
    if (!f) {
        fprintf(stdout, "File %s does not exist.\n", fname);
        return NULL;
    }
    
    char buf[10000];
    filedata *fd = (filedata *) malloc(sizeof(filedata));
    fd->type = _type_parse(fgets(buf, 10000, f), &(fd->n_col));
    fd->record = NULL;
    fd->n_rec = 0;
    void **v;
    while(v = _value_parse(fgets(buf, 10000, f), fd->type, fd->n_col)) {
        fd->record = (void ***) realloc(fd->record, (++fd->n_rec)*sizeof(void **));
        fd->record[fd->n_rec-1] = v;
    }
    
    fclose(f);
    return fd;
    
}

/*  
    Function: void f_free(filedata *f);
    
    Releases the space allocated for a filedata structure
*/ 
void f_free(filedata *f) {
    if (!f) return;
    free(f->type);
    for (int i=0; i<f->n_rec; i++) {
        for (int k=0; k<f->n_col; k++)
            free(f->record[i][k]);
        free(f->record[i]);
    }
    free(f->record);
    free(f);
}


/*
    Funciont: int f_records(filedata *fd)
    
    Returns the number of records in the data 
*/
int f_records(filedata *fd) {
    return fd->n_rec;
}

/*
    Funciont: int f_columns(filedata *fd)
    
    Returns the number of columns in the data 
*/
int f_columns(filedata *fd) {
    return fd->n_col;
}


/*
    Function: type_t *f_types(filedata *fd)
    
    Returns an array with the types of the columns of the data.

    WARNING: the array is NOT a copy, it is a pointer to the actual array
    contained in the filedata structure. The caller should not change
    it in any way.
*/
type_t *f_types(filedata *fd) {
    return fd->type;
}

/*
    Function void **f_vals(filedata *fd, int n)
    
    Returns the values of the nth record read from the file (0<=n<fd->n_rec) 
    If 
    
    void **val = f_vals(fd, n);
    
    then vals[i] is a pointer to the value in the ith column of the nth
    record. What this value actually is (int or string) depends on the 
    type of the ith column, which can be obtained by calling f_types

    The function returns NULL if n is greater (or equal. we count from 0) 
    than the number of records.

    WARNING: the array is NOT a copy, it is a pointer to the actual array
    contained in the filedata structure. The caller should not change
    it in any way.
*/
void **f_vals(filedata *fd, int n) {
    if (n>=fd->n_rec) 
        return NULL;
    return fd->record[n];
}


