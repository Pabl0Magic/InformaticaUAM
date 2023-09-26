/**
 * @brief It defines the inventory module
 * 
 * @file inventory.h
 * @author Pablo Almarza and Mariusz Wiśniewski
 * 
 * @version 02.0
 * @date 04-04-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"
#include "object.h"


#define INVENTORY_CAPACITY 20       /*!< Max number of objects a player can carry */

/**
 * @brief Parameters to save all the objects
 * 
 */
typedef struct _Inventory Inventory;
/**
 * @brief It allocates the memory for the inventory
 * as it does for the set module and sets
 * the max number of objects that can be carried
 * @author Pablo Almarza
 * 
 * @return Inventory* The space allocated
 * @date 04-04-2019
 */
Inventory* inventory_create();

/**
 * @brief It will destroy the memory allocated 
 * for the inventory
 * @author Pablo Almarza
 * 
 * @param i The inventory structure
 * @date 04-04-2019
 */
STATUS inventory_destroy(Inventory *i);

/**
 * @brief It will set the new object carried into
 * the inventory unless the inventory is full
 * @author Pablo Almarza
 * 
 * @param i The inventory structure
 * @param id The id of the object
 * @return STATUS OK if it goes as expected
 * @date 04-04-2019
 */
STATUS inventory_set_object_to_inventory(Inventory* i, Id id);

/**
 * @brief It will get a object that is stored
 * in the inventory by his id
 * @author Pablo Almarza
 * 
 * @param i The inventory structure
 * @param index The id of the object
 * @return Id The id of the object
 * @date 04-04-2019
 */
Id inventory_get_object_from_inventory(Inventory* i, int index);

/**
 * @brief It checks if the inventory is full
 * @author Pablo Almarza
 * 
 * @param i The inventory structure 
 * @return BOOL TRUE if the inventory is full, ERROR other case
 * @date 04-04-2019
 */
BOOL inventory_is_full(Inventory* i);

/**
 * @brief It gets the number of objects that are
 * at the moment in the inventory
 * @author Pablo Almarza
 * 
 * @param i The inventory structure
 * @return int The number of objects carried
 * @date 04-04-2019
 */
int inventory_get_number_objects(Inventory* i);

/**
 * @brief Find the object that the player wants
 * @author Pablo Almarza
 * 
 * @param i The inventory structure
 * @param id The id of the object that you want to find
 * @return TRUE if the object is in the inventory
 * @date 04-04-2019
 */
BOOL inventory_find_object(Inventory* i,Id id);

/**
 * @brief Print all the information of the inventory
 * @author Pablo Almarza
 * 
 * @param i The inventory structure
 * @return STATUS OK if it goes as expected
 * @date 04-04-2019
 */
STATUS inventory_print(Inventory* i);

/**
 * @brief Gets a pointer to the set of objects
 * @author Mariusz Wiśniewski
 * 
 * @param inv A pointer to the inventory structure
 * @return Set - A pointer to the set of objects
 * @date 04-04-2019
 */
Set* inventory_get_objects(Inventory* inv);

/**
 * @brief Deletes an object from the inventory
 * @author Mariusz Wiśniewski
 * 
 * @param inv A pointer to the inventory structure,
 * an id of the object that we want to delete from the inventory
 * @param id The id of the object we want to delete
 * @return STATUS OK if everything goes as expected
 * @date 04-04-2019
 */
STATUS inventory_delete_object(Inventory* inv, Id id);


#endif