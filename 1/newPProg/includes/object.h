/** 
 * @brief Object module header
 * 
 * @file object.h
 * @author Pablo Almarza and Rodrigo Juez
 * @version 1.0 
 * @date 13-03-2019
 * @copyright GNU Public License
 */

#include "types.h"
#ifndef OBJECT_H
#define OBJECT_H
#include "set.h"

/**
* @brief Enumeration of the different commmands available to the user, the order has to coincidence with the ones in command.c
* @author Pablo Almarza
* @date: 13-03-2019
*/
typedef enum enum_Visibility {
  NO_STATUS = -1,   /*!< No command */
  HIDDEN,             /*!< Hide object */
  VISIBLE              /*!< Show object */
  } T_Object_visibility;

/**
 * @brief It stores the definitions of the ID of the object which is the place where the item is stored and its name
 * @author  Pablo Almarza
 * @date: 13-03-2019
 */
typedef struct _Object Object;

/**
 * @brief Allocates memory for a new object structure => ID and name
 * @author Pablo Almarza
 *
 * @param id The id of the object 
 * @return Object* The memory allocated
 * @date: 13-03-2019
 */
Object *Object_create(Id id);

/**
 * @brief Gets the space to which the player cannot move carrying the object in the argument
 * @author Rodrigo Juez
 *
 * @param a The object structure
 * @date: 06-05-2019
 */
Id Object_get_cantmove(Object* a);

/**
 * @brief Sets the space you cannot move carrying object a
 * @author Rodrigo Juez
 *
 * @param a The object structure
 * @param cantmove the id of the space you cannot move with object a
 * @date: 06-05-2019
 */
STATUS Object_set_cantmove(Object* a, Id cantmove);
/**
 * @brief Frees the memory assigned to the object pointer previously created
 * @author Pablo Almarza
 *
 * @param a The object structure
 * @date: 13-03-2019
 */
STATUS Object_destroy(Object *a);

/**
 * @brief It changes the previous object's id for a new one which is passed by reference
 * @author Pablo Almarza
 *
 * @param a The object structure
 * @param id The id of the object
 * @return OK if it goes as expected
 * @date: 13-03-2019
 */
STATUS Object_set_ID(Object *a, Id id);

/**
 * @brief Sets a new description of the object overwriting the old one
 * @author Rodrigo Juez
 * 
 * @param object The object structure
 * @param desc New description we want to set
 * @return OK if it goes as expected
 * @date 21-03-2019
 */
STATUS Object_set_description(Object *object, char *desc);

/**
 * @brief Sets the second description of the object overwriting the old one
 * @author Rodrigo Juez
 * 
 * @param object The object structure
 * @param descalt Second description we want to set
 * @return OK if it goes as expected
 * @date 21-03-2019
 */
STATUS Object_set_second_description(Object *object, char *descalt);

/**
 * @brief  It sets the illuminated description for the object
 * @author Pablo Almarza
 * 
 * @param object The object description 
 * @param descilu The description when it is illuminated
 * @return STATUS OK if it goes as expected
 */
STATUS Object_set_illuminated_description(Object *object, char *descilu);

/**
 * @brief Sets a new name for an object
 * @author Pablo Almarza
 * 
 * @param a The object structure
 * @param name The name of the object
 * @return OK if it goes as expected
 * @date: 13-03-2019
 */

STATUS Object_set_name(Object *a, char *name);

/**
 * @brief Getter for the object's id
 * @author Pablo Almarza
 * 
 * @param a The object structure
 * @return Id The id of the object
 * @date: 13-03-2019
 */
Id Object_get_id(Object *a);

/**
 * @brief Returns the description of the object in the argument 
 * @author Rodrigo Juez
 *
 * @param object The object structure
 * @return char* The decription as a string
 * @date 21-03-2019
 */
char* Object_get_description(Object *object);

/**
 * @brief Returns the second description of the object in the argument 
 * @author Pablo Almarza
 *
 * @param object The object structure
 * @return char* The decription as a string
 * @date 21-03-2019
 */
char* Object_get_second_description(Object *object);

/**
 * @brief It gets the illuminated description of the object 
 * @author Pablo Almarza
 * 
 * @param object The object structure
 * @return char* The descriptiom as a string
 */
char* Object_get_illuminated_description(Object *object);

/**
 * @brief Getter for the object's name
 * @author Pablo Almarza
 * 
 * @param a The object structure
 * @return char* The name of the object
 * @date: 13-03-2019
 */
char *Object_get_name(Object *a);

/**
 * @brief Prints the object's id and name in external screen 
 * @author Pablo Almarza
 * 
 * @param a The object structure
 * @return OK if it goes as expected
 * @date: 13-03-2019
 */
STATUS Object_print(Object *a);

/**
 * @brief Get the object's visibility status 
 * @author Mariusz Wiśniewski
 * 
 * @param a The object structure
 * @return T_Object_visibility Object's visibility status
 * @date: 11-04-2019
 */
T_Object_visibility Object_get_visibility(Object *a);


/**
 * @brief Sets the object's visibility status 
 * @author Mariusz Wiśniewski
 * 
 * @param a The object structure
 * @param vis Object's visibility status
 * @return OK if it goes as expected
 * @date: 11-04-2019
 */
STATUS Object_set_visibility(Object *a, T_Object_visibility vis);

/**
 * @brief Gets the information if an object can illuminate a space 
 * @author Mariusz Wiśniewski
 * 
 * @param a The object structure
 * @return BOOL Object's illuminate_space status
 * @date: 11-04-2019
 */
BOOL Object_get_illuminate_space(Object* a);

/**
 * @brief Sets the information if an object can illuminate a space  
 * @author Mariusz Wiśniewski
 * 
 * @param a The object structure
 * @param ilum illuminate_space status
 * @return OK if it goes as expected
 * @date: 11-04-2019
 */
STATUS Object_set_illuminate_space(Object* a, BOOL ilum);

/**
 * @brief Gets the information if an object is turned on  
 * @author Pablo Almarza
 * 
 * @param a The object structure
 * @return BOOL object's turned_on status
 * @date: 11-04-2019
 */
BOOL Object_get_turned_on(Object *a);

/**
 * @brief Sets the information if an object is turned on  
 * @author Pablo Almarza
 * 
 * @param a The object structure
 * @param turn turned_on status
 * @return BOOL object's turned_on status
 * @date: 11-04-2019
 */
STATUS Object_set_turned_on(Object *a, BOOL turn);

/**
 * @brief Sets the first location of the object
 * @author Pablo Almarza
 * 
 * @param a The object structure
 * @param firstloc The first location of the object
 * @return STATUS OK if it goes as expected
 * @date: 15-04-2019
 */
STATUS Object_set_first_location(Object *a, Id firstloc);

/**
 * @brief It gets the first location of an object
 * @author Pablo Almarza
 * 
 * @param a The object structure
 * @return Id Id of the first location
 * @date: 15-04-2019
 */
Id Object_get_first_location(Object *a);

/**
 * @brief Gets the set of ids of links that can be openned with the object
 * @author Miguel Arnaiz
 * 
 * @param a The object structure
 * @return Set* The set we ids of links that can be openned with the object
 * @date: 15-04-2019
 */
Set* Object_get_open_link(Object *a);

/**
 * @brief Adds a new id to the set of object open links.
 * @author Miguel Arnaiz
 * 
 * @param a The object structure
 * @param link_id The new id of the link we want to add to the set of the object open links
 * @return STATUS OK if gone as expected
 * @date: 15-04-2019
 */
STATUS Object_set_open_link(Object *a, Id link_id);

/**
 * @brief It gets if an object can be moved from its original position
 * @author Rodrigo Juez
 * 
 * @param a The object structure
 * @return BOOL TRUE it can be moved
 * @date: 15-04-2019
 */
BOOL Object_get_movable(Object *a);

/**
 * @brief It gets if an object has been moved from its original position
 * @author Rodrigo Juez
 * 
 * @param a The object structure
 * @return BOOL TRUE it has been moved
 * @date: 15-04-2019
 */
BOOL Object_get_moved(Object *a);

/**
 * @brief It sets if an object can be moved from its original location
 * @author Rodrigo Juez
 * 
 * @param a The object structure
 * @param movable if it can be moved
 * @return STATUS OK if everything goes as expected
 * @date: 15-04-2019
 */
STATUS Object_set_movable(Object *a, BOOL movable);

/**
 * @brief It sets if an object has been moved from its original location
 * @author Rodrigo Juez
 * 
 * @param a The object structure
 * @param moved if it has been moved
 * @return STATUS OK if everything goes as expected
 * @date: 15-04-2019
 */
STATUS Object_set_moved(Object *a, BOOL moved);


#endif /* OBJECT_H */

