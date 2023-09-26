/**
 * @brief Create a Player module that integrates the necessary functionality to manage
 * players, also in a similar way as the player module does for spaces. In particular,
 * players must be implemented as a data structure with the following fields:
 * identification, name, location (a player identifier where the player is located) and
 * an object (storing the object identifier the player is carrying). In addition, it must
 * be included the necessary functions to create and destroy players (create and
 * destroy), change the values of their fields (set and get) and print the content
 * (print) as in the previous case.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "player.h"
#include "object.h"
#include "space.h"
#include "set.h"

struct _player
{
    Id id;                                  /*!< id The id of the player */
    char name[WORD_SIZE + 1];               /*!< name The name of the player */
    Inventory* objects;                     /*!< objects Pointer to inventory structure */
    Id space;                               /*!< space The space where the player is */
};

/* Create the memory for the player */
player *player_create(Id id)
{

    player *newplayer = NULL;

    newplayer = (player *)calloc(1, sizeof(player));

    if (newplayer == NULL)
        return NULL;

    newplayer->id = id;
    newplayer->name[0] = '\0';

    newplayer->objects = inventory_create();
    newplayer->space = NO_ID;

    return newplayer;
}

/* Free the memory */
STATUS player_destroy(player *player)
{
    if (!player)
        return ERROR;

    inventory_destroy(player->objects);
    free(player);
    player = NULL;
    return OK;
}

/* Set an object to the player */
STATUS player_set_object(player *player, Id object_id)
{
    if (!player || !player->objects)
        return ERROR;

    inventory_set_object_to_inventory(player->objects, object_id);

    return OK;
}

/* Set the space where the player will be */
STATUS player_set_space(player *player, Id id)
{
    if (!player || id==NO_ID)
        return ERROR;
    player->space = id;

    return OK;
}

/* Set the name of the player */
STATUS player_set_name(player *player, char *name)
{
    if (!player || !name)
        return ERROR;

    if (!strcpy(player->name, name))
    {
        return ERROR;
    }

    return OK;
}

/* Get the name of the player */
const char *player_get_name(player *player)
{
    if (!player)
    {
        return NULL;
    }
    return player->name;
}

/* Get the id of the player */
Id player_get_id(player *player)
{
    if (!player)
    {
        return NO_ID;
    }
    return player->id;
}

/* Get the object of the player */
Inventory* player_get_objects(player *player)
{
    if (!player || !player->objects)
    {
        return NULL;
    }
    return player->objects;
}

/* Get an object by its id */
Id player_get_particular_object(player* player, int num) {

    if (!player || !player->objects) {
        return NO_ID;
    }

    return inventory_get_object_from_inventory(player->objects, num);
}

/* Delete an object that the player is carrying */
STATUS player_delete_object(player* player, Id object_id) {

    if (!player || player_get_num_of_objects(player) < 1) {
        return ERROR;
    }

    inventory_delete_object(player->objects, object_id);

    return OK;
}

/* Get the njmber of objects that the player has */
int player_get_num_of_objects (player* player) {

    if (!player || !player->objects) {
        return -1;
    }

    return inventory_get_number_objects(player->objects);
}

/* Get the space where the player is */
Id player_get_space(player *player)
{
    if (!player) return NO_ID;
    
    return player->space;
}

/* Print the information */
STATUS player_print(player *player)
{
    if (!player)
    {
        return ERROR;
    }

    fprintf(stdout, "--> player (Id: %ld; Name: %s)\n", player->id, player->name);
    return OK;
}

BOOL player_obj_find(player *player, Id object){
    if(!player || object==NO_ID) return FALSE;
    return inventory_find_object(player->objects, object);
}