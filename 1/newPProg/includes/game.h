/** 
 * @brief It defines the game's functions, commands implementation and game's structure
 * 
 * @file game.h
 * @author Rodrigo Juez, Miguel Arnaiz, Mariusz Wiśniewski and Pablo Almarza
 * @version 1.0 
 * @date 18-01-2019
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "player.h"
#include "die.h"
#include "types.h"
#include "link.h"
#define MAX_OBJECTS 40      /*!< The max number of objects that are in the game */
#define MAX_LINKS 100       /*!< The max number of links that are in the game */

/**
 * @brief Manages a command type to know what command is used
 * and strings to manage the direction in the move command and
 * object to manage the commands involving objects
 * 
 */
typedef struct _Dialogue Dialogue;

/**
* @brief Is the basic game's struct, where the object and player(s) are stored and where the board
* with the information is also stored, it also stores the command input
* @author Rodrigo Juez

* @date: 13-03-2019
*/
typedef struct _Game Game;

/* Declarations from dialogue */
Dialogue* Dialogue_ini();
void Dialogue_destroy(Dialogue *dialogue);
STATUS Dialogue_set_repeated(Dialogue *dialogue, T_Command rep);
char* Dialogue_interact_with_player(Game* game, Dialogue *dialogue, T_Command action, STATUS success);

/**
 * @brief If the space was turned on and an object turned it on and then the 
 * object leaves the space, then the space will be turned off again
 * 
 * @param game The game structure
 * @param space_id The id of the space that will be turned off
 * @param object_id The id of the object that was turned on
 * @return BOOL TRUE if the object was turned on in that space
 * @date 03-05-2019
 */
BOOL game_no_object_illuminated_on_this_space(Game *game, Id space_id, Id object_id);

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
 * @brief Sets a new string in the field particular_link
 * @author Miguel Arnaiz
 * 
 * @param game The game structure
 * @param link_name The name of the link we wawnt to store
 * @return STATUS OK if gone as expected
 * @date 04-05-2019
 */
STATUS game_set_particular_link(Game *game, char *link_name);

/**
 * @brief Returns the dialogue of the game
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @return Dialogue* The name of the game
 * @date 04-05-2019
 */
Dialogue* game_get_dialogue(Game *game);

/**
 * @brief Returns the name of the game
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @return char* The name of the game
 * @date 18-01-2019
 */
char* game_get_name(Game* game);

/**
 * @brief sets the name of the game
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @param name the name of the game
 * @return STATUS if the operation was correct
 * @date 18-01-2019
 */
STATUS game_set_name(Game* game, char* name);

/**
 * @brief Returns a specific object selected by the position it was added from the data.dat
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @param position The position of the object
 * @return Object* The object that we want
 * @date 18-01-2019
 */
Object *game_get_object_by_order(Game *game, int position);

/**
* @brief It adds a link useful for GameReader
* @author Rodrigo Juez
*
* @param game The game structure
* @param link The link structure 
* @return OK if it goes as expected
* @date: 20-03-2019
*/
STATUS game_add_link(Game *game, Link *link);

/**
 * @brief returns the link corresponding to that Id returning NULL if invalid ID
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @param id The id of the link
 * @return Link* The link that we want
 * @date: 20-03-2019
 */
Link *game_get_link_from_id(Game *game, Id id);

/**
 * @brief return the link from the array position
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @param index The position of the link
 * @return Link* The link that we want
 * @date: 20-03-2019 
 */
Link *game_get_link_from_index(Game *game, int index);

/**
* @brief Gets the pointer of the player
* @author Rodrigo Juez
*
* @param game The game structure
* @return  player** The player that plays
* @date: 20-03-2019
*/
player *game_get_player(Game *game);

/**
* @brief Gets the array of spaces
* @author Rodrigo Juez
*
* @param game The game structure
* @return Space** The space we want
* @date: 20-03-2019
*/
Space **game_get_spaces(Game *game);

/**
* @brief Gets the last status of the action for displaying it in the log and the feedback
* @author Rodrigo Juez
*
* @param game The game structure
* @return STATUS OK if goes as expected
* @date: 20-03-2019 
*/
STATUS game_get_last_status(Game *game);

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
* @brief It adds an space useful for creating 
* @author Teacher
*
* @param game The game structure
* @param space The space structure
* @return OK if it goes as expected
* @date: 13-03-2019
*/
STATUS game_add_space(Game* game, Space* space);

/**
* @brief Initializes to empty a game struct which is the info with last commands object and player location
* and the spaces it has
* @author Rodrigo Juez
*
* @param game The game structure
* @return OK if it goes as expected
* @date: 20-03-2019
*/
STATUS game_create(Game **game);

/**
* @brief Reads de file data.dat and loads the game. Loads the spaces in the board from a file
* and then sets the player and the object to the position
* assigned to id 0
* @author Rodrigo Juez
*
* @param game The game structure
* @param filename The file created
* @return OK if it goes as expected
* @date: 20-03-2019
*/
STATUS game_create_from_file(Game** game, char* filename);

/**
* @brief Updates the information of the game to the command inserted by the user
* @author Rodrigo Juez
*
* @param game The game structure
* @param cmd The command line
* @return OK if it goes as expected
* @date: 13-03-2019
*/
STATUS game_update(Game* game, T_Command cmd);

/**
* @brief The function frees the memory allocated for the struct of the game
* @author Rodrigo Juez
*
* @param game The game structure
* @return OK if it goes as expected
* @date: 20-03-2019
*/
STATUS game_destroy(Game* game);

/**
* @brief It is useless at the moment because it always returns false.
* It is meant to be implemented in future iterations.
* @author Teacher
*
* @param game The game structure
* @return False if its not over
* @date: 13-03-2019
*/
BOOL game_is_over(Game* game);
/**
* @brief Obtains info about the object and player location and displays,
* it also puts the text prompt
* @author Rodrigo Juez
*
* @param game The game structure
* @date: 13-03-2019
*/
void game_print_data(Game* game);

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
* @brief Returns the cuantity of objects
* @author Rodrigo Juez
*
* @param game The game structure
* @return int The number of max objects
* @date: 13-03-2019
*/
int game_get_max_objects(Game *game);

/**
* @brief Returns the cuantity of spaces
* @author Mariusz Wiśniewski
*
* @param game The game structure
* @return int The number of created spaces
* @date: 28-04-2019
*/
int game_get_num_of_spaces(Game *game);

/**
 * @brief Getter of the player location
 * @author Rodrigo Juez
 *
 * @param game The game structure
 * @return Id The id of the space where the player is
 * @date: 13-03-2019
 */
Id game_get_player_location(Game* game);

/**
* @brief Getter of the object location and saved in the game's struct
* @author Rodrigo Juez
*
* @param game The game structure
* @param id_object The id of the object
* @return Id Id if the soace where the object is
* @date: 13-03-2019
*/
Id game_get_object_location(Game* game, Id id_object);

/**
* @brief It is used in the graphic engine to display the command log
* @author Rodrigo Juez
*
* @param game The game structure
* @return T_Command The last command
* @date: 13-03-2019
*/
T_Command game_get_last_command(Game* game);

/**
 * @brief Get the object's id and stores it in the game's struct
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @param object_id The object id
 * @return Object* The object you want
 * @date: 13-03-2019 
 */
Object *game_get_object_from_id(Game *game, Id object_id);

/**
* @brief It sets the Id of the object to the space selected by the ID in the arguments
* @author Rodrigo Juez
*
* @param game The game structure
* @param id_space The space id
* @param id_object The object id
* @return OK if it goes as expected
* @date: 13-03-2019
*/
STATUS game_set_object_location(Game* game, Id id_space, Id id_object);

/**
* @brief Adds an object to the game struct checking before if theres space for it 
* @author Miguel Arnaiz
*
* @param game The game structure
* @param object The object structure
* @return OK if it goes as expected
* @date: 13-03-2019
*/
STATUS game_add_object(Game *game, Object *object);

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
 * @brief Get an object by its name
 * @author Miguel Arnaiz
 * 
 * @param game The game structure
 * @param name The name of the object
 * @return Object* The object we want to get  or NULL if error
 * @date: 13-03-2019
 */
Object *game_get_object_fromName(Game *game, char *name);

/**
 * @brief Get a link by its name
 * @author Miguel Arnaiz
 * 
 * @param game The game structure
 * @param link_name The name of the link
 * @return Link* The link we want to get or NULL if error
 * @date: 13-03-2019
 */
Link *game_get_link_fromName(Game *game, char *link_name);


#endif
