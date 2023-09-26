/** 
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * 
 * @file game.c
 * @author Rodrigo Juez, Mariusz Wiśniewski, Miguel Arnaiz and Pablo Almarza
 * @version 7.0 
 * @date 13-03-2019 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_management.h"
#include "object.h"
#include "player.h"
#include "set.h"
#include "space.h"
#include "die.h"
#include "link.h"
#define N_CALLBACK 14                     /*!< Number of callbacks we have */

/**
 * @brief Is the basic game's struct, where the object and player(s) are stored and where the board
 * with the information is also stored, it also stores the command input
 * @author Rodrigo Juez
 * 
 */
struct _Game{
  char name[SIZE_NAME];                   /*!< name It's the name of the game */
  Object *object[MAX_OBJECTS];            /*!< *object Pointer to the object structure */
  player *player;                         /*!< *player Pointer to player structure */
  Space *spaces[MAX_SPACES + 1];          /*!< *spaces Pointer to space structure */
  T_Command last_cmd;                     /*!< last_cmd The command */
  Die *die;                               /*!< *die Pointer to die structure */
  STATUS ok;                              /*!< ok No errors */
  char particular_obj[MAX_OBJ_NAME];      /*!< particular_obj Name of the object */
  char particular_link[MAX_OBJ_NAME];     /*!< particular_link Name of the link */
  Link *links[MAX_LINKS];                 /*!< links Pointer to link structure */
  Dialogue *dialogue;                     /*!< dialogue Pointer to dialogue structure */
};

/**
   Define the function type for the callbacks
*/
typedef STATUS (*callback_fn)(Game *game);

/**
   List of callbacks for each command in the game 
*/

/**
 * @brief It executes the unknown command
 * @author Rodrigo Juez
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_unknown(Game *game);

/**
 * @brief It executes the exit command
 * @author Rodrigo Juez
 * 
 * @param game The game structure
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_exit(Game *game);

/**
 * @brief It executes the move command
 * @author Rodrigo Juez
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_move(Game *game);

/**
 * @brief It executes the next command
 * @author Rodrigo Juez
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_next(Game *game);

/**
 * @brief It executes the back command
 * @author Rodrigo Juez
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_back(Game *game);

/**
 * @brief It executes the right command
 * @author Rodrigo Juez
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_right(Game *game);

/**
 * @brief It executes the left command
 * @author Rodrigo Juez
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_left(Game *game);

/**
 * @brief It executes the pick command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_pick(Game *game);

/**
 * @brief It executes the drop command
 * @author Mariusz Wiśniewski
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_drop(Game *game);

/**
 * @brief It executes the roll command
 * @author Pablo Almarza
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_die(Game *game);

/**
 * @brief It executes the inspect command
 * @author Miguel Arnaiz
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_inspect(Game *game);

/**
 * @brief It executes the turn on command
 * 
 * @param game The game structure
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_turnon(Game *game);

/**
 * @brief It executes the turn off command
 * 
 * @param game The game structure
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_turnoff(Game *game);

/**
 * @brief It executes the open link command
 * @author Miguel Arnaiz
 * 
 * @param game The game structure
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_openlink(Game *game);

/**
 * @brief It executes the object hide command
 * @author Mariusz Wiśniewski
 * 
 * @param game A pointer to the game structure
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_hide_object(Game *game);

/**
 * @brief It executes the object show command
 * @author Mariusz Wiśniewski
 * 
 * @param game A pointer to the game structure
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_show_object(Game *game);

/**
 * @brief It executes the save command
 * @author Rodrigo Juez
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_save(Game *game);
/**
 * @brief It executes the load command
 * @author Rodrigo Juez
 * 
 * @param game The game structure 
 * @return STATUS OK if it goes as expected
 */
STATUS game_callback_load(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_pick,
    game_callback_drop,
    game_callback_die,
    game_callback_inspect,
    game_callback_move,
    game_callback_turnon,
    game_callback_turnoff,
    game_callback_openlink,
    game_callback_show_object,
    game_callback_hide_object,
    game_callback_save,
    game_callback_load};

/**
   Private functions
*/


void game_illumination_on_the_go(Game *game, Id origin_id, Id destination_id);

/**
 * @brief It obtains the space ID at an index in the array
 * 
 * @param game The game structure
 * @param position The position of the space
 * @return Id The id of the space
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief It sets the location of the player
 * 
 * @param game The game structure
 * @param id The id of the player
 * @return STATUS OK if it goes as expected
 */
STATUS game_set_player_location(Game *game, Id id);

/**
   Game interface implementation
*/

Object *game_get_object_by_order(Game *game, int position){
  if(!game|| position < 0){return NULL;}
  return game->object[position];
}


player *game_get_player(Game *game)
{
  if (!game)
  {
    return NULL;
  }
  return game->player;
}

Space **game_get_spaces(Game *game)
{
  if (!game)
  {
    return NULL;
  }
  return game->spaces;
}

Die *game_get_die(Game *game)
{
  if (!game)
  {
    return NULL;
  }
  return game->die;
}

STATUS game_get_last_status(Game *game)
{
  if (!game)
  {
    return ERROR;
  }
  return game->ok;
}

char *game_get_particular_obj(Game *game)
{
  if (!game)
  {
    return NULL;
  }
  return game->particular_obj;
}

STATUS game_create(Game **game)
{
  int i;

  (*game) = (Game *)malloc(sizeof(Game));
  if (!*game)
    return ERROR;

  for (i = 0; i < MAX_SPACES; i++)
  {
    (*game)->spaces[i] = NULL;
  }
  for (i = 0; i < MAX_OBJECTS; i++)
  {
    (*game)->object[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    (*game)->links[i] = NULL;
  }
  sprintf((*game)->name, "INSERT IN DATA.DAT");
  (*game)->player = player_create(1);
  (*game)->last_cmd = NO_CMD;
  (*game)->die = die_ini(1);
  (*game)->ok = OK;
  strcpy( (*game)->particular_obj, "");
  strcpy( (*game)->particular_link, "");
  (*game)->dialogue=Dialogue_ini();
  color=TRUE;

  return OK;
}

Dialogue* game_get_dialogue(Game *game){
  if(!game) return NULL;
  return game->dialogue;
}

STATUS game_create_from_file(Game **game, char *filename)
{

  if (game_create(game) == ERROR)
    return ERROR;

  if (game_management_load_spaces(*game, filename) == ERROR)
    return ERROR;

  if (game_management_load_objects(*game, filename) == ERROR)
    return ERROR;

  if (game_management_load_links(*game, filename) == ERROR)
    return ERROR;
  game_set_player_location(*game, game_get_space_id_at(*game, 0));

  return OK;
}

STATUS game_destroy(Game *game)
{
  int i;
  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++)
  {
    space_destroy(game->spaces[i]);
  }
  for (i = 0; (i < MAX_OBJECTS) && (game->object[i] != NULL); i++)
  {
    Object_destroy(game->object[i]);
  }

  for (i = 0; (i < MAX_LINKS); i++)
  {
    link_destroy(game->links[i]);
  }
  Dialogue_destroy(game->dialogue);
  player_destroy(game->player);
  die_destroy(game->die);
  if (game)
  {
    free(game);
  }
  return OK;
}

Link *game_get_link_from_index(Game *game, int index)
{
  if (!game)
  {
    return NULL;
  }

  return game->links[index];
}

Link *game_get_link_from_id(Game *game, Id id)
{
  int i = 0;
  if (!game || id == NO_ID)
    return NULL;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (link_get_id(game->links[i]) == id)
    {
      return game->links[i];
    }
  }
  return NULL;
}

STATUS game_add_space(Game *game, Space *space)
{
  int i = 0;

  if (!space || !game)
  {
    return ERROR;
  }

  while ((i < MAX_SPACES) && (game->spaces[i] != NULL))
  {
    i++;
  }

  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;
  return OK;
}

BOOL game_no_object_illuminated_on_this_space(Game *game, Id space_id, Id object_id) {
  int num_of_turned_on_objects = 0;
  int num_of_objects = space_get_num_objects(game_get_space(game, space_id));
  int i;
  Object *object;

  if (!game || space_id == NO_ID || object_id == NO_ID) return FALSE;
  
  for (i = 0; i < num_of_objects; i++) {
    if (Object_get_turned_on(game_get_object_from_id(game, space_get_object_id_from_index(game_get_space(game, space_id), i))) == TRUE) {
      num_of_turned_on_objects++;
      object = game_get_object_from_id(game, space_get_object_id_from_index(game_get_space(game, space_id), i));
    }
  }

  if ((num_of_turned_on_objects == 1 && Object_get_id(object) == object_id) || num_of_turned_on_objects == 0) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

void game_illumination_on_the_go(Game *game, Id origin_id, Id destination_id) {
  int i;
  if (!game || origin_id == NO_ID || destination_id == NO_ID) return;

  if (space_get_illuminated(game_get_space(game, destination_id)) == FALSE) {
    for (i = 1; i < MAX_OBJECTS; i++) {
      if ((inventory_find_object(player_get_objects(game_get_player(game)), i) == TRUE) && (Object_get_turned_on(game_get_object_from_id(game, i)) == TRUE)) {
        space_set_illuminated(game_get_space(game, destination_id), TRUE);
        break;
      }
    }
  }

  if (space_get_illuminated(game_get_space(game, origin_id)) == TRUE) {
    for (i = 1; i < MAX_OBJECTS; i++) {
      if (player_get_num_of_objects(game_get_player(game)) > 0 && Object_get_turned_on(game_get_object_from_id(game, player_get_particular_object(game_get_player(game), i))) == TRUE &&
        space_get_turned_on_object_on_the_space(game_get_space(game, origin_id)) == FALSE) {
        space_set_illuminated(game_get_space(game, origin_id), FALSE);
        break;
      }
    }
  } 
}

Id game_get_space_id_at(Game *game, int position)
{

  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Space *game_get_space(Game *game, Id id)
{
  int i = 0;
  if (!game)
  {
    return NULL;
  }
  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game)
{
  if (!game)
  {
    return NO_ID;
  }
  return player_get_space(game->player);
}

int game_get_max_objects(Game *game)
{
  int i = 0;
  if (!game)
  {
    return -1;
  }
  for (i = 0; i < MAX_OBJECTS && game->object[i] != NULL; i++)
    ;
  return i;
}

int game_get_num_of_spaces(Game *game) {
  int i = 0;
  if (!game) return -1;
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    ;
  return i;
}

Id game_get_object_location(Game *game, Id id_object)
{
  int i;

  if (!game || id_object == NO_ID)
  {
    return NO_ID;
  }

  for (i = 0; i < MAX_SPACES; i++)
  {
    if (space_find_object((game->spaces[i]), id_object))
    {
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

STATUS game_set_player_location(Game *game, Id id)
{
  if (!game || id == NO_ID)
  {
    return ERROR;
  }

  player_set_space(game->player, id);
  return OK;
}

STATUS game_set_object_location(Game *game, Id id_space, Id id_object)
{
  int i;
  Space *temp;
  if (!game)
  {
    return ERROR;
  }
  for (i = 0; i < MAX_SPACES; i++)
  {
    if (space_find_object(game->spaces[i], id_object))
    {
      space_del_object(game->spaces[i], id_object);
      break;
    }
  }

  temp = game_get_space(game, id_space);
  if (!space_set_object(temp, id_object))
  {
    return ERROR;
  }

  return OK;
}

STATUS game_update(Game *game, T_Command cmd)
{
  if (!game)
  {
    return ERROR;
  }
  game->last_cmd = cmd;
  game->ok = (*game_callback_fn_list[cmd])(game);
  return OK;
}


char* game_get_name(Game* game){
  if(!game) return NULL;
  return game->name;
}

STATUS game_set_name(Game* game, char* name){
  if(!game|| !name) return ERROR;
  strcpy(game->name, name);

  return OK;
}



T_Command game_get_last_command(Game *game)
{
  if (!game)
  {
    return NO_CMD;
  }
  return game->last_cmd;
}

/*Esta es la funcion en la que ponemos la informacion del dado los objetos etc (NO MODIFICADA)*/
void game_print_data(Game *game)
{
  int i;
  int x;
  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: \n");
  for (x = 0; x < MAX_SPACES; x++)
  {
    space_print(game->spaces[x]);    
  }

  printf("=> Player location: %ld\n", player_get_space(game->player));
  printf("prompt:> ");
}

Object *game_get_object_from_id(Game *game, Id object_id)
{
  int i;

  if (object_id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    if (object_id == Object_get_id(game->object[i]))
    {
      return game->object[i];
    }
  }
  return NULL;
}

BOOL game_is_over(Game *game)
{

  if (!game)
  {
    return TRUE;
  }
  return FALSE;
}
Object *game_get_object_fromName(Game *game, char *name){
    int i;
    char *cmp;
    if(!game || !name){return NULL;}

    for(i = 0; i < MAX_OBJECTS ; i++){
      cmp= Object_get_name(game_get_object_by_order(game,i));
      if(!cmp){break;}
        if(strcmp(name,cmp) == 0 ){
            return game_get_object_by_order(game,i);
        }   
        
    }
    
    return NULL;
}

STATUS game_add_link(Game *game, Link *link){
  int i;
  if (!game || !link)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_LINKS && link_get_id(game->links[i]) != NO_ID; i++)
  {
    if (link_get_id(game->links[i]) == link_get_id(link))
    {
      return ERROR;
    }
  }
  if (i < MAX_LINKS)
  {
    game->links[i] = link;
    return OK;
  }
  return ERROR;
}

STATUS game_add_object(Game *game, Object *object){
  int i = 0;

  if (!object || !game)
  {
    return ERROR;
  }

  while ((i < MAX_OBJECTS) && (game->object[i] != NULL))
  {
    i++;
  }

  if (i >= MAX_OBJECTS)
  {
    return ERROR;
  }

  game->object[i] = object;

  return OK;
}

/**
   Callbacks implementation for each action 
*/

STATUS game_callback_unknown(Game *game){

  if (!game)
  {
    return ERROR;
  }

  return ERROR;
}

STATUS game_callback_exit(Game *game){
  if (!game)
  {
    return ERROR;
  }
  
  printf("Game over.\n");
  return OK;
}

STATUS game_callback_next(Game *game){
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  Link *link;
  Id space1 = NO_ID;
  Id space2 = NO_ID;
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_south(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
      link = game_get_link_from_id(game, current_id);
      space1 = link_get_space1(link);
      space2 = link_get_space2(link);

      if (link_get_open(link))
      {

        if (space1 == space_id)
        {
          game_set_player_location(game, space2);
          return OK;
        }
        if (space2 == space_id)
        {
          game_set_player_location(game, space1);
          return OK;
        }
      }

      else
      {
        return ERROR;
      }
    }
  }
  return ERROR;
}

STATUS game_callback_back(Game *game){
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  Link *link;
  Id space1 = NO_ID;
  Id space2 = NO_ID;
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_north(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
      link = game_get_link_from_id(game, current_id);
      space1 = link_get_space1(link);
      space2 = link_get_space2(link);

      if (link_get_open(link))
      {

        if (space1 == space_id)
        {
          game_set_player_location(game, space2);
          return OK;
        }
        if (space2 == space_id)
        {
          game_set_player_location(game, space1);
          return OK;
        }
      }

      else
      {
        return ERROR;
      }
    }
  }
  return ERROR;
}

STATUS game_callback_left(Game *game){
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  Link *link;
  Id space1 = NO_ID;
  Id space2 = NO_ID;
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_west(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
      link = game_get_link_from_id(game, current_id);
      space1 = link_get_space1(link);
      space2 = link_get_space2(link);

      if (link_get_open(link))
      {

        if (space1 == space_id)
        {
          game_set_player_location(game, space2);
          return OK;
        }
        if (space2 == space_id)
        {
          game_set_player_location(game, space1);
          return OK;
        }
      }

      else
      {
        return ERROR;
      }
    }
  }
  return ERROR;
}

STATUS game_callback_right(Game *game){
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  Link *link;
  Id space1 = NO_ID;
  Id space2 = NO_ID;
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_east(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
      link = game_get_link_from_id(game, current_id);
      space1 = link_get_space1(link);
      space2 = link_get_space2(link);

      if (link_get_open(link))
      {

        if (space1 == space_id)
        {
          game_set_player_location(game, space2);
          return OK;
        }
        if (space2 == space_id)
        {
          game_set_player_location(game, space1);
          return OK;
        }
      }

      else
      {
        return ERROR;
      }
    }
  }
  return ERROR;
}

STATUS game_callback_pick(Game *game){
  Id player_space = NO_ID;
  Id object_space = NO_ID;
  Id idobject = NO_ID;
  char name[MAX_OBJ_NAME+4];
  strcpy(game->particular_obj, "");
  player_space = player_get_space(game->player);


  printf("Write the name of an object you want to pick up!\n");
  if(scanf("%s", name)>MAX_OBJ_NAME){return ERROR;};
  strcpy(game->particular_obj, name);


  idobject= Object_get_id(game_get_object_fromName(game,name));
  if(idobject==NO_ID){return ERROR;}

  object_space = game_get_object_location(game, idobject);

  if ((player_space == object_space) && (Object_get_movable(game_get_object_from_id(game, idobject)) == TRUE))
  {
    player_set_object(game->player, Object_get_id(game_get_object_from_id(game, idobject))); 
    Object_set_moved(game_get_object_from_id(game, idobject), TRUE);
    game_set_object_location(game, NO_ID, idobject);
    if (game_no_object_illuminated_on_this_space(game, player_space, idobject) == TRUE) {
      space_set_turned_on_object_on_the_space(game_get_space(game, player_space), FALSE);
    }
  }
  else {return ERROR;}
  return OK;
}

STATUS game_callback_drop(Game *game){
  int i=0;
  Id player_location = game_get_player_location(game);
  char name[MAX_OBJ_NAME+4];
  char *buff = NULL;
  Id object_id = NO_ID;
  strcpy(game->particular_obj, "");

  if (!game || player_get_objects(game->player) == NULL)
    return ERROR;

  if (player_location == NO_ID)
    return ERROR;

  if(space_get_num_objects((game_get_space(game,game_get_player_location(game))))>=4)
    return ERROR;
  
  printf("Write the name of an object you want to drop!\n");
  scanf("%s", name);
  strcpy(game->particular_obj, name);
  for (i = 0; i < player_get_num_of_objects(game_get_player(game)); i++)
  {
    buff = Object_get_name(game_get_object_from_id(game, player_get_particular_object(game_get_player(game), i)));
    if (!strcmp(buff, name))
    {
      object_id = set_obtain_Id_by_position(inventory_get_objects(player_get_objects(game->player)), i);
      break;
    }
  }


    if (object_id == NO_ID)
  {
    return ERROR;
  }

  game_set_object_location(game, player_location, object_id);
  if (Object_get_turned_on(game_get_object_from_id(game, object_id)) == TRUE) {
    space_set_turned_on_object_on_the_space(game_get_space(game, player_location), TRUE);
  }
  player_delete_object(game->player, object_id);
  if(player_location == Object_get_first_location(game_get_object_from_id(game, object_id))){
    Object_set_moved(game_get_object_from_id(game, object_id),FALSE);
  }
  return OK;
}

STATUS game_callback_die(Game *game){
  if (die_roll(game->die) != OK)
  {
    return ERROR;
  }
  else
  {
    die_get_last_roll(game->die);
  }
  return OK;
}

STATUS game_callback_move(Game *game){
  char select[6];
  int i = 0;
  int x=0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  Object *object=NULL;
  Link *link;
  Id space1 = NO_ID;
  Id space2 = NO_ID;
  space_id = game_get_player_location(game);
  printf("Select where do you want to move! (south(s), north(n), east(e), west(w), up(u), down(d)): ");
  scanf("%s", select);
  strcpy(game->particular_obj, ""); 

  if (!strcmp(select, "north") || !strcmp(select, "n")){
    strcpy(game->particular_obj, "north"); 

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++){
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id){
        current_id = space_get_north(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
        link = game_get_link_from_id(game, current_id);
        space1 = link_get_space1(link);
        space2 = link_get_space2(link);
        
        if (link_get_open(link)){
          
          if (space1 == space_id){
            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space2==Object_get_cantmove(object)){return ERROR;}
              if(Object_get_cantmove(object)==-1){break;}
            }
            game_set_player_location(game, space2);
            game_illumination_on_the_go(game, space_id, space2);
            return OK;
          }
          if (space2 == space_id){
            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space1==Object_get_cantmove(object)){return ERROR;}
            }
            game_set_player_location(game, space1);
            game_illumination_on_the_go(game, space_id, space1);
            return OK;
          }
        }

        else{
          return ERROR;
        }
      }
    }
    return ERROR;
  }
  else if (!strcmp(select, "south") || !strcmp(select, "s")){
    strcpy(game->particular_obj, "south");

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++){
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id)
      {
        current_id = space_get_south(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
        link = game_get_link_from_id(game, current_id);
        space1 = link_get_space1(link);
        space2 = link_get_space2(link);
        if (link_get_open(link)){
          if (space1 == space_id){

            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space2==Object_get_cantmove(object)){return ERROR;}
            }
            game_set_player_location(game, space2);
            game_illumination_on_the_go(game, space_id, space2);
            return OK;
          }

          if (space2 == space_id){
            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space1==Object_get_cantmove(object)){return ERROR;}
            }
            game_set_player_location(game, space1);
            game_illumination_on_the_go(game, space_id, space1);
            return OK;
          }
        }

        else{ return ERROR; }
      }
    }
    return ERROR;
  }
  else if (!strcmp(select, "east") || !strcmp(select, "e")){
    strcpy(game->particular_obj, "east");

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++){
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id){
        current_id = space_get_east(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
        link = game_get_link_from_id(game, current_id);
        space1 = link_get_space1(link);
        space2 = link_get_space2(link);

        if (link_get_open(link)){
          if (space1 == space_id){
            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space2==Object_get_cantmove(object)) return ERROR;
            }

            game_set_player_location(game, space2);
            game_illumination_on_the_go(game, space_id, space2);
            return OK;
          }
          if (space2 == space_id) {
            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space1==Object_get_cantmove(object)){return ERROR;}
            }
            game_set_player_location(game, space1);
            game_illumination_on_the_go(game, space_id, space1);
            return OK;
          }
        }

      else{ return ERROR; }
      }
    }
    return ERROR;
  }
  else if (!strcmp(select, "west") || !strcmp(select, "w")){
    strcpy(game->particular_obj, "west");

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++){
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id){
        current_id = space_get_west(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
        link = game_get_link_from_id(game, current_id);
        space1 = link_get_space1(link);
        space2 = link_get_space2(link);

        if (link_get_open(link)){
          if (space1 == space_id){
            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space2==Object_get_cantmove(object)){return ERROR;}
            }

            game_set_player_location(game, space2);
            game_illumination_on_the_go(game, space_id, space2);
            return OK;
            }
        if (space2 == space_id){

          for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space1==Object_get_cantmove(object)){return ERROR;}
            }

          game_set_player_location(game, space1);
          game_illumination_on_the_go(game, space_id, space1);
          return OK;
        }
      }

      else
      {
        return ERROR;
      }}}
    return ERROR;  
  }
  else if (!strcmp(select, "up") || !strcmp(select, "u")){
    strcpy(game->particular_obj, "up");

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++){
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id)
      {
        current_id = space_get_up(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
        link = game_get_link_from_id(game, current_id);
        space1 = link_get_space1(link);
        space2 = link_get_space2(link);
        if (link_get_open(link)){
          if (space1 == space_id){
            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space2==Object_get_cantmove(object)){return ERROR;}
            }

            game_set_player_location(game, space2);
            game_illumination_on_the_go(game, space_id, space2);
            return OK;
          }

          if (space2 == space_id){
            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space1==Object_get_cantmove(object)){return ERROR;}
            }

            game_set_player_location(game, space1);
            game_illumination_on_the_go(game, space_id, space1);
            return OK;
          }
        }

        else{ return ERROR; }
      }
    }
    return ERROR;
  }
  else if (!strcmp(select, "down") || !strcmp(select, "d")){
    strcpy(game->particular_obj, "down");

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++){
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id)
      {
        current_id = space_get_down(game->spaces[i]); /*NOW THIS OBTAINS AN LINK ID SO I NEED TO GET THE REAL NEXT*/
        link = game_get_link_from_id(game, current_id);
        space1 = link_get_space1(link);
        space2 = link_get_space2(link);
        if (link_get_open(link)){
          if (space1 == space_id){
            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space2==Object_get_cantmove(object)){return ERROR;}
            }

            game_set_player_location(game, space2);
            game_illumination_on_the_go(game, space_id, space2);
            return OK;
          }

          if (space2 == space_id){

            for(x=0; x<player_get_num_of_objects(game->player); x++){
              object=game_get_object_from_id(game, player_get_particular_object(game->player, x));
              if(space2==Object_get_cantmove(object)){return ERROR;}
            }
            
            game_set_player_location(game, space1);
            game_illumination_on_the_go(game, space_id, space1);
            return OK;
          }
        }

        else{ return ERROR; }
      }}}
    
  return ERROR;
}

STATUS game_callback_inspect(Game *game){
  char name[MAX_OBJ_NAME];
  char *temp=NULL;
  int i;
  strcpy(game->particular_obj, ""); 

  if(!game){return ERROR;}
  
  printf("Introduce the name of the object you want to inspect or space(s) if you want to inspect the space you are in: ");
  scanf("%s", name);
  strcpy(game->particular_obj, name);

  
  for(i=0 ; i<MAX_OBJECTS && game->object[i]!=NULL; i++){
    temp=Object_get_name(game->object[i]);
    if(strcmp(name, temp)==0){

      if(set_find( space_get_objects(game_get_space( game, game_get_player_location(game) ) ) , Object_get_id( game_get_object_fromName(game, temp) ) ) == TRUE || player_obj_find(game->player, Object_get_id( game_get_object_fromName(game, temp) ) )){
        return OK;
        }

      }

     else {

      if(!strcmp(name, "s")|| !strcmp(name, "space")){
        strcpy(game->particular_obj, "space");
        return OK;

      }
    }
  }
  
  return ERROR;
}

STATUS game_callback_turnon(Game *game){
  char name[MAX_OBJ_NAME];
  char *temp = NULL;
  Id spaceid;
  int i;
  strcpy(game->particular_obj, "");

  if(!game){return ERROR;}

  printf("Introduce the name of the object you want to turn on: ");
  scanf("%s", name);
  strcpy(game->particular_obj, name);


  spaceid = game_get_player_location(game);

  for(i=0; i<MAX_OBJECTS && game->object[i]!=NULL; i++){
    temp = Object_get_name(game->object[i]);
    if(strcmp(name, temp) == 0){
      if(Object_get_illuminate_space(game_get_object_fromName(game, game->particular_obj)) == TRUE){
        if(Object_get_turned_on(game_get_object_fromName(game, game->particular_obj)) == TRUE){
          printf("%s is already turned on", game->particular_obj);
        } else if(game_get_player_location(game) == game_get_object_location(game, Object_get_id(game_get_object_fromName(game, game->particular_obj))) || inventory_find_object(player_get_objects(game_get_player(game)), Object_get_id(game_get_object_fromName(game, game->particular_obj)))) {
          Object_set_turned_on(game->object[i], TRUE);
          space_set_illuminated(game_get_space(game, spaceid), TRUE);
          return OK;
        }
      } 
    }
  }
  return ERROR;
}

STATUS game_callback_turnoff(Game *game){
  char name[MAX_OBJ_NAME];
  char *temp = NULL;
  Id spaceid;
  int i;
  strcpy(game->particular_obj, "");

  if(!game){return ERROR;}

  
  printf("Introduce the name of the object you want to turn off: ");
  scanf("%s", name);
  strcpy(game->particular_obj, name);


  for(i=0; i<MAX_OBJECTS && game->object[i]!=NULL; i++){
    temp = Object_get_name(game->object[i]);
    if(strcmp(name, temp) == 0){
      if(Object_get_illuminate_space(game_get_object_fromName(game, game->particular_obj)) == TRUE){
        if(Object_get_turned_on(game_get_object_fromName(game, game->particular_obj)) == TRUE){
          if(game_get_player_location(game) == game_get_object_location(game, Object_get_id(game_get_object_fromName(game, game->particular_obj))) || inventory_find_object(player_get_objects(game_get_player(game)), Object_get_id(game_get_object_fromName(game, game->particular_obj)))){
            spaceid = game_get_object_location(game, Object_get_id(game_get_object_fromName(game, game->particular_obj)));
            Object_set_turned_on(game_get_object_fromName(game, game->particular_obj), FALSE);
            space_set_illuminated(game_get_space(game, spaceid), FALSE);
            return OK;
            }
          } else if(game_get_player_location(game) == game_get_object_location(game, Object_get_id(game_get_object_fromName(game, game->particular_obj))) || inventory_find_object(player_get_objects(game_get_player(game)), Object_get_id(game_get_object_fromName(game, game->particular_obj)))){
              printf("%s is already turned off", game->particular_obj);
              return OK;
          }
        }
      }
    }
    
  return ERROR;
}


STATUS game_callback_openlink(Game *game){
  char obj_name[MAX_OBJ_NAME];
  char link_name[MAX_OBJ_NAME];
  char with[MAX_OBJ_NAME];
  Link *link=NULL;
  Object *obj=NULL;

  if(!game) return ERROR;

  strcpy(obj_name, "");
  strcpy(link_name, "");
  strcpy(with, "");

  printf("Enter <name of the link> <with(w)> <name of the object>: ");
  scanf("%s %s %s", link_name, with, obj_name);
  strcpy(game->particular_link, link_name);
  strcpy(game->particular_obj, obj_name);

  link = game_get_link_fromName(game, link_name);
  if(!link || link_get_open(link)==TRUE) return ERROR;
  
  if(strcmp(with, "w")!=0 && strcmp(with, "with")!=0) return ERROR;

  obj = game_get_object_fromName(game, obj_name);
  if(!obj) return ERROR;  

  if(Object_get_movable(obj)==TRUE){
    if(inventory_find_object(player_get_objects(game_get_player(game)), Object_get_id(obj))==FALSE) return ERROR;
  } else {
    if(game_get_object_location(game, Object_get_id(obj)) != game_get_player_location(game) ) return ERROR;
  }

  if(!set_find(Object_get_open_link(obj), link_get_id(link))) return ERROR;
  if(!link_set_open(link, TRUE)) return ERROR;
  
  return OK;
}


Link *game_get_link_fromName(Game *game, char *link_name){
  int i;
  char *cmp;
  
  if(!link_name) return NULL;  

  for(i = 0; i < MAX_LINKS ; i++){
    cmp = link_get_name(game_get_link_from_index(game,i));
    if(!cmp){break;}
      if(strcmp(link_name ,cmp) == 0 ){
          return game_get_link_from_index(game,i);
      }           
  }
  
  return NULL;
}

STATUS game_callback_hide_object(Game *game) {
  Id player_space = NO_ID;
  Id object_space = NO_ID;
  Id idobject = NO_ID;
  char name[MAX_OBJ_NAME+4];
  player_space = player_get_space(game->player);

  if (!game) return ERROR;

  printf("Write the name of an object you want to hide!\n");
  if(scanf("%s", name)>6){return ERROR;};
  strcpy(game->particular_obj, name);

  idobject = Object_get_id(game_get_object_fromName(game,name));
  if(idobject==NO_ID){return ERROR;}

  object_space = game_get_object_location(game, idobject);

  if (player_space == object_space && Object_get_visibility(game_get_object_from_id(game, idobject)) == VISIBLE)
  {
    Object_set_visibility(game_get_object_from_id(game, idobject), HIDDEN);
  }
  else {return ERROR;}
  return OK;
}

STATUS game_callback_show_object(Game *game) {
  Id player_space = NO_ID;
  Id object_space = NO_ID;
  Id idobject = NO_ID;
  char name[MAX_OBJ_NAME];

  if (!game) return ERROR;
  player_space = player_get_space(game->player);


  printf("Write the name of an object you want to show!\n");
  if(scanf("%s", name)>MAX_OBJ_NAME){return ERROR;};
  strcpy(game->particular_obj, name);

  idobject = Object_get_id(game_get_object_fromName(game,name));
  if(idobject==NO_ID){return ERROR;}

  object_space = game_get_object_location(game, idobject);

  if (player_space == object_space && Object_get_visibility(game_get_object_from_id(game, idobject)) == HIDDEN)
  {
    Object_set_visibility(game_get_object_from_id(game, idobject), VISIBLE);
  }
  else {return ERROR;}
  return OK;
}

STATUS game_callback_save(Game *game){
  FILE *pf=NULL;
  STATUS flag=ERROR;
  char filename[MAX_DESC];
  if(!game){return ERROR;}

  fprintf(stdout, "Write the name of the savegame:");
  scanf("%s", filename);  
  pf=fopen(filename, "w");
  if(!pf) return flag;
  flag=game_management_save(pf, game);
  fclose(pf);   
  return flag;
}

STATUS game_callback_load(Game *game){
  char filename[MAX_DESC];

  fprintf(stdout, "Write the name of the game you want to load:");
  scanf("%s", filename); 
  
  game_management_load_previous_game(filename, game);
  return OK;
}

char* game_get_particular_link(Game *game){
  if(!game) return NULL;
  return game->particular_link;
}

STATUS game_set_particular_link(Game *game, char *link_name){
  if(!game || !link_name) return ERROR;
  strcpy(game->particular_link, link_name);
  return OK;
}
