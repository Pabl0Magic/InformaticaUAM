/** 
 * @brief It implements the command interpreter
 * 
 * @file command.h
 * @author Profesores PPROG 
 * @version 1.0 
 * @date 20-03-2019 
 * @copyright GNU Public License
 */
#ifndef COMMAND_H
#define COMMAND_H
#define N_CMD 15         /*!< The number of commands */
/**
* @brief Enumeration of the different commmands available to the user, the order has to coincidence with the ones in command.c
* @author Pablo Almarza
* @date: 13-03-2019
*/
typedef enum enum_Command {
  NO_CMD = -1,    /*!< No command */
  UNKNOWN,        /*!< Unknown command */
  EXIT,           /*!< Exit command */
  PICK,           /*!< Pick command */
  DROP,           /*!< Drop command */
  ROLL,           /*!< Roll command */
  INSPECT,        /*!< Inspect command */
  MOVE,           /*!< Move command */
  TURNON,         /*!< Turn on command */
  TURNOFF,        /*!< Turn off command */
  OPENLINK,       /*!< Open link command */
  SHOW,           /*!< Show command */
  HIDE,           /*!< Hide command */
  SAVE,           /*!< Save command */
  LOAD            /*!< Load command */
  } T_Command;
  
/**
* @brief It's basically a scanf for the commands in the promt where it compares the input to the
* to the commands in cmd_to_str
* @return T_Command The command introduced 
* @date: 13-03-2019
*/
T_Command command_get_user_input();

#endif
