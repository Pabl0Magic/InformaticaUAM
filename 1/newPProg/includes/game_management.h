/** 
 * @brief It defines the game's functions, commands implementation and game's structure
 * 
 * @file game_management.h
 * @author Rodrigo Juez and Miguel Arnaiz
 * @version 1.0 
 * @date 13-03-2019
 * @copyright GNU Public License
 */

#ifndef GAMEREADER_H
#define GAMEREADER_H
#include "types.h"
#include "game.h"
#include "die.h"

/**
 * @brief Reads a file and starts to add spaces until all the data file is loaded 
 * and the game is created
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @param filename The name of the file
 * @return OK if it goes as expected
 * Date: 13-03-2019
 */
STATUS game_management_load_spaces(Game* game, char* filename);
/**
 * @brief Reads a file and starts to add the objects to their spaces
 * @author Miguel Arnaiz
 * 
 * @param game The game structure
 * @param filename The name of the file
 * @return OK if it goes as expected 
 * Date: 13-03-2019
 */
STATUS game_management_load_objects(Game* game, char* filename);

/**
 * @brief Reads a file and starts to add the links to their spaces
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @param filename The name of the file
 * @return OK if it goes as expected 
 * Date: 13-03-2019
 */
STATUS game_management_load_links(Game* game, char* filename);

/**
 * @brief takes a pointer to a file and writes the game modifiable values
 * @author Rodrigo Juez
 * 
 * @param pf The name of the file
 * @param game The game structure
 * @return OK if it goes as expected 
 * Date: 26-04-2019
 */
STATUS game_management_save(FILE *pf, Game *game);

/**
 * @brief reads the values of the old game from a file and applies to the actual game
 * @author Rodrigo Juez
 * 
 * @param filename The name of the file
 * @param game The game structure
 * @return OK if it goes as expected 
 * Date: 26-04-2019
 */
STATUS game_management_load_previous_game(char* filename, Game *game);


#endif /* GAMEREADER_H */

