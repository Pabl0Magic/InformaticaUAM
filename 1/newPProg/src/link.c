/**
 * @brief Link module main
 * 
 * @file link.c
 * @author Miguel Arnaiz
 * 
 * @version 0.1
 * @date 10-03-2019
 * 
 * @copyright Copyright (c) 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

/**
 * @brief Manage the links functionality
 * 
 */
struct _Link{
    Id id_link;                 /*!< id_link Id of the link */
    char name[MAX_OBJ_NAME];    /*!< name The name of the link */
    Id space1;                  /*!< space1 Id of the first space */
    Id space2;                  /*!< space2 Id of the second space */
    BOOL open;                  /*!< open The inks are open always */
};

/*Creates a new link allocating memory with the sent id.*/
Link *link_create(Id id_link){
    Link *link=NULL;

    if(id_link<0) return NULL;

    link = (Link*)malloc(sizeof(Link));
    if(!link) return NULL;

    link->id_link = id_link;
    link->space1 = NO_ID;
    link->space2 = NO_ID;
    link->open = TRUE;

    return link;
}

/*Frees the memory reserved for a link.*/
void link_destroy(Link *l){
    if(l){
        free(l);
    }
}

/*Gets the id of the sent link.*/
Id link_get_id(Link *l){
    if(!l) return NO_ID;
    return l->id_link;
}
/*Gets the name of the sent link.*/
char* link_get_name(Link *l){
    if(!l) return NULL;
    return l->name;
}
/*Sets the name of the sent link.*/
STATUS link_set_name(Link *l, char* name){
    if(!l || !name){
        return ERROR;
    }

    strcpy(l->name, name);

    return OK;
}

/*Gets the id of the space1 of the sent link.*/
Id link_get_space1(Link *l){
    if(!l) return NO_ID;
    return l->space1;
}

/*Gets the id of the space2 of the sent link.*/
Id link_get_space2(Link *l){
       if(!l) return NO_ID;
       return l->space2;
}

Id link_get_oposite(Link *l, Id id){
    if(!l || id == NO_ID) return NO_ID;

    if(id==l->space1) {return l->space2;}
    else if(id==l->space2) {return l->space1;}
    else {return NO_ID;}

}

/*Gets the status of the open of the sent link.*/
BOOL link_get_open(Link *l){
    if(!l) return NO_ID;
    return l->open;
}


/*Sets the link's id to the new one sent.*/
STATUS link_set_id(Link *l, Id id){
    if(!l || id == NO_ID) return ERROR;
    l->id_link = id;
    return OK;
}

/*Sets the space1's id to the new one sent.*/
STATUS link_set_space1(Link *l, Id space1){
    if(!l || space1 == NO_ID) return ERROR;
    l->space1 = space1;
    return OK;
}

/*Sets the space2's id to the new one sent.*/
STATUS link_set_space2(Link *l, Id space2){
    if(!l || space2 == NO_ID) return ERROR;
    l->space2 = space2;
    return OK;
}

/*Sets the bool open to the new one sent. (openning or closing the link)*/
STATUS link_set_open(Link *l, BOOL open){
    if(!l) return ERROR;
    l->open = open;
    return OK;
}

/*Prints the link sent*/
STATUS link_print(FILE *pf, Link *l){
    if(!pf || !l) return ERROR;

    fprintf(pf, "Link id: %ld\n", l->id_link);
    fprintf(pf, "Space1 id: %ld\n", l->space1);
    fprintf(pf, "Space2 id: %ld\n", l->space2);
    fprintf(pf, "Open bool: %d\n", l->open);

    return OK;

}