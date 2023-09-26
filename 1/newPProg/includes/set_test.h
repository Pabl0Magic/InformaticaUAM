/** 
 * @brief It declares the tests for the set module
 * 
 * @file set_test.h
 * @author Rodrigo Juez
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#ifndef set_TEST_H
#define set_TEST_H
#include "set.h"

/**
 * @test Test function for set_ini function
 * @pre checks if the memory allocation for the set_ini is correct
 * @post Output == Non NULL pointer to set
 * 
 * @author Rodirgo Juez
 */
void test1_set_ini();

/**
 * @test Test function for set_destroy function
 * @pre checks if the liberation of memory is correct
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test1_set_destroy();

/**
 * @test Test function for set_obtain_by_position function
 * @pre checks if the id by position is obtained correctly
 * @post Output == ID
 * 
 * @author Rodrigo Juez
 */
void test1_set_obtain_by_position();

/**
 * @test Test function for set_obtain_by_position function
 * @pre checks if the obtained id is correct when doing error control
 * @post Output == ID
 * 
 * @author Rodrigo Juez
 */
void test2_set_obtain_by_position();

/**
 * @test Test function for set_obtain_by_position function
 * @pre checks if the error control for the obtained Id when out of boundaries position
 * @post Output == NO_ID
 * 
 * @author Rodrigo Juez
 */
void test3_set_obtain_by_position();

/**
 * @test Test function for set_del function
 * @pre checks if the error control for the set_del function
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test1_set_del();

/**
 * @test Test function for set_del function
 * @pre checks if the error control when unknown id deleted
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test2_set_del();

/**
 * @test Test function for set_del function
 * @pre checks if the deletion is correct
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test3_set_del();

/**
 * @test Test function for set_del function
 * @pre checks if the error control for set_del is correct
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test4_set_del();

/**
 * @test Test function for set_del function
 * @pre checks if the getter of the cuantity of ids is correct when doing error control
 * @post Output == Number of ids
 * 
 * @author Rodrigo Juez
 */
void test1_set_get_numIds();

/**
 * @test Test function for set_get_numIds function
 * @pre checks if it gets a correct amount of ids
 * @post Output == Number of ids
 * 
 * @author Rodrigo Juez
 */
void test2_set_get_numIds();

/**
 * @test Test function for set_get_numIds function
 * @pre checks if the addition of an invalid set is correct
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test1_set_add();

/**
 * @test Test function for set_add function
 * @pre checks if the error control in set add is correct
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test2_set_add();

/**
 * @test Test function for set_add function
 * @pre checks if the addition is correct
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test3_set_add();

/**
 * @test Test function for set_find function
 * @pre checks if the set finds a valid id
 * @post Output == TRUE
 * 
 * @author Rodrigo Juez
 */
void test1_set_find();

/**
 * @test Test function for set_find function
 * @pre checks if the set finds an invalid set
 * @post Output == FALSE
 * 
 * @author Rodrigo Juez
 */
void test2_set_find();

/**
 * @test Test function for set_print function
 * @pre checks if the printing id correct
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test1_set_print();

#endif
