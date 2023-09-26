/** 
 * @brief It declares the tests for the inventory module
 * 
 * @file inventory_test.h
 * @author Mariusz Wiśniewski
 * @version 2.0 
 * @date 04-04-2019
 * @copyright GNU Public License
 */

#ifndef inventory_TEST_H
#define inventory_TEST_H

/**
 * @test Test inventory creation 
 * @post Non NULL pointer to the inventory
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_create();

/**
 * @test Test inventory destruction
 * @pre Pointer to the inventory
 * @post Output == OK 
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_destroy();

/**
 * @test Test inventory destruction
 * @pre NULL pointer to the inventory
 * @post Output == ERROR 
 * 
 * @author Mariusz Wiśniewski 
 */
void test2_inventory_destroy();

/**
 * @test Test adding objects to the inventory
 * @pre Pointer to the inventory, id of a new object
 * @post Output == OK 
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_set_object_to_inventory();

/**
 * @test Test adding objects to the inventory
 * @pre NULL pointer to the inventory, id of a new object
 * @post Output == ERROR 
 * 
 * @author Mariusz Wiśniewski 
 */
void test2_inventory_set_object_to_inventory();

/**
 * @test Test deleting objects from the inventory
 * @pre Pointer to the inventory, id of the deleting object
 * that already exists in the inventory
 * @post Output == OK 
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_delete_object();

/**
 * @test Test deleting objects from the inventory
 * @pre NULL pointer to the inventory, id of the deleting object
 * that does not exist in the inventory
 * @post Output == ERROR 
 * 
 * @author Mariusz Wiśniewski 
 */
void test2_inventory_delete_object();

/**
 * @test Test deleting objects from the inventory
 * @pre Pointer to the inventory, id of the deleting object
 * that does not exist in the inventory
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski 
 */
void test3_inventory_delete_object();

/**
 * @test Test getting object's id from the inventory
 * @pre Pointer to the inventory, index of the object
 * that we want to find and exists in the inventory
 * @post Output == Object's id
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_get_object_from_inventory();

/**
 * @test Test getting object's id from the inventory
 * @pre NULL pointer to the inventory, index of the object
 * that we want to find but does not exist in the inventory
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski 
 */
void test2_inventory_get_object_from_inventory();

/**
 * @test Test getting object's id from the inventory
 * @pre Pointer to the inventory, index of the object
 * that we want to find but does not exist in the inventory
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski 
 */
void test3_inventory_get_object_from_inventory();

/**
 * @test Test checking if the inventory is full
 * @pre Pointer to the full inventory
 * @post Output == TRUE
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_is_full();

/**
 * @test Test checking if the inventory is full
 * @pre Pointer to the not full inventory
 * @post Output == FALSE
 * 
 * @author Mariusz Wiśniewski 
 */
void test2_inventory_is_full();

/**
 * @test Test checking if the inventory is full
 * @pre NULL pointer to the empty inventory
 * @post Output == FALSE
 * 
 * @author Mariusz Wiśniewski 
 */
void test3_inventory_is_full();

/**
 * @test Test getting the number of objects in the inventory
 * @pre Pointer to the inventory
 * @post Output == Number of objects
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_get_number_objects();

/**
 * @test Test getting the number of objects in the inventory
 * @pre Pointer to the empty inventory
 * @post Output == Number of objects(0)
 * 
 * @author Mariusz Wiśniewski 
 */
void test2_inventory_get_number_objects();

/**
 * @test Test getting the number of objects in the inventory
 * @pre NULL pointer to the inventory
 * @post Output == Number of objects(1)
 * 
 * @author Mariusz Wiśniewski 
 */
void test3_inventory_get_number_objects();

/**
 * @test Test finding a particular object in the inventory
 * @pre Pointer to the inventory, id of an object that is
 * in the inventory
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_find_object();

/**
 * @test Test finding a particular object in the inventory
 * @pre Pointer to the empty inventory, id of an object that is
 * not in the inventory
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski 
 */
void test2_inventory_find_object();

/**
 * @test Test finding a particular object in the inventory
 * @pre NULL pointer to the inventory, id of an object that is
 * not in the inventory
 * @post Output == ERROR
 * 
 * @author Mariusz Wiśniewski 
 */
void test3_inventory_find_object();

/**
 * @test Test getting a pointer to the set
 * @pre Pointer to the inventory with an object inside
 * @post Output!=NULL
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_get_objects();

/**
 * @test Test getting a pointer to the set
 * @pre Pointer to the inventory with no objects
 * @post Output == NULL
 * 
 * @author Mariusz Wiśniewski 
 */
void test2_inventory_get_objects();

/**
 * @test Test getting a pointer to the set
 * @pre NULL pointer to the inventory with no object
 * @post Output == NULL
 * 
 * @author Mariusz Wiśniewski 
 */
void test3_inventory_get_objects();

/**
 * @test Test printing information about the inventory
 * @pre Pointer to the inventory
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski 
 */
void test1_inventory_print();

/**
 * @test Test printing information about the inventory
 * @pre NULL pointer to the inventory
 * @post Output == OK
 * 
 * @author Mariusz Wiśniewski 
 */
void test2_inventory_print();

#endif