/** 
 * @brief It defines the screen
 * 
 * @file screen.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date: 13-03-2019
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__
#include "types.h"    

/**
 * @brief It stores the spot where the different banners and information is placed
 * @author Teacher
 * @date: 13-03-2019
 */
typedef struct _Area Area;

/**
 * @brief creates several areas in the screen delimited by a width and height and in the coordenates designated
 * 
 */
void  screen_init();

/**
 * @brief frees the screen passed by the global variable __data
 * 
 */
void  screen_destroy();

/**
 * @brief prints the whole screen including every space created
 * 
 */
void screen_paint();

/**
 * @brief Gets a string
 * 
 * @param str The string that is needed to print
 */
void  screen_gets(char *str);

/**
 * @brief creates only a portion of the screen delimited by the area and the coordinates
 * 
 * @param x Measure parameter
 * @param y Measure parameter
 * @param width Measure parameter
 * @param height Measure parameter
 * @return Area* The area allocated
 */
Area* screen_area_init(int x, int y, int width, int height);

/**
 * @brief frees a specific area of the screen do not confuse with the whole screen function
 * 
 * @param area The area structure
 */
void  screen_area_destroy(Area* area);

/**
 * @brief eliminates every data from a specific area in the screen, used in other functions to print again with new data
 * 
 * @param area The area structure
 */
void  screen_area_clear(Area* area);

/**
 * @brief resets the cursor to the default location
 * 
 * @param area The area structure
 */
void  screen_area_reset_cursor(Area* area);

/**
 * @brief adds information to the area passed as an argument, it does NOT erase the data which was previosuly in that area
 * 
 * @param area The area structure
 * @param str The string we want to put in the area
 */
void  screen_area_puts(Area* area, char *str);

#endif
