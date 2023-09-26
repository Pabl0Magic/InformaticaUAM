#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "space.h"
#include "set.h"

#define MAX_HORI 7                /*!< Max number of characters read in a row */
#define MAX_VERT 3                /*!< Max number of characters read in a column */

/**
 * @brief Is one spot on the board and stores 
 * the connections it has with other spaces, the ID and the object on it 
 * 
 */
struct _Space{
  Id id;                                /*!< id The id of the space */
  char name[WORD_SIZE + 1];             /*!< name The name of the space */
  Id linknorth;                         /*!< linknorth The north link */
  Id linksouth;                         /*!< linksouth The south link */
  Id linkeast;                          /*!< linkeast The east link */
  Id linkwest;                          /*!< linkwest The west link */
  Id linkup;                            /*!< linkup The upstairs link */
  Id linkdown;                          /*!< linkdown The downstairs link */
  Set *objects;                         /*!< objects Pointer to set structure */
  char gdesc[MAX_VERT*MAX_HORI];        /*!< gdesc Where the drawings are stored */
  char description[MAX_DESC];           /*!< description The description of the space */
  char detailed_desc[MAX_DESC];         /*!< detailed_desc The detailed description of the space */
  BOOL illuminated;                     /*!< ilumanated The space is ilumanted or not */
  BOOL turned_on_object_on_the_space;   /*!< turned_on_object_on_the_space The space is illuminated by an object that was turned on */
};

/*Gets the set of objects of the space*/
Set* space_get_objects(Space *space){
  if(!space) return NULL;
  return space->objects;
}

/*Gets the information if an space was turned on by an object that was already turned on*/
BOOL space_get_turned_on_object_on_the_space(Space *space) {
  if (!space) return FALSE;
  return space->turned_on_object_on_the_space;
}

/*Sets the information if an space was turned on by an object that was already turned on*/
STATUS space_set_turned_on_object_on_the_space(Space *space, BOOL value) {
  if (!space) return ERROR;
  space->turned_on_object_on_the_space = value;
  return OK;
}

/*It gets the detailed description of the space*/
char* space_get_detailed_desc(Space *space){
  if(!space) return NULL;
  return space->detailed_desc;
}

/*It sets a new detailed description to the space*/
STATUS space_set_detailed_desc(Space *space, char *detDesc){
  if(!space || !detDesc) return ERROR;
  strcpy(space->detailed_desc, detDesc);
  return OK;
}

/*It gets the description of the space */
char* space_get_description(Space *space){
    if(!space){return NULL;}
    return space->description;
}


/* It sets a new descrption for the space */
STATUS space_set_description(Space *space, char *desc){
    if(!space || !desc){return ERROR;}
    strcpy(space->description, desc);
    return OK;
}

/* We get the graphic description */
char *space_get_draw(Space *space){
  if(!space){return NULL;}
  if(!(space->gdesc)){return NULL;}
  if(strlen(space->gdesc)<21){return NULL;}
  return space->gdesc;  
  }

/* We set the gdesc to read the design in the data file */
STATUS space_set_draw(Space *space, char *gdesc){
  if(!space || !gdesc){return ERROR;}
  strcpy(space->gdesc, gdesc);
  return OK;
}

/* We allocate memory to generate a new space */
Space* space_create(Id id) {
  Space *newSpace = NULL;

  if (id == NO_ID)
    return NULL;

  newSpace = (Space*) malloc(sizeof (Space));

  if (newSpace == NULL) {
    return NULL;
  }
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->linknorth = NO_ID;
  newSpace->linksouth = NO_ID;
  newSpace->linkeast = NO_ID;
  newSpace->linkwest = NO_ID;
  newSpace->linkup=NO_ID;
  newSpace->linkdown=NO_ID;
  newSpace->illuminated = TRUE;
 
  newSpace->objects = set_ini();
  strcpy(newSpace->description, "");
  strcpy(newSpace->detailed_desc, "");
  strcpy(newSpace->gdesc, "");

  return newSpace;
}

/* We free the memory allocated for the space */
STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);
  free(space);

  
  return OK;
}

/* We set the name of the space  */
STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}

/* We set the north space to id */
STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->linknorth = id;
  return OK;
}

/* We set the south space to id */
STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->linksouth = id;
  return OK;
}

/* We set the east space to id */
STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->linkeast = id;
  return OK;
}

/* We set the west space to id */
STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->linkwest = id;
  return OK;
}

STATUS space_set_up(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->linkup = id;
  return OK;
}

STATUS space_set_down(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->linkdown = id;
  return OK;
}

/* We set the object in a particular space */
STATUS space_set_object(Space* space, Id id_object) {
  if (!space) {
    return ERROR;
  }
  if(!set_add(space->objects, id_object)){
    return ERROR;
  }
  return OK;
}

/* We get the name of the space */
const char *space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

/* We return the id of the space */
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

/* We get the id of the north space */
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->linknorth;
}

/* We get the id of the south space */
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->linksouth;
}

/* We get the id of the east space */
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->linkeast;
}

/* We get the id of the west space */
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->linkwest;
}

Id space_get_up(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->linkup;
}

Id space_get_down(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->linkdown;
}

/* Print the information */
STATUS space_print(Space* space) {
  Id idaux = NO_ID;
  BOOL boolaux = FALSE;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  if (space->objects!=NULL) {
    fprintf(stdout, "Objects: ");
    set_print(stdout, space->objects);
    } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  boolaux = space_get_illuminated(space);
  fprintf(stdout, "---> illuminated space: ");
  if(boolaux == 0){
    fprintf(stdout, "FALSE\n");
  } else {
    fprintf(stdout, "TRUE\n");
  }

  printf("%s", space->gdesc);
  return OK;
}

/*adds an object to the id*/
STATUS space_add_object(Space *space, Id obj){
  if(obj==NO_ID || !space) {return ERROR;}
  return set_add(space->objects,obj);
}

/*deletes an object from a space selected by an Id, when an object is deleted the other ones are compacted and there are no empty spots in the middle*/
STATUS space_del_object(Space *space, Id obj){
  if(obj==NO_ID || !space) {return ERROR;}
  return set_del(space->objects, obj);
}

/*gets the cuantity of objects in the space selected*/
int space_get_num_objects(Space *space){
  if(!space){return -1;}
  return set_get_numIds(space->objects);
}

/*finds an object selected by the target Id*/
BOOL space_find_object(Space *space, Id obj){
  if(obj==NO_ID || !space) {return ERROR;}
  return set_find(space->objects, obj);
}

/*gets the ID in a determined position*/
Id space_get_object_id_from_index(Space *space, int index){
  if(!space || index < 0){return NO_ID;}
  return set_obtain_Id_by_position(space->objects, index);
}

/*gets the boolean of illuminated*/
BOOL space_get_illuminated(Space *space){
  if(!space) return FALSE;
  return space->illuminated;
}

/*sets a new boolean for illuminated*/
STATUS space_set_illuminated(Space *space, BOOL illuminated){
  if(!space) return ERROR;
  space->illuminated = illuminated;
  return OK;
}


