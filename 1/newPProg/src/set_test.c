/** 
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author Rodrigo Juez
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "set_test.h"
#include "test.h"
#define MAX_TESTS 24        /*!< Max number of tests */
/** 
 * @brief Main function for set unit tests. 
 * 
 * You may execute ALL
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

    if (all || test == 1)test1_set_ini();
    if (all || test == 2)test1_set_destroy();
    if (all || test == 3)test1_set_obtain_by_position();
    if (all || test == 4)test2_set_obtain_by_position();
    if (all || test == 5)test3_set_obtain_by_position();
    if (all || test == 6)test1_set_del();
    if (all || test == 7)test2_set_del();
    if (all || test == 8)test3_set_del();
    if (all || test == 9)test4_set_del();
    if (all || test == 10)test1_set_get_numIds();
    if (all || test == 11)test2_set_get_numIds();
    if (all || test == 12)test1_set_add();
    if (all || test == 13)test2_set_add();
    if (all || test == 14)test3_set_add();
    if (all || test == 15)test1_set_find();
    if (all || test == 16)test2_set_find();
    if (all || test == 17)test1_set_print();
    PRINT_PASSED_PERCENTAGE;
    return (EXIT_SUCCESS);
}

void test1_set_ini(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    if(test){result = 1;}

    PRINT_TEST_RESULT(result);
    set_destroy(test);
}

void test1_set_destroy(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    if(test){result = 1;}
    set_destroy(test);
    test=NULL;
    PRINT_TEST_RESULT(result);
}

void test1_set_obtain_by_position(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    set_add(test, 2);
    set_add(test, 4);
    if(set_obtain_Id_by_position(test,1)==4){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}
void test2_set_obtain_by_position(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    set_add(test, 2);
    if(set_obtain_Id_by_position(test,2)==-1){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}
void test3_set_obtain_by_position(){
    int result=0;
    Set *test=NULL;
    if(set_obtain_Id_by_position(test,2)==-1){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}

void test1_set_del(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    
    if(set_del(test, 2)==ERROR){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);

}
void test2_set_del(){
    int result=0;
    Set *test=NULL;
    
    if(set_del(test, 2)==ERROR){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}
void test3_set_del(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    set_add(test,4);
    if(set_del(test, 2)==ERROR){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}
void test4_set_del(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    set_add(test, 2);
    if(set_del(test, 2)==OK){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}

void test1_set_get_numIds(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    set_add(test, 2);
    if(set_get_numIds(test)==1){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}
void test2_set_get_numIds(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    set_add(test, 2);
    if(set_obtain_Id_by_position(test, 2)==-1){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}

void test1_set_add(){
int result=0, i=0;
    Set *test=NULL;
    test=set_ini(5);
    for(i=0; i<20; i++){
        set_add(test, 2);
    }
        
    if(set_add(test, 2)==ERROR){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}
void test2_set_add(){
    int result=0;
    Set *test=NULL;
            
    if(set_add(test, 2)==ERROR){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}
void test3_set_add(){
    int result=0;
    Set *test=NULL;
    test=set_ini(5);
    set_add(test,2);
        
    if(set_add(test, 2)==OK){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}

void test1_set_find(){
    int result=0, i=0;
    Set *test=NULL;
    test=set_ini(5);
    for(i=0; i<MAX_IDS; i++){
        set_add(test, i);
    }
        
    if(set_find(test, 2)==TRUE){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}
void test2_set_find(){
    int result=0, i=0;
    Set *test=NULL;
    test=set_ini(5);
    for(i=0; i<MAX_IDS; i++){
        set_add(test, i);
    }
        
    if(set_find(test, 99)==FALSE){result=1;}
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}

void test1_set_print(){ 
    int result=0, i=0;
    Set *test=NULL;
    test=set_ini(5);
    for(i=0; i<MAX_IDS; i++){
        set_add(test, i);
    }
        
    result=set_print(stdout,test);
    fprintf(stdout,"\n");
    PRINT_TEST_RESULT(result);
    set_destroy(test);
}
