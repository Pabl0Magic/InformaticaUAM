/** 
 * @brief It defines the set module functionality
 * 
 * @file set.h
 * @author Pablo Almarza and Miguel Arnaiz
 * @version 1.0 
 * @date 22-02-2019
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H
#include "types.h"
#include <stdio.h>
#define MAX_IDS 20 /*!< Max number of ids the set can handle */

/**
 * @brief Manages an array of Id's and an integer to know how much id's we got stored
 * @author Miguel Arnaiz 
 * @date 22-02-2019
 */
typedef struct _Set Set;

/**
* @brief It creates the space to allocate elements
* @author Pablo Almarza
*
* @return memory allocated
* @date 22-02-2019
*/
Set *set_ini();

/**
 * @brief Set the obtain Id by position object
 * @author Miguel Arnaiz 
 * 
 * @param s The set structure
 * @param index The id of the object
 * @return Id The id of the object
 * @date 22-02-2019
 */
Id set_obtain_Id_by_position(Set *s, int index);

/** 
* @brief It destroys the memory allocated for set
* @author Pablo Almarza
*
* @param s Data from the set structure
* @return OK if it all went properly
* @date 22-02-2019
*/
void set_destroy(Set *s);

/**
* @brief It adds a new element to the array and set the number
* of vectors +1
* @author Pablo Almarza
*
* @param s Data from the set structure
* @param id Receive the id of the object that will be added
* @return OK if it all went properly
* @date 22-02-2019
*/
STATUS set_add(Set *s, Id id);

/**
 * @brief checks if it is full
 * @author Miguel Arnaiz 
 * 
 * @param s The set structure
 * @return FALSE or TRUE 
 * @date 22-02-2019
 */
BOOL set_isFull(Set *s);

/**
 * @brief It deletes an element from the array and set the number of vectors -1
 * @author Miguel Arnaiz 
 * 
 * @param s The set structure
 * @param id The id of the object
 * @return OK if it goes as expected 
 * @date 22-02-2019
 */
STATUS set_del(Set *s, Id id);

/** 
* @brief It gets the total number of ids that 
* the array has storaged
* @author Pablo Almarza
*
* @param s The structure of set
* @return The number of ids that are stored in the array
* @date 22-02-2019
*/
int set_get_numIds(Set *s);

/**
 * @brief Print the information
 * @author Miguel Arnaiz 
 * 
 * @param pf The file created
 * @param s The set structure
 * @return OK if it goes as expected
 * @date 22-02-2019
 */
STATUS set_print(FILE *pf, Set *s);

/**
* @brief It gets the position that an object
* has in the array
* @author Pablo Almarza
*
* @param set The structure of set
* @param id The id of the object that we want
* to know where it is in the array
* @return The position of the object as an id (long integer)
* @date 22-02-2019 
*/
BOOL set_find(Set *set, Id id);

#endif
