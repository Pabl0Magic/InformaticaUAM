/*
    Project: EDAT Lab 3 test program
    File:    table.h
    Author:  Simone Santini
    Rev.     1.0
    Date:    10/13/2019  (check it out: it's Sunday! 
                          and I am here, working for you.
                          Praise to the commmitted professor.)
    
    
    This file defines the structure table and the functions that operate
    on it. There functions are *not* implemented in the file table.c: that
    file contains only empty functions. Implementing these function is part 
    of your assignment.
    

    A table is a file in which the data are stored in records and columns using 
    a binary format, that is, using the same format used in central memory. 
    
    The general schema, apart from the creation of the table is that once a
    table is open, its information is kept in a structure in central memory, 
    and that then the table is explored one record at the time. Note that the
    table_read_record function returns the position in the file where the 
    next record is to be read. The function reads the record in, but it doesn't 
    return any value: the function table_get_col must be called to return
    a pointer to the values, to be read and interpreted according to their 
    type as specified by the return value of table_types.
    
    In this example, we open a table, read and print its contents (see the 
    comments to the function for details on their use).
    
    table_t *tb = table_open("mytable.dat");
    int ncols = table_ncols(tb);
    type_t *tp = table_types(tb);
    long pos = table_first_pos(tb);
    
    while (pos > 0) {
        pos = table_read_record(tb, pos);    
        for (int i=0; i< table_ncols(tb); i++) {
            void *val = table_get_col(tb, i);
            print_value(stdout, tp[i], val);
            printf("  ");
        }
        printf("\n");
    }
    table_close(tb);
    
    The function print_value is defined in type.h. Alternatively, one can 
    do the printing "by hand", interpreting the type (this is NOT the 
    recommended method, as it makes it harder to extend the table to other 
    data types, I put it here as an example of how to work with pointers.)

    if (tp[i] == INT)
        printf("%d  ", *((int *) val));
    else if (tp[i] == STR)
        printf("%s  ", (char *) val);
    else if ...
       ....

*/

#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"

/*
    Table structure, defined here abstractly. The complete definition is in 
    table.c
*/

typedef struct table_ table_t;


/* 
    void table_create(char* path, int ncols, type_t* types);

    Stores an empty table in a newly created file.

    Note that this function does not return any value nor does it do anything 
    in memory. It creates a new file, stores in it a header that indicates
    the number of columns, the types of these columns, and that the table 
    has 0 records. Then closes the file and returns.
    
    Parameters:
    path:    path name (referred to the current directory) of the file
             where the table is to be stored.
    ncols:   number of columns of the table.
    types:   array of ncols elements of type type_t with the type of each
             one of the columns (see type.h and type.c for details on the 
             types recognized by the table).
    
    Returns:
    Returns:
        1: table created
        0: error in creation

    WARNING: if the file specified in path already exists, this function
    erases it and creates a new one. That is, all the data contained in the 
    file will be lost.
*/
int table_create(char* path, int ncols, type_t* types);

/*
    table_t* table_open(char* path)
    
    Opens a table and returns the structure necessary to use it. The file
    <path> must exist for this function to succeeds. This functions 
    allocates a table_t structure and fills in the necessary fields so that
    the other functions defined here can operate on the table.
    
    Parameters:
    path:   path name (referred to the current directory) of the file
            where the table is stored. The file must exist.
            
    Returns:
    A pointer to a newly allocated table_t structure with the information
    necessary to operate on the table (the table is NOT read in memory), or 
    NULL is the file <path> does not exist.
    
    NOTE: The calling program should not release the structure returned
    by this function. Use table_close instead.
*/
table_t* table_open(char* path);

/* 
    void table_close(table_t* table);
    
    Closes a table freeing all the resources allocated. This function must 
    leave the whole system in the state it was before the table was opened:
    all files closed, all memory released.
    
    Note that after calling this function, it will no longer be possible
    to operate on the table <table>.
    
    Parameters:
    table:  The table that we eant to close.
    
    Returns:
        Nothing
*/
void table_close(table_t* table);

/* 
    int table_ncols(table_t* table);

    Returns the number of columns of the table <table>
    
    Parameters:
    table:  The table on which we want to operate.
    
    Returns:
        n>0:    The table has n columns
        n<0:    Incorrect parameter
*/
int table_ncols(table_t* table);


/* 
    type_t*table_types(table_t* table);
    
    Returns an array containing the types of the columns of the table 
    <table>.

    Parameters:
    table:  The table on which we want to operate.
    
    Returns:
    An array of table_ncols(table) element. Each element is of type type_t, 
    and contains the type of the corresponding column. For the definition 
    of type_t, see the file type.h/type.c. Returns NULL if the parameter 
    is invalid.
    
    WARNING: The array that is returned is not a copy of the one used 
    internally by these functions, but a pointer to the same array. The 
    caller should not free the pointer returned by this function nor 
    should it modify it in any way.
*/
type_t*table_types(table_t* table);

/* 
    long table_first_pos(table_t* table);

    Returns the position of the file where the first record begin. Calling 
    table_read_record with this value as position will result in reading
    the first record of the table (see the example at the beginning of this 
    file.
    
    Parameters:
    table:  The table on which we want to operate.
    
    Returns:
    n>0:    the first record begins at position n in the file
    n<0:    there is no first record: the table is empty
    n=0:    error in the parameter
*/
long table_first_pos(table_t* table);

/* 
    long table_last_pos(table_t* table);

    Returns the last position of the file, that is, the position where a new
    record will be inserted upon calling table_insert_record. Note that 
    table_insert_record does not use this function, which is used simply to
    give information to the calling program.

    Parameters:
    table:  The table on which we want to operate.
    
    Returns:
    n>0:    the new record begins at position n in the file
    n<=0:   error in the parameter
*/
long table_last_pos(table_t* table);

/* 
    long table_read_record(table_t* table, long pos);
     
    Reads a record that begins at a given position in the table file. 

    Parameters:
    table:  The table on which we want to operate.
    pos:    Position in the file where the record begins. The pos-th byte
            in the file must be the beginning of a record; if it is not, the 
            result of the call will be unpredictable.
            
    Returns:
    n>0:     The next record in the file begins at position n 
    n<0:     No record read, we had already reached the end of the file 
    
    Note: this function reads the record, but it returns no data from that 
    record. Use the function table_get_col to read the data of the record 
    after it has been read.
*/
long table_read_record(table_t* table, long pos);


/*
    void *table_get_col(table_t* table, int col)
    
    Returns the pointer to the data contained in the col-th column of the 
    record currently in memory. The record must have been previpusly read
    using table_read_record. If no record was read in memory, the result
    will be unpredictable.

    Parameters:
    table:  The table on which we want to operate.
    col:    The column that we want to read, 0<=col<ncol,
    
    Returns:
    A pointer to the data that is contained in the column, or MULL if the 
    column number is out of range. The way the data are interpreted 
    depends on the type of the column, as specified by the col-th element
    of the array returned by table_types (see the example at the beginning
    of the file).
*/
void *table_get_col(table_t* table, int col);

/*  void table_insert_record(table_t* table, void** values);

    Inserts a record at the end of the file given the pointers to the 
    values of each column. 
    
    Parameters:
    table:  The table on which we want to operate.
    values: Array of ncol pointers to the data that are to be stored in the 
            record. The element values[i] must be a pointer to a datum of the 
            same type as the i-th column of the file. If this constraint is 
            not respected, the results will be unpredictable.
    
    Returns:
    1: inserted OK 
    0: error
*/
int table_insert_record(table_t* table, void** values);

#endif