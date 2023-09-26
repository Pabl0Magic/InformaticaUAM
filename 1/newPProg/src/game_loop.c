/** 
 * @brief It defines the game loop 
 * 
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graphic_engine.h"
#include "command.h"
#include "game_rules.h"

#define DIVISOR_FOR_INTERRUPTIONS 9			/*!< It allows us to have the desired remainder */
#define MIN_TURNS_WITHOUT_INTERRUPTION 6	/*!< It defines the min number of turns that the random functions from game rules will not execute */

/**
 * @brief Main function to execute all the game
 * 
 * @param argc Number of arguments that will be introduced
 * @param argv The name of the arguments that will be introduced
 * @return int 0 if it finishes 
 */
int main(int argc, char *argv[]){
  	FILE *pf=NULL;
  	char str[MAX_TXT+10]="", command_status[MAX_TXT]="";
  	extern char *cmd_to_str[];
	Game *game=NULL; T_Command command = NO_CMD; Graphic_engine *gengine;
	int random_num_of_turns;
	int turn_idx = 0;
	srand(time(NULL));
	random_num_of_turns = (rand() % DIVISOR_FOR_INTERRUPTIONS + MIN_TURNS_WITHOUT_INTERRUPTION);

	if (argc < 2){fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]); return 1;}
	
	if(argv[2] && strcmp(argv[2], "-l") == 0){
		if(argc<4){printf("Use: %s <game_data_file> -l filename.txt\n", argv[0]);}
		pf = fopen(argv[3], "w");
		if(!pf)  return 1;
	}

	if (game_create_from_file(&game, argv[1]) == ERROR){fprintf(stderr, "Error while initializing game.\n"); game_destroy(game); return 1;}
	if ((gengine = graphic_engine_create()) == NULL){fprintf(stderr, "Error while initializing graphic engine.\n"); game_destroy(game); return 1;}

	if ((gengine = graphic_engine_create()) == NULL){
		fprintf(stderr, "Error while initializing graphic engine.\n"); 
		game_destroy(game); 
		return 1;
	}
	while ( (command != EXIT) && !game_is_over(game) ){
		graphic_engine_paint_game(gengine, game);
		executed = FALSE;
		command = command_get_user_input();
		game_update(game, command); 
		turn_idx++;
		if (turn_idx == random_num_of_turns) {
			game_rules_execute(game);
			executed = TRUE;
			random_num_of_turns = (rand() % DIVISOR_FOR_INTERRUPTIONS + MIN_TURNS_WITHOUT_INTERRUPTION);
			turn_idx = 0;
		}
		if(argv[2] && strcmp(argv[2], "-l") == 0){
			if(game_get_last_command(game) == UNKNOWN){	sprintf(command_status, " ");}
				
			else{ 
				if(game_get_last_status(game)){ sprintf(command_status, ": OK"); }
				else {
					sprintf(command_status, ": ERROR");	
				}
			}
			
			if(((game_get_last_command(game) == PICK || game_get_last_command(game) == DROP || game_get_last_command(game) == INSPECT || game_get_last_command(game) == MOVE) 
			|| game_get_last_command(game) == HIDE || game_get_last_command(game) == SHOW) && strcmp(game_get_particular_obj(game), "") != 0) {
				sprintf(str, "%s %s%s\n",cmd_to_str[game_get_last_command(game)-NO_CMD], game_get_particular_obj(game), command_status);
			}else{ 
				sprintf(str, "%s%s\n",cmd_to_str[game_get_last_command(game)-NO_CMD], command_status);
			}

				fprintf(pf,"%s",str);
		}
	}
	game_destroy(game);
	graphic_engine_destroy(gengine);
	if(pf){ fclose(pf); }
	return 0;
}