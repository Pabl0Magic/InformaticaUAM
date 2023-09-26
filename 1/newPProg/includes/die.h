/** 
 * @brief It defines the game's functions, commands implementation and game's structure
 * 
 * @file die.h
 * @author Pablo Almarza
 * @version 1.0 
 * @date 13-03-2019
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include "types.h"
/**
 * @brief Declaration of the die's structure
 * @author Pablo Almarza
 * @date: 13-03-2019
 */
typedef struct _Die Die;

/**
 * @brief Initializes the memory and variables allocating it from the Die structure,
 * also sets time to Null for a correct number random generating
 * @author Pablo Almarza
 *
 * @param id The id of the die
 * @return Die The memory allocated 
 * @date: 13-03-2019
 */
Die* die_ini(Id id);

/**
 * @brief Frees the memory allocated for the die struct
 * @author Pablo Almarza
 *
 * @param d The die structure
 * @date: 13-03-2019
 */
void die_destroy(Die *d);

/**
 * @brief It generates a random number between 1 and 6
 * @author Pablo Almarza
 *
 * @param d The die structure
 * @return OK if it goes as expected
 * @date: 13-03-2019
 */
STATUS die_roll(Die *d);

/**
 * @brief Returns the last roll generated by the die_roll function
 * @author Pablo Almarza
 *
 * @param die The die structure
 * @return int The last roll
 * date: 13-03-2019
 */
int die_get_last_roll(Die *die);

/**
 * @brief Function that helps printing the die data in the screen
 * @author Pablo Almarza
 
 * @param d The die structure
 * @param pf The file created
 * @return OK if it goes as expected
 * @date: 13-03-2019
 */
STATUS die_print(Die *d, FILE *pf);

/**
 * @brief This function returns the ID of the die, making it usable for other implementation
 * @author Pablo Almarza
 *
 * @param d The die structure
 * @return Id The last roll
 * @date: 13-03-2019
 */
Id get_die_id(Die *d);

#endif