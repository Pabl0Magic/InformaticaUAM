#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

/**
 * @brief Parameters to save all the objects
 * 
 */
struct _Inventory {
    Set* objects;           /*!< objects Pointer to set structure */
    Id max_nObjects;        /*!< max_nObjects Capacity of the inventory */ 
};

/*Allocate the memory*/
Inventory* inventory_create() {
    Inventory* newinventory = NULL;

    newinventory = (Inventory*)malloc(sizeof(Inventory));
    if (!newinventory) {
        return NULL;
    }

    newinventory->max_nObjects = INVENTORY_CAPACITY;

    newinventory->objects = set_ini();

    return newinventory;
}

/*Destroy the memory*/
STATUS inventory_destroy(Inventory* i) {

    if (!i) {return ERROR;}
    set_destroy(i->objects);
    free(i);
    i = NULL;
    return OK;
}

/*Set the new object into the inventory*/
STATUS inventory_set_object_to_inventory(Inventory* i, Id object_id) {
    if(!i || object_id < 0|| inventory_is_full(i) == TRUE) {
        return ERROR;
    }

    if (!set_add(i->objects, object_id)) {
        return ERROR;
    }

    return OK;
}

/*Deletes an object from the inventory*/
STATUS inventory_delete_object(Inventory* inv, Id id) {
    
    if (!inv || id == NO_ID || inventory_find_object(inv, id) == FALSE) {
        return ERROR;
    }

    set_del(inv->objects, id);
    return OK;
}

/*Get an object from the inventory*/
Id inventory_get_object_from_inventory(Inventory* i, int index) {

    Id obj;
    if (!i || inventory_get_number_objects(i) == ERROR) {
        return NO_ID;
    }
    obj = set_obtain_Id_by_position(i->objects, index);
    if (!obj) {
        return NO_ID;
    }
    

    return obj;
}

/*Check if the inventory is full*/
BOOL inventory_is_full(Inventory* i) {
    if (!i) return FALSE;
    if(set_get_numIds(i->objects) == i->max_nObjects){
        return TRUE;
    }

    return FALSE;
}

/*Get the number of objects*/
int inventory_get_number_objects(Inventory* i) {
    if(!i) {
        return ERROR;
    }
    
    return set_get_numIds(i->objects);
}

/*Find an object*/
BOOL inventory_find_object(Inventory* i, Id id) {
    if (!i || id < 0) {
        return ERROR;
    }

    if(!set_find(i->objects, id)) {
        return ERROR;
    }

    return OK;
}

/* Gets the set*/
Set* inventory_get_objects(Inventory* inv) {

    if (!inv || !inv->objects || inventory_get_number_objects(inv) == ERROR) {
        return NULL;
    }

    return inv->objects;
}

/*Print the information*/
STATUS inventory_print(Inventory* i) {

    int aux;

    if(!i) {
        return ERROR;
    }

    for (aux=0; aux<set_get_numIds(i->objects); aux++) {
        fprintf(stdout, "--> Object %d in the inventory: %ld\n", aux, set_obtain_Id_by_position(i->objects, aux));
    }
    return OK;
}