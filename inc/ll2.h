/*******************************************************************************
* Copyright (C) 2017 by Ben Heberlein
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. This file
* was created for the University of Colorado Boulder course Advanced Practical
* Embedded Software Development. Ben Heberlein and the University of Colorado 
* are not liable for any misuse of this material.
*
*******************************************************************************/
/**
 * @file ll2.h
 * @brief The interface for a doubly linked list implementation
 * 
 * This header file provides the interface for a doubly linked list
 * implementation. The doubly linked contains functions to add and remove nodes
 * nodes, search through the linked list and return the index, return the size 
 * of the list, and destroy all nodes in the list.
 *
 * @author Ben Heberlein
 * @date September 7 2017
 * @version 1.0
 *
 */

#ifndef __LL2_H__
#define __LL2_H__

#include <stdint.h>

/**
 * @brief Structure for a node
 */
typedef struct ll2_node_s {
    struct ll2_node_s *prev;
    struct ll2_node_s *next;
    uint32_t data;
} ll2_node_t;

/**
 * @brief Enum for linked list error codes
 */
typedef enum ll2_err_e {
    LL2_SUCCESS=0,
    LL2_INDEX=-1,
    LL2_MEM=-2,
    LL2_NULLPTR=-3,
    LL2_OTHER=-4,
} ll2_err_t;

/**
 * @brief Destroys all nodes in the list
 * 
 * This function destroys all nodes in the linked list, starting from the head
 * node and transversing up the list. If there is a memory error, the function
 * returns LL2_MEM. If there is another error, the function returns LL2_OTHER.
 * Returns LL2_SUCCESS for successful operation. 
 *
 * @param head A double pointer to the linked list head
 *
 * @return A status code of type ll2_err_t
 */
ll2_err_t ll2_destroy(ll2_node_t **head);

/**
 * @brief Adds a node to the list at the specified index
 * 
 * This function adds data to the linked list at the specified index. If the
 * list is not long enough, the function returns LL2_INDEX. If another error
 * occurs, the function returns LL2_OTHER. Returns LL2_SUCCESS for successful
 * operation.
 * 
 * @param head A double pointer to the linked list head
 * @param data The data that should be inserted
 *
 * @return A status code of type ll2_err_t
 */
ll2_err_t ll2_add_node(ll2_node_t **head, uint32_t data, uint16_t index);

/**
 * @brief Removes a node at the specified index
 * 
 * This function removes a node from the linked list at the index specified.
 * If the index is out of bounds, the function will return LL2_INDEX. If 
 * there is a memory error, the function returns LL2_MEM. If there is another
 * error, the function returns LL2_OTHER.
 * 
 * @param head A double pointer to the linked list head
 * @param index the index that should be deleted
 *
 * @return A status code of type ll2_err_t
 */
ll2_err_t ll2_remove_node(ll2_node_t **head, uint16_t index);

/**
 * @brief Searches the linked list for data
 * 
 * This function searches the linked list for the specified data. If the data
 * is found, the function will return the index of the data through the index
 * pointer and return LL2_SUCCESS. If the data is not found, the function will 
 * return LL2_DATA. If there is another error, the function returns LL2_OTHER. 
 * 
 * @param head A double pointer to the linked list head
 * @param data The data to search for in the list
 * @param index A pointer to return the index of the data
 *
 * @return A status code of type ll2_err_t
 */
ll2_err_t ll2_search(ll2_node_t **head, uint32_t data, uint16_t *index);

/**
 * @brief Finds the size of the linked list
 * 
 * This function returns the size of the linked list directly. 
 * 
 * @param head A double pointer to the linked list head
 *
 * @return The number of nodes in the list
 */
uint16_t ll2_size(ll2_node_t **head); 

#endif /* __LL2_H__ */
