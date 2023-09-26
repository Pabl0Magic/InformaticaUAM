/** 
 * @brief It defines a textual graphic engine
 * 
 * @file graphic_engine.h
 * @author Profesores PPROG, Rodrigo Juez and Mariusz Wiśniewski
 * @version 1.0 
 * @date 23-03-2019
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"
#include "die.h"
#define MAX_TXT 8 /*!< Max number of characters that can be written */

/**
 * @brief It manages the parameters
 * to print the game
 * 
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Initializes the screen printing the map, description, banner, help and feedback
 * to different coordinates in the screen
 * @author Rodrigo Juez
 *
 * @return Graphic_engine* 
 * @date: 13-03-2019
 */
Graphic_engine* graphic_engine_create();
/**
 * @brief This frees the struct of the graphic engine
 * @author Rodrigo Juez
 *
 * @param ge The graphic engine structure 
 * @date: 13-03-2019
 */
void graphic_engine_destroy(Graphic_engine *ge);
/**
 * @brief Prints the objects of the player in two lines, the description area and the feedback
 * @author Rodrigo Juez
 *
 * @param ge The graphic engine structure 
 * @param game The game structure 
 * @date: 13-03-2019
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
