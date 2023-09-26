/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Mariusz Wiśniewski
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID  ==  Supplied Space Id
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Output == OK 
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test3_space_set_name();

/**
 * @test Test function for space_north setting
 * @pre Pointer to the space, id of the northern space 
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_north();

/**
 * @test Test function for space_north setting
 * @pre NULL pointer to the space, id of the northern space 
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_north();

/**
 * @test Test function for space_south setting
 * @pre Pointer to the space, id of the southern space 
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_south();

/**
 * @test Test function for space_south setting
 * @pre NULL pointer to the space, id of the southern space 
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_south();

/**
 * @test Test function for space_east setting
 * @pre Pointer to the space, id of the eastern space 
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_east();

/**
 * @test Test function for space_east setting
 * @pre NULL pointer to the space, id of the eastern space 
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_east();

/**
 * @test Test function for space_west setting
 * @pre Pointer to the space, id of the western space 
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_west();

/**
 * @test Test function for space_west setting
 * @pre NULL pointer to the space, id of the western space 
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_west();

/**
 * @test Test function for getting id from a space
 * @pre Pointer to the space that is already created
 * @post Output == Space ID
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_id();

/**
 * @test Test function for getting id from a space
 * @pre NULL pointer to the space that is not created
 * @post Output == NO_ID(-1)
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_id();

/**
 * @test Test function for setting an object to a space
 * @pre Pointer to the space that is already created,
 * id of the object
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_object();

/**
 * @test Test function for setting an object to a space
 * @pre NULL pointer to the space that is not created,
 * id of the object
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_object();

/**
 * @test Test function for getting a name of a space
 * @pre Pointer to the space that is already created
 * and have the name set, id of the space
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_name();

/**
 * @test Test function for getting a name of a space
 * @pre NULL pointer to the space that is already created
 * and does not have the name set, id of the space
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_name();

/**
 * @test Test function for getting id of the northern space
 * @pre Pointer to the space that is already created
 * and have the northern space set
 * @post Output == ID of the northern space
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_north();

/**
 * @test Test function for getting id of the northern space
 * @pre NULL pointer to the space that is already created
 * and does not have the northern space set
 * @post Output == NO_ID
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_north();

/**
 * @test Test function for getting id of the souththern space
 * @pre Pointer to the space that is already created
 * and have the southern space set
 * @post Output == ID of the southern space
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_south();

/**
 * @test Test function for getting id of the southern space
 * @pre NULL pointer to the space that is already created
 * and does not have the southern space set
 * @post Output == NO_ID
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_south();

/**
 * @test Test function for getting id of the eastern space
 * @pre Pointer to the space that is already created
 * and have the eastern space set
 * @post Output == ID of the eastern space
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_east();

/**
 * @test Test function for getting id of the eastern space
 * @pre NULL pointer to the space that is already created
 * and does not have the eastern space set
 * @post Output == NO_ID
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_east();

/**
 * @test Test function for getting id of the western space
 * @pre Pointer to the space that is already created
 * and have the western space set
 * @post Output == ID of the western space
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_west();

/**
 * @test Test function for getting id of the western space
 * @pre NULL pointer to the space that is already created
 * and does not have the western space set
 * @post Output == NO_ID
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_west();

/**
 * @test Test function for getting the id of the object
 * that has a given index
 * @pre Pointer to the space that is already created and does not
 * contain any object,index of an object
 * @post Output == NO_ID
 * 
 * @author Mariusz Wiśniewski
 */

void test1_space_get_object_id_from_index();

/**
 * @test Test function for getting the id of the object
 * that has a given index
 * @pre Pointer to the space that is already created and contains
 * an object,index of an object
 * @post Output == Object id
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_object_id_from_index();

/**
 * @test Test function for getting the id of the object
 * that has a given index
 * @pre NULL pointer to the space that is not created and does not
 * contain any object,index of an object
 * @post Output == NO_ID
 * 
 * @author Mariusz Wiśniewski
 */
void test3_space_get_object_id_from_index();

/**
 * @test Test function for setting a drawing on a space
 * @pre NULL pointer to the space that is not created,
 * a string with a drawing
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_draw();

/**
 * @test Test function for setting a drawing on a space
 * @pre Pointer to the space that is already created,
 * a string with a drawing
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_draw();

/**
 * @test Test function for getting a drawing on a space
 * @pre Pointer to the space that is already created and
 * contains a drawing
 * @post Output == Drawing from the space
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_draw();

/**
 * @test Test function for getting a drawing on a space
 * @pre NULL pointer to the space that is not created
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_draw();

/**
 * @test Test function for destroying a space
 * @pre Pointer to the space that is already created
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_destroy();

/**
 * @test Test function for destroying a space
 * @pre NULL pointer to the space that is not created
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_destroy();

/**
 * @test Test function for printing information about a space
 * @pre Pointer to the space that is already created
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_print();

/**
 * @test Test function for destroying a space
 * @pre NULL pointer to the space that is not created
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_print();

/**
 * @test Test function for adding an object to a space
 * @pre Pointer to the space that is already created,
 * id of the object
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_add_object();

/**
 * @test Test function for adding an object to a space
 * @pre NULL pointer to the space that is not created,
 * id of the object
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_add_object();

/**
 * @test Test function for deleting an object from a space
 * @pre Pointer to the space that is already created and
 * does not contain any objects, id of the object
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_del_object();

/**
 * @test Test function for deleting an object from a space
 * @pre Pointer to the space that is already created and
 * contains an object, id of the object
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_del_object();

/**
 * @test Test function for deleting an object from a space
 * @pre NULL pointer to the space that is not created and
 * does not contain any objects, id of the object
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test3_space_del_object();

/**
 * @test Test function for getting a number of objects from a space
 * @pre Pointer to the space that is already created and
 * contains an object
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_num_objects();

/**
 * @test Test function for getting a number of objects from a space
 * @pre Pointer to the space that is not created and does not
 * contain any objects
 * @post Output == -1
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_num_objects();

/**
 * @test Test function for checking if an object with a given id is in the space
 * @pre Pointer to the space that is already created and
 * contains an object, id of an object
 * @post Output == TRUE
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_find_object();

/**
 * @test Test function for checking if an object with a given id is in the space
 * @pre NULL pointer to the space that is not created and
 * does not contain any objects, id of an object
 * @post Output == FALSE
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_find_object();

/**
 * @test Test function for setting a description of a space
 * @pre Pointer to the space that is already created,
 * a string with a description
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_description();

/**
 * @test Test function for setting a description of a space
 * @pre NULL pointer to the space that is not created,
 * a string with a description
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_description();

/**
 * @test Test function for getting a description of a space
 * @pre Pointer to the space that is already created and
 * contains a description
 * @post Output == String that contains the description
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_description();

/**
 * @test Test function for getting a description of a space
 * @pre NULL pointer to the space that is not created and
 * does not contain any description
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_description();


/**
 * @test Test function for getting id of the down space
 * @pre Pointer to the space that is already created
 * and have the down space set
 * @post Output == ID of the down space
 * 
 * @author Rodrigo Juez
 */
void test1_space_get_down();
/**
 * @test Test function for getting id of the down space
 * @pre NULL pointer to the space that is already created
 * and does not have the down space set
 * @post Output == NO_ID
 * 
 * @author Rodrigo Juez
 */
void test2_space_get_down();
/**
 * @test Test function for getting id of the up space
 * @pre Pointer to the space that is already created
 * and have the up space set
 * @post Output == ID of the up space
 * 
 * @author Rodrigo Juez
 */
void test1_space_get_up();
/**
 * @test Test function for getting id of the up space
 * @pre NULL pointer to the space that is already created
 * and does not have the up space set
 * @post Output == NO_ID
 * 
 * @author Rodrigo Juez
 */
void test2_space_get_up();
/**
 * @test Test function for space_up setting
 * @pre Pointer to the space, id of the upper space 
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test1_space_set_up();
/**
 * @test Test function for space_north setting
 * @pre NULL pointer to the space, id of the up space
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test2_space_set_up();
/**
 * @test Test function for space_down setting
 * @pre Pointer to the space, id of the down space 
 * @post Output == OK
 * 
 * @author Rodrigo Juez
 */
void test1_space_set_down();
/**
 * @test Test function for space_down setting
 * @pre NULL pointer to the space, id of the down space 
 * @post Output == ERROR
 * 
 * @author Rodrigo Juez
 */
void test2_space_set_down();

/**
 * @test Test function for space_get_illuminated
 * @pre NULL pointer to the space 
 * @post Output == FALSE
 * 
 * @author Miguel Arnaiz
 */
void test1_space_get_illuminated();

/**
 * @test Test function for space_get_illuminated
 * @pre Pointer to the space 
 * @post Output == FALSE
 * 
 * @author Miguel Arnaiz
 */
void test2_space_get_illuminated();

/**
 * @test Test function for space_get_illuminated
 * @pre Pointer to the space 
 * @post Output == TRUE
 * 
 * @author Miguel Arnaiz
 */
void test3_space_get_illuminated();

/**
 * @test Test function for space_set_illuminated
 * @pre NULL pointer to the space, FALSE
 * @post Output == ERROR
 * 
 * @author Miguel Arnaiz
 */
void test1_space_set_illuminated();

/**
 * @test Test function for space_set_illuminated
 * @pre NULL pointer to the space, TRUE
 * @post Output == ERROR
 * 
 * @author Miguel Arnaiz
 */
void test2_space_set_illuminated();

/**
 * @test Test function for space_set_illuminated
 * @pre Pointer to the space, FALSE
 * @post Output == OK
 * 
 * @author Miguel Arnaiz
 */
void test3_space_set_illuminated();

/**
 * @test Test function for space_set_illuminated
 * @pre Pointer to the space, TRUE
 * @post Output == OK
 * 
 * @author Miguel Arnaiz
 */
void test4_space_set_illuminated();

/**
 * @test Test function for space_get_objects
 * @pre NULL pointer to the space
 * @post Output == NULL
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_objects();

/**
 * @test Test function for space_get_objects
 * @pre Pointer to the space
 * @post Output != NULL
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_objects();

/**
 * @test Test function for space_get_turned_on_object_on_the_space
 * @pre NULL pointer to the space
 * @post Output == FALSE
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_turned_on_object_on_the_space();

/**
 * @test Test function for space_get_turned_on_object_on_the_space
 * @pre Pointer to the space
 * @post Output == FALSE
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_turned_on_object_on_the_space();

/**
 * @test Test function for space_get_turned_on_object_on_the_space
 * @pre Pointer to the space
 * @post Output == TRUE
 * 
 * @author Mariusz Wiśniewski
 */
void test3_space_get_turned_on_object_on_the_space();

/**
 * @test Test function for space_set_turned_on_object_on_the_space
 * @pre NULL pointer to the space
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_turned_on_object_on_the_space();

/**
 * @test Test function for space_set_turned_on_object_on_the_space
 * @pre Pointer to the space
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_turned_on_object_on_the_space();

/**
 * @test Test function for space_get_detailed_desc
 * @pre NULL pointer to the space
 * @post Output == NULL
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_get_detailed_desc();

/**
 * @test Test function for space_get_detailed_desc
 * @pre Pointer to the space
 * @post Output != NULL
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_get_detailed_desc();

/**
 * @test Test function for space_set_detailed_desc
 * @pre NULL pointer to the space
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski
 */
void test1_space_set_detailed_desc();

/**
 * @test Test function for space_set_detailed_desc
 * @pre Pointer to the space
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski
 */
void test2_space_set_detailed_desc();

#endif
