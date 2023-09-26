/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Rodrigo Juez, Mariusz Wiśniewski and Pablo Almarza
 * @version 3.0 
 * @date 01-04-2019
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "set.h"
#define MAX_SPACES 100 /*!< Max number of spaces the game can have */
#define FIRST_SPACE 1  /*!< The first space */

/**
 * @brief Is one spot on the board and stores the connections it has with other spaces, the ID and the object on it 
 * @author Mariusz Wiśniewski
 * @date 13-03-2019
 */
typedef struct _Space Space;

/**
 * @brief It gets the set of objects of the sent space
 * @author Miguel Arnaiz
 * 
 * @param space The space structure
 * @return Set* The set of objects or NULL if any error
 * @date 18-04-2019
 */
Set* space_get_objects(Space *space);

/**
 * @brief Gets the information if an space was turned on by an object that was already turned on
 * @author Mariuz Wiśniewski
 * 
 * @param space The space structure
 * @return BOOL TRUE if it has been turned on
 * @date: 04-05-2019
 */
BOOL space_get_turned_on_object_on_the_space(Space *space);

/**
 * @brief Sets the information if an space is turned on by an object that is already turned on
 * @author Mariusz Wiśniewski
 * 
 * @param space The space structure
 * @param value TRUE if the space is turned on by an object
 * @return STATUS OK if it goes as expected
 * @date: 04-05-2019
 */
STATUS space_set_turned_on_object_on_the_space(Space *space, BOOL value);

/**
 * @brief It gets the detailed description of the sent space
 * @author Miguel Arnaiz
 * 
 * @param space The space structure
 * @return char* Return a string which contains the detailed description
 * @date 16-04-2019
 */
char* space_get_detailed_desc(Space *space);

/**
 * @brief It sets a new detailed description to the sent space
 * @author Miguel Arnaiz
 * 
 * @param space The space structure
 * @param detDesc A string with the detailed description we want to set
 * @return STATUS OK if it goes as expected
 * @date 16-04-2019
 */
STATUS space_set_detailed_desc(Space *space, char *detDesc);

/**
 * @brief It gets the description of the space
 * @author Mariusz Wiśniewski
 * 
 * @param space The space structure
 * @return char* Return a string that contains the description of the space
 * @date 16-04-2019
 */
char *space_get_description(Space *space);

/**
 * @brief Set the description of the space
 * @author Mariusz Wiśniewski
 * 
 * @param space The space structure
 * @param desc The description of the space
 * @return STATUS OK if it goes as expected
 * @date 16-04-2019
 */
STATUS space_set_description(Space *space, char *desc);

/**
 * @brief Get the picture
 * @author Pablo Almarza
 * 
 * @param space The space structure
 * @return char* Return a string that contains the picture
 * @date 16-04-2019
 */
char *space_get_draw(Space *space);

/**
 * @brief Set the picture
 * @author Pablo Almarza
 * 
 * @param space The space structure
 * @param gdesc The strings of the picture
 * @return STATUS OK if it goes as expected
 * @date 16-04-2019
 */
STATUS space_set_draw(Space *space, char *gdesc);
/**
 * @brief This function initializes a space to 0
 * @author Rodrigo Juez
 * 
 * @param id The id of the space
 * @return Space* The memory allocated
 * @date 13-03-2019
 */
Space *space_create(Id id);
/**
 * @brief Frees the allocated memory for space
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @return OK if it goes as expected
 * @date 13-03-2019
 */
STATUS space_destroy(Space *space);
/**
 * @brief Checks if the space have an id and return it
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @return Id The id of the space
 * @date 13-03-2019
 */
Id space_get_id(Space *space);
/**
 * @brief Checks if the name is correctly copied
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param name The name of the space
 * @return OK if it goes as expected 
 * @date 13-03-2019
 */
STATUS space_set_name(Space *space, char *name);
/**
 * @brief Returns the space's name
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @return const char* The name of the space
 * @date 13-03-2019
 */
const char *space_get_name(Space *space);
/**
 * @brief   sets the id above the player
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param id The id of the space
 * @return OK if it goes as expected
 * @date 13-03-2019
 */

STATUS space_set_north(Space *space, Id id);
/**
 * @brief returns the id of the space above the player
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @return Id The id of the current space
 * @date 13-03-2019
 */
Id space_get_north(Space *space);
/**
 * @brief Check if south is aggregated to id
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param id The id of the space
 * @return OK if it goes as expected 
 * @date 13-03-2019
 */
STATUS space_set_south(Space *space, Id id);
/**
 * @brief Checks if player can go south
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @return Id The id of the current space
 * @date 13-03-2019
 */
Id space_get_south(Space *space);
/**
 * @brief Check if east is aggregated to id
 * @author Mariusz Wiśniewski
 * 
 * @param space The space structure
 * @param id The id of the space
 * @return OK if it goes as expected 
 * @date 13-03-2019
 */
STATUS space_set_east(Space *space, Id id);
/**
 * @brief Checks if player can go east
 * @author Mariusz Wiśniewski
 * 
 * @param space The space structure
 * @return Id The id of the current space
 * @date 13-03-2019
 */
Id space_get_east(Space *space);
/**
 * @brief When moved to west it is set
 * @author Mariusz Wiśniewski
 * 
 * @param space The space structure
 * @param id The id of the space
 * @return OK if it goes as expected 
 * @date 13-03-2019
 */
STATUS space_set_west(Space *space, Id id);
/**
 * @brief Checks if player can go west
 * @author Mariusz Wiśniewski
 * 
 * @param space The space structure
 * @return Id The id of the current space
 * @date 13-03-2019
 */
Id space_get_west(Space *space);
/**
 * @brief It assigns the object of a player
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param id_object The id of the object
 * @return OK if it goes as expected
 * @date 13-03-2019
 */
STATUS space_set_object(Space *space, Id id_object);
/**
 * @brief It prints the space indicated to the function
 * @author Rodrigo Juez
 * 
 * @param space The space structure 
 * @return OK if it goes as expected
 * @date 13-03-2019
 */
STATUS space_print(Space *space);

/**
 * @brief adds an object to the space, the maximum objects allowed in a space are 4
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param obj The id of the object to be added
 * @return STATUS OK if it goes as expected
 * @date 01-04-2019
 */
STATUS space_add_object(Space *space, Id obj);

/**
 * @brief deletes an object from a space selected by an Id,
 * when an object is deleted the other ones are compacted and there are no empty spots in the middle
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param obj The id of the object we want to delete
 * @return STATUS OK if it goes as expected
 * @date 01-04-2019  
 */
STATUS space_del_object(Space *space, Id obj);
/**
 * @brief gets the cuantity of objects in the space selected
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @return int The number of objects that are in the space
 * @date 01-04-2019  
 */
int space_get_num_objects(Space *space);
/**
 * @brief finds an object selected by the target Id
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param obj The id of the object we want to find
 * @return STATUS OK if it goes as expected
 * @date 01-04-2019
 */
BOOL space_find_object(Space *space, Id obj);

/**
 * @brief gets the id of an object selected by its position, this is useful to print an object whichever is it
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param index The position where the object is in the array
 * @return Id* The id of the object
 * @date 01-04-2019
 */
Id space_get_object_id_from_index(Space *space, int index);

/**
 * @brief gets if the space sent is illuminated or not
 * @author Miguel Arnaiz
 * 
 * @param space The space structure
 * @return BOOL True or False if the space is illuminated or not respectively
 * @date 11-04-2019
 */
BOOL space_get_illuminated(Space *space);

/**
 * @brief sets the sent boolean to the sent space
 * @author Miguel Arnaiz
 * 
 * @param space The space structure
 * @param illuminated Boolean we want to set to illuminated
 * @return STATUS OK if it goes as expected
 * @date 11-04-2019
 */
STATUS space_set_illuminated(Space *space, BOOL illuminated);

/**
 * @brief sets the id in the upper flor to the player
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param id Id of the link
 * @return STATUS OK if it goes as expected
 * @date 11-04-2019
 */
STATUS space_set_up(Space* space, Id id);
/**
 * @brief sets the id of the floor under the player
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @param id Id of the link
 * @return STATUS OK if it goes as expected
 * @date 11-04-2019
 */
STATUS space_set_down(Space* space, Id id);
/**
 * @brief gets the upper space (floor)
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @return Id of the space
 * @date 11-04-2019
 */
Id space_get_up(Space* space);
/**
 * @brief gets the floor under the player
 * @author Rodrigo Juez
 * 
 * @param space The space structure
 * @return Id of the space
 * @date 11-04-2019
 */
Id space_get_down(Space* space);



#endif
