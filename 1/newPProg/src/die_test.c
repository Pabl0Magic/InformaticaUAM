/** 
 * @brief It tests link module
 * 
 * @file link_test.c
 * @author Rodrigo Juez
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "test.h"
#include "die_test.h"

#define MAX_TESTS 10      /*!< Max number of tests */

/** 
 * @brief Main function for link unit tests. 
 * 
 * You may execute ALL
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;
  if (argc < 2) {
    printf("Running all tests for module Player:\n");
  } 
  else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
	  if (test < 1 && test > MAX_TESTS) {
	    printf("Error: unknown test %d\t", test);
	    exit(EXIT_SUCCESS);
    }
  }
    if (all || test == 1)test1_die_ini();
    if (all || test == 2)test1_die_destroy();
    if (all || test == 3)test1_die_roll();
    if (all || test == 4)test2_die_roll();
    if (all || test == 5)test3_die_roll();
    if (all || test == 6)test1_die_get_last_roll();
    if (all || test == 7)test2_die_get_last_roll();
    if (all || test == 8)test3_die_get_last_roll();
    if (all || test == 9)test1_die_print();
    if (all || test == 10)test1_die_get_id();

   
    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_die_ini(){
    int result=0;
    Die *test=NULL;
    test=die_ini(5);
    if(test){result = 1;}

    PRINT_TEST_RESULT(result);
    die_destroy(test);
}

void test1_die_destroy(){
    int result=0;
    Die *test=NULL;
    test=die_ini(5);
    die_destroy(test);
    test=NULL;
    if(!test){result=1;}

    PRINT_TEST_RESULT(result);
}

void test1_die_roll(){
    int result=0;
    Die *test=NULL;
    test=die_ini(5);
    result=die_roll(test);
    PRINT_TEST_RESULT(result);
    die_destroy(test);
}
void test2_die_roll(){
    int result=0,i;
    Die *test=NULL;
    test=die_ini(5);
    result=1;
    for(i=0; i<20; i++){
        result=die_roll(test);
        if(result==0){break; result=0;}
    }
    
    PRINT_TEST_RESULT(result);
    die_destroy(test);
}
void test3_die_roll(){
    int result=0;
    Die *test=NULL;
    if(die_roll(test)==ERROR){result=1;};
    PRINT_TEST_RESULT(result);
}

void test1_die_get_last_roll(){
    int result=0;
    Die *test=NULL;
    test=die_ini(5);
    result=die_roll(test);
    result=die_get_last_roll(test);
    if(result==-1){result=0;}
    else{result=1;}
    PRINT_TEST_RESULT(result);
    die_destroy(test);
}
void test2_die_get_last_roll(){
    int result=0,i;
    Die *test=NULL;
    test=die_ini(5);
    for(i=0; i<20; i++){
        result=die_roll(test);
        if(result==0){break; result=0;}
    }
    result=die_get_last_roll(test);
    if(result==-1){result=0;}
    PRINT_TEST_RESULT(result);
    die_destroy(test);
}
void test3_die_get_last_roll(){
    int result=0;
    Die *test=NULL;
    test=die_ini(5);
    result=die_get_last_roll(test);
    if(result==0){result=1;}
    PRINT_TEST_RESULT(result);
    die_destroy(test);
}

void test1_die_print(){
    int result=0;
    Die *test=NULL;
    test=die_ini(5);
    die_roll(test);
    result=die_print(test,stdout);
    printf("\n");
    PRINT_TEST_RESULT(result);
    die_destroy(test);
}

void test1_die_get_id(){
    int result=0;
    Die *test=NULL;
    test=die_ini(5);
    result=get_die_id(test);
    PRINT_TEST_RESULT(result);
    die_destroy(test);
}
