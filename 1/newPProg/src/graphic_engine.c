#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "screen.h"
#include "string.h"
#include "graphic_engine.h"
#include "die.h"
#include "link.h"
#include "inventory.h"
#include "game_rules.h"
#define MAX_NAME_OBJ 5        /*!< Max number of characters an object can have */
#define MAX_ADD 7             /*!< Max number of added spaces */
#define MAX_UPS 14            /*!< Max number of ups */
#define STR 500               /*!< Max number of characters the string can have */
#define SIZE_SIMBOL 80        /*!< Max size of the simbol */
#define SIZE_OBJS 16          /*!< Max size of the objects */
#define MAX_LINE_PLAYER 25    /*!< Max size the player can occupy in a line */
#define MAX_LINE_OBJ 19       /*!< Max size the objects can occupy in a line */
#define SIZE_OPEN 8           /*!< Max size used to print if an object is opened or closed */
/**
 * @brief It manages the parameters
 * to print the game
 * 
 */
struct _Graphic_engine{
  Area *map,                  /*!< Map parameter */
  *descript,                  /*!< Map parameter */ 
  *banner,                    /*!< Map parameter */ 
  *help,                      /*!< Map parameter */
  *feedback;                  /*!< Map parameter */
};

Graphic_engine *graphic_engine_create(){
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;
  
  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));
  
  ge->map      = screen_area_init( 1, 1, 48+23, 13+9);
  ge->descript = screen_area_init(50+24, 1, 29, 13+9);
  ge->banner   = screen_area_init(28+11,15+9, 23,  1);
  ge->help     = screen_area_init( 1,16+9, 78+24,  2+1);
  ge->feedback = screen_area_init( 1,19+10, 78+24,  2+2);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge){
  if (!ge)
    return;
  
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  
  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game){
  int i=0;
  int j=0;
  char *draw, *drawleft, *drawright, *dialogue;
  char top[MAX_TXT], topleft[MAX_TXT], topright[MAX_TXT];
  char middle[MAX_TXT], middleleft[MAX_TXT], middleright[MAX_TXT];
  char bottom[MAX_TXT], bottomleft[MAX_TXT], bottomright[MAX_TXT];
  char simbol[SIZE_SIMBOL];
  char objs2[SIZE_OBJS];
  char helpchar[SIZE_OBJS];
  char objs1[SIZE_OBJS];
  char objs1left[SIZE_OBJS];
  char objs1right[SIZE_OBJS];
  char objs2left[SIZE_OBJS];
  char objs2right[SIZE_OBJS];
  char up[SIZE_OBJS], nextup[SIZE_OBJS];
  char upleft[SIZE_OBJS], nextupleft[SIZE_OBJS];
  char upright[SIZE_OBJS], nextupright[SIZE_OBJS];
  char opened[SIZE_OPEN];
  char down[SIZE_OBJS], nextdown[SIZE_OBJS];
  char downleft[SIZE_OBJS], nextdownleft[SIZE_OBJS];
  char downright[SIZE_OBJS], nextdownright[SIZE_OBJS];

  Id link_back=NO_ID;
  Id link_next=NO_ID;
  Id link_right=NO_ID;
  Id link_left=NO_ID;
  Id link_up=NO_ID;
  Id link_down=NO_ID;
  int fill=0;
  int counterforcommas=0;
  Id nextlink_right=NO_ID;
  Id nextlink_left=NO_ID;
  Id nextlink_up=NO_ID;
  Id nextlink_down=NO_ID;

  char add[MAX_ADD];
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_right=NO_ID, id_left=NO_ID,id_up=NO_ID,id_down=NO_ID, obj_loc1=NO_ID;
  Id nextid_right = NO_ID; Id nextid_left=NO_ID, nextid_up=NO_ID, nextid_down=NO_ID;
  Id uplink_left=NO_ID, uplink_right=NO_ID;
  Id downlink_right=NO_ID, downlink_left=NO_ID;

  Id nextuplink_left=NO_ID, nextuplink_right=NO_ID;
  Id nextdownlink_right=NO_ID, nextdownlink_left=NO_ID;

  Space* space_act = NULL;
  Space *space_next=NULL, *space_left=NULL, *space_right=NULL, *nextspace_left=NULL, *nextspace_right=NULL;
  char obj1[MAX_NAME_OBJ];
  char str[STR];
  Id last_roll=NO_ID;
  int cuanttobj; /*global cuantity of objects*/
  int nids=0; 
  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID){
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
   
      
    link_back=space_get_north(space_act);
    link_next=space_get_south(space_act);
    link_left =space_get_west(space_act);
    link_right=space_get_east(space_act);
    link_up=space_get_up(space_act);
    link_down=space_get_down(space_act);

    id_back  = link_get_oposite(game_get_link_from_id(game,link_back),id_act);
    id_next  = link_get_oposite(game_get_link_from_id(game,link_next),id_act);
    id_right = link_get_oposite(game_get_link_from_id(game,link_right),id_act);
    id_left  = link_get_oposite(game_get_link_from_id(game,link_left),id_act);
    id_up  = link_get_oposite(game_get_link_from_id(game,link_up),id_act);
    id_down  = link_get_oposite(game_get_link_from_id(game,link_down),id_act);


    space_next= game_get_space(game, id_next);
   
    nextlink_left =space_get_west(space_next);
    nextlink_right=space_get_east(space_next);
    nextlink_up=space_get_up(space_next);
    nextlink_down=space_get_down(space_next);

    nextid_right = link_get_oposite(game_get_link_from_id(game,nextlink_right),id_next);
    nextid_left  = link_get_oposite(game_get_link_from_id(game,nextlink_left),id_next);
    nextid_up  = link_get_oposite(game_get_link_from_id(game,nextlink_up),id_next);
    nextid_down  = link_get_oposite(game_get_link_from_id(game,nextlink_down),id_next);


    space_left= game_get_space(game, id_left);
    uplink_left=space_get_up(space_left);
    downlink_left=space_get_down(space_left);
    space_right= game_get_space(game, id_right);
    uplink_right =space_get_up(space_right);
    downlink_right=space_get_down(space_right);
    nextspace_left= game_get_space(game, nextid_left);
    nextspace_right= game_get_space(game, nextid_right);

    if(link_get_open(game_get_link_from_id(game, link_back)) == TRUE){
      strcpy(opened, "  OPEN");
    }
    else{
      strcpy(opened, "CLOSED");
    }

    if (id_back != NO_ID) {
      sprintf(str, "                            %s ^ %s", opened , link_get_name(game_get_link_from_id(game, link_back)));
      screen_area_puts(ge->map, str);
    }
    
    strcpy(top,"       ");
    strcpy(middle, "       ");
    strcpy(bottom,"       ");
    strcpy(topleft,"       ");
    strcpy(middleleft, "       ");
    strcpy(bottomleft,"       ");
    strcpy(topright,"       ");
    strcpy(middleright, "       ");
    strcpy(bottomright,"       ");
    strcpy(obj1, "   ");   

    nids = space_get_num_objects(game_get_space(game, id_act));
    strcpy(objs1, "");
    strcpy(objs2, "");
    strcpy(objs1left, "");
    strcpy(objs2left, "");
    strcpy(objs1right, "");
    strcpy(objs2right, "");
    for(i=0; i<nids/2; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(space_act, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(space_act, i))));
        strcat(objs1, obj1);
        strcat(objs1, " ");
      }
    }
    
    for(; i<nids; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(space_act, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(space_act, i))));
        strcat(objs2, obj1);
        strcat(objs2, " ");
      }
    }
   

    nids = space_get_num_objects(game_get_space(game, id_left));
    for(i=0; i<nids/2; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(space_left, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(space_left, i))));
        strcat(objs1left, obj1);
        strcat(objs1left, " ");
      }
    }
    
    for(; i<nids; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(space_left, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(space_left, i))));
        strcat(objs2left, obj1);
        strcat(objs2left, " ");
      }
    }



    nids = space_get_num_objects(game_get_space(game, id_right));
    for(i=0; i<nids/2; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(space_right, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(space_right, i))));
        strcat(objs1right, obj1);
        strcat(objs1right, " ");
      }
    }
    
    for(; i<nids; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(space_right, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(space_right, i))));
        strcat(objs2right, obj1);
        strcat(objs2right, " ");
      }
    }




    while(strlen(objs1)<MAX_UPS){
      strcat(objs1, " ");
    }
    while(strlen(objs2)<MAX_UPS){
      strcat(objs2, " ");
    }

    while(strlen(objs1left)<MAX_UPS){
      strcat(objs1left, " ");
    }
    while(strlen(objs2left)<MAX_UPS){
      strcat(objs2left, " ");
    }

    while(strlen(objs1right)<MAX_UPS){
      strcat(objs1right, " ");
    }
    while(strlen(objs2right)<MAX_UPS){
      strcat(objs2right, " ");
    }

    draw=space_get_draw(game_get_space(game, id_act));
    drawleft=space_get_draw(game_get_space(game, id_left));
    drawright=space_get_draw(game_get_space(game, id_right));
    if(draw!=NULL){
    
      for(i=0; i<MAX_ADD; i++){
        top[i]=draw[i];
      }
      for(i=MAX_ADD; i<2*MAX_ADD; i++){
        middle[i-MAX_ADD]=draw[i];
      }
      for(i=2*MAX_ADD; i<3*MAX_ADD; i++){
        bottom[i-(2*MAX_ADD)]=draw[i];
      }
    }
    if(drawleft!=NULL){
    
      for(i=0; i<MAX_ADD; i++){
        topleft[i]=drawleft[i];
      }
      for(i=MAX_ADD; i<2*MAX_ADD; i++){
        middleleft[i-MAX_ADD]=drawleft[i];
      }
      for(i=2*MAX_ADD; i<3*MAX_ADD; i++){
        bottomleft[i-(2*MAX_ADD)]=drawleft[i];
      }
    }
    
    if(drawright!=NULL){
    
      for(i=0; i<MAX_ADD; i++){
        topright[i]=drawright[i];
      }
      for(i=MAX_ADD; i<2*MAX_ADD; i++){
        middleright[i-MAX_ADD]=drawright[i];
      }
      for(i=2*MAX_ADD; i<3*MAX_ADD; i++){
        bottomright[i-(2*MAX_ADD)]=drawright[i];
      }
    }
    
    if(link_up!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, link_up)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
        
      
      sprintf(up, "%s ^ %s %ld", opened, link_get_name(game_get_link_from_id(game, link_up)), id_up);
      fill=strlen(up);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(up, simbol);
      }
    }
    else {sprintf(up, "               ");}
    
    if(uplink_left!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, link_left)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(upleft, "%s ^ %s %ld", opened, link_get_name(game_get_link_from_id(game, uplink_left)), link_get_oposite(game_get_link_from_id(game,uplink_left), id_left));
      fill=strlen(upleft);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(upleft, simbol);
      }
    }
    else {sprintf(upleft, "               ");}

    if(uplink_right!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, link_right)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(upright, "%s ^ %s %ld", opened, link_get_name(game_get_link_from_id(game, uplink_right)), link_get_oposite(game_get_link_from_id(game,uplink_right), id_right));
    fill=strlen(upright);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(upright, simbol);
      }
    }
    else {sprintf(upright, "               ");}


    if(link_down!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, link_down)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(down, "%s v %s %ld",opened ,link_get_name(game_get_link_from_id(game, link_down)), id_down);
      fill=strlen(down);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(down, simbol);
      }
    }
    else {sprintf(down, "               ");}

    if(downlink_left!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, downlink_left)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(downleft,  "%s v %s %ld",opened ,link_get_name(game_get_link_from_id(game, downlink_left)), link_get_oposite(game_get_link_from_id(game,downlink_left), id_left));
    fill=strlen(downleft);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(downleft, simbol);
      }
    }
    else {sprintf(downleft, "               ");}
    if(downlink_right!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, downlink_right)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(downright,  "%s v %s %ld",opened ,link_get_name(game_get_link_from_id(game, downlink_right)), link_get_oposite(game_get_link_from_id(game,downlink_right), id_right));
    fill=strlen(downright);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(downright, simbol);
      }
    }
    else {sprintf(downright, "               ");}

  if (id_act != NO_ID) {
    
    /*CURRENT*/
      if(id_left != NO_ID){sprintf(str, "  +---------------+        "); }
      else {sprintf(str, "                           ");}

      sprintf(simbol, "+---------------+"); strcat(str, simbol);
      
      if(id_right != NO_ID){sprintf(simbol, "        +---------------+"); strcat(str, simbol);}
      screen_area_puts(ge->map, str);
  


      if(id_left != NO_ID){sprintf(str, "  |             %2d|      ",(int) id_left);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  |(>'-')>      %2d|",(int) id_act); strcat(str, simbol);

      if(id_right != NO_ID){sprintf(simbol,"        |             %2d|",(int) id_right); strcat(str, simbol);}
      screen_area_puts(ge->map, str);



      if(id_left != NO_ID){
        strcpy(helpchar, link_get_name(game_get_link_from_id(game, link_left)));
        for(i=strlen(helpchar); i<6; i++){
          sprintf(simbol, " "); strcat(helpchar, simbol);
        }

        sprintf(str, "  |     %s   | %s ",topleft, helpchar);
        sprintf(simbol, " ");
        
        fill=strlen(str);
        for(i=fill; i<21; i++){
          strcat(str, simbol);
        }
      }
      
      


      else {sprintf(str, "                           ");}

      sprintf(simbol, "|     %s   |",top); strcat(str, simbol);

      if(id_right != NO_ID){
        strcpy(helpchar, link_get_name(game_get_link_from_id(game, link_right)));
        for(i=strlen(helpchar); i<6; i++){
          sprintf(simbol, " "); strcat(helpchar, simbol);
        }

        sprintf(simbol," %s |     %s   |",helpchar,topright); 
        strcat(str, simbol);
        sprintf(simbol, " ");
        
      fill=strlen(str);
      for(i=fill; i<21; i++){
        strcat(str, simbol);
      }
      
      }
      screen_area_puts(ge->map, str);



      
      if(id_left != NO_ID){sprintf(str, "  |     %s   |  <--",middleleft);}
      else {sprintf(str, "                        ");}

      sprintf(simbol, "   |     %s   |",middle); strcat(str, simbol);

      if(id_right != NO_ID){sprintf(simbol,"  -->   |     %s   |",middleright); strcat(str, simbol);}
      screen_area_puts(ge->map, str);

      


      if(id_left != NO_ID){
        if(link_get_open(game_get_link_from_id(game, link_left)) == TRUE){
          strcpy(opened, " OPEN ");
        }
        else{
          strcpy(opened, "CLOSED");
        }
        
        sprintf(str, "  |     %s   | %s ",bottomleft,opened);}

      else {sprintf(str, "                           ");}

      sprintf(simbol, "|     %s   |",bottom); strcat(str, simbol);

      if(id_right != NO_ID){
        if(link_get_open(game_get_link_from_id(game, link_right)) == TRUE){
          strcpy(opened, " OPEN ");
        }
        else{
          strcpy(opened, "CLOSED");
        }

        sprintf(simbol," %s |     %s   |",opened, bottomright); strcat(str, simbol);
        }
      screen_area_puts(ge->map, str);




      if(id_left != NO_ID){sprintf(str, "  | %s|      ",objs1left);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  | %s|",objs1); strcat(str, simbol);

      if(id_right != NO_ID){sprintf(simbol,"        | %s|",objs1right); strcat(str, simbol);}
      screen_area_puts(ge->map, str);



   
      if(id_left != NO_ID){sprintf(str, "  | %s|      ",objs2left);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  | %s|",objs2); strcat(str, simbol);

      if(id_right != NO_ID){sprintf(simbol,"        | %s|",objs2right); strcat(str, simbol);}
      screen_area_puts(ge->map, str);


      if(id_left != NO_ID){sprintf(str, "  |%s|      ",downleft);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  |%s|",down); strcat(str, simbol);

      if(id_right != NO_ID){sprintf(simbol,"        |%s|",downright); strcat(str, simbol);}
      screen_area_puts(ge->map, str);


      if(id_left != NO_ID){sprintf(str, "  |%s|      ",upleft);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  |%s|",up); strcat(str, simbol);

      if(id_right != NO_ID){sprintf(simbol,"        |%s|",upright); strcat(str, simbol);}
      screen_area_puts(ge->map, str);



      if(id_left != NO_ID){sprintf(str, "  +---------------+     ");}
      else {sprintf(str, "                        ");}
      sprintf(simbol, "   +---------------+"); strcat(str, simbol);
      if(id_right != NO_ID){sprintf(simbol, "        +---------------+"); strcat(str, simbol);}
      screen_area_puts(ge->map, str);
    }

    
    strcpy(top,"       ");
    strcpy(middle, "       ");
    strcpy(bottom,"       ");
    strcpy(topleft,"       ");
    strcpy(middleleft, "       ");
    strcpy(bottomleft,"       ");
    strcpy(topright,"       ");
    strcpy(middleright, "       ");
    strcpy(bottomright,"       ");
    strcpy(obj1, "   ");  
    

    nids = space_get_num_objects(game_get_space(game, id_next));
    strcpy(objs1, "");
    strcpy(objs2, "");
    strcpy(objs1left, "");
    strcpy(objs2left, "");
    strcpy(objs1right, "");
    strcpy(objs2right, "");

    for(i=0; i<nids/2; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(space_next, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(space_next, i))));
        strcat(objs1, obj1);
        strcat(objs1, " ");
      }
    }
    
    for(; i<nids; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(space_next, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(space_next, i))));
        strcat(objs2, obj1);
        strcat(objs2, " ");
      }
    }
   
/*you need to get nextspace_left and nextspace_right*/
    nids = space_get_num_objects(game_get_space(game, nextid_left));
    for(i=0; i<nids/2; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(nextspace_left, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(nextspace_left, i))));
        strcat(objs1left, obj1);
        strcat(objs1left, " ");
      }
    }
    
    for(; i<nids; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(nextspace_left, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(nextspace_left, i))));
        strcat(objs2left, obj1);
        strcat(objs2left, " ");
      }
    }



    nids = space_get_num_objects(game_get_space(game, nextid_right));
    for(i=0; i<nids/2; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(nextspace_right, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(nextspace_right, i))));
        strcat(objs1right, obj1);
        strcat(objs1right, " ");
      }
    }
    
    for(; i<nids; i++){
      if (Object_get_visibility(game_get_object_from_id(game, space_get_object_id_from_index(nextspace_right, i))) == VISIBLE) {
        strcpy(obj1, Object_get_name(game_get_object_from_id(game, space_get_object_id_from_index(nextspace_right, i))));
        strcat(objs2right, obj1);
        strcat(objs2right, " ");
      }
    }




    while(strlen(objs1)<MAX_UPS){
      strcat(objs1, " ");
    }
    while(strlen(objs2)<MAX_UPS){
      strcat(objs2, " ");
    }

    while(strlen(objs1left)<MAX_UPS){
      strcat(objs1left, " ");
    }
    while(strlen(objs2left)<MAX_UPS){
      strcat(objs2left, " ");
    }

    while(strlen(objs1right)<MAX_UPS){
      strcat(objs1right, " ");
    }
    while(strlen(objs2right)<MAX_UPS){
      strcat(objs2right, " ");
    }

    draw=space_get_draw(game_get_space(game, id_next));
    drawleft=space_get_draw(game_get_space(game, nextid_left));
    drawright=space_get_draw(game_get_space(game, nextid_right));
    if(draw!=NULL){
    
      for(i=0; i<MAX_ADD; i++){
        top[i]=draw[i];
      }
      for(i=MAX_ADD; i<2*MAX_ADD; i++){
        middle[i-MAX_ADD]=draw[i];
      }
      for(i=2*MAX_ADD; i<3*MAX_ADD; i++){
        bottom[i-(2*MAX_ADD)]=draw[i];
      }
    }
    if(drawleft!=NULL){
    
      for(i=0; i<MAX_ADD; i++){
        topleft[i]=drawleft[i];
      }
      for(i=MAX_ADD; i<2*MAX_ADD; i++){
        middleleft[i-MAX_ADD]=drawleft[i];
      }
      for(i=2*MAX_ADD; i<3*MAX_ADD; i++){
        bottomleft[i-(2*MAX_ADD)]=drawleft[i];
      }
    }
    
    if(drawright!=NULL){
    
      for(i=0; i<MAX_ADD; i++){
        topright[i]=drawright[i];
      }
      for(i=MAX_ADD; i<2*MAX_ADD; i++){
        middleright[i-MAX_ADD]=drawright[i];
      }
      for(i=2*MAX_ADD; i<3*MAX_ADD; i++){
        bottomright[i-(2*MAX_ADD)]=drawright[i];
      }
    }



nextuplink_left=space_get_up(game_get_space(game, nextid_left));
nextuplink_right=space_get_up(game_get_space(game, nextid_right));

nextdownlink_left=space_get_down(game_get_space(game, nextid_left));
nextdownlink_right=space_get_down(game_get_space(game, nextid_right));


if(nextlink_up!=NO_ID){
  if(link_get_open(game_get_link_from_id(game, nextlink_up)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
  sprintf(nextup, "%s ^ %s %ld", opened, link_get_name(game_get_link_from_id(game, nextlink_up)), nextid_up);
      fill=strlen(nextup);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(nextup, simbol);
      }
    }
    else {sprintf(nextup, "               ");}
    
    if(nextuplink_left!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, nextuplink_left)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(nextupleft, "%s ^ %s %ld", opened, link_get_name(game_get_link_from_id(game, nextuplink_left)), link_get_oposite(game_get_link_from_id(game,nextuplink_left), nextid_left));
      fill=strlen(nextupleft);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(nextupleft, simbol);
      }
    }
    else {sprintf(nextupleft, "               ");}

    if(nextuplink_right!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, nextuplink_right)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(nextupright, "%s ^ %s %ld", opened, link_get_name(game_get_link_from_id(game, nextuplink_right)), link_get_oposite(game_get_link_from_id(game,nextuplink_right), nextid_right));
    fill=strlen(nextupright);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(nextupright, simbol);
      }
    }
    else {sprintf(nextupright, "               ");}


    if(nextlink_down!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, nextlink_down)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(nextdown,  "%s v %s %ld",opened ,link_get_name(game_get_link_from_id(game, nextlink_down)), nextid_down);
      fill=strlen(nextdown);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(nextdown, simbol);
      }
    }
    else {sprintf(nextdown, "               ");}

    if(nextdownlink_left!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, nextdownlink_left)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(nextdownleft,  "%s v %s %ld",opened ,link_get_name(game_get_link_from_id(game, nextdownlink_left)), link_get_oposite(game_get_link_from_id(game,nextdownlink_left), nextid_left));
    fill=strlen(nextdownleft);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(nextdownleft, simbol);
      }
    }
    else {sprintf(nextdownleft, "               ");}
    
    if(nextdownlink_right!=NO_ID){
      if(link_get_open(game_get_link_from_id(game, nextdownlink_right)) == TRUE){
          strcpy(opened, "OP");
        }
        else{
          strcpy(opened, "CL");
        }
      sprintf(nextdownright,  "%s v %s %ld",opened ,link_get_name(game_get_link_from_id(game, nextdownlink_right)), link_get_oposite(game_get_link_from_id(game,nextdownlink_right), nextid_right));
    fill=strlen(nextdownright);
      for(i=fill; i<15; i++){
        sprintf(simbol," ");
        strcat(nextdownright, simbol);
      }
    }
    else {sprintf(nextdownright, "               ");}




    if(link_get_open(game_get_link_from_id(game, link_next)) == TRUE){
      strcpy(opened, "  OPEN");
    }
    else{
      strcpy(opened, "CLOSED");
    }



    
    if (id_next != NO_ID) {
    sprintf(str, "                            %s v %s", opened, link_get_name(game_get_link_from_id(game, link_next)));
    screen_area_puts(ge->map, str);
    memset(str, 0, sizeof(char)); 
    /*CURRENT*/
      if(nextid_left != NO_ID){sprintf(str, "  +---------------+        "); }
      else {sprintf(str, "                           ");}

      sprintf(simbol, "+---------------+"); strcat(str, simbol);
      
      if(nextid_right != NO_ID){sprintf(simbol, "        +---------------+"); strcat(str, simbol);}
      screen_area_puts(ge->map, str);
  


      if(nextid_left != NO_ID){sprintf(str, "  |             %2d|      ",(int) nextid_left);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  |             %2d|",(int) id_next); strcat(str, simbol);

      if(nextid_right != NO_ID){sprintf(simbol,"        |             %2d|",(int) nextid_right); strcat(str, simbol);}
      screen_area_puts(ge->map, str);



      if(nextid_left != NO_ID){
        strcpy(helpchar, link_get_name(game_get_link_from_id(game, nextlink_left)));
        for(i=strlen(helpchar); i<6; i++){
          sprintf(simbol, " "); strcat(helpchar, simbol);
        }
        
        sprintf(str, "  |     %s   | %s ",topleft, helpchar);
        sprintf(simbol, " ");
        
        fill=strlen(str);
        for(i=fill; i<21; i++){
          strcat(str, simbol);
        }
      }
      
      


      else {sprintf(str, "                           ");}

      sprintf(simbol, "|     %s   |",top); strcat(str, simbol);
    
      if(nextid_right != NO_ID){
        strcpy(helpchar, link_get_name(game_get_link_from_id(game, nextlink_right)));
        for(i=strlen(helpchar); i<6; i++){
          sprintf(simbol, " "); strcat(helpchar, simbol);
        }
        sprintf(simbol," %s |     %s   |",helpchar,topright); 
      strcat(str, simbol);
      sprintf(simbol, " ");
        
      fill=strlen(str);
      for(i=fill; i<21; i++){
        strcat(str, simbol);
      }
      
      }
      screen_area_puts(ge->map, str);



      
      if(nextid_left != NO_ID){sprintf(str, "  |     %s   |  <--",middleleft);}
      else {sprintf(str, "                        ");}

      sprintf(simbol, "   |     %s   |",middle); strcat(str, simbol);

      if(nextid_right != NO_ID){sprintf(simbol,"  -->   |     %s   |",middleright); strcat(str, simbol);}
      screen_area_puts(ge->map, str);




      if(nextid_left != NO_ID){
        
        if(link_get_open(game_get_link_from_id(game, nextlink_left)) == TRUE){
          strcpy(opened, " OPEN ");
        }
        else{
          strcpy(opened, "CLOSED");
        }
        
        sprintf(str, "  |     %s   | %s ",bottomleft,opened);
        
        }
      else {sprintf(str, "                           ");}

      sprintf(simbol, "|     %s   |",bottom); strcat(str, simbol);

      if(nextid_right != NO_ID){
        
        if(link_get_open(game_get_link_from_id(game, nextlink_right)) == TRUE){
          strcpy(opened, " OPEN ");
        }
        else{
          strcpy(opened, "CLOSED");
        }

        sprintf(simbol," %s |     %s   |",opened, bottomright); strcat(str, simbol);
        
        }
      screen_area_puts(ge->map, str);




      if(nextid_left != NO_ID){sprintf(str, "  | %s|      ",objs1left);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  | %s|",objs1); strcat(str, simbol);

      if(nextid_right != NO_ID){sprintf(simbol,"        | %s|",objs1right); strcat(str, simbol);}
      screen_area_puts(ge->map, str);



   
      if(nextid_left != NO_ID){sprintf(str, "  | %s|      ",objs2left);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  | %s|",objs2); strcat(str, simbol);

      if(nextid_right != NO_ID){sprintf(simbol,"        | %s|",objs2right); strcat(str, simbol);}
      screen_area_puts(ge->map, str);


      if(nextid_left != NO_ID){sprintf(str, "  |%s|      ",nextdownleft);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  |%s|",nextdown); strcat(str, simbol);

      if(nextid_right != NO_ID){sprintf(simbol,"        |%s|",nextdownright); strcat(str, simbol);}
      screen_area_puts(ge->map, str);



      if(nextid_left != NO_ID){sprintf(str, "  |%s|      ",nextupleft);}
      else {sprintf(str, "                         ");}

      sprintf(simbol, "  |%s|",nextup); strcat(str, simbol);

      if(nextid_right != NO_ID){sprintf(simbol,"        |%s|",nextupright); strcat(str, simbol);}
      screen_area_puts(ge->map, str);


            
      if(nextid_left != NO_ID){sprintf(str, "  +---------------+     ");}
      else {sprintf(str, "                        ");}
      sprintf(simbol, "   +---------------+"); strcat(str, simbol);
      if(nextid_right != NO_ID){sprintf(simbol, "        +---------------+"); strcat(str, simbol);}
      screen_area_puts(ge->map, str);
    }


  }


  /* Paint the in the description area */


  if(game_get_last_command(game)==INSPECT && game_get_last_status(game)==OK){

    if(space_get_illuminated(game_get_space(game, id_act)) == FALSE ){
      screen_area_clear(ge->descript);
      sprintf(str, "The %s is not illuminated.", space_get_name(game_get_space(game, id_act)));
      screen_area_puts(ge->descript, str);
    } else {

      if(strcmp(game_get_particular_obj(game), "space") == 0 ){
      screen_area_clear(ge->descript);

      sprintf(str, " %s's description:", space_get_name(game_get_space(game, game_get_player_location(game))));
      screen_area_puts(ge->descript, str);

      if(!strcmp(space_get_detailed_desc(game_get_space(game, game_get_player_location(game))), "") || !strcmp(space_get_detailed_desc(game_get_space(game, game_get_player_location(game))), " ")){
        sprintf(str, " No description avaliable for this space.");
        screen_area_puts(ge->descript, str);
      }else{
        
        sprintf(str, " %s ", space_get_detailed_desc(game_get_space(game, game_get_player_location(game))) );
        screen_area_puts(ge->descript, str);
        
      }



      }
      else if(strcmp(game_get_particular_obj(game), "") != 0 && Object_get_visibility(game_get_object_fromName(game, game_get_particular_obj(game))) == VISIBLE){

        screen_area_clear(ge->descript);
        sprintf(str, " %s's description: ", game_get_particular_obj(game));
        screen_area_puts(ge->descript, str);


        if(Object_get_visibility(game_get_object_fromName(game, game_get_particular_obj(game))) == HIDDEN || !strcmp(Object_get_description(game_get_object_fromName(game, game_get_particular_obj(game))), "" )){
          sprintf(str, " No description avaliable for this object.");
          screen_area_puts(ge->descript, str);
        } else if (Object_get_moved(game_get_object_fromName(game, game_get_particular_obj(game))) == TRUE) {
          sprintf(str, "%s", Object_get_second_description(game_get_object_fromName(game, game_get_particular_obj(game))) );
          screen_area_puts(ge->descript, str);
        } else if (Object_get_moved(game_get_object_fromName(game, game_get_particular_obj(game))) == TRUE && space_get_illuminated(game_get_space(game, id_act)) == TRUE) {
          sprintf(str, "%s", Object_get_illuminated_description(game_get_object_fromName(game, game_get_particular_obj(game))));
          screen_area_puts(ge->descript, str);
        } else{
          sprintf(str, "%s", Object_get_description(game_get_object_fromName(game, game_get_particular_obj(game))) );
          screen_area_puts(ge->descript, str);
        }
      }
      if(strcmp(game_get_particular_obj(game), "space") == 0 ){
        screen_area_clear(ge->descript);

        sprintf(str, " %s's description:", space_get_name(game_get_space(game, game_get_player_location(game))));
        screen_area_puts(ge->descript, str);

      if(!strcmp(space_get_detailed_desc(game_get_space(game, game_get_player_location(game))), "") || !strcmp(space_get_detailed_desc(game_get_space(game, game_get_player_location(game))), " ")){
        sprintf(str, " No description avaliable for this space.");
        screen_area_puts(ge->descript, str);
      }else{
        
        sprintf(str, "%s", space_get_detailed_desc(game_get_space(game, game_get_player_location(game))) );
        screen_area_puts(ge->descript, str);
        
      }



    }
    else if(strcmp(game_get_particular_obj(game), "") != 0 && Object_get_visibility(game_get_object_fromName(game, game_get_particular_obj(game))) == VISIBLE){

      screen_area_clear(ge->descript);
      sprintf(str, "%s's description: ", game_get_particular_obj(game));
      screen_area_puts(ge->descript, str);


      if(Object_get_visibility(game_get_object_fromName(game, game_get_particular_obj(game))) == HIDDEN || !strcmp(Object_get_description(game_get_object_fromName(game, game_get_particular_obj(game))), "" )){
        sprintf(str, "No description avaliable for this object.");
        screen_area_puts(ge->descript, str);
      } else if (Object_get_moved(game_get_object_fromName(game, game_get_particular_obj(game))) == TRUE) {
        sprintf(str, "%s", Object_get_second_description(game_get_object_fromName(game, game_get_particular_obj(game))) );
        screen_area_puts(ge->descript, str);
      } else if (Object_get_moved(game_get_object_fromName(game, game_get_particular_obj(game))) == TRUE && space_get_illuminated(game_get_space(game, id_act)) == TRUE) {
          sprintf(str, "%s", Object_get_illuminated_description(game_get_object_fromName(game, game_get_particular_obj(game))));
          screen_area_puts(ge->descript, str);
      } else{
        sprintf(str, "%s", Object_get_description(game_get_object_fromName(game, game_get_particular_obj(game))) );
        screen_area_puts(ge->descript, str);
      }
    }

    }
    
  }
  else {

    screen_area_clear(ge->descript);

    if(space_get_illuminated(space_act) == TRUE){ sprintf(str, "      Space illuminated"); color=TRUE;}
    else{  sprintf(str, "     Space NOT illuminated"); color=FALSE;}
    
    screen_area_puts(ge->descript, str);
    sprintf(str, " ");
    screen_area_puts(ge->descript, str);

    if ( id_act != NO_ID && ( strcmp(space_get_description(game_get_space(game, id_act)), " " ) != 0 && strcmp(space_get_description(game_get_space(game, id_act)), "" ) != 0 ) ){
      sprintf(str, "Space: %s", space_get_description(game_get_space(game, id_act)));
      screen_area_puts(ge->descript, str);
      sprintf(str, " ");
      screen_area_puts(ge->descript, str);
    }
    

    sprintf(str, "Objects Location: ");
    screen_area_puts(ge->descript, str);

    strcpy(str, "\0");
  
  
  
    cuanttobj=game_get_max_objects(game);
  

  for(j=0; j<cuanttobj; j++){
    obj_loc1=game_get_object_location(game, Object_get_id(game_get_object_by_order(game,j)));
    
    if(obj_loc1!=NO_ID && Object_get_visibility(game_get_object_by_order(game,j)) == VISIBLE) {
      sprintf(add, "%s: %ld", Object_get_name(game_get_object_by_order(game,j)), obj_loc1);
      strcat(str,add);
      counterforcommas=game_get_max_objects(game)-1;
      if (j != counterforcommas) { strcat(str, ", "); }
    }
    
      if(strlen(str)>=MAX_LINE_OBJ){  
        screen_area_puts(ge->descript, str);
        strcpy(str, "\0");
      }
    }
  
    screen_area_puts(ge->descript, str);
    sprintf(str, " ");
    screen_area_puts(ge->descript, str);



    last_roll=die_get_last_roll(game_get_die(game));

    if(player_get_objects(game_get_player(game)) != NULL) {
      strcpy(str, "Player's Objects: ");
      screen_area_puts(ge->descript, str);
      strcpy(str, "\0");


      for (i = 0; i < player_get_num_of_objects(game_get_player(game)) && player_get_particular_object(game_get_player(game), i) != NO_ID; i++) {    
        strcat(str, Object_get_name(game_get_object_from_id(game, player_get_particular_object(game_get_player(game), i))));
        if (i != player_get_num_of_objects(game_get_player(game)) - 1) {
          strcat(str, ", ");
        }
        if(strlen(str)>=MAX_LINE_PLAYER){  
          screen_area_puts(ge->descript, str);
          strcpy(str, "\0");
        }
      }
      screen_area_puts(ge->descript, str);
    }
    sprintf(str, " ");
    screen_area_puts(ge->descript, str);

    sprintf(str, "Last Die Roll:%ld", last_roll);
    screen_area_puts(ge->descript, str);

  }
  

  /* Paint the in the banner area */
  screen_area_puts(ge->banner, game_get_name(game));

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " move(m), pick_up(p), drop(d), inspect(i), turnon(ton), exit(e), save(s), load(l)");
  screen_area_puts(ge->help, str);
  sprintf(str, " turnoff(tof), roll(rl), open linkname w objname, show_object(so), hide_object(ho)");
  screen_area_puts(ge->help, str);
  
  /* Paint in the feedback area */
  dialogue=Dialogue_interact_with_player(game, game_get_dialogue(game), game_get_last_command(game), game_get_last_status(game));
  screen_area_puts(ge->feedback, dialogue);
  if (executed == TRUE) {
    screen_area_puts(ge->feedback, "The game has just acted in a random way. Be aware!");
  }
  free(dialogue);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
  screen_area_clear(ge->map);

}