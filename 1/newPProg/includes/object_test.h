/** 
 * @brief It declares the tests for the object module
 * 
 * @file object_test.h
 * @author Pablo Almarza
 * @version 5.0 
 * @date 08-04-2019
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
 * @test Test object creation
 * @pre object ID
 * @post Non NULL pointer to object 
 * 
 * @author Pablo Almarza
 */
void test1_object_create();

/**
 * @test Test object creation
 * @pre object ID
 * @post object_ID == Supplied object Id
 * 
 * @author Pablo Almarza
 */
void test2_object_create();   

/**
 * @test Test function for object destruction
 * @pre object ID
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_object_destroy();

/**
 * @test Test function for object destruction
 * @pre pointer to object = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test2_object_destroy();

/**
 * @test Test function for object_Id setting
 * @pre object ID
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_object_set_ID();

/**
 * @test Test function for object_Id setting
 * @pre object ID = NO_ID
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test2_object_set_ID();

/**
 * @test Test function for object_Id setting
 * @pre pointer to object = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test3_object_set_ID();

/**
 * @test Test function for object_description setting
 * @pre Description = "Example"
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_object_set_description();

/**
 * @test Test function for object_description setting
 * @pre Description = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test2_object_set_description();

/**
 * @test Test function for object_description setting
 * @pre pointer to object = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test3_object_set_description();

/**
 * @test Test function for object_name setting
 * @pre String with object name
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre Object name = NULL 
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test3_object_set_name();

/**
 * @test Test function for object_id getting
 * @pre object ID
 * @post Output == Supplied object Id
 * 
 * @author Pablo Almarza
 */
void test1_object_get_id();

/**
 * @test Test function for object_name getting
 * @pre pointer to object = NULL
 * @post Output == NO_ID 
 * 
 * @author Pablo Almarza
 */
void test2_object_get_id();

/**
 * @test Test function for object_description getting
 * @pre object description = "Example"
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_object_get_description();

/**
 * @test Test function for object_description getting
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_object_get_description();

/**
 * @test Test function for object_name getting
 * @pre String with object name
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_object_get_name();

/**
 * @test Test function for object_name getting
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_object_get_name();

/**
 * @test Test function for object printing
 * @pre object ID
 * @post Output == OK 
 */
void test1_object_print();

/**
 * @test Test function for object printing
 * @pre pointer to object = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test2_object_print();

/**
 * @test Test function for object_first_location setting
 * @pre firstloc
 * @post Output == OK
 * 
 * @author Pablo Almarza
 */
void test1_object_set_first_location();

/**
 * @test Test function for object_first_location setting
 * @pre firstloc = NO_ID
 * @post Output == OK
 * 
 * @author Pablo Almarza
 */
void test2_object_set_first_location();
/**
 * @test Test function for object_first_location setting
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test3_object_set_first_location();

/**
 * @test Test function for object_first_location getting
 * @pre firstloc = id
 * @post The id that I set
 * 
 * @author Pablo Almarza
 */
void test1_object_get_first_location();

/**
 * @test Test function for object_first_location getting
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_object_get_first_location();

/**
 * @test Test function for object_second_description setting
 * @pre descalt = "Example"
 * @post Output == OK
 * 
 * @author Pablo Almarza
 */
void test1_object_set_second_description();

/**
 * @test Test function for object_second_description setting
 * @pre descalt = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_object_set_second_description();

/**
 * @test Test function for object_second_description setting
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test3_object_set_second_description();

/**
 * @test Test function for object_second_description getting
 * @pre descalt = "Example"
 * @post The description that I set
 * 
 * @author Pablo Almarza
 */
void test1_object_get_second_description();

/**
 * @test Test function for object_second_description getting
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_object_get_second_description();

/**
 * @test Test function for object_get_movable getting
 * @pre pointer to object = created
 * @post Output == TRUE
 * 
 * @author Rodrigo Juez
 */
void test1_object_get_movable();
/**
 * @test Test function for object_get_movable getting
 * @pre pointer to object = created
 * @post Output == FALSE
 * 
 * @author Rodrigo Juez
 */
void test2_object_get_movable();
/**
 * @test Test function for object_get_movable getting
 * @pre pointer to object = NULL
 * @post Output == FALSE
 * 
 * @author Rodrigo Juez
 */
void test3_object_get_movable();
/**
 * @test Test function for object_get_moved getting
 * @pre pointer to object = created
 * @post Output == TRUE
 * 
 * @author Rodrigo Juez
 */

void test1_object_get_moved();
/**
 * @test Test function for object_get_moved getting
 * @pre pointer to object = created
 * @post Output == FALSE
 * 
 * @author Rodrigo Juez
 */
void test2_object_get_moved();
/**
 * @test Test function for object_get_moved getting
 * @pre pointer to object = NULL
 * @post Output == FALSE
 * 
 * @author Rodrigo Juez
 */
void test3_object_get_moved();
/**
 * @test Test function for object_set_movable
 * @pre pointer to object = created
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */

void test1_object_set_movable();
/**
 * @test Test function for object_set_movable
 * @pre pointer to object = created
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test2_object_set_movable();
/**
 * @test Test function for object_set_movable
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test3_object_set_movable();
/**
 * @test Test function for moved
 * @pre pointer to object = created
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */

void test1_object_set_moved();
/**
 * @test Test function for moved
 * @pre pointer to object = created
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test2_object_set_moved();
/**
 * @test Test function for moved
 * @pre pointer to object = created
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test3_object_set_moved();

/**
 * @test Test function for object_illuminated_description setting
 * @pre descalt = "Example"
 * @post Output == OK
 * 
 * @author Pablo Almarza
 */
void test1_object_set_illuminated_description();

/**
 * @test Test function for object_illuminated_description setting
 * @pre descalt = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_object_set_illuminated_description();

/**
 * @test Test function for object_illuminated_description setting
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test3_object_set_illuminated_description();

/**
 * @test Test function for object_illuminated_description getting
 * @pre descalt = "Example"
 * @post The description that I set
 * 
 * @author Pablo Almarza
 */
void test1_object_get_illuminated_description();

/**
 * @test Test function for object_illuminated_description getting
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_object_get_illuminated_description();

/**
 * @test Test function for object_set_cantmove
 * @pre pointer to object = NULL
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test1_object_set_cantmove();

/**
 * @test Test function for object_set_cantmove
 * @pre pointer to object = NULL
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test2_object_set_cantmove();

/**
 * @test Test function for object_set_cantmove
 * @pre pointer to object = NULL
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test3_object_set_cantmove();

/**
 * @test Test function for object_get_cantmove
 * @pre pointer to object = NULL
 * @post Output == 23
 * 
 * @author Rodrigo Juez
 */
void test1_object_get_cantmove();

/**
 * @test Test function for object_get_cantmove
 * @pre pointer to object = NULL
 * @post Output == NO_ID
 * 
 * @author Rodrigo Juez
 */
void test2_object_get_cantmove();

/**
 * @test Test function for object_get_cantmove
 * @pre pointer to object = NULL
 * @post Output == NO_ID
 * 
 * @author Rodrigo Juez
 */
void test3_object_get_cantmove();
#endif
