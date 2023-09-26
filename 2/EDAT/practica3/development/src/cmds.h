/*
    Project: EDAT Lab 3 test program
    File:    cmds.h
    Author:  Simone Santini
    Rev.     1.0
    Date:    10/11/2019 
    
    This file contains the main command execution function as well as the
    function that does a controlled reading of the commands from the screen.
    This system accepts the following commands:
    
    read <file>
    Reads a text file and keeps its contents in memory
    
    tmake <file>
    Stores the contents of the text file currently in memory in a table using
    the table.c functions,
    the table is stored in the given file. The table is kept open in memory.
    
    tclose
    Closes the table that is currently kept open 
    
    topen <file>
    Opens the given table file and keeps it open in memory
    
    check 
    Checks the contents of the current text file with those of the table
    currently open in memory. 
    
    tshow <n>
    Shows the contents of the nth record of the table and of the nth record
    of the text file currently in memory (if they are loaded in memory). 
    
    verify <file>
    Complete verification step: loads the text <file>, stores it as a table
    in <file>.dat, closes the table, opens it again, and checks the 
    correspondence of all the records.
    
    mkindex <file>
    Creates an empty index in the given file.
    
    iinsert <key> <pos>
    Inserts the pair <key> <pos> in the index currently in memory.
    
    ifind <key>
    Finds the key <key> and displays the position(s) associated.

    ishow
    Shows the whole contents of the index currently in memory
    
    tindex <file> <col>
    Creates an index in the file <file> for the column <col> of the 
    table currently in memory, and stores all the record in the index
    
    retrieve <key>
    Retrieves and prints the contents of the key <key>.
*/
#ifndef ____CMDS__INCLUDED____
#define ____CMDS__INCLUDED____

#include <termios.h>


typedef struct _cmdstatus cmdstatus;



/*
    Function: c_create()

    Creates an empty command status function and returns it. 
*/
cmdstatus *c_create();


/*
  Function: void c_close(cmdstatus *cs);

  Closes a status: closes the table, saves the index and closes it,
  frees the text space and frees the command structure.

  NOTE: This function must be called for the index to be saved on disk.
*/
void c_close(cmdstatus *cs);

/*
    Function: c_key_init(cmdstatus *cs)
    
    Initializes the keyboard to work in the non-standard mode that we 
    need to control command input with the function cmd_get: this function
    should be called once before calling c_cmd_get for the first time. At the 
    end of the program, the main program should call c_key_restore to 
    restore the keyboard in its default state.
*/
void c_key_init(cmdstatus *cs);


/*
    Function: c_key_restore(cmdstatus *cmd);
    
    Restores the keyboard to work in the standard mode. This function
    should be called once before exiting the program. 
*/
void c_key_restore(cmdstatus *cmd);


/*
    Function:  char *c_cmd_get(int maxlen);
    
    Reads a line from the keyboard, limiting the inmput to maxlen 
    characters. Only maxlen characters will be displayed on the screen
    (if you type more, the last character will be overwritten).
    Only the ascii characters, the backspace and the Enter key are 
    recognized.
    
    Returns: the string entered (in a newly allocated array) or NULL if 
    there is any problem.
*/
char *c_cmd_get(int maxlen);


/*
    Function: int c_execute(cmdstatus *cs, char *cmd)
    
    Executes the command "cmd", given as it is read from the command 
    line. Searches the command in the command list and executes the 
    associated function. Prints an error message if the command does not 
    exist in the list.
    
    Returns 1 if the command has been executed, 0 if it was unknown or
    there was en error.
*/
int c_execute(cmdstatus *cs, char *cmd);

/*
  Function: void c_print_status(cmdstatus *cs);

  Prints on the screen the current status of the command program.
*/
void c_print_status(cmdstatus *cs);

#endif
