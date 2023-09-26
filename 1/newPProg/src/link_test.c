/** 
 * @brief It tests link module
 * 
 * @file link_test.c
 * @author Rodrigo Juez
 * @version 2.0 
 * @date 19-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "test.h"
#include "link_test.h"

#define MAX_TESTS 37        /*!< Max number of tests */

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



  if (all || test == 1)test1_link_create();
  if (all || test == 2)test1_link_create();
  if (all || test == 3)test1_link_destroy();
  if (all || test == 4)test2_link_destroy();
  if (all || test == 5)test1_link_get_id();
  if (all || test == 6)test2_link_get_id();
  if (all || test == 7)test1_link_get_space1();
  if (all || test == 8)test2_link_get_space1();
  if (all || test == 9)test3_link_get_space1();
  if (all || test == 10)test1_link_get_space2();
  if (all || test == 11)test2_link_get_space2();
  if (all || test == 12)test3_link_get_space2();
  if (all || test == 13)test1_link_get_oposite();
  if (all || test == 14)test2_link_get_oposite();
  if (all || test == 15)test3_link_get_oposite();
  if (all || test == 16)test4_link_get_oposite();
  if (all || test == 17)test1_link_get_open();
  if (all || test == 18)test2_link_get_open();
  if (all || test == 19)test3_link_get_open();
  if (all || test == 20)test1_link_get_name();
  if (all || test == 21)test2_link_get_name();
  if (all || test == 22)test1_link_set_open();
  if (all || test == 23)test2_link_set_open();
  if (all || test == 24)test1_link_set_id();
  if (all || test == 25)test2_link_set_id();
  if (all || test == 26)test3_link_set_id();
  if (all || test == 27)test1_link_set_name();
  if (all || test == 28)test2_link_set_name();
  if (all || test == 29)test3_link_set_name();
  if (all || test == 30)test1_link_set_space1();
  if (all || test == 31)test2_link_set_space1();
  if (all || test == 32)test3_link_set_space1();
  if (all || test == 33)test1_link_set_space2();
  if (all || test == 34)test2_link_set_space2();
  if (all || test == 35)test3_link_set_space2();
  if (all || test == 36)test1_link_print();
  if (all || test == 37)test2_link_print();
  PRINT_PASSED_PERCENTAGE;
  return 1;
}

void test1_link_create() {
  int result = 0;
  Link *new = link_create(5);
  if(new){result=1;}
  PRINT_TEST_RESULT(result);
  link_destroy(new);  
}

void test2_link_create(){
  Link *new;
  new = link_create(-1);
  PRINT_TEST_RESULT(new == NULL);
}

void test1_link_destroy() {
  int result = 0;
  Link *test = link_create(5);
  link_set_space1(test,2);
  link_set_space2(test,3);
  link_destroy(test);
  test=NULL;
  if(test==NULL){result=1;}
  PRINT_TEST_RESULT(result);
}
void test2_link_destroy() {
  int result=0;
  Link *test=NULL;
  link_destroy(test);
  if(test==NULL){result=1;}
  PRINT_TEST_RESULT(result);
}

void test1_link_get_id() {
  int result = 0;
  Link *test = link_create(5);
  result=link_get_id(test);
  if(result!=5){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test2_link_get_id() {
  int result = 0;
  Link *test = NULL;
  result=link_get_id(test);
  if(result==-1){result=1;}
  PRINT_TEST_RESULT(result);
}

void test1_link_get_space1() {
  int result = 0;
  Link *test = link_create(5);
  link_set_space1(test,3);
  result=link_get_space1(test);
  if(result!=3){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test2_link_get_space1() {
  int result = 0;
  Link *test = link_create(5);
  
  result=link_get_space1(test);
  if(result!=-1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test3_link_get_space1() {
  int result = 0;
  Link *test = NULL;
  link_set_space1(test,3);
  result=link_get_space1(test);
  if(result!=-1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test1_link_get_space2() {
  int result = 0;
  Link *test = link_create(5);
  link_set_space2(test,3);
  result=link_get_space2(test);
  if(result!=3){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test2_link_get_space2() {
  int result = 0;
  Link *test = link_create(5);
  
  result=link_get_space2(test);
  if(result!=-1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test3_link_get_space2() {
  int result = 0;
  Link *test = NULL;
  link_set_space2(test,3);
  result=link_get_space2(test);
  if(result!=-1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test1_link_get_oposite() {
  int result = 0;
  Link *test = link_create(5);
  link_set_space2(test,3);
  link_set_space1(test,2);
  result=link_get_oposite(test, 3);
  if(result!=2){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}
void test2_link_get_oposite() {
  int result = 0;
  Link *test = link_create(5);
  link_set_space2(test,3);
  result=link_get_oposite(test, 3);
  if(result!=-1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}
void test3_link_get_oposite() {
  int result = 0;
  Link *test = NULL;
  result=link_get_oposite(test, 3);
  if(result!=-1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test4_link_get_oposite() {
  int result = 0;
  Link *test = link_create(5);
  link_set_space1(test,3);
  result=link_get_oposite(test, 2);
  if(result!=-1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test1_link_get_open() {
  int result = 0;
  Link *test = NULL;

  result=link_get_open(test);
  if(result!=-1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test2_link_get_open() {
  int result = 0;
  Link *test =link_create(5);

  result=link_get_open(test);
  if(result!=1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}
void test3_link_get_open() {
  int result = 0;
  Link *test =link_create(5);
  link_set_open(test,FALSE);
  result=link_get_open(test);
  if(result==0){result=1;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test1_link_get_name(){
  Link *test;
  test = link_create(5);
  link_set_name(test, "link");
  PRINT_TEST_RESULT(strcmp(link_get_name(test), "link") == 0);
  link_destroy(test);
}

void test2_link_get_name(){
  Link *test = NULL;
  PRINT_TEST_RESULT(link_get_name(test) == NULL);
}

void test1_link_set_open() {
  int result = 0;
  Link *test =link_create(5);
  link_set_open(test,FALSE);
  result=link_get_open(test);
  if(result==0){result=1;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test2_link_set_open() {
  int result = 0;
  Link *test =NULL;
  link_set_open(test,FALSE);
  result=link_get_open(test);
  if(result!=-1){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test1_link_set_id() {
  int result = 0;
  Link *test =link_create(5);
  if(link_set_id(test,1120)==ERROR){
    result=0;   
    PRINT_TEST_RESULT(result);
    link_destroy(test);
    return;
}
  result=link_get_id(test);
  if(result!=1120){result=0;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test2_link_set_id() {
  int result = 0;
  Link *test =NULL;
  if(link_set_id(test, 1120)==ERROR){result=1;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test3_link_set_id(){
  Link *test;
  test = link_create(5);
  PRINT_TEST_RESULT(link_set_id(test, NO_ID) == ERROR);
  link_destroy(test);
}
void test1_link_set_name(){
  Link *test;
  test = link_create(5);
  PRINT_TEST_RESULT(link_set_name(test, "link") == OK);
  link_destroy(test);
}

void test2_link_set_name(){
  Link *test;
  test = link_create(5);
  PRINT_TEST_RESULT(link_set_name(test, NULL) == ERROR);
  link_destroy(test);
}

void test3_link_set_name(){
  Link *test = NULL;
  PRINT_TEST_RESULT(link_set_name(test, "link") == ERROR);
}

void test1_link_set_space1(){
  Link *test;
  test = link_create(5);
  PRINT_TEST_RESULT(link_set_space1(test, 3) == OK);
  link_destroy(test);
}

void test2_link_set_space1(){
  Link *test;
  test = link_create(5);
  PRINT_TEST_RESULT(link_set_space1(test, NO_ID) == ERROR);
  link_destroy(test);
}

void test3_link_set_space1(){
  Link *test = NULL;
  PRINT_TEST_RESULT(link_set_space1(test, 3) == ERROR);
}

void test1_link_set_space2(){
  Link *test;
  test = link_create(5);
  PRINT_TEST_RESULT(link_set_space2(test, 4) == OK);
  link_destroy(test);
}

void test2_link_set_space2(){
  Link *test;
  test = link_create(5);
  PRINT_TEST_RESULT(link_set_space2(test, NO_ID) == ERROR);
  link_destroy(test);
}

void test3_link_set_space2(){
  Link *test = NULL;
  PRINT_TEST_RESULT(link_set_space2(test, 4) == ERROR);
}

void test1_link_print(){
  int result = 0;
  Link *test =link_create(5);
  link_set_open(test, FALSE);
  link_set_space1(test, 99);
  link_set_space2(test,400);
  result=link_print(stdout,test);
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}

void test2_link_print(){
  int result = 0;
  Link *test =NULL;
  if(link_print(stdout,test)==ERROR){result=1;}
  PRINT_TEST_RESULT(result);
  link_destroy(test);
}


