#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "die.h"
#include "types.h"

#define MAX_DIE 6       /*!< Max number the die can get */

/**
 * @brief Declaration of the die's structure
 * 
 */
struct _Die{
    Id id;              /*!< Id Id of the die */
    int last_roll;      /*!< last_roll Number of the last roll */
};

/* Allocate the memory for the die */
Die *die_ini(Id id){
    Die *d=NULL;
    srand(time(NULL)); /*makes the seed of the randomness to be the time*/
    d=(Die*)malloc(sizeof(Die));
    d->id=id;
    d->last_roll=0;
    if(!d){ return NULL;} 
    return d;
}

/* Do the functionality of a die (roll) */
STATUS die_roll(Die *d){

    if(!d) return ERROR;
    
    d->last_roll=(rand()%MAX_DIE)+1;
    
    return OK;
}

/* Get the last roll of the die */
int die_get_last_roll(Die *d){
    if(!d)
        return -1;

    return d->last_roll;
}

/* Free the memory used for die module */
void die_destroy(Die *d){
    if(d){
        free(d);
    }
}

/* Print the information */
STATUS die_print(Die *d, FILE *pf){
    if(!d || !pf) {return ERROR;}
    
    fprintf(pf, "Id %ld: %d ",d->id, d->last_roll);
    
    return OK;
}

/* Get the id of the die */
Id get_die_id(Die *d){
    if(!d){
        return NO_ID;
    }
    return d->id;
}
