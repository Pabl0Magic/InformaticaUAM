 /******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "import.h"
#include "cmds.h"
#include "table.h"
#include "type.h"

/*
    Simple test: receives a command line such as 
    
        3 INT STR int
        
    Creates a table with thiose columns and types, opens it, 
    and prints some information about it.
*/
void simple_test(int argc, char **argv) {
    int cols = atoi(argv[0]);
    if (cols <=0) {
        printf("Number of columns must be positive\n");
        exit(1);
    }
    if (argc-1 != cols) {
        printf("Error: %d columns specified, %d types given\n", cols, argc-1);
        return;
    }
    type_t *types = (type_t *) malloc(cols*sizeof(type_t));
    for (int i=0; i<cols; i++) {
        types[i] = type_parse(argv[i+1]);
    }
    table_create("test_tab.dat", cols, types);
    table_t *t = table_open("test_tab.dat");
    printf("Testing the basic functions of a table\n");
    printf("Number of columns: %d\n", table_ncols(t));
    printf("Types: ");
    type_t *tps = table_types(t);
    for (int i=0; i<table_ncols(t); i++) {
        printf("%s  ", type_to_str(tps[i]));
    }
    printf("\n");
    printf("First position: %ld (%02XH)\n", table_first_pos(t), (unsigned int) table_first_pos(t));
    printf("Last position: %ld (%02XH)\n", table_last_pos(t), (unsigned int) table_last_pos(t));
    table_close(t);
}



int main(int argc, char **argv)
{
    if (argc>1) {
        simple_test(argc-1, argv+1);
    }
    else {
        cmdstatus *cs = c_create();
    
        c_key_init(cs);
        c_print_status(cs);
        while(1) {
            char *cmd = c_cmd_get(40);
            printf("\n");
            if (!strncmp(cmd, "quit", strlen("quit"))) {
                c_key_restore(cs);
		c_close(cs);
                printf("bye!\n");
                exit(0);
            }            
            c_execute(cs, cmd);
            c_print_status(cs);
        }
    }
    return 0;  
}

