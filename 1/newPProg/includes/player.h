/** 
 * @brief It defines a Player
 * 
 * @file player.h
 * @author Mariusz Wiśniewski
 * @version 1.0 
 * @date 13-03-2019
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "space.h"
#include "set.h"
#include "inventory.h"

/**
 * @brief It can store the place is located in, name, object and Id of the player
 * @author Mariusz Wiśniewski
 * @date: 13-03-2019
 */
typedef struct _player player;

/**
 * @brief Initializes a new player 
 * @author Mariusz Wiśniewski
 * 
 * @param id The id of the player
 * @return player* The memlory allocated
 * @date: 13-03-2019
 */
player *player_create(Id id);

/**
 * @brief Frees the dinamic memory allocated for the player
 * @author Mariusz Wiśniewski
 * 
 * @param player The player structure
 * @return OK if it goes as expected 
 * @date: 13-03-2019
 */
STATUS player_destroy(player *player);

/**
 * @brief Checks if player and the space exist, if so, assign the space to the player
 * @author Mariusz Wiśniewski
 *
 * @param player The player structure
 * @param id The id of the player
 * @return OK if it goes as expected 
 * @date: 13-03-2019
 */
STATUS player_set_space(player *player, Id id);

/**
 * @brief Checks the player, if correct assign the id to the player 
 * @author Mariusz Wiśniewski
 *
 * @param player The player structure
 * @param id The id of the player
 * @return OK if it goes as expected 
 * @date: 13-03-2019
 */
STATUS player_set_ID(player *player, Id id);

/**
 * @brief Assign the name to the player which the user introduced
 * @author Mariusz Wiśniewski
 *
 * @param player The player structure
 * @param name The player's name
 * @return OK if it goes as expected 
 * @date: 13-03-2019
 */
STATUS player_set_name(player *player, char *name);

/**
 * @brief Assign the object to the player
 * @author Mariusz Wiśniewski
 *
 * @param player The player structure
 * @param id The id of the player
 * @return OK if it goes as expected
 * @date: 13-03-2019
 */
STATUS player_set_object(player *player, Id id);

/**
 * @brief Obtains the name to the player introduced by the user
 * @author Mariusz Wiśniewski
 *
 * @param player The player structure
 * @return const char* The name of the player
 * @date: 13-03-2019
 */
const char *player_get_name(player *player);

/**
 * @brief Obtains the ID of the player 
 * @author Mariusz Wiśniewski
 *
 * @param player The player structure
 * @return Id The id of the player
 * @date: 13-03-2019
 */
Id player_get_id(player *player);

/**
 * @brief Get the objects for the player
 * @author Mariusz Wiśniewski
 * 
 * @param player The player structure
 * @return Inventory* The player objects
 */
Inventory* player_get_objects(player *player);

/**
 * @brief Obtains the ADT space from the player aka the position
 * @author Mariusz Wiśniewski
 * 
 * @param player The player structure
 * @return Id The id of the space where the player is
 * @date: 13-03-2019
 */
Id player_get_space(player *player);

/**
 * @brief Gets the number of objects carried by the player
 * @author Mariusz Wiśniewski
 * 
 * @param player The player structure
 * @return int the number of objects carried by the player 
 * @date: 22-03-2019
 */
int player_get_num_of_objects (player* player);

/**
 * @brief Gets the id of a particular object carried by the player
 * @author Mariusz Wiśniewski
 * 
 * @param player The player structure, 
 * @param num The index of an object
 * @return Id id of the particular object carried by the player
 * @date: 22-03-2019
 */
Id player_get_particular_object(player* player, int num);

/**
 * @brief Removes an object from player's inventory
 * @author Mariusz Wiśniewski
 * 
 * @param player The player structure, 
 * @param object_id Id of the object that we want to remove from the inventory
 * @return OK if it goes as expected 
 * @date: 22-03-2019
 */
STATUS player_delete_object(player* player, Id object_id);

/**
 * @brief Prints the player's ID, name, the object assigned and the space (location) in an external screen
 * @author Mariusz Wiśniewski
 * 
 * @param player The player structure
 * @return OK if it goes as expected
 * @date: 13-03-2019
 */
STATUS player_print(player *player);

/**
 * @brief  Finds if the player is carrying an object selected by ID
 * @author Rodrigo Juez
 * 
 * @param player The player structure
 * @param object the Id you want to find
 * @return TRUE if it finds it
 * @date: 13-03-2019
 */
BOOL player_obj_find(player *player, Id object);

#endif /* PLAYER_H */
