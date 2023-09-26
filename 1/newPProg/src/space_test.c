/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Mariusz Wiśniewski
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "space.h"
#include "space_test.h"
#include "test.h"

#define MAX_TESTS 56        /*!< Max number of tests */

/** 
 * @brief Main function for SPACE unit tests. 
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
        printf("Running all test for module Space:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_space_create();
    if (all || test == 2) test2_space_create();
    if (all || test == 3) test1_space_set_name();
    if (all || test == 4) test2_space_set_name();
    if (all || test == 5) test3_space_set_name();
    if (all || test == 6) test1_space_set_north();
    if (all || test == 7) test2_space_set_north();
    if (all || test == 8) test1_space_set_south();
    if (all || test == 9) test2_space_set_south();
    if (all || test == 10) test1_space_set_east();
    if (all || test == 11) test2_space_set_east();
    if (all || test == 12) test1_space_set_west();
    if (all || test == 13) test2_space_set_west();
    if (all || test == 14) test1_space_get_name();
    if (all || test == 15) test2_space_get_name();
    if (all || test == 16) test1_space_get_object_id_from_index();
    if (all || test == 17) test2_space_get_object_id_from_index();
    if (all || test == 18) test3_space_get_object_id_from_index();
    if (all || test == 19) test1_space_get_north();
    if (all || test == 20) test2_space_get_north();
    if (all || test == 21) test1_space_get_south();
    if (all || test == 22) test2_space_get_south();
    if (all || test == 23) test1_space_get_east();
    if (all || test == 24) test2_space_get_east();
    if (all || test == 25) test1_space_get_west();
    if (all || test == 26) test2_space_get_west();
    if (all || test == 27) test1_space_get_id();
    if (all || test == 28) test2_space_get_id();
    if (all || test == 29) test1_space_set_draw();
    if (all || test == 30) test2_space_set_draw();
    if (all || test == 31) test1_space_get_draw();
    if (all || test == 32) test2_space_get_draw();
    if (all || test == 32) test1_space_destroy();
    if (all || test == 33) test2_space_destroy();
    if (all || test == 34) test1_space_print();
    if (all || test == 35) test2_space_print();
    if (all || test == 36) test1_space_add_object();
    if (all || test == 37) test2_space_add_object();
    if (all || test == 38) test1_space_del_object();
    if (all || test == 39) test2_space_del_object();
    if (all || test == 40) test3_space_del_object();
    if (all || test == 41) test1_space_get_num_objects();
    if (all || test == 42) test2_space_get_num_objects();
    if (all || test == 43) test1_space_find_object();
    if (all || test == 44) test2_space_find_object();
    if (all || test == 45) test1_space_set_description();
    if (all || test == 46) test2_space_set_description();
    if (all || test == 47) test1_space_get_description();
    if (all || test == 48) test2_space_get_description();
    if (all || test == 49) test1_space_get_up();
    if (all || test == 50) test2_space_get_up();
    if (all || test == 51) test1_space_get_down();
    if (all || test == 52) test2_space_get_down();
    if (all || test == 53) test1_space_set_up();
    if (all || test == 54) test2_space_set_up();
    if (all || test == 55) test1_space_set_down();
    if (all || test == 56) test2_space_set_down();
    if (all || test == 57) test1_space_get_objects();
    if (all || test == 58) test2_space_get_objects();
    if (all || test == 59) test1_space_get_turned_on_object_on_the_space();
    if (all || test == 60) test2_space_get_turned_on_object_on_the_space();
    if (all || test == 61) test3_space_get_turned_on_object_on_the_space();
    if (all || test == 62) test1_space_set_turned_on_object_on_the_space();
    if (all || test == 63) test2_space_set_turned_on_object_on_the_space();
    if (all || test == 64) test1_space_get_detailed_desc();
    if (all || test == 65) test2_space_get_detailed_desc();
    if (all || test == 66) test1_space_set_detailed_desc();
    if (all || test == 67) test2_space_set_detailed_desc();


    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_space_create() {
    int result;
  Space* s = space_create(5);
  if (s != NULL) {
      result = 1;
  }
  else {
      result = 0;
  }
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

void test2_space_create() {
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_get_id(s) == 4);
    space_destroy(s);
}

void test1_space_set_name() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
    space_destroy(s);
}
void test2_space_set_name() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}
void test3_space_set_name() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
    space_destroy(s);
}

void test1_space_set_north() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_north(s, 4) == OK);
    space_destroy(s);
}
void test2_space_set_north() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_north(s, 4) == ERROR);
}

void test1_space_set_south() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_south(s, 4) == OK);
    space_destroy(s);
}
void test2_space_set_south() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_south(s, 4) == ERROR);
}

void test1_space_set_east() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_east(s, 4) == OK);
    space_destroy(s);
}
void test2_space_set_east() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_east(s, 4) == ERROR);
}

void test1_space_set_west() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_west(s, 4) == OK);
    space_destroy(s);
}
void test2_space_set_west() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_west(s, 4) == ERROR);
}

void test1_space_set_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_set_object(s,TRUE) == OK);
    space_destroy(s);
}
void test2_space_set_object() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_object(s,TRUE) == ERROR);
}

void test1_space_get_name() {
    Space *s;
    s = space_create(1);
    space_set_name(s, "adios");
    PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
    space_destroy(s);

}
void test2_space_get_name() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_name(s) == NULL);

}

void test1_space_get_object_id_from_index() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_get_object_id_from_index(s, 0) == NO_ID);
    space_destroy(s);
     
}
void test2_space_get_object_id_from_index() {
    Space *s;
    s = space_create(1);
    space_set_object(s,TRUE);
    PRINT_TEST_RESULT(space_get_object_id_from_index(s, 0) == TRUE);
    space_destroy(s);
     
}
void test3_space_get_object_id_from_index() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_object_id_from_index(s, 0) == NO_ID);
}

void test1_space_get_north() {
    Space *s;
    s = space_create(5);
    space_set_north(s, 4);
    PRINT_TEST_RESULT(space_get_north(s) == 4);
    space_destroy(s);
}
void test2_space_get_north() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_north(s) == NO_ID);
}

void test1_space_get_south() {
    Space *s;
    s = space_create(5);
    space_set_south(s, 2);
    PRINT_TEST_RESULT(space_get_south(s) == 2);
    space_destroy(s);
}
void test2_space_get_south() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_south(s) == NO_ID);
}

void test1_space_get_east() {
    Space *s;
    s = space_create(5);
    space_set_east(s, 1);
    PRINT_TEST_RESULT(space_get_east(s) == 1);
    space_destroy(s);
}
void test2_space_get_east() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_east(s) == NO_ID);
}

void test1_space_get_west() {
    Space *s;
    s = space_create(5);
    space_set_west(s, 6);
    PRINT_TEST_RESULT(space_get_west(s) == 6);
    space_destroy(s);
}
void test2_space_get_west() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_west(s) == NO_ID);
}

void test1_space_get_id() {
    Space *s;
    s = space_create(25);
    PRINT_TEST_RESULT(space_get_id(s) == 25);
    space_destroy(s);
}
void test2_space_get_id() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_set_draw() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_draw(s, "draw") == ERROR);
}
void test2_space_set_draw() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_draw(s, "draw") == OK);
    space_destroy(s);
}

void test1_space_get_draw() {
    Space *s;
    s = space_create(5);
    space_set_draw(s, "  ___   / _ \\ / / \\ \\");
    PRINT_TEST_RESULT(strcmp(space_get_draw(s), "  ___   / _ \\ / / \\ \\") == 0);
    space_destroy(s);
}
void test2_space_get_draw() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_draw(s) == ERROR);
}

void test1_space_destroy() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_destroy(s) == OK);
}
void test2_space_destroy() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_destroy(s) == ERROR);
}

void test1_space_print() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_print(s) == OK);
    space_destroy(s);
}
void test2_space_print() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_print(s) == ERROR);
}

void test1_space_add_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_add_object(s,TRUE) == OK);
    space_destroy(s);
}
void test2_space_add_object() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_add_object(s,TRUE) == ERROR);
}

void test1_space_del_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_del_object(s, 1) == ERROR);
    space_destroy(s);
     
}
void test2_space_del_object() {
    Space *s;
    s = space_create(1);
    space_set_object(s,TRUE);
    PRINT_TEST_RESULT(space_del_object(s, 1) == OK);
    space_destroy(s);
}
void test3_space_del_object() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_del_object(s, 1) == ERROR);
}

void test1_space_get_num_objects() {
    Space *s;
    s = space_create(5);
    space_add_object(s, TRUE);   
    PRINT_TEST_RESULT(space_get_num_objects(s) == 1);
    space_destroy(s);
}
void test2_space_get_num_objects() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_num_objects(s) == -1);
}

void test1_space_find_object() {
    Space *s;
    s = space_create(5);
    space_add_object(s, 5);
    PRINT_TEST_RESULT(space_find_object(s, 5) == TRUE);
    space_destroy(s);
}
void test2_space_find_object() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_find_object(s, 5) == FALSE);
}

void test1_space_set_description() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_description(s, "desc") == OK);
    space_destroy(s);
}
void test2_space_set_description() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_description(s, "desc") == ERROR);
}

void test1_space_get_description() {
    Space *s;
    s = space_create(5);
    space_set_description(s, "desc");
    PRINT_TEST_RESULT(strcmp(space_get_description(s), "desc") == 0);
    space_destroy(s);
}
void test2_space_get_description() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_description(s) == ERROR);
}

void test1_space_get_up() {
    Space *s;
    s = space_create(5);
    space_set_up(s, 4);
    PRINT_TEST_RESULT(space_get_up(s) == 4);
    space_destroy(s);
}
void test2_space_get_up() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_up(s) == NO_ID);
}

void test1_space_get_down() {
    Space *s;
    s = space_create(5);
    space_set_down(s, 4);
    PRINT_TEST_RESULT(space_get_down(s) == 4);
    space_destroy(s);
}
void test2_space_get_down() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_down(s) == NO_ID);
}

void test1_space_set_up() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_up(s, 4) == OK);
    space_destroy(s);
}
void test2_space_set_up() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_up(s, 4) == ERROR);
}

void test1_space_set_down() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_down(s, 4) == OK);
    space_destroy(s);
}
void test2_space_set_down() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_down(s, 4) == ERROR);
}

void test1_space_get_illuminated() {
    Space *s=NULL;
    PRINT_TEST_RESULT(space_get_illuminated(s) == FALSE);
}

void test2_space_get_illuminated() {
    Space *s=NULL;
    s = space_create(3);
    PRINT_TEST_RESULT(space_get_illuminated(s) == FALSE);
    space_destroy(s);
}

void test3_space_get_illuminated() {
    Space *s=NULL;
    s = space_create(5);
    space_set_illuminated(s, TRUE);
    PRINT_TEST_RESULT(space_get_illuminated(s) == TRUE);
    space_destroy(s);
}

void test1_space_set_illuminated() {
    Space *s=NULL;
    PRINT_TEST_RESULT(space_set_illuminated(s, FALSE) == ERROR);
}

void test2_space_set_illuminated() {
    Space *s=NULL;
    PRINT_TEST_RESULT(space_set_illuminated(s, TRUE) == ERROR);
}

void test3_space_set_illuminated() {
    Space *s=NULL;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_illuminated(s, FALSE) == OK);
    space_destroy(s);
}

void test4_space_set_illuminated() {
    Space *s=NULL;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_illuminated(s, TRUE) == OK);
    space_destroy(s);
}

void test1_space_get_objects() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_objects(s) == NULL);
}

void test2_space_get_objects() {
    Space *s = NULL;
    s = space_create(4);
    PRINT_TEST_RESULT(space_get_objects(s) != NULL);
    space_destroy(s);
}

void test1_space_get_turned_on_object_on_the_space() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_turned_on_object_on_the_space(s) == FALSE);
}

void test2_space_get_turned_on_object_on_the_space() {
    Space *s = NULL;
    s = space_create(4);
    space_set_turned_on_object_on_the_space(s, FALSE);
    PRINT_TEST_RESULT(space_get_turned_on_object_on_the_space(s) == FALSE);
    space_destroy(s);
}

void test3_space_get_turned_on_object_on_the_space() {
    Space *s = NULL;
    s = space_create(4);
    space_set_turned_on_object_on_the_space(s, TRUE);
    PRINT_TEST_RESULT(space_get_turned_on_object_on_the_space(s) == TRUE);
    space_destroy(s);
}

void test1_space_set_turned_on_object_on_the_space() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_turned_on_object_on_the_space(s, TRUE) == ERROR);
}

void test2_space_set_turned_on_object_on_the_space() {
    Space *s = NULL;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_turned_on_object_on_the_space(s, TRUE) == OK);
    space_destroy(s);
}

void test1_space_get_detailed_desc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_detailed_desc(s) == NULL);
}

void test2_space_get_detailed_desc() {
    Space *s = NULL;
    s = space_create(4);
    PRINT_TEST_RESULT(space_get_detailed_desc(s) != NULL);
    space_destroy(s);
}

void test1_space_set_detailed_desc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_detailed_desc(s, "char") == ERROR);
}

void test2_space_set_detailed_desc() {
    Space *s = NULL;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_detailed_desc(s, "char") == OK);
    space_destroy(s);
}