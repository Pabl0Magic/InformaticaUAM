/** 
 * @brief It implements the command interpreter
 * 
 * @file command.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 30    /*!< Max length of a command */
#define N_CMD 15         /*!< The number of commands */

/**
 * @brief Enumeration of all the commands
 * 
 */
char *cmd_to_str[N_CMD] = {"No command", "Unknown", "exit", "pick_up", "drop", "roll", "inspect", "move", "turnon", "turnoff", "open", "show_object", "hide_object", "save", "load"};

/**
 * @brief Enumeration of shorted commands
 * 
 */
char *short_cmd_to_str[N_CMD] =  {"","","e","p","d","rl","i","m", "ton", "toff", "o", "so", "ho", "s", "l"};



T_Command command_get_user_input(){
  T_Command cmd = NO_CMD;
  char input[CMD_LENGHT] = "";
  int i=UNKNOWN - NO_CMD + 1;
  
  if (scanf("%s", input) > 0){
    cmd = UNKNOWN;
    while(cmd == UNKNOWN && i < N_CMD){
      if (!strcasecmp(input,short_cmd_to_str[i]) || !strcasecmp(input,cmd_to_str[i])){
          cmd = i + NO_CMD;
        }
        /*Gets user input from the prompt does a strcmp to check if it's one of the commands and returns the command itself using the command ADT
        be careful with the order of the commands to not switch them*/
        else { i++; }
  }
}
  return cmd;
}
