#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "types.h"
#include "game_rules.h"

#define N_RULES 8          /*!< The number of rules */

/**
   Define the function type for the rules
*/
typedef STATUS (*callback_rl)(Game *game);

/**
   List of callbacks for (each rule in the game 
*/

/**
 * @brief It executes the no_rule command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 * @date 05-05-2019
 */
STATUS game_rules_callback_no_rule(Game *game);

/**
 * @brief It executes the turn_on command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 * @date 05-05-2019
 */
STATUS game_rules_callback_turn_on(Game *game);

/**
 * @brief It executes the turn_off command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 * @date 05-05-2019
 */
STATUS game_rules_callback_turn_off(Game *game);

/**
 * @brief It executes the open_link command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 * @date 05-05-2019
 */
STATUS game_rules_callback_open_link(Game *game);

/**
 * @brief It executes the pick command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 * @date 05-05-2019
 */
STATUS game_rules_callback_object_pick(Game *game);

/**
 * @brief It executes the drop command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 * @date 05-05-2019
 */
STATUS game_rules_callback_object_drop(Game *game);

/**
 * @brief It executes the hide_object command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 * @date 05-05-2019
 */
STATUS game_rules_callback_hide_object(Game *game);

/**
 * @brief It executes the show_object command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 * @date 05-05-2019
 */

STATUS game_rules_callback_show_object(Game *game);

static callback_rl game_callback_rl_list[N_RULES] = {
    game_rules_callback_no_rule,
    game_rules_callback_turn_on,
    game_rules_callback_turn_off,
    game_rules_callback_open_link,
    game_rules_callback_object_pick,
    game_rules_callback_object_drop,
    game_rules_callback_hide_object,
    game_rules_callback_show_object
    };

/**
   Callbacks implementation for each rule 
*/

STATUS game_rules_callback_no_rule(Game *game) {
    if(!game) return ERROR;
    
    return OK;
}

STATUS game_rules_callback_turn_on(Game *game) {
    int num_of_spaces = game_get_num_of_spaces(game);
    Id i;
    int j;
    int object_idx;
    Id *objects;
    int num_of_objects = 0;
    if (!game) return ERROR;
    for (i = 1; i <= num_of_spaces; i++) {
        if (game_get_space(game, i) != NULL) {
            num_of_objects += space_get_num_objects(game_get_space(game, i));
        }
    }

    if (num_of_objects == 0) return ERROR;
    objects = (Id *)malloc(num_of_objects*sizeof(Id));

    i = 1;
    for (j = 0; j < num_of_objects; j++) {
        for (; i <= MAX_OBJECTS && game_get_object_from_id(game, i) != NULL; i++) {
            if (Object_get_turned_on(game_get_object_from_id(game, i)) == FALSE) {
                objects[j] = i;
                break;
            }
        }
    }

    srand(time(NULL));
    object_idx = (rand() & num_of_objects);
    Object_set_turned_on(game_get_object_from_id(game, objects[object_idx]), TRUE);
    free(objects);

    return OK;
}
    
STATUS game_rules_callback_turn_off(Game *game) {
    int num_of_spaces = game_get_num_of_spaces(game);
    Id i;
    Id *objects;
    int j;
    int object_idx;
    int num_of_objects = 0;
    if (!game) return ERROR;
    for (i = 1; i <= num_of_spaces && game_get_space(game, i) != NULL ; i++) {
        num_of_objects += space_get_num_objects(game_get_space(game, i));
    }
    if (num_of_objects == 0) return ERROR;

    objects = (Id *)malloc(num_of_objects*sizeof(Id));

    i = 1;
    for (j = 0; j < num_of_objects; j++) {
        for (; i <= MAX_OBJECTS && game_get_object_from_id(game, i) != NULL; i++) {
            if (Object_get_turned_on(game_get_object_from_id(game, i)) == TRUE) {
                objects[j] = i;
                break;
            }
        }
    }

    srand(time(NULL));
    object_idx = (rand() % num_of_objects);
    Object_set_turned_on(game_get_object_from_id(game, objects[object_idx]), FALSE);
    free(objects);

    return OK;
}

STATUS game_rules_callback_open_link(Game *game) {
    int link_idx;
    Id link_id = NO_ID;
    int num_of_closed_links = 0;
    Id i;
    int j;
    Id *closed_links;
    if (!game) return ERROR;

    for (i = 1; i <= MAX_LINKS && game_get_link_from_id(game, i) != NULL && link_get_open(game_get_link_from_id(game, i)) == FALSE; i++) {
        num_of_closed_links++;
    }

    if (num_of_closed_links == 0) return ERROR;

    closed_links = (Id *)malloc(num_of_closed_links * sizeof(Id));

    i = 1;
    for (j = 0; j < num_of_closed_links; j++) {
        for (; i <= MAX_LINKS; i++) {
            if (game_get_link_from_id(game, i) != NULL && link_get_open(game_get_link_from_id(game, i)) == FALSE) {
                closed_links[j] = i;
                break;
            }
        }
    }

    srand(time(NULL));
    link_idx = (rand() % num_of_closed_links);
    link_id = closed_links[link_idx];
    free(closed_links);
    if (link_get_open(game_get_link_from_id(game, link_id)) == FALSE) {
        link_set_open(game_get_link_from_id(game, link_id), TRUE);
        return OK;
    }   
    return ERROR;
}

STATUS game_rules_callback_object_pick(Game *game) {
    Id player_space = NO_ID;
    Id object_space = NO_ID;
    int object_idx;
    Id idobject = NO_ID;
    Id *objects;
    Id i;
    int j;
    int num_of_objects = 0;
    if (!game) return ERROR;

    player_space = player_get_space(game_get_player(game));
    num_of_objects = space_get_num_objects(game_get_space(game, player_space));
    if (num_of_objects == 0) return ERROR;

    objects = (Id *)malloc(num_of_objects * sizeof(Id));

    i = 1;
    for (j = 0; j < num_of_objects; j++) {
        for (; i <= MAX_OBJECTS && game_get_object_from_id(game, i) != NULL; i++) {
            if (game_get_object_location(game, i) == player_space) {
                objects[j] = i;
                break;
            }
        }
    }

    srand(time(NULL));
    object_idx = (rand() % num_of_objects);
    idobject = objects[object_idx];
    free(objects);
    if(idobject==NO_ID){return ERROR;}

    object_space = game_get_object_location(game, idobject);

    if ((player_space == object_space) && (Object_get_movable(game_get_object_from_id(game, idobject)) == TRUE))
    {
        player_set_object(game_get_player(game), idobject); 
        Object_set_moved(game_get_object_from_id(game, idobject), TRUE);
        game_set_object_location(game, NO_ID, idobject);
        if (game_no_object_illuminated_on_this_space(game, player_space, idobject) == TRUE) {
            space_set_turned_on_object_on_the_space(game_get_space(game, player_space), FALSE);
        }
    }
    else {return ERROR;}
    return OK;
}

STATUS game_rules_callback_object_drop(Game *game) {
    Id player_space = NO_ID;
    int object_idx;
    Id idobject = NO_ID;
    int num_of_objects = 0;
    if (!game) return ERROR;

    player_space = player_get_space(game_get_player(game));
    num_of_objects = player_get_num_of_objects(game_get_player(game));
    if (num_of_objects == 0) return ERROR;

    srand(time(NULL));
    object_idx = (rand() % num_of_objects);
    idobject = player_get_particular_object(game_get_player(game), object_idx);
    if(idobject==NO_ID){return ERROR;}


    game_set_object_location(game, player_space, idobject);
    if (Object_get_turned_on(game_get_object_from_id(game, idobject)) == TRUE) {
        space_set_turned_on_object_on_the_space(game_get_space(game, player_space), TRUE);
    }
    player_delete_object(game_get_player(game), idobject);
    if(player_space == Object_get_first_location(game_get_object_from_id(game, idobject))){
        Object_set_moved(game_get_object_from_id(game, idobject),FALSE);
    }

    return OK;
}

STATUS game_rules_callback_hide_object(Game *game) {
    int num_of_objects = game_get_max_objects(game);
    int numf_of_visible_objects = 0;
    int object_idx;
    Id i;
    int j;
    Id *objects;
    if (!game) return ERROR;

    for (i = 1; i <= num_of_objects; i++) {
        if (Object_get_visibility(game_get_object_from_id(game, i)) == VISIBLE) {
            numf_of_visible_objects++;
        }
    }

    if (numf_of_visible_objects == 0) return ERROR;
    objects = (Id *)malloc(numf_of_visible_objects*sizeof(Id));

    i = 1;
    for (j = 0; j < numf_of_visible_objects; j++) {
        for (; i <= num_of_objects; i++) {
            if (game_get_object_from_id(game, i) != NULL && Object_get_visibility(game_get_object_from_id(game, i)) == VISIBLE) {
                objects[j] = i;
                break;
            }
        }
    }

    srand(time(NULL));
    object_idx = (rand() % numf_of_visible_objects);
    Object_set_visibility(game_get_object_from_id(game, objects[object_idx]), HIDDEN);
    free(objects);

    return OK;
}

STATUS game_rules_callback_show_object(Game *game) {
    int num_of_objects = game_get_max_objects(game);
    int numf_of_hidden_objects = 0;
    int object_idx;
    Id i;
    int j;
    Id *objects;
    if (!game) return ERROR;

    for (i = 1; i <= num_of_objects; i++) {
        if (Object_get_visibility(game_get_object_from_id(game, i)) == HIDDEN) {
            numf_of_hidden_objects++;
        }
    }

    if (numf_of_hidden_objects == 0) return ERROR;
    objects = (Id *)malloc(numf_of_hidden_objects*sizeof(Id));

    i = 1;
    for (j = 0; j < numf_of_hidden_objects; j++) {
        for (; i <= num_of_objects; i++) {
            if (game_get_object_from_id(game, i) != NULL && Object_get_visibility(game_get_object_from_id(game, i)) == HIDDEN) {
                objects[j] = i;
                break;
            }
        }
    }

    srand(time(NULL));
    object_idx = (rand() % numf_of_hidden_objects);
    Object_set_visibility(game_get_object_from_id(game, objects[object_idx]), VISIBLE);
    free(objects);

    return OK;
}

/* Execute randomly chosen function */
STATUS game_rules_execute(Game *game) {
    T_Rule rule = NO_RULE;

    if (!game) return ERROR;

    srand(time(NULL));
    rule = (rand() % N_RULES);

    return (*game_callback_rl_list[rule])(game);
}
