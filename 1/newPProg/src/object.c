/** 
 * @brief It tests object module
 * 
 * @file object.c
 * @author Pablo Almarza and Rodrigo Juez
 * @version 2.0 
 * @date 10-03-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "game.h"

/**
  * @brief An object structure that consists of:
  * a string for the object's name,
  * object's id of Id type,
  * a string for the description of the object.
  */ 
struct _Object
{
    Id id;                                  /*!< id The id of the object */
    Id firstloc;                            /*!< firstloc The id of the first location of a object */
    char name[MAX_OBJ_NAME];                /*!< name The name of the object */
    char description[MAX_DESC];             /*!< description The desciption of the object */
    char descriptionalt[MAX_DESC];          /*!< descriptionalt The second desciption of the object shown when it has been moved */
    char descriptionilu[MAX_DESC];          /*!< descriptionilu The desciption when the object is illuminated*/
    T_Object_visibility visibility;         /*!< visibility The visibility status of the object */
    BOOL illuminate_space;                   /*!< illuminate_space The information if the object can illuminate a space */
    BOOL turned_on;                         /*!< turned_on TRUE if it is turned */
    Set *open_link;                         /*!< open_link the link that the object can open */
    BOOL movable;                           /*!< movable TRUE if it can be moved from its original location */
    BOOL moved;                             /*!< moved TRUE if it has been moved from its original location */
    Id cantmove;                            /*!< cantmove The id of a space that an object can't go thorugh */
};

/* It gets the id of a link that can be opened by the object */
Set* Object_get_open_link(Object *a) {
    if (!a) {
        return NULL;
    }
    return a->open_link;
}

/* It sets the id of a link that can be opened by the object */
STATUS Object_set_open_link(Object *a, Id link_id) {
    if (!a || link_id==NO_ID) {
        return ERROR;
    }

    set_add(a->open_link, link_id);
    
    return OK;
}

/*It gets the description of the object */
char* Object_get_description(Object *object){
    if(!object){return NULL;}
    return object->description;
}


/* It sets a new descrption for the object */
STATUS Object_set_description(Object *object, char *desc){
    if(!object || !desc){return ERROR;}
    strcpy(object->description, desc);
    return OK;
}

/*It gets the second description of the object */
char* Object_get_second_description(Object *object){
    if(!object){return NULL;}
    return object->descriptionalt;
}


/* It sets the second description for the object */
STATUS Object_set_second_description(Object *object, char *descalt){
    if(!object || !descalt){return ERROR;}
    strcpy(object->descriptionalt, descalt);
    return OK;
}

/*It gets the second description of the object */
char* Object_get_illuminated_description(Object *object){
    if(!object){return NULL;}
    return object->descriptionilu;
}


/* It sets the second description for the object */
STATUS Object_set_illuminated_description(Object *object, char *descilu){
    if(!object || !descilu){return ERROR;}
    strcpy(object->descriptionilu, descilu);
    return OK;
}

/* Allocates the memory for the object module */
Object *Object_create(Id id)
{
    Object *newObject = NULL;

    newObject = (Object*)malloc(sizeof(Object));

    if (newObject == NULL)
        return NULL;

    newObject->id = id;
    newObject->cantmove=NO_ID;
    newObject->name[0]='\0';
    strcpy(newObject->description, "");
    newObject->visibility = VISIBLE;
    newObject->illuminate_space = FALSE;
    newObject->turned_on = FALSE;
    newObject->open_link=set_ini();
    

    return newObject;
}

Id Object_get_cantmove(Object* a){
    if(!a) return NO_ID;

    return a->cantmove;
}

STATUS Object_set_cantmove(Object* a, Id cantmove){
    if(!a) return ERROR;

    a->cantmove=cantmove;

    return OK;
}

/* It will free the memory allocated for the object */
STATUS Object_destroy(Object *a)
{
    if (!a)
    {
        return ERROR;
    }
    set_destroy(a->open_link);
    free(a);
    return OK;
}

/* It sets the id of the object */
STATUS Object_set_ID(Object *a, Id id)
{
    if (!a || id==NO_ID)
    {
        return ERROR;
    }
    a->id=id;
   
    set_destroy(a->open_link);
    return OK;
}

/* It sets the object's name */
STATUS Object_set_name(Object *a, char *name)
{
    if (!a || !name)
    {
        return ERROR;
    }

    if (!strcpy(a->name, name))
    {
        return ERROR;
    }

    return OK;
}

/* It gets the object's name */
char *Object_get_name(Object *a)
{
    if (!a)
    {
        return NULL;
    }
   
    return a->name;
}

/* It gets the object's id*/
Id Object_get_id(Object *a)
{
    if (!a)
    {
        return NO_ID;
    }
    return a->id;
}

/* Prints all the information */
STATUS Object_print(Object *a)
{
    if (!a) return ERROR;

    fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", a->id, a->name);
    
    return OK;
}

/* Gets the object's visibility status */
T_Object_visibility Object_get_visibility(Object *a) {

    if (!a) return NO_STATUS;

    return a->visibility;
}

/* Sets the object's visibility status */
STATUS Object_set_visibility(Object *a, T_Object_visibility vis) {

    if (!a || vis == NO_STATUS) return ERROR;
    a->visibility = vis;
    return OK;
}

/* Gets the value of illuminate_space field */
BOOL Object_get_illuminate_space(Object* a) {

    if (!a) return FALSE;

    return a->illuminate_space;
}

/* Sets the value of illuminate_space field */
STATUS Object_set_illuminate_space(Object* a, BOOL ilum) {

    if (!a) return ERROR;
    a->illuminate_space = ilum;
    return OK;
}

/* Gets the information if an object is turned on */
BOOL Object_get_turned_on(Object *a) {
    if (!a) return FALSE;

    return a->turned_on;
}

/* Sets the information if an object is turned on */
STATUS Object_set_turned_on(Object *a, BOOL turn) {
    if (!a || (turn == TRUE && Object_get_illuminate_space(a) == FALSE)) return ERROR;
    a->turned_on = turn;
    return OK;
}


/* Set the first location of a object */
STATUS Object_set_first_location(Object *a, Id firstloc) {
    if (!a || firstloc == NO_ID) {
        return ERROR;
    }
    
    a->firstloc = firstloc;

    return OK;
}
/* Get the first location of a object */
Id Object_get_first_location(Object *a) {
    if (!a) {
        return NO_ID;
    }

    return a->firstloc;
}

/*Get if an object can be moved*/
BOOL Object_get_movable(Object *a){
    if(!a){
        return FALSE;
    }
    return a->movable;
}
/*Get if an object has been moved*/
BOOL Object_get_moved(Object *a){
    if(!a){
        return FALSE;
    }/*Get if an object can be moved*/

    return a->moved;
}

/*Set if an object can be moved*/
STATUS Object_set_movable(Object *a, BOOL movable){
    if(!a){
        return ERROR;
    }
    a->movable=movable;
    return OK;
}

/*Set if an object can be moved*/
STATUS Object_set_moved(Object *a, BOOL moved){
    if(!a){
        return ERROR;
    }
    a->moved=moved;
    return OK;
}