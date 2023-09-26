/** 
 * @brief Handles the tries for actions and returns an elaborate answer
 * 
 * @file dialogue.c
 * @author Rodrigo Juez
 * @version 1.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialogue.h"

/**
 * @brief Manages a command type to know what command is used
 * and strings to manage the direction in the move command and
 * object to manage the commands involving objects
 * 
 */
struct _Dialogue {
    T_Command repeated;                     /*!< repeated The field that will be used if some command is repeated */
    char direction[MAX_OBJ_NAME];           /*!< direction The field used for move command */
    char object[MAX_OBJ_NAME];              /*!< object The field used for interactions with commands and objects */
};

/*Allocating memory for dialogue module */
Dialogue* Dialogue_ini(){
    Dialogue* new=NULL;
    new=(Dialogue*)malloc(sizeof(Dialogue));
    if(!new){return NULL;}

    new->repeated = NO_CMD;
    strcpy(new->direction, "");
    strcpy(new->object, "");
    return new;
}

/*Destroying the memory allocated*/
void Dialogue_destroy(Dialogue *dialogue){
    if(dialogue){
        free(dialogue);
    }
}

/*Set if some command is repeated*/
STATUS Dialogue_set_repeated(Dialogue *dialogue, T_Command rep){
    if(!dialogue || rep == NO_CMD) return ERROR;
    dialogue->repeated = rep;
    return OK;
}

/*Interact with the player*/
char* Dialogue_interact_with_player(Game* game, Dialogue *dialogue, T_Command action, STATUS success){
    BOOL repeated=FALSE;
    char *phrase=NULL;
    if(!dialogue|| action < -1){return ERROR;}

    if(action == MOVE && action == dialogue->repeated && dialogue->direction!=NULL){
        if(strcmp(game_get_particular_obj(game), dialogue->direction) == 0){
            repeated = TRUE;
        }
        strcpy(dialogue->direction, game_get_particular_obj(game));
    } else if((action == PICK || action == DROP || action == INSPECT || action == TURNON || action == TURNOFF || action == SHOW || action == HIDE) && action == dialogue->repeated && dialogue->object!=NULL) {
        if(strcmp(game_get_particular_obj(game), dialogue->object) == 0){
            repeated = TRUE;
        }
        strcpy(dialogue->object, game_get_particular_obj(game));
    } else if(action == OPENLINK && action == dialogue->repeated && dialogue->direction!=NULL && dialogue->object!=NULL){ 
        if(strcmp(game_get_particular_obj(game), dialogue->object) == 0 && strcmp(game_get_particular_link(game), dialogue->direction) == 0){
            repeated = TRUE;
        }
        strcpy(dialogue->direction, game_get_particular_link(game));
        strcpy(dialogue->object, game_get_particular_obj(game));
    } else if(action == dialogue->repeated){
        repeated = TRUE;
    }
            
    dialogue->repeated = action;

    phrase=(char*)malloc(sizeof(char)*MAX_DESC);
    if(!phrase) return NULL;
    memset(phrase, 0, sizeof(char));
    if(action==UNKNOWN){
        if(repeated){
            sprintf(phrase, "Don't you know how to type?!");
        }
        else{
            sprintf(phrase, "Please try a valid command");
        }
    }

    if(action==EXIT){
        sprintf(phrase, "Game Over");
    }

    if(action==PICK){
        if(success==OK){
            sprintf(phrase, "You now have %s in your inventory", game_get_particular_obj(game));
        }
        else{
            if(repeated){
                sprintf(phrase, "Hey, you just tried that. Don't you see you cannot pick %s?", game_get_particular_obj(game));
            }
            else{
                sprintf(phrase, "You cannot pick %s.", game_get_particular_obj(game));
            }
        }
        
    }

    if(action==DROP){
        if(success==OK){
            sprintf(phrase, "You don't have %s in your inventory any more", game_get_particular_obj(game));
        }
        else{
            if(repeated){
                sprintf(phrase, "You have already tried to drop %s, you don't have it in your inventory!!!", game_get_particular_obj(game));
            }
            else{
                sprintf(phrase, "You don't have %s in your inventory so you cannot drop it.", game_get_particular_obj(game));
            }
        }
        
    }

    if(action==ROLL){
        if(success==OK){
            sprintf(phrase, "You have rolled the die succesfully. You got a %d.", die_get_last_roll(game_get_die(game)));
        }
        else{
            if(repeated){
                sprintf(phrase, "You have alredy tried to roll the die without success. Try another action.");
            }
            else{
                sprintf(phrase, "Rolling the die didn't work mate.");
            }
        }
        
    }

    if(action==INSPECT){
        if(success==OK){
            sprintf(phrase, "You've inspected %s, you have the descrition in the right", game_get_particular_obj(game));
        }
        else{
            if(repeated){
                sprintf(phrase, "You have tried to inspect %s without success why bothering to try again?", game_get_particular_obj(game));
            }
            else{
                sprintf(phrase, "You can't inspect %s, where is it?", game_get_particular_obj(game));
            }
        }
        
    }

    if(action==MOVE){
        if(success==OK){
            sprintf(phrase, "You've gone %s. Now you are in %s", game_get_particular_obj(game), space_get_description(game_get_space(game, game_get_player_location(game))));
        }
        else{
            if(repeated){
                sprintf(phrase, "Would you mind trying to go to a direction that is not %s please?!", game_get_particular_obj(game));
            }
            else{
                sprintf(phrase, "You cannot go %s, try another direction", game_get_particular_obj(game));
            }
        }
        
    }

    if(action==TURNON){
        if(success==OK){
            sprintf(phrase, "The %s has been turned on successfully.", game_get_particular_obj(game));
        }
        else{
            if(repeated){
                sprintf(phrase, "Try other action because turning on %s is clearly not working.", game_get_particular_obj(game));
            }
            else{
                sprintf(phrase, "Or you don't have the %s, or it can't be turned on.", game_get_particular_obj(game));
            }
        }
        
    }

    if(action==TURNOFF){
        if(success==OK){
            sprintf(phrase, "The %s has been turned off successfully.", game_get_particular_obj(game));
        }
        else{
            if(repeated){
                sprintf(phrase, "Try another action because turning off %s is clearly not working.", game_get_particular_obj(game));
            }
            else{
                sprintf(phrase, "Or you don't have the %s, or it's already turned off.", game_get_particular_obj(game));
            }
        }
        
    }

    if(action==OPENLINK){
        if(success==OK){
            sprintf(phrase, "The %s link has been openned successfully with the %s.", game_get_particular_link(game), game_get_particular_obj(game));
        }
        else{
            if(repeated){
                sprintf(phrase, "Try another action because openning the %s with the %s is clearly not working.", game_get_particular_link(game), game_get_particular_obj(game));
            }
            else{
                sprintf(phrase, "Maybe you can't access the link %s from that space, or maybe you have not picked the %s.", game_get_particular_link(game),game_get_particular_obj(game));
            }
        }
        
    }

    if(action==HIDE){
        if(success==OK){
            sprintf(phrase, "The %s has been hidden successfully.", game_get_particular_obj(game));
        }
        else{
            if(repeated){
                sprintf(phrase, "Try another action because hidding %s is clearly not working.", game_get_particular_obj(game));
            }
            else{
                sprintf(phrase, "You can't hide the %s right now.", game_get_particular_obj(game));
            }
        }
        
    }

    if(action==SHOW){
        if(success==OK){
            sprintf(phrase, "The %s has been shown successfully.", game_get_particular_obj(game));
        }
        else{
            if(repeated){
                sprintf(phrase, "Try another action because showing %s is clearly not working.", game_get_particular_obj(game));
            }
            else{
                sprintf(phrase, "You can't show the %s right now.", game_get_particular_obj(game));
            } 
        }
        
    }

    if(action==SAVE){
        if(success==OK){
            if(repeated){
                sprintf(phrase, "Ok I know you want to be sure you saved it right but you don't have to save quadrillion times in a row!");

            }
            else{
                sprintf(phrase, "Your game was saved successfully don't worry if you close the game :3");
            }
        }
        else{
            sprintf(phrase, "Something didn't go quite right when saving your game...");
        }       
    }

    if(action==LOAD){
        if(success==OK){
            sprintf(phrase, "Game loaded successfully! :3 you can continue where you left off");
        }
        else{
            sprintf(phrase, "Something didn't go quite as right as it should have been");
        }        
    }
    
    return phrase;
}