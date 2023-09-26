/*
    Project: EDAT Lab 3 test program
    File:    table.h
    Author:  Simone Santini
    Rev.     1.0
    Date:    10/13/2019  (check it out: it's Sunday! 
                          and I am here, working for you.
                          Praise to the commmitted professor.)
    
    File in which YOU (Yes: you!) have to implement the functions defined in 
    the file table.h. The functions are defined in this file, but they are 
    elft empty or return dummy values. It is up to you to implement them
    to guarantee the functionality expressed in table.h 
*/
#include "table.h"
#include "type.h"

/*
    This is the structure that contains the data relative to a table. You 
    have to implement it. Keep in mind that all the information about the table 
    that the functions have is in this structure, so you must put in there 
    all that is needed for the correct work of the functions
*/

struct table_ {
    FILE *f;
    type_t *types;
    void **current_record;
    int ncols;
    long first_pos;
    long record_pos;
    long num_records;
};

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
        1: table created
        0: error in creation
    
    WARNING: if the file specified in path already exists, this function
    erases it and creates a new one. That is, all the data contained in the 
    file will be lost.
*/
int table_create(char* path, int ncols, type_t* types) {
    FILE * tableFilePointer;
    int records = 0;
    int i;
    if(!path || !types) return 0;

    tableFilePointer = fopen(path, "wb");
    if(tableFilePointer == NULL) return 0;

    fwrite(&ncols, sizeof(int), 1, tableFilePointer);
    for (i = 0; i < ncols; i++) {
        switch (types[i]) {
            case STR:
            case INT:
            case LLNG:
            case DBL:
                fwrite(&types[i], sizeof(int), 1, tableFilePointer);
                break;
            default:
                fprintf(stderr, "Invalid type for column in create: %d.\n", i);
                break;
        }
    }
    fwrite(&records, sizeof(int), 1, tableFilePointer);

    fclose(tableFilePointer);

    return 1;
}

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
table_t* table_open(char* path) {
    int columns, i, error = 0;

    table_t *table;
    
    if (!path) {
        return NULL;
    }
    /* Do all your usual memory allocation, with their null-checks */
    table = (table_t *) malloc(sizeof(table_t));
    if (!table) {
        return NULL;
    }
    
    /* Try to open the path file in binary mode */
    table->f = fopen(path, "rb+");
    if (!table->f) {
        fprintf(stderr, "File with path %s doesn't exist. Use table_create(%s, ncols, *types) to create a table.\n", path, path);
        free(table);
        return NULL;
    }
    
    /* Fetch and save the columns */
    if(fread(&(table->ncols), sizeof(int), 1, table->f) == 0) return NULL;
    
    /* Now fetch the types into an array of type_t */
    table->types = (type_t *) malloc(table->ncols * sizeof(type_t));
    if(fread(table->types, sizeof(int), table->ncols, table->f) == 0) return NULL;

    /* Check the types array to see if it matches our criterias for types */
    for (i = 0; i < table->ncols; i++) {
        if(    table->types[i] != STR 
            && table->types[i] != INT
            && table->types[i] != DBL
            && table->types[i] != LLNG) {
            fprintf(stderr, "Invalid table %s: unrecognized type in column %d\n", path, i + 1);
            error = 1;
        }
    }
    /* Error flag so we can get as many bad columns as there may be */
    if (error == 1) {
        free(table->types);
        fclose(table->f);
        free(table);
        return NULL;
    }
    /*  The current byte the file pointer is pointing to is the position of the records.
    The next one is the position of the first record. 
    Save both to avoid redundant calculations 
    
    Note: num_records is saved inside the RAM memory to avoid reading the file 
          every time a record is inserted. Worth wasting 4 bytes in saving
          your HDD or SSD from eternal doom. */
    table->record_pos = ftell(table->f);
    if(!fread(&(table->num_records), sizeof(int), 1, table->f)){
        free(table->types);
        fclose(table->f);
        free(table);
        return NULL;
    }
    table->first_pos = ftell(table->f);
    
    /* Initialize variables that you need to initialize to avoid segfaults and problems */
    table->current_record = NULL;
    return table;
}

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
void table_close(table_t* table) {
    int i, j;
    
    /* Avoid invalid frees */
    if(!table) {
        return;
    }
    /* Free the current_record saved into memory if there has been any loaded */
    if (table->current_record) {
        for (i = 0; i < table->ncols; i++) {
            /* Avoid invalid frees to null, free each saved pointer */
            if(table->current_record[i]) free(table->current_record[i]);
        }
        /* Free the current_record pointer */
        free(table->current_record);
    }
    /* Do your usual freeing, and set the passed pointer
    to NULL to avoid random values in different setups.
    Checks for nulls to avoid weird invalid frees.
    For example: if an user magically gets these pointers
    with dumped offsets and alike and frees them for
    whatever reason */
    if (table->types) free(table->types);
    if (table->f) fclose(table->f);
    free(table);
    table = NULL;

    return;
}

/* 
    int table_ncols(table_t* table);

    Returns the number of columns of the table <table>
    
    Parameters:
    table:  The table on which we want to operate.
    
    Returns:
        n>0:    The table has n columns
        n<0:    Incorrect parameter
*/
int table_ncols(table_t* table) {
    if(!table) {
        return -1;
    }
    return table->ncols;
}


/* 
    type_t *table_types(table_t* table);
    
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
type_t *table_types(table_t* table) {
    if (!table) {
        return NULL;
    }
    
    return table->types;
}

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
    n<0:    error in the parameter
*/
long table_first_pos(table_t* table) {
    if(!table) {
        return -1L;
    }

    return table->first_pos;
}

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
long table_last_pos(table_t* table) {
    if(!table) {
        return -1L;
    }
    /* Seek the end of the file */
    fseek(table->f, 0, SEEK_END);
    /* We don't have to go back in this file, we can just return 
    the position and this will help us in the read_record routine */
    return ftell(table->f);
}

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
long table_read_record(table_t* t, long pos) {
    int len, i, *num;
    long long *bignum;
    double *dbl;
    char *buf, *aux;
    
    if(!t || pos < 0){
        return -1L;
    }

    /* Go to the desired position and read the length of the tuple */
    fseek(t->f, pos, SEEK_SET);
    if(fread(&len, sizeof(int), 1, t->f) == 0) return -1L;

    /* If there isn't a current_record in memory, allocate it */
    if (!t->current_record) t->current_record = (void **) malloc(t->ncols * sizeof(void *));
    /* If there is a current_record in memory, free its contents */
    else {
        for(i = 0; i < t->ncols; i++){
            if(t->current_record[i]) 
            {
                free(t->current_record[i]);    
            }
        }
    }

    /* Read the whole buffer. Interpret the char* as a byte* */
    buf = (char *) malloc(len);
    if(!buf) return 1;
    if((fread(buf, 1, len, t->f) == 0)) return -1L;

    /* Check and copy every value */
    aux = buf;
    for (i = 0; i < t->ncols; i++) {
        switch (t->types[i]) {
            case STR:
                t->current_record[i] = strdup(aux);
                aux += strlen(aux) + 1;
                continue;
            case INT:
                num = (int*) malloc(sizeof(int));
                *num = *((int*) aux);
                t->current_record[i] = num;
                aux += sizeof(int);
                continue;
            case LLNG:
                bignum = (long long*) malloc(sizeof(long long));
                *bignum = *((long long*) aux);
                t->current_record[i] = bignum;
                aux += sizeof(long long);
                continue;
            case DBL:
                dbl = (double*) malloc(sizeof(double));
                *dbl = *((double*) aux);
                t->current_record[i] = dbl;
                aux += sizeof(double);
                continue;
            default:
                fprintf(stderr, "Invalid type for column in read in column %d\n", i + 1);
                break;
        }
    }
    free(buf);
    return ftell(t->f);
}


/*
    void *table_get_col(table_t* table, int col)
    
    Returns the pointer to the data contained in the col-th column of the 
    record currently in memory. The record must have been previously read
    using table_read_record. If no record was read in memory, the result
    will be unpredictable.

    Parameters:
    table:  The table on which we want to operate.
    col:    The column that we want to read, 0<=col<ncol,
    
    Returns:
    A pointer to the data that is contained in the column, or NULL if the 
    column number is out of range. The way the data are interpreted 
    depends on the type of the column, as specified by the col-th element
    of the array returned by table_types (see the example at the beginning
    of the file).
*/
void *table_get_col(table_t* table, int col) {
    if (!table) return NULL;
    if (table->current_record == NULL || table->ncols < col) return NULL;
    
    return table->current_record[col];
}

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
int table_insert_record(table_t* t, void** values) {
    int i, length = 0;
    char null = '\0';
    void *new_tuple = NULL;
    if (!t || !values) {
        return 0;
    }

    /* Try to get to the last position of the table */
    if (!table_last_pos(t)) return 0;
    /* This function above moves the pointer of the file
    to the end of the file (EOF), we don't need to check
    and we can just use fwrite() */
    
    /* Calculate the total length of the record */
    for (i = 0; i < t->ncols; i++) {
        switch(t->types[i]){
            case INT:
                length += sizeof(int);
                break;
            case STR:
                length += strlen(values[i]) + 1;
                break;
            case LLNG:
                length += sizeof(long long);
                break;
            case DBL:
                length += sizeof(double);
                break;
            default:
                fprintf(stderr, "Error: Invalid type for column %d\n", i);
                break;
        }
    }
    /* Write the total length of the record */
    fwrite(&length, sizeof(int), 1, t->f);

    /* Write each row */
    for (i = 0; i < t->ncols; i++) {
        switch(t->types[i]){
            case INT:
                fwrite(values[i], sizeof(int), 1, t->f);
                break;
            case STR:
                /* Write the string and the NULL terminating character */
                fwrite(values[i], sizeof(char), strlen(values[i]), t->f);
                fwrite(&null, sizeof(char), 1, t->f);
                break;
            case LLNG:
                fwrite(values[i], sizeof(long long), 1, t->f);
                break;
            case DBL:
                fwrite(values[i], sizeof(double), 1, t->f);
                break;
            default:
                break;
        }
    }
    
    /* Add one record to the table before leaving */
    t->num_records++;
    fseek(t->f, t->record_pos, SEEK_SET);
    fwrite(&t->num_records, sizeof(int), 1, t->f);
    return 1;
}
