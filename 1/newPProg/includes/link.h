/**
 * @brief Link module header
 * 
 * @file link.h
 * @author Miguel Arnaiz
 * 
 * @version 0.1
 * @date 19-03-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef LINK_H
#define LINK_H

#include "types.h"

/**
 * @brief The structure consists on:
 *      - An id for the link
 *      - An id for the first connected space
 *      - An id for the second connected space
 *      - An bool for the link open/closed = true/false
 * 
 * @author Miguel Arnaiz
 * @date 21-03-2019
 */
typedef struct _Link Link;

/**
 * @brief Creates a new link allocating memory with the sent id
 * @author Miguel Arnaiz
 * 
 * @param id_link The id we want to set to the new link
 * @return Link* The created Link* variable
 * @date 21-03-2019
 */
Link *link_create(Id id_link);

/**
 * @brief Frees the memory reserved for a link.
 * @author Miguel Arnaiz
 * 
 * @param l The link we want to destroy
 * @date 21-03-2019
 */
void link_destroy(Link *l);

/**
 * @brief Gets the id of the sent link.
 * @author Miguel Arnaiz
 * 
 * @param l The link structure
 * @return Id The id of the link sent
 * @date 21-03-2019
 */
Id link_get_id(Link *l);

/**
 * @brief Gets the id of the space1 of the sent link.
 * @author Miguel Arnaiz
 * 
 * @param l The link structure
 * @return Id The id of the space1 of the link sent
 * @date 21-03-2019
 */
Id link_get_space1(Link *l);

/**
 * @brief Gets the id of the space2 of the sent link.
 * @author Miguel Arnaiz
 * 
 * @param l The link structure
 * @return Id The id of the space2 link sent
 * @date 21-03-2019
 */
Id link_get_space2(Link *l);

/**
 * @brief returns the oposite space of the inserted in the argument
 * 
 * @param l The link structure
 * @param id The id of the link 
 * @return Id The id of the opposite link
 */
Id link_get_oposite(Link *l, Id id);


/**
 * @brief Gets the status of the open of the sent link.
 * @author Miguel Arnaiz
 * 
 * @param l The link structure
 * @return BOOL TRUE/ FALSE == link open/closed
 * @date 21-03-2019
 */
BOOL link_get_open(Link *l);


/**
 * @brief Sets the link's id to the new one sent.
 * @author Miguel Arnaiz
 * 
 * @param l The link structure
 * @param id The id of the link we want to set
 * @return STATUS OK if it goes as expected
 * @date 21-03-2019
 */
STATUS link_set_id(Link *l, Id id);

/**
 * @brief Sets the space1's id to the new one sent.
 * @author Miguel Arnaiz
 * 
 * @param l The link structure
 * @param space1 The space1 id we want to set
 * @return STATUS OK if it goes as expected
 * @date 21-03-2019
 */
STATUS link_set_space1(Link *l, Id space1);
/**
 * @brief Gets the name of the link sent
 * @author Rodrigo Juez
 * 
 * @param l The link structure
 * @return char*
 * @date 21-03-2019
 */
char* link_get_name(Link *l);
/**
* @brief Sets the name of the link
 * @author Rodrigo Juez
 * 
 * @param l The link structure
 * @param name of the link
 * @return STATUS OK if it goes as expected
 * @date 21-03-2019
 */
STATUS link_set_name(Link *l, char* name);
/**
 * @brief Sets the space2's id to the new one sent.
 * @author Miguel Arnaiz
 * 
 * @param l The link structure
 * @param space2 The space2 id we want to set
 * @return STATUS OK if it goes as expected
 * @date 21-03-2019
 */
STATUS link_set_space2(Link *l, Id space2);

/**
 * @brief Sets the bool open to the new one sent. (openning or closing the link)
 * @author Miguel Arnaiz
 * 
 * @param l The link structure
 * @param open The open BOOL we want to set
 * @return STATUS OK if it goes as expected
 * @date 21-03-2019 
 */
STATUS link_set_open(Link *l, BOOL open);

/**
 * @brief Prints the link sent in the file sent.
 * @author Miguel Arnaiz
 * 
 * @param pf File where the link is printed
 * @param l The link structure
 * @return STATUS OK if it goes as expected
 * @date 21-03-2019 
 */
STATUS link_print(FILE *pf, Link *l);

#endif