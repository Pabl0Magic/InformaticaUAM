/** 
 * @brief It declares the tests for the object module
 * 
 * @file dialogue_test.h
 * @author Rodrigo Juez
 * @version 5.0 
 * @date 07-05-2019
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_TEST_H
#define DIALOGUE_TEST_H
#include "dialogue.h"
/**
 * @test Test dialogue creation
 * @pre 
 * @post Non NULL pointer to dialogue 
 * 
 * @author Rodrigo Juez
 */
void test1_dialogue_create();
/**
 * @test Test dialogue creation
 * @pre 
 * @post Non NULL pointer to dialogue 
 * 
 * @author Rodrigo Juez
 */
void test2_dialogue_create();
/**
 * @test Test dialogue destroy
 * @pre dialogue pointer
 * @post void
 * 
 * @author Rodrigo Juez
 */
void test1_dialogue_destroy();
/**
 * @test Test dialogue destroy
 * @pre dialogue pointer
 * @post void
 * 
 * @author Rodrigo Juez
 */
void test2_dialogue_destroy();
/**
 * @test Test dialogue_set_repeated
 * @pre dialogue pointer and action done
 * @post STATUS OK 
 * 
 * @author Rodrigo Juez
 */
void test1_dialogue_set_repeated();
/**
 * @test Test dialogue_set_repeated
 * @pre dialogue pointer and action done
 * @post STATUS ERROR 
 * 
 * @author Rodrigo Juez
 */
void test2_dialogue_set_repeated();
/**
 * @test Test dialogue_set_repeated
 * @pre dialogue pointer and action done
 * @post STATUS OK 
 * 
 * @author Rodrigo Juez
 */
void test3_dialogue_set_repeated();
/**
 * @test Test dialogue_set_repeated
 * @pre dialogue pointer and action done
 * @post STATUS ERROR 
 * 
 * @author Rodrigo Juez
 */
void test4_dialogue_set_repeated();
/**
 * @test Test dialogue_interact_with_player
 * @pre Game pointer, Dialogue pointer, Last action done, STATUS of the last action done
 * @post char* with the response of the game 
 * 
 * @author Rodrigo Juez
 */
void test1_dialogue_interact_with_player();
/**
 * @test Test dialogue_interact_with_player
 * @pre Game pointer, Dialogue pointer, Last action done, STATUS of the last action done
 * @post char* with the response of the game 
 * 
 * @author Rodrigo Juez
 */
void test2_dialogue_interact_with_player();
/**
 * @test Test dialogue_interact_with_player
 * @pre Game pointer, Dialogue pointer, Last action done, STATUS of the last action done
 * @post NULL pointer
 * 
 * @author Rodrigo Juez
 */
void test3_dialogue_interact_with_player();
/**
 * @test Test dialogue_interact_with_player
 * @pre Game pointer, Dialogue pointer, Last action done, STATUS of the last action done
 * @post NULL pointer 
 * 
 * @author Rodrigo Juez
 */
void test4_dialogue_interact_with_player();
/**
 * @test Test dialogue_interact_with_player
 * @pre Game pointer, Dialogue pointer, Last action done, STATUS of the last action done
 * @post char* with the response of the game 
 * 
 * @author Rodrigo Juez
 */
void test5_dialogue_interact_with_player();
/**
 * @test Test dialogue_interact_with_player
 * @pre Game pointer, Dialogue pointer, Last action done, STATUS of the last action done
 * @post NULL pointer
 * 
 * @author Rodrigo Juez
 */
void test6_dialogue_interact_with_player();



#endif
