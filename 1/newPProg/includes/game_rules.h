/** 
 * @brief It defines the game_rules' functions and rules implementation
 * 
 * @file game_rules.h
 * @author Mariusz Wiśniewski
 * @version 1.0 
 * @date 25-04-2019
 * @copyright GNU Public License
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H


/**
* @brief Enumeration of the different commmands available as game rules
* @author Mariusz Wiśniewski
* @date: 27-04-2019
*/
typedef enum enum_Rule {
  NO_RULE,     /*!< No command */
  TURN_ON,          /*!< Turn on command */
  TURN_OFF,         /*!< Turn off command */
  OPEN_LINK,        /*!< Open link command */
  PICK_OBJECT,      /*!< Pick object command */
  DROP_OBJECT,      /*!< Drop object command */
  HIDE_OBJECT,      /*!< Hide object command */
  SHOW_OBJECT       /*!< Show object command */
  } T_Rule;

BOOL executed;  /*!< Inform if the function is executed */

/**
 * @brief It executes a random game rule
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure
 * @return STATUS OK if it goes as expected
 * @date: 25-04-2019
 */
STATUS game_rules_execute(Game *game);

#endif