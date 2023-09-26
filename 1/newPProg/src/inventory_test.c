/** 
 * @brief It tests inventory module
 * 
 * @file inventory_test.c
 * @author Mariusz Wiśniewski
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "inventory.h"
#include "inventory_test.h"
#include "test.h"

#define MAX_TESTS 28            /*!< Max number of tests */

/** 
 * @brief Main function for INVENTORY unit tests. 
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
        printf("Running all test for module inventory:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_inventory_create();
    if (all || test == 2) test1_inventory_destroy();
    if (all || test == 3) test2_inventory_destroy();
    if (all || test == 4) test1_inventory_set_object_to_inventory();
    if (all || test == 5) test2_inventory_set_object_to_inventory();
    if (all || test == 6) test1_inventory_delete_object();
    if (all || test == 7) test2_inventory_delete_object();
    if (all || test == 8) test3_inventory_delete_object();
    if (all || test == 9) test1_inventory_get_object_from_inventory();
    if (all || test == 10) test2_inventory_get_object_from_inventory();
    if (all || test == 11) test3_inventory_get_object_from_inventory();
    if (all || test == 12) test1_inventory_is_full();
    if (all || test == 13) test2_inventory_is_full();
    if (all || test == 14) test3_inventory_is_full();
    if (all || test == 15) test1_inventory_get_number_objects();
    if (all || test == 16) test2_inventory_get_number_objects();
    if (all || test == 17) test3_inventory_get_number_objects();
    if (all || test == 18) test1_inventory_find_object();
    if (all || test == 19) test2_inventory_find_object();
    if (all || test == 20) test3_inventory_find_object();
    if (all || test == 21) test1_inventory_get_objects();
    if (all || test == 22) test2_inventory_get_objects();
    if (all || test == 23) test3_inventory_get_objects();
    if (all || test == 24) test1_inventory_print();
    if (all || test == 25) test2_inventory_print();


    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_inventory_create() {
  Inventory* i = inventory_create();
  PRINT_TEST_RESULT(i != NULL);
  inventory_destroy(i);
}

void test1_inventory_destroy() {
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(inventory_destroy(i) == OK);
}
void test2_inventory_destroy() {
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_destroy(i) == ERROR);
}

void test1_inventory_set_object_to_inventory() {
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(inventory_set_object_to_inventory(i, 1) == OK);
    inventory_destroy(i);
}
void test2_inventory_set_object_to_inventory() {
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_set_object_to_inventory(i, 1) == ERROR);
}

void test1_inventory_delete_object() {
    Inventory *i = inventory_create();
    inventory_set_object_to_inventory(i, 1);
    PRINT_TEST_RESULT(inventory_delete_object(i, 1) == OK);
    inventory_destroy(i);
}
void test2_inventory_delete_object() {
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_delete_object(i, 1) == ERROR);
}
void test3_inventory_delete_object() {
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(inventory_delete_object(i, 1) == ERROR);
    inventory_destroy(i);
}

void test1_inventory_get_object_from_inventory() {
    Inventory *i = inventory_create();
    inventory_set_object_to_inventory(i, 1);
    PRINT_TEST_RESULT(inventory_get_object_from_inventory(i, 0) == TRUE);
    inventory_destroy(i);
}
void test2_inventory_get_object_from_inventory() {
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_object_from_inventory(i, 0) == ERROR);
}
void test3_inventory_get_object_from_inventory() {
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(inventory_get_object_from_inventory(i, 0) == ERROR);
    inventory_destroy(i);
}

void test1_inventory_is_full() {
    Inventory *i = inventory_create();
    inventory_set_object_to_inventory(i, 1);
    inventory_set_object_to_inventory(i, 2);
    inventory_set_object_to_inventory(i, 3);
    inventory_set_object_to_inventory(i, 4);
    inventory_set_object_to_inventory(i, 5);
    inventory_set_object_to_inventory(i, 6);
    inventory_set_object_to_inventory(i, 7);
    inventory_set_object_to_inventory(i, 8);
    inventory_set_object_to_inventory(i, 9);
    inventory_set_object_to_inventory(i, 10);
    inventory_set_object_to_inventory(i, 11);
    inventory_set_object_to_inventory(i, 12);
    inventory_set_object_to_inventory(i, 13);
    inventory_set_object_to_inventory(i, 14);
    inventory_set_object_to_inventory(i, 15);
    inventory_set_object_to_inventory(i, 16);
    inventory_set_object_to_inventory(i, 17);
    inventory_set_object_to_inventory(i, 18);
    inventory_set_object_to_inventory(i, 19);
    inventory_set_object_to_inventory(i, 20);
    PRINT_TEST_RESULT(inventory_is_full(i) == TRUE);
    inventory_destroy(i);
}
void test2_inventory_is_full() {
    Inventory *i = inventory_create();
    inventory_set_object_to_inventory(i, 20);
    PRINT_TEST_RESULT(inventory_is_full(i) == FALSE);
    inventory_destroy(i);
}
void test3_inventory_is_full() {
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_is_full(i) == FALSE);
}

void test1_inventory_get_number_objects() {
    Inventory *i = inventory_create();
    inventory_set_object_to_inventory(i, 1);
    PRINT_TEST_RESULT(inventory_get_number_objects(i) == 1);
    inventory_destroy(i);
}
void test2_inventory_get_number_objects() {
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(inventory_get_number_objects(i) == 0);
    inventory_destroy(i);
}
void test3_inventory_get_number_objects() {
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_number_objects(i) == 0);
}

void test1_inventory_find_object() {
    Inventory *i = inventory_create();
    inventory_set_object_to_inventory(i, 1);
    PRINT_TEST_RESULT(inventory_find_object(i, 1) == TRUE);
    inventory_destroy(i);
}
void test2_inventory_find_object() {
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(inventory_find_object(i, TRUE) == FALSE);
    inventory_destroy(i);
}
void test3_inventory_find_object() {
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_find_object(i, TRUE) == FALSE);
}

void test1_inventory_get_objects() {
    Inventory *i = inventory_create();
    inventory_set_object_to_inventory(i, 1);
    PRINT_TEST_RESULT(inventory_get_objects(i) != NULL);
    inventory_destroy(i);
}
void test2_inventory_get_objects() {
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(inventory_get_objects(i) == NULL);
    inventory_destroy(i);
}
void test3_inventory_get_objects() {
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_objects(i) == NULL);
}

void test1_inventory_print() {
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(inventory_print(i) == OK);
    inventory_destroy(i);
}
void test2_inventory_print() {
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_print(i) == ERROR);
}
