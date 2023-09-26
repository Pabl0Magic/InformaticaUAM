/**
 * @brief It defines common types
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000          /*!< The max size of the word */
#define NO_ID -1                /*!< To see thev errors */
#define MAX_OBJ_NAME 7          /*!< Max number of characters an object can have in his name */
#define MAX_DESC 500            /*!< Max number of descriptions */
#define SIZE_NAME 22            /*!< Max number of characters te game can have */
/**
 * @brief defines the type Id which is used as a way to differenciate simple integers and variables onlyused for Ids
 * 
 */
typedef long Id;

/**
 * @brief boolean type of variable used for checking empty functions or if a statement is true
 * 
 */
typedef enum { 
    FALSE,      /*!< Identifier if something is false */
    TRUE        /*!< Identifier if something is true */
} BOOL;

/**
 * @brief Usually used for error control in different functions, the movements and actions of the player are checked and returned using this ADT
 * 
 */
typedef enum { 
    ERROR,      /*!< Some error */
    OK          /*!< No error */ 
} STATUS; 

/**
 * @brief the destination of the player used in the commandss
 * 
 */
typedef enum { 
    N,      /*!< North identifier */
    S,      /*!< South identifier */
    E,      /*!< East identifier */
    W,      /*!< West identifier */
    U,      /*!< Up identifier */
    D       /*!< Down identifier */
} DIRECTION;

BOOL color;     /*!< Color Identifier to work with the illumination */

#endif

