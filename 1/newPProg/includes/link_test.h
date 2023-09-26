/** 
 * @brief It declares the tests for the link module
 * 
 * @file link_test.h
 * @author Rodrigo Juez and Pablo Almarza
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#ifndef link_TEST_H
#define link_TEST_H
#include "link.h"

/**
 * @test Test function for link_ini function
 * @pre creates a Link and checks if memory allocation is correct
 * @post Output == Non NULL pointer to link
 * 
 * @author Rodrigo Juez
 */
void test1_link_create();

/**
 * @test Test function for link_ini function
 * @pre link id = -1
 * @post Output == NULL
 * 
 * @author Pablo Almarza
 */
void test2_link_create();

/**
 * @test Test function for link destruction
 * @pre link ID
 * @post Output == OK 
 * 
 * @author Rodrigo Juez
 */
void test1_link_destroy();

/**
 * @test Test function for link destruction
 * @pre pointer to link = NULL
 * @post Output == NULL
 * 
 * @author Rodrigo Juez
 */
void test2_link_destroy();

/**
 * @test Test function for link_id getting
 * @pre link ID
 * @post Output == Supplied link Id
 * 
 * @author Rodrigo Juez
 */
void test1_link_get_id();

/**
 * @test Test function for link_name getting
 * @pre pointer to link = NULL
 * @post Output == NO_ID 
 * 
 * @author Rodrigo Juez
 */
void test2_link_get_id();

/**
 * @test Test function for link_get_space1 function
 * @pre creates a Link and sets and gets a space 
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test1_link_get_space1();

/**
 * @test Test function for link_get_space1 function
 * @pre creates a Link and ONLY (without setting) gets a space 
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test2_link_get_space1();
/**
 * @test Test function for link_get_space1 function
 * @pre tries to get the space1 from a NULL link 
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test3_link_get_space1();
/**
 * @test Test function for link_get_space2 function
 * @pre creates a Link and sets and gets a space 
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test1_link_get_space2();

/**
 * @test Test function for link_get_space2 function
 * @pre creates a Link and ONLY (without setting) gets a space 
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test2_link_get_space2();
/**
 * @test Test function for link_get_space2 function
 * @pre tries to get the space1 from a NULL link 
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test3_link_get_space2();
/**
 * @test Test function for link_ini function
 * @pre creates a link sets two spaces and checks if it returns the correct one 
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test1_link_get_oposite();
/**
 * @test Test function for link_ini function
 * @pre creates a link sets one space and checks if the error control is the correct one 
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test2_link_get_oposite();
/**
 * @test Test function for link_ini function
 * @pre tries to get the oposite to a space from a NULL link and checks if the error control is correct 
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test3_link_get_oposite();
/**
 * @test Test function for link_ini function
 * @pre checks the error control if the space is not found
 * @post Output == Id
 * 
 * @author Rodrigo Juez
 */
void test4_link_get_oposite();
/**
 * @test Test function for link_ini function
 * @pre test error control for NULL link
 * @post Output == Bool
 * 
 * @author Rodrigo Juez
 */
void test1_link_get_open();
/**
 * @test Test function for link_ini function
 * @pre tests the default assign of an open link 
 * @post Output == Bool
 * 
 * @author Rodrigo Juez
 */
void test2_link_get_open();
/**
 * @test Test function for link_ini function
 * @pre checks if a modified value is get correctly 
 * @post Output == Bool
 * 
 * @author Rodrigo Juez
 */
void test3_link_get_open();

 /**
 * @test Test function for link_name getting
 * @pre String with link name
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_link_get_name();

/**
 * @test Test function for link_name getting
 * @pre pointer to link = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_link_get_name();
/**
 * @test Test function for link_ini function
 * @pre checks the normal functionality of the link_set_open
 * @post Output == STATUS
 * 
 * @author Rodrigo Juez
 */
void test1_link_set_open();
/**
 * @test Test function for link_ini function
 * @pre checks the error control for a NULL link
 * @post Output == STATUS
 * 
 * @author Rodrigo Juez
 */
void test2_link_set_open();
/**
 * @test Test function for link_Id setting
 * @pre link ID
 * @post Output == OK 
 * 
 * @author Rodrigo Juez
 */
void test1_link_set_id();
/**
 * @test Test function for link_Id setting
 * @pre link ID = NO_ID
 * @post Output == ERROR 
 * 
 * @author Rodrigo Juez
 */
void test2_link_set_id();

/**
 * @test Test function for link_Id setting
 * @pre pointer to link = NULL
 * @post Output == ERROR 
 * 
 * @author Pablo Almarza
 */
void test3_link_set_id();
/**
 * @test Test function for link_name setting
 * @pre String with link name
 * @post Output == OK 
 * 
 * @author Pablo Almarza
 */
void test1_link_set_name();

/**
 * @test Test function for link_name setting
 * @pre link name = NULL 
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_link_set_name();

/**
 * @test Test function for link_name setting
 * @pre pointer to link = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test3_link_set_name();

/**
 * @test Test function for link_set_space1 function
 * @pre link Id
 * @post Output == Id
 * 
 * @author Pablo ALmarza
 */
void test1_link_set_space1();

/**
 * @test Test function for link_set_space1 function
 * @pre link Id = NO_ID
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test2_link_set_space1();

/**
 * @test Test function for link_set_space1 function
 * @pre  pointer to test = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test3_link_set_space1();

/**
 * @test Test function for link_set_space2 function
 * @pre  link Id
 * @post Output == OK
 * 
 * @author Pablo ALmarza
 */
void test1_link_set_space2();

/**
 * @test Test function for link_set_space2 function
 * @pre link Id = NO_ID
 * @post Output == ERROR
 * 
 * @author Pablo ALmarza
 */
void test2_link_set_space2();

/**
 * @test Test function for link_set_space2 function
 * @pre pointer to test = NULL
 * @post Output == ERROR
 * 
 * @author Pablo Almarza
 */
void test3_link_set_space2();

/**
 * @test Test function for link printing
 * @pre link ID
 * @post Output == OK 
 * 
 * @author Rodrigo Juez
 */
void test1_link_print();
 
/**
 * @test Test function for link printing
 * @pre pointer to link = NULL
 * @post Output == ERROR 
 * 
 * @author Rodrigo Juez
 */
void test2_link_print();


#endif
