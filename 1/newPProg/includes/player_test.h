/** 
 * @brief It declares the tests for the player module
 * 
 * @file player_test.h
 * @author Pablo Almarza
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @test Test player creation
 * @pre Player ID
 * @post Non NULL pointer to player 
 * 
 * @author Pablo Almarza
 */
void test1_player_create();

/**
 * @test Test player creation
 * @pre Player ID
 * @post Player_ID == Supplied Player Id
 * 
 * @author Pablo Almarza
 */
void test2_player_create();

/**
 * @test Test function for player destruction
 * @pre Player ID
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_player_destroy();

/**
 * @test Test function for player_name setting
 * @pre pointer to player = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test2_player_destroy();

/**
 * @test Test function for player_space setting
 * @pre Player set ina random space
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_player_set_space();

/**
 * @test Test function for player_space setting
 * @pre pointer to player = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_player_set_space();

/**
 * @test Test function for player_name setting
 * @pre String with player name
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_player_set_name();

/**
 * @test Test function for player_name setting
 * @pre pointer to player = NULL 
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_player_set_name();

/**
 * @test Test function for player_name setting
 * @pre pointer to player_name = NULL (point to player = NON NULL) 
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test3_player_set_name();

/**
 * @test Test function for player_object setting
 * @pre give an object id to player
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_player_set_object();

/**
 * @test Test function for player_object setting
 * @pre pointer to player = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_player_set_object();

/**
 * @test Test function for player_name getting
 * @pre String with player name
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_player_get_name();

/**
 * @test Test function for player_name getting
 * @pre pointer to player = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_player_get_name();

/**
 * @test Test function for player_id getting
 * @pre Player ID
 * @post Output == Supplied Player Id
 * 
 * @author Pablo Almarza
 */
void test1_player_get_id();

/**
 * @test Test function for player_name getting
 * @pre pointer to player = NULL
 * @post Output == NO_ID 
 * 
 * @author Pablo Almarza
 */
void test2_player_get_id();

/**
 * @test Test function for player_objects getting
 * @pre we set an object id to the player
 * @post Output == Supplied object id 
 * 
 * @author Pablo Almarza
 */
void test1_player_get_objects();

/**
 * @test Test function for player_name getting
 * @pre Spointer to player = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test2_player_get_objects();

/**
 * @test Test function for player_space getting
 * @pre Random space that is set
 * @post Output == Supplied Space Id 
 * 
 * @author Pablo Almarza
 */
void test1_player_get_space();

/**
 * @test Test function for player_space getting
 * @pre pointer to player = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test2_player_get_space();

/**
 * @test Test function for getting the number of objects the player carries
 * @pre Set an object
 * @post Output == number of objects that I set (1)
 * 
 * @author Pablo Almarza
 */
void test1_player_get_num_of_objects();

/**
 * @test Test function for getting the number of objects the player carries
 * @pre Set several objects
 * @post Output == number of objects that I set (3)
 * 
 * @author Pablo Almarza
 */
void test2_player_get_num_of_objects();

/**
 * @test Test function for getting the number of objects the player carries
 * @pre pointer to player = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test3_player_get_num_of_objects();

/**
 * @test Test function for getting a particular object from the player
 * @pre set several objects
 * @post Output == supplied particular object  
 * 
 * @author Pablo Almarza
 */
void test1_player_get_particular_object();

/**
 * @test Test function for getting a particular object from the player
 * @pre pointer to player = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test2_player_get_particular_object();

/**
 * @test Test function for deleting an object from the player
 * @pre set an objectc to be deleted
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_player_delete_object();

/**
 * @test Test function for deleting an object from the player
 * @pre I don't set any object
 * @post Output == ERROR   
 * 
 * @author Pablo Almarza
 */
void test2_player_delete_object();

/**
 * @test Test function for deleting an object from the player
 * @pre Set multiple objects
 * @post Output == OK 
 * 
 * @author Pablo Almarza 
 */
void test3_player_delete_object();

/**
 * @test Test function for deleting an object from the player
 * @pre pointer to player = NULL
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test4_player_delete_object();

/**
 * @test Test function for player printing
 * @pre Player ID
 * @post Output == OK 
 */
void test1_player_print();

/**
 * @test Test function for player printing
 * @pre pointer to player = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test2_player_print();

/**
 * @test Test function for player_obj_find
 * @pre pointer to player and Id object to find
 * @post Output == TRUE 
 * 
 * @author Rodrigo Juez
 */
void test1_player_find_obj();

/**
 * @test Test function for player_obj_find
 * @pre pointer to player and Id object to find
 * @post Output == FALSE 
 * 
 * @author Rodrigo Juez
 */
void test2_player_find_obj();

/**
 * @test Test function for player_obj_find
 * @pre pointer to player and Id object to find
 * @post Output == FALSE 
 * 
 * @author Rodrigo Juez
 */
void test3_player_find_obj();


#endif