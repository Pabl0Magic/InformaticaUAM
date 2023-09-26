#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "types.h"

/**
 * @brief Manages an array of Id's and an integer to know how much id's we got stored
 * 
 */
struct _Set
{
    Id array_ids[MAX_IDS];              /*!< array_ids Array where the ids are stored */    
    int num_ids;                        /*!< num_ids Number of ids stored */
};

Id set_obtain_Id_by_position(Set *s, int index){
    if(!s || (index >= s->num_ids) || (index < 0)){return NO_ID;}
    
    return s->array_ids[index];
}

/* Allocate the memory needed for initialise the module*/
Set *set_ini(){
    Set *s=NULL;
    int i;

    s=(Set*)malloc(sizeof(Set));
    if(!s){ 
        return NULL;
    }

    s->num_ids=0;
    for(i=0; i<MAX_IDS; i++){
        s->array_ids[i] = NO_ID;
    }

    return s;
}


/* Destroy the memory allocated for the module */
void set_destroy(Set *s){
    if(s){
        free(s);
        s = NULL;
    }
}

/* Add a new thing to the array by passing its id*/
STATUS set_add(Set *s, Id id){
    if(!s){return ERROR;}
    if(set_isFull(s) || id==NO_ID){return ERROR;}
    s->array_ids[s->num_ids]=id;
    s->num_ids++;
    return OK;
}

/* Check if it is full */
BOOL set_isFull(Set *s){
    if(!s || s->num_ids==MAX_IDS){return TRUE;}
    return FALSE;
}

/* Delete the thing from the array by passing as an argument his id */
STATUS set_del(Set *s, Id id) {

    int i=0, j=0;
    
    if(!s || id==NO_ID){return ERROR;}
    if(s->num_ids==0 || !s || id==NO_ID) return ERROR;
    for(i=0; i< s->num_ids; i++){
        if(s->array_ids[i]==id){            
            for(j = i; j < s->num_ids; j++){
                s->array_ids[j] = s->array_ids[j+1];
            }
            
            s->num_ids--;
            return OK;
        }/*when an Id is deleted the whole array is moved to be all compacted without empty spaces in the middle*/
    }
    return ERROR;
}

/* It gets the number of ids stored in the array*/
int set_get_numIds(Set *s){
    if (!s){
        return -1;
    }
    
    return s->num_ids;
}

/* Returns if a set is located in that specific set */
BOOL set_find(Set *set, Id id){
    int i;

    if(!set || id ==NO_ID){
        return FALSE;
    }

    for( i = 0; i < set->num_ids; i++)
    {
        if(set->array_ids[i] == id){
            return TRUE;
        }
    }
    /*finds the id but only returns a boolean variable*/
    return FALSE;
}

/* Print all the information */
STATUS set_print(FILE *pf, Set *s){
    int i;
    if(!s || !pf) {return ERROR;}
    if(s->num_ids == 0){fprintf(pf, "Set Empty\n"); return OK;}
    fprintf(pf, "Set with %d elements: ", s->num_ids);
    for(i=0; i<(s->num_ids); i++){
        fprintf(pf, "%ld ", s->array_ids[i]);
    }
    return OK;
}
