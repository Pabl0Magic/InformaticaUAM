/** 
 * @brief It defines the dialogue module functionality
 * 
 * @file dialogue.h
 * @author Rodrigo Juez and Miguel Arnaiz
 * @version 3.0 
 * @date 04-05-2019
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "types.h"
#include "command.h"
#include "die.h"
#include "space.h"
/**
 * @brief The Dialogue module consists of the previous command done including the direction and the object
 * 
 * @author Rodrigo
 * @date 21-03-2019
 */
typedef struct _Dialogue Dialogue;

/**
 * @brief This is Redone to avoid circular dependencies
 * 
 * @author Mariusz Wiśniewski 
 * @date 21-03-2019
 */
typedef struct _Game Game;
/*soy consciente de que hay que comentarlas*/

/**
 * @brief Allocates the necessary memory and initializes 
 * all the fields to work with Dialogue
 * @author Miguel Arnaiz
 * 
 * @return Dialogue* The memory allocated 
 * @date: 04-05-2019
 */
Dialogue* Dialogue_ini();

/**
 * @brief It will destroy the memory that was allocated for Dialogue
 * @author Miguel Arnaiz
 * 
 * @param dialogue The dialogue structure
 * @date: 04-05-2019
 */
void Dialogue_destroy(Dialogue *dialogue);

/**
 * @brief Interactive messages with the player and unique ones for every case,
 * all commandshave an answer from this function
 * @author Miguel Arnaiz
 * 
 * @param game The game structure
 * @param dialogue The dialogue structure
 * @param action The command that the player does
 * @param success OK or ERROR depending on if the command was executed correctly
 * @return char* A string of characters that interact with the player
 * @date: 04-05-2019
 */
char* Dialogue_interact_with_player(Game* game, Dialogue *dialogue, T_Command action, STATUS success);

/**
 * @brief Set if a command have been repeated to produce a different answer
 * @author Miguel Arnaiz
 * 
 * @param dialogue The dialogue structure
 * @param rep The command printed by the user
 * @return STATUS OK if it goes as expected
 */
STATUS Dialogue_set_repeated(Dialogue *dialogue, T_Command rep);

/* Declaration of several functions from game */


/**
 * @brief Gets the game particular_link
 * @author Miguel Arnaiz
 * 
 * @param game The game structure
 * @return char* The particular link field
 * @date 04-05-2019
 */
char* game_get_particular_link(Game *game);

/**
* @brief Gets the name of the last picked object used for displaying in feedback and log
* @author Rodrigo Juez
* 
* @param game The game structure
* @return char* The name of the object
* @date: 20-03-2019
*/
char *game_get_particular_obj(Game *game);

/**
* @brief Gets the die's structure
* @author Rodrigo Juez
*
* @param game The game structure
* @return the die's struct
* @date: 13-03-2019
*/
Die *game_get_die(Game *game);

/**
* @brief Getter of the space's struct for the game implementation
* @author Rodrigo Juez
*
* @param game The game structure
* @param id The space id
* @return Space* The space we want
* @date: 13-03-2019
*/
Space* game_get_space(Game* game, Id id);


/**
 * @brief Getter of the player location
 * @author Rodrigo Juez
 *
 * @param game The game structure
 * @return Id The id of the space where the player is
 * @date: 13-03-2019
 */
Id game_get_player_location(Game* game);



#endif
