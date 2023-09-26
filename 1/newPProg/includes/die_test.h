/** 
 * @brief It declares the tests for the link module
 * 
 * @file die_test.h
 * @author Rodrigo Juez
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#ifndef die_TEST_H
#define die_TEST_H
#include "die.h"

/**
 * @test Test function for die_ini function
 * @pre checks if the memory allocation for the die_ini is correct
 * @post Non NULL pointer to die
 * 
 * @author Rodrigo Juez
 */
void test1_die_ini();
/**
 * @test Test function for die_destroy function
 * @pre checks if its correctly freed 
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test1_die_destroy();
/**
 * @test Test function for die_roll function
 * @pre checks if the 1 time roll is correct
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test1_die_roll();
/**
 * @test Test function for die_roll function
 * @pre checks if the continuous roll of the dice is correct 
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test2_die_roll();
/**
 * @test Test function for die_roll function
 * @pre checks if the  roll of the error control of the die module is correct
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test3_die_roll();
/**
 * @test Test function for die_get_last_roll function
 * @pre checks if the get last roll is correct when rolling the dice 
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test1_die_get_last_roll();
/**
 * @test Test function for die_get_last_roll function
 * @pre checks if the continuous roll returns the correct roll information
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test2_die_get_last_roll();
/**
 * @test Test function for die_get_last_roll function
 * @pre checks if the bad initialization of the die is correct
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test3_die_get_last_roll();
/**
 * @test Test function for die_print function
 * @pre tests the printing of the dice 
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test1_die_print();
/**
 * @test Test function for die_get_id function
 * @pre tests if the information of the id is correctly obtained
 * @post Output == ID
 * 
 * @author Rodrigo Juez
 */
void test1_die_get_id();


#endif
