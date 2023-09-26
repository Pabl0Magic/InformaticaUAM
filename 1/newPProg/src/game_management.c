#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_management.h"

STATUS game_management_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char desc[MAX_DESC] = "";
  char detailedDesc[MAX_DESC] = "";
  char *toks = NULL;
  char *gdesc = NULL;
  BOOL illuminated = TRUE;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up = NO_ID, down = NO_ID;
  Space* space = NULL;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  

  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#n:", line, 3) == 0) {

      toks = strtok(line + 3, "|");
      game_set_name(game, toks);
   
    }

    if (strncmp("#s:", line, 3) == 0) {
      strcpy(desc, "");

      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      up = atol(toks);
      toks = strtok(NULL, "|");
      down = atol(toks);
      toks = strtok(NULL, "|");
      illuminated = atol(toks);
      toks = strtok(NULL, "|");
      if(toks != NULL){
        strcpy(desc, toks);
      }
      toks = strtok(NULL, "|");
      if(toks != NULL){
        strcpy(detailedDesc, toks);
      }
      gdesc = strtok(NULL,"&");
      

  #ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
  #endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_set_up(space,up);
        space_set_down(space, down);
        space_set_illuminated(space, illuminated);
        if (illuminated == TRUE) {
          space_set_turned_on_object_on_the_space(space, TRUE);
        }
        else {
          space_set_turned_on_object_on_the_space(space, FALSE);
        }
        space_set_draw(space,gdesc);
        space_set_description(space, desc);
        space_set_detailed_desc(space, detailedDesc);
        game_add_space(game, space);

      }
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  return status;
}

STATUS game_management_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char desc[MAX_DESC] = "";
  char descalt[MAX_DESC] = "";
  char descilu[MAX_DESC] = "";
  char *toks = NULL;
  Object *object;
  Id id = NO_ID, spaceid = NO_ID, turn = NO_ID;
  Id link_id=NO_ID;
  BOOL illuminate;
  BOOL movable=TRUE;
  BOOL moved=FALSE;
  STATUS status = OK;
  T_Object_visibility hidden= FALSE;
  Id cantmove=NO_ID;
  int i;

  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      strcpy(desc, "");

      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      spaceid = atol(toks);
      toks = strtok(NULL, "|");
      illuminate = atoi(toks);
      toks = strtok(NULL, "|");
      movable = atoi(toks);
      toks = strtok(NULL, "|");
      turn = atoi(toks);
      toks = strtok(NULL, "|");
      hidden = atoi(toks);
      toks = strtok(NULL, "|");
      cantmove = atoi(toks);
      toks = strtok(NULL, "|");
      if(toks){strcpy(desc, toks);}
      toks = strtok(NULL, "|");
      if(toks){strcpy(descalt, toks);}
      toks = strtok(NULL, "|");
      if(toks){strcpy(descilu, toks);}

      object = Object_create(id);
      if (object != NULL) {
        Object_set_name(object, name);
        Object_set_cantmove(object, cantmove);
        Object_set_visibility(object, hidden);
        Object_set_description(object, desc);
        Object_set_illuminate_space(object, illuminate);
        Object_set_second_description(object, descalt);
        Object_set_illuminated_description(object, descilu);
        Object_set_first_location(object, spaceid);
        game_add_object(game, object);
        game_set_object_location(game, spaceid, id);
        Object_set_turned_on(object, turn);
        Object_set_moved(object, moved);
        Object_set_movable(object, movable);
        for (i = 0; i < MAX_LINKS; i++){
          toks = strtok(NULL, "|");
        if (toks) {
          link_id = atol(toks); 
          Object_set_open_link(object, link_id);
        }
        else break;
        }
          
        }
      }

    }

  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}

STATUS game_management_load_links(Game* game, char *filename){
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE];
  char* toks = NULL;
  Id linkId=NO_ID;
  Id space1=NO_ID;
  Id space2=NO_ID;
  BOOL open=TRUE;
  Link *link=NULL;
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }


  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      linkId = atol(toks);
      toks = strtok(NULL, "|");
      if(toks){
        strcpy(name, toks);
      }
      toks = strtok(NULL, "|");
      space1 = atol(toks);
      toks = strtok(NULL, "|");
      space2 = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
      link=link_create(linkId);
      if(!link){return ERROR;}
      link_set_name(link, name);
      link_set_open(link,open);
      link_set_space1(link,space1);
      link_set_space2(link,space2);
      
      game_add_link(game, link);
    }
  }

  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  

return status;
}


STATUS game_management_save(FILE *pf, Game *game){
  int i=0, x=0;
  Object *obj=NULL;
  player *player=NULL;
  Inventory *inventory=NULL;
  Space* space=NULL;
  Link *link=NULL;
  if(!game || !pf){return ERROR;}

  for(i=0; game_get_object_by_order(game, i)!=NULL; i++){
    obj=game_get_object_by_order(game, i);
    fprintf(pf, "\n#o: %ld|%ld|%i|%i|%i|%i|%i|", Object_get_id(obj), game_get_object_location(game, Object_get_id(obj)), Object_get_visibility(obj), Object_get_illuminate_space(obj), Object_get_turned_on(obj), Object_get_movable(obj), Object_get_moved(obj));
  }
  for(i=0; game_get_spaces(game)[i]!=NULL; i++){
    space=game_get_spaces(game)[i];
    fprintf(pf, "\n#s: %ld|%ld|%ld|%ld|%ld|%ld|%ld|%i|", space_get_id(space), space_get_north(space), space_get_south(space), space_get_east(space), space_get_west(space), space_get_up(space), space_get_down(space), space_get_illuminated(space));
    for(x=0; space_get_object_id_from_index(space, x)!=NO_ID; x++){
      fprintf(pf, "%ld|", space_get_object_id_from_index(space, x));
    }
  }

  for(i=0; game_get_link_from_index(game,i)!=NULL; i++){
    link=game_get_link_from_index(game,i);
    fprintf(pf, "\n#l: %ld|%i|", link_get_id(link), link_get_open(link));
  }

  player=game_get_player(game);
  fprintf(pf, "\n#p: %ld|%ld|", player_get_id(player), player_get_space(player));
  inventory=player_get_objects(player);
  i=0;
  while(inventory_get_object_from_inventory(inventory,i)!=NO_ID){
    fprintf(pf, "%ld|", inventory_get_object_from_inventory(inventory, i));
    i++;
  }
  
  return OK;
}


STATUS game_management_load_previous_spaces(char *filename, Game *game){
  char line[WORD_SIZE] = "";
  char* toks = NULL;
  FILE *file=NULL;
  int i=0;
  Space *space=NULL;
  Id spaceid=-1, north=-1, south=-1, east=-1, west=-1, up=-1, down=-1, object=-1;
  BOOL illuminated=FALSE;

  file=fopen(filename, "r");
  if(!file) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      spaceid = atol(toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      up = atol(toks);
      toks = strtok(NULL, "|");
      down = atol(toks);
      toks = strtok(NULL, "|");
      illuminated = atol(toks);
      space=game_get_space(game, spaceid);
      space_set_north(space, north);
      space_set_east(space, east);
      space_set_south(space, south);
      space_set_west(space, west);
      space_set_up(space, up);
      space_set_down(space, down);
      space_set_illuminated(space, illuminated);

      for (i = 0; i < INVENTORY_CAPACITY; i++) {
          toks = strtok(NULL, "|");
          if (toks) {
            object = atol(toks); 
            if(space_find_object(space, object)==FALSE){
              space_add_object(space, object);
            }
          }
          else break;
        }   
    }
  }
  fclose(file);
  return OK;
}

STATUS game_management_load_previous_obj(char *filename, Game *game){
  char line[WORD_SIZE] = "";
  char* toks = NULL;
  FILE *file=NULL;
  Object *obj=NULL;
  Id objid=-1, obj_location=-1;
  BOOL objilluminate_space=FALSE, objturnedon=FALSE, objmovable=FALSE, objmoved=FALSE;
  T_Object_visibility objvisibility=NO_STATUS;

  file=fopen(filename, "r");
  if(!file) return ERROR;
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      objid = atol(toks);
      toks = strtok(NULL, "|");
      obj_location = atol(toks);
      toks = strtok(NULL, "|");
      objvisibility = atol(toks);
      toks = strtok(NULL, "|");
      objilluminate_space = atol(toks);
      toks = strtok(NULL, "|");
      objturnedon = atol(toks);
      toks = strtok(NULL, "|");
      objmovable = atol(toks);
      toks = strtok(NULL, "|");
      objmoved = atol(toks);
      obj=game_get_object_from_id(game, objid);
      game_set_object_location(game, obj_location, Object_get_id(obj));
      Object_set_visibility(obj, objvisibility);
      Object_set_illuminate_space(obj, objilluminate_space);
      Object_set_turned_on(obj, objturnedon);
      Object_set_movable(obj, objmovable);
      Object_set_moved(obj, objmoved);      
    }
  }

  fclose(file);
  return OK;
}

STATUS game_management_load_previous_player(char *filename, Game *game){
  char line[WORD_SIZE] = "";
  char* toks = NULL;
  FILE *file=NULL;
  int i=0;
  player *player=NULL;
  Id playerid=-1, playerspace=-1;
  Id playerobject=-1;
  Inventory *inventory=NULL;
  playerid=playerid;
  file=fopen(filename, "r");
  if(!file) return ERROR;
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      playerid = atol(toks);
      toks = strtok(NULL, "|");
      playerspace = atol(toks);
      player=game_get_player(game);
      player_set_space(player, playerspace);
      inventory=player_get_objects(player);

      for (i = 0; i < INVENTORY_CAPACITY; i++) {
        toks = strtok(NULL, "|");
        if (toks) {
          playerobject = atol(toks);
        }
        else {
          playerobject=0;
        }
        if (playerobject && (inventory_find_object(inventory, playerobject)==FALSE)) {
          inventory_set_object_to_inventory(inventory, playerobject);
        }
        else break;
      }   
    }
  }
  fclose(file);
  return OK;

}

STATUS game_management_load_previous_links(char *filename, Game *game){
  char line[WORD_SIZE] = "";
  char* toks = NULL;
  FILE *file=NULL;
  Link *link=NULL;
    Id linkid=-1;
    BOOL linkopen=0;
  file=fopen(filename, "r");
  if(!file) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      linkid = atol(toks);
      toks = strtok(NULL, "|");
      linkopen = atol(toks);
      link=game_get_link_from_id(game, linkid);
      link_set_open(link, linkopen);
       
    }
  }
  fclose(file);
  return OK;
}


STATUS game_management_load_previous_game(char* filename, Game *game){

  if(!game_management_load_previous_spaces(filename, game))return ERROR;
  if(!game_management_load_previous_obj(filename, game)) return ERROR;
  if(!game_management_load_previous_player(filename, game)) return ERROR;
  if(!game_management_load_previous_links(filename, game)) return ERROR;
  return OK;
}


