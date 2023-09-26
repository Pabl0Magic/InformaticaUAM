/** 
 * @brief It tests dialogue module
 * 
 * @file dialogue_test.c
 * @author Rodrigo Juez
 * @version 2.0 
 * @date 07-05-2019
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "test.h"
#include "game.h"
#include "dialogue_test.h"
#include "types.h"
#define MAX_TESTS 14           /*!< Max number of tests */ 

/** 
 * @brief Main function for player unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all tests for module object:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_dialogue_create();
    if (all || test == 2) test2_dialogue_create();
    if (all || test == 3) test1_dialogue_destroy();
    if (all || test == 4) test2_dialogue_destroy();
    if (all || test == 5) test1_dialogue_set_repeated();
    if (all || test == 6) test2_dialogue_set_repeated();
    if (all || test == 7) test3_dialogue_set_repeated();
    if (all || test == 8) test4_dialogue_set_repeated();
    if (all || test == 9) test1_dialogue_interact_with_player();
    if (all || test == 10) test2_dialogue_interact_with_player();
    if (all || test == 11) test3_dialogue_interact_with_player();
    if (all || test == 12) test4_dialogue_interact_with_player();
    if (all || test == 13) test5_dialogue_interact_with_player();
    if (all || test == 14) test6_dialogue_interact_with_player();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_dialogue_create(){
    Dialogue *dialogue=NULL;
    dialogue = Dialogue_ini();
    PRINT_TEST_RESULT(dialogue != NULL);
    Dialogue_destroy(dialogue);
}
void test2_dialogue_create(){
    Dialogue *dialogue=NULL;
    PRINT_TEST_RESULT(dialogue == NULL);
    Dialogue_destroy(dialogue);
}

void test1_dialogue_destroy(){
    Dialogue *dialogue=NULL;
    dialogue = Dialogue_ini();
    Dialogue_destroy(dialogue);
    dialogue=NULL;
    PRINT_TEST_RESULT(dialogue == NULL);
}


void test2_dialogue_destroy(){
    Dialogue *dialogue=NULL;
    Dialogue_destroy(dialogue);
    PRINT_TEST_RESULT(dialogue == NULL);
}

void test1_dialogue_set_repeated(){
    Dialogue *dialogue=NULL;
    dialogue=Dialogue_ini();
    PRINT_TEST_RESULT(Dialogue_set_repeated(dialogue, UNKNOWN)==OK);
    Dialogue_destroy(dialogue);
}

void test2_dialogue_set_repeated(){
    Dialogue *dialogue=NULL;
    dialogue=Dialogue_ini();
    PRINT_TEST_RESULT(Dialogue_set_repeated(dialogue, MOVE)==OK);
    Dialogue_destroy(dialogue);
}

void test3_dialogue_set_repeated(){
    Dialogue *dialogue=NULL;
    dialogue=Dialogue_ini();
    PRINT_TEST_RESULT(Dialogue_set_repeated(dialogue, NO_CMD)==ERROR);
    Dialogue_destroy(dialogue);
}

void test4_dialogue_set_repeated(){
    Dialogue *dialogue=NULL;
    PRINT_TEST_RESULT(Dialogue_set_repeated(dialogue, UNKNOWN)==ERROR);
    Dialogue_destroy(dialogue);
}

void test1_dialogue_interact_with_player(){
    Dialogue *dialogue=NULL;
    char *string=NULL;
    BOOL flag=FALSE;
    Game *game=NULL;
    dialogue=Dialogue_ini();
    game_create(&game);
    string= Dialogue_interact_with_player(game, dialogue, UNKNOWN, OK);
    if(string){
        flag=TRUE;
    }
    
    PRINT_TEST_RESULT(flag);
    Dialogue_destroy(dialogue);
}

void test2_dialogue_interact_with_player(){
    Dialogue *dialogue=NULL;
    char *string=NULL;
    BOOL flag=FALSE;
    Game *game=NULL;
    dialogue=Dialogue_ini();
    string= Dialogue_interact_with_player(game, dialogue, UNKNOWN, OK);
    if(string){
        flag=TRUE;
    }
    
    PRINT_TEST_RESULT(flag);
    Dialogue_destroy(dialogue);
}

void test3_dialogue_interact_with_player(){
    Dialogue *dialogue=NULL;
    char *string=NULL;
    BOOL flag=FALSE;
    Game *game=NULL;
    string= Dialogue_interact_with_player(game, dialogue, UNKNOWN, OK);
    if(!string){
        flag=TRUE;
    }
    
    PRINT_TEST_RESULT(flag);
    Dialogue_destroy(dialogue);
}

void test4_dialogue_interact_with_player(){
    Dialogue *dialogue=NULL;
    char *string=NULL;
    BOOL flag=FALSE;
    Game *game=NULL;
    dialogue=Dialogue_ini();
    game_create(&game);
    string= Dialogue_interact_with_player(game, dialogue, MOVE, ERROR);
    if(string){
        flag=TRUE;
    }
    
    PRINT_TEST_RESULT(flag);
    Dialogue_destroy(dialogue);
}
void test5_dialogue_interact_with_player(){
    Dialogue *dialogue=NULL;
    char *string=NULL;
    BOOL flag=FALSE;
    Game *game=NULL;
    dialogue=Dialogue_ini();
    game_create(&game);
    string= Dialogue_interact_with_player(game, dialogue, MOVE, OK);
    if(string){
        flag=TRUE;
    }
    
    PRINT_TEST_RESULT(flag);
    Dialogue_destroy(dialogue);
}
void test6_dialogue_interact_with_player(){
    Dialogue *dialogue=NULL;
    char *string=NULL;
    BOOL flag=FALSE;
    Game *game=NULL;
    dialogue=Dialogue_ini();
    game_create(&game);
    string= Dialogue_interact_with_player(game, dialogue, NO_CMD, OK);
    if(string){
        flag=TRUE;
    }
    
    PRINT_TEST_RESULT(flag);
    Dialogue_destroy(dialogue);
}


