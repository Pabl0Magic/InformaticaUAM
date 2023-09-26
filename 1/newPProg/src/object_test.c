/** 
 * @brief It tests object module
 * 
 * @file object_test.c
 * @author Profesores Pprog
 * @version 2.0 
 * @date 08-04-2019
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "test.h"
#include "object_test.h"
#include "object.h"
#include "types.h"

#define MAX_TESTS 54           /*!< Max number of tests */ 

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


    if (all || test == 1) test1_object_create();
    if (all || test == 2) test2_object_create();    
    if (all || test == 3) test1_object_destroy();
    if (all || test == 4) test2_object_destroy();
    if (all || test == 5) test1_object_set_ID();
    if (all || test == 6) test2_object_set_ID(); 
    if (all || test == 7) test3_object_set_ID(); 
    if (all || test == 8) test1_object_set_description();
    if (all || test == 9) test2_object_set_description();
    if (all || test == 10) test3_object_set_description();
    if (all || test == 11) test1_object_set_name();
    if (all || test == 12) test2_object_set_name();
    if (all || test == 13) test3_object_set_name();
    if (all || test == 14) test1_object_get_id();
    if (all || test == 15) test2_object_get_id();
    if (all || test == 16) test1_object_get_description();
    if (all || test == 17) test2_object_get_description();
    if (all || test == 18) test1_object_get_name();
    if (all || test == 19) test2_object_get_name();   
    if (all || test == 20) test1_object_print();
    if (all || test == 21) test2_object_print();
    if (all || test == 22) test1_object_set_first_location();
    if (all || test == 23) test2_object_set_first_location();
    if (all || test == 24) test3_object_set_first_location();
    if (all || test == 25) test1_object_get_first_location();
    if (all || test == 26) test2_object_get_first_location();
    if (all || test == 27) test1_object_set_second_description();
    if (all || test == 28) test2_object_set_second_description();
    if (all || test == 29) test3_object_set_second_description();
    if (all || test == 30) test1_object_get_second_description();
    if (all || test == 31) test2_object_get_second_description();
    if (all || test == 32) test1_object_get_movable();
    if (all || test == 33) test2_object_get_movable();
    if (all || test == 34) test3_object_get_movable();
    if (all || test == 35) test1_object_get_moved();
    if (all || test == 36) test2_object_get_moved();
    if (all || test == 37) test3_object_get_moved();
    if (all || test == 38) test1_object_set_movable();
    if (all || test == 39) test2_object_set_movable();
    if (all || test == 40) test3_object_set_movable();
    if (all || test == 41) test1_object_set_moved();
    if (all || test == 42) test2_object_set_moved();
    if (all || test == 43) test3_object_set_moved();
    if (all || test == 44) test1_object_set_illuminated_description();
    if (all || test == 45) test2_object_set_illuminated_description();
    if (all || test == 46) test3_object_set_illuminated_description();
    if (all || test == 47) test1_object_get_illuminated_description();
    if (all || test == 48) test2_object_get_illuminated_description();
    if (all || test == 49) test1_object_set_moved();
    if (all || test == 50) test2_object_set_moved();
    if (all || test == 51) test3_object_set_moved();
    if (all || test == 52) test1_object_get_cantmove();
    if (all || test == 53) test2_object_get_cantmove();
    if (all || test == 54) test3_object_get_cantmove();
    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_object_create(){
    Object *object;
    object = Object_create(10);
    PRINT_TEST_RESULT(object != NULL);
    Object_destroy(object);
}
void test2_object_create(){
    Object *object;
    object = Object_create(10);
    PRINT_TEST_RESULT(Object_get_id(object) == 10);
    Object_destroy(object);
}  

void test1_object_destroy(){
    Object *object;
    object = Object_create(15);
    PRINT_TEST_RESULT(Object_destroy(object) == OK);
}
void test2_object_destroy(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_destroy(object) == ERROR);
}

void test1_object_set_ID(){
    Object *object;
    object = Object_create(12);
    PRINT_TEST_RESULT(Object_set_ID(object, 16) == OK);
    Object_destroy(object);
}
void test2_object_set_ID(){
    Object *object;
    object = Object_create(19);
    PRINT_TEST_RESULT(Object_set_ID(object, NO_ID) == ERROR);
    Object_destroy(object);
}
void test3_object_set_ID(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_set_ID(object, 15) == ERROR);
}

void test1_object_set_description(){
    Object *object;
    object = Object_create(15);
    PRINT_TEST_RESULT(Object_set_description(object, "Example") == OK);
    Object_destroy(object);
}
void test2_object_set_description(){
    Object *object;
    object = Object_create(3);
    PRINT_TEST_RESULT(Object_set_description(object, NULL) == ERROR);
    Object_destroy(object);
}
void test3_object_set_description(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_set_description(object, "Example") == ERROR);
}

void test1_object_set_name(){
    Object *object;
    object = Object_create(19);
    PRINT_TEST_RESULT(Object_set_name(object, "book") == OK);
    Object_destroy(object);
}
void test2_object_set_name(){
    Object *object;
    object = Object_create(12);
    PRINT_TEST_RESULT(Object_set_name(object, NULL) == ERROR);
    Object_destroy(object);
}
void test3_object_set_name(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_set_name(object, "book") == ERROR);
}

void test1_object_get_id(){
    Object *object;
    object = Object_create(12);
    Object_set_ID(object, 29);
    PRINT_TEST_RESULT(Object_get_id(object) == 29);
    Object_destroy(object);
}
void test2_object_get_id(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_get_id(object) == NO_ID);
}

void test1_object_get_description(){
    Object *object;
    object = Object_create(12);
    Object_set_description(object, "Example");
    PRINT_TEST_RESULT(strcmp(Object_get_description(object), "Example") == 0);
    Object_destroy(object);
}
void test2_object_get_description(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_get_description(object) == NULL);
}

void test1_object_get_name(){
    Object *object;
    object =Object_create(12);+
    Object_set_name(object, "book");
    PRINT_TEST_RESULT(strcmp(Object_get_name(object), "book") == 0);
    Object_destroy(object);
}
void test2_object_get_name(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_get_name(object) == NULL);
}   

void test1_object_print(){
    Object *object;
    object = Object_create(20);
    Object_set_ID(object, 12);
    Object_set_name(object, "book");
    PRINT_TEST_RESULT(Object_print(object) == OK);
    Object_destroy(object);
}
void test2_object_print(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_print(object) == ERROR);
}

void test1_object_set_first_location(){
    Object *object;
    object = Object_create(12);
    Object_set_first_location(object, 15);
    PRINT_TEST_RESULT( Object_set_first_location(object, 15) == OK);
    Object_destroy(object);
}
void test2_object_set_first_location(){
    Object *object;
    object = Object_create(43);
    PRINT_TEST_RESULT(Object_set_first_location(object, NO_ID) == ERROR);
    Object_destroy(object);
}
void test3_object_set_first_location(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_set_first_location(object, 12) == ERROR);
}
void test1_object_get_first_location(){
    Object *object;
    object = Object_create(13);
    Object_set_first_location(object, 17);
    PRINT_TEST_RESULT(Object_get_first_location(object) == 17);
    Object_destroy(object);
}
void test2_object_get_first_location(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_get_first_location(object) == NO_ID);
}

void test1_object_set_second_description(){
    Object *object;
    object = Object_create(13);
    PRINT_TEST_RESULT(Object_set_second_description(object, "Example") == OK);
    Object_destroy(object);
}
void test2_object_set_second_description(){
    Object *object;
    object = Object_create(34);
    PRINT_TEST_RESULT(Object_set_second_description(object, NULL) == ERROR);
    Object_destroy(object);
}
void test3_object_set_second_description(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_set_second_description(object, "Example") == ERROR);
}

void test1_object_get_second_description(){
    Object *object;
    object = Object_create(34);
    Object_set_second_description(object, "Example");
    PRINT_TEST_RESULT(strcmp(Object_get_second_description(object), "Example") == 0);
    Object_destroy(object);
}
void test2_object_get_second_description(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_get_second_description(object) == NULL);
}
void test1_object_get_movable(){
    Object *object;
    object = Object_create(13);
    Object_set_movable(object, TRUE);
    PRINT_TEST_RESULT(Object_get_movable(object) == TRUE);
    Object_destroy(object);
}
void test2_object_get_movable(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_get_movable(object) == FALSE);
}
void test3_object_get_movable(){
    Object *object;
    object = Object_create(13);
    Object_set_movable(object, FALSE);
    PRINT_TEST_RESULT(Object_get_movable(object) == FALSE);
    Object_destroy(object);
}
void test1_object_get_moved(){
    Object *object;
    object = Object_create(13);
    Object_set_moved(object, TRUE);
    PRINT_TEST_RESULT(Object_get_moved(object) == TRUE);
    Object_destroy(object);
}
void test2_object_get_moved(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_get_moved(object) == FALSE);
}
void test3_object_get_moved(){
    Object *object;
    object = Object_create(13);
    Object_set_moved(object, FALSE);
    PRINT_TEST_RESULT(Object_get_moved(object) == FALSE);
    Object_destroy(object);
}
void test1_object_set_movable(){
    Object *object;
    object = Object_create(12);
    PRINT_TEST_RESULT( Object_set_movable(object, TRUE) == OK);
    Object_destroy(object);
}
void test2_object_set_movable(){
    Object *object;
    object = Object_create(12);
    PRINT_TEST_RESULT( Object_set_movable(object, FALSE) == OK);
    Object_destroy(object);
}
void test3_object_set_movable(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_set_movable(object, TRUE) == ERROR);
}
void test1_object_set_moved(){
    Object *object;
    object = Object_create(12);
    PRINT_TEST_RESULT( Object_set_moved(object, TRUE) == OK);
    Object_destroy(object);
}
void test2_object_set_moved(){
    Object *object;
    object = Object_create(12);
    PRINT_TEST_RESULT( Object_set_moved(object, FALSE) == OK);
    Object_destroy(object);
}
void test3_object_set_moved(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_set_moved(object, TRUE) == ERROR);
}

void test1_object_set_illuminated_description(){
    Object *object;
    object = Object_create(13);
    PRINT_TEST_RESULT(Object_set_illuminated_description(object, "Example") == OK);
    Object_destroy(object);
}
void test2_object_set_illuminated_description(){
    Object *object;
    object = Object_create(34);
    PRINT_TEST_RESULT(Object_set_illuminated_description(object, NULL) == ERROR);
    Object_destroy(object);
}
void test3_object_set_illuminated_description(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_set_illuminated_description(object, "Example") == ERROR);
}

void test1_object_get_illuminated_description(){
    Object *object;
    object = Object_create(34);
    Object_set_illuminated_description(object, "Example");
    PRINT_TEST_RESULT(strcmp(Object_get_illuminated_description(object), "Example") == 0);
    Object_destroy(object);
}
void test2_object_get_illuminated_description(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_get_illuminated_description(object) == NULL);
}

void test1_object_set_cantmove(){
    Object *object;
    object = Object_create(12);
    PRINT_TEST_RESULT( Object_set_cantmove(object, 24) == OK);
    Object_destroy(object);
}
void test2_object_set_cantmove(){
    Object *object;
    object = Object_create(12);
    PRINT_TEST_RESULT( Object_set_cantmove(object, NO_ID) == ERROR);
    Object_destroy(object);
}
void test3_object_set_cantmove(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_set_cantmove(object, 25) == ERROR);
}

void test1_object_get_cantmove(){
    Object *object;
    object = Object_create(13);
    Object_set_cantmove(object, 23);
    PRINT_TEST_RESULT(Object_get_cantmove(object) == 23);
    Object_destroy(object);
}
void test2_object_get_cantmove(){
    Object *object = NULL;
    PRINT_TEST_RESULT(Object_get_cantmove(object) == NO_ID);
}
void test3_object_get_cantmove(){
    Object *object;
    object = Object_create(13);
    Object_set_cantmove(object, NO_ID);
    PRINT_TEST_RESULT(Object_get_cantmove(object) == NO_ID);
    Object_destroy(object);
}