/** 
 * @brief It tests player module
 * 
 * @file player_test.c
 * @author Pablo Almarza
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 33            /*!< Max number of tests */ 

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
        printf("Running all tests for module Player:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_player_create();
    if (all || test == 2) test2_player_create();    
    if (all || test == 3) test1_player_destroy();
    if (all || test == 4) test2_player_destroy();
    if (all || test == 5) test1_player_set_space();
    if (all || test == 6) test2_player_set_space();
    if (all || test == 7) test1_player_set_name();
    if (all || test == 8) test2_player_set_name();
    if (all || test == 9) test3_player_set_name();
    if (all || test == 10) test1_player_set_object();
    if (all || test == 11) test2_player_set_object();
    if (all || test == 12) test1_player_get_name();
    if (all || test == 13) test2_player_get_name();   
    if (all || test == 14) test1_player_get_id();
    if (all || test == 15) test2_player_get_id();
    if (all || test == 16) test1_player_get_objects();
    if (all || test == 17) test2_player_get_objects();
    if (all || test == 18) test1_player_get_space();
    if (all || test == 19) test2_player_get_space();
    if (all || test == 20) test1_player_get_num_of_objects();
    if (all || test == 21) test2_player_get_num_of_objects();
    if (all || test == 22) test3_player_get_num_of_objects();
    if (all || test == 23) test1_player_get_particular_object();
    if (all || test == 24) test2_player_get_particular_object();
    if (all || test == 25) test1_player_delete_object();
    if (all || test == 26) test2_player_delete_object();
    if (all || test == 27) test3_player_delete_object();
    if (all || test == 28) test4_player_delete_object();
    if (all || test == 29) test1_player_print();
    if (all || test == 30) test2_player_print();
    if (all || test == 31) test1_player_find_obj();
    if (all || test == 32) test2_player_find_obj();
    if (all || test == 33) test3_player_find_obj();



    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_player_create(){
    player *player;
    player = player_create(12);
    PRINT_TEST_RESULT(player != NULL);
    player_destroy(player);
}
void test2_player_create(){
    player *player;
    player = player_create(5);
    PRINT_TEST_RESULT(player_get_id(player) == 5);
    player_destroy(player);
}


void test1_player_destroy(){
    player *player;
    player = player_create(10);
    PRINT_TEST_RESULT(player_destroy(player) == OK);
}
void test2_player_destroy(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_destroy(player) == ERROR);
}


void test1_player_set_space(){
    player *player;
    player = player_create(2);
    PRINT_TEST_RESULT(player_set_space(player, 7) == OK);
    player_destroy(player);
}
void test2_player_set_space(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_set_space(player, TRUE) == ERROR);
}


void test1_player_set_name(){
    player *player;
    player = player_create(13);
    PRINT_TEST_RESULT(player_set_name(player, "meme") == OK);
    player_destroy(player);
}
void test2_player_set_name(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_set_name(player, "meme") == ERROR);
}
void test3_player_set_name(){
    player *player;
    player = player_create(2);
    PRINT_TEST_RESULT(player_set_name(player, NULL) == ERROR);
    player_destroy(player);
}


void test1_player_set_object(){
    player *player;
    player = player_create(1);
    PRINT_TEST_RESULT(player_set_object(player, TRUE) == OK);
    player_destroy(player);
}
void test2_player_set_object(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_set_object(player, TRUE) == ERROR);
}


void test1_player_get_name(){
    player *player;
    player = player_create(1);
    player_set_name(player, "works");
    PRINT_TEST_RESULT(strcmp(player_get_name(player), "works") == 0);
    player_destroy(player);
}
void test2_player_get_name(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_get_name(player) == NULL);
}


void test1_player_get_id(){
    player *player;
    player = player_create(33);
    PRINT_TEST_RESULT(player_get_id(player) == 33);
    player_destroy(player);
}
void test2_player_get_id(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_get_id(player) == NO_ID);
}


void test1_player_get_objects(){
    player *player;
    player = player_create(11);
    player_set_object(player, 19);
    PRINT_TEST_RESULT(set_obtain_Id_by_position(inventory_get_objects(player_get_objects(player)), 0) == 19);
    player_destroy(player);
}
void test2_player_get_objects(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_get_objects(player) == ERROR);
}


void test1_player_get_space(){
    player *player;
    player = player_create(25);
    player_set_space(player, 14);
    PRINT_TEST_RESULT(player_get_space(player) == 14);
    player_destroy(player);
}
void test2_player_get_space(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_get_space(player) == NO_ID);
}


void test1_player_get_num_of_objects(){
    player *player;
    player = player_create(5);
    player_set_object(player, TRUE);
    PRINT_TEST_RESULT(player_get_num_of_objects(player) == 1);
    player_destroy(player);
}
void test2_player_get_num_of_objects() {
    player *player;
    player = player_create(5);
    player_set_object(player, 7);
    player_set_object(player, 12);
    player_set_object(player, 34);
    PRINT_TEST_RESULT(player_get_num_of_objects(player) == 3);
    player_destroy(player);
}
void test3_player_get_num_of_objects(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_get_num_of_objects(player) == -1);
}


void test1_player_get_particular_object(){
    player *player;
    player = player_create(28);
    player_set_object(player, 1);
    player_set_object(player, 56);
    PRINT_TEST_RESULT(player_get_particular_object(player, 1) == 56);
    player_destroy(player);
}
void test2_player_get_particular_object(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_get_particular_object(player, TRUE) == NO_ID);
}


void test1_player_delete_object(){
    player* player;
    player = player_create(1);
    player_set_object(player, TRUE);
    PRINT_TEST_RESULT(player_delete_object(player, TRUE) == OK);
    player_destroy(player);
}
void test2_player_delete_object(){
    player* player;
    player = player_create(1);
    PRINT_TEST_RESULT(player_delete_object(player, TRUE) == ERROR);
    player_destroy(player);
}
void test3_player_delete_object() {
    player* player;
    player = player_create(1);
    player_set_object(player, 3);
    player_set_object(player, 15);
    player_set_object(player, 18);
    PRINT_TEST_RESULT(player_delete_object(player, 15) == OK);
    player_destroy(player);
}
void test4_player_delete_object() {
    player *player = NULL;
    PRINT_TEST_RESULT(player_delete_object(player, TRUE) == ERROR);
}

void test1_player_print(){
    player *player;
    player = player_create(5);
    PRINT_TEST_RESULT(player_print(player) == OK);
    player_destroy(player);
}
void test2_player_print(){
    player *player = NULL;
    PRINT_TEST_RESULT(player_print(player) == ERROR);
}
void test1_player_find_obj(){
    player *player;
    player = player_create(28);
    
    player_set_object(player, 22);

    PRINT_TEST_RESULT(player_obj_find(player, 22));
    player_destroy(player);
}

void test2_player_find_obj(){
    player *player;
    player = player_create(28);
    
    player_set_object(player, 22);

    PRINT_TEST_RESULT(!player_obj_find(player, 20));
    player_destroy(player);
}

void test3_player_find_obj(){
    player *player=NULL;
   
    PRINT_TEST_RESULT(!player_obj_find(player, 22));
    player_destroy(player);
}