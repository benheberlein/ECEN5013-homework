/******************************************************************************
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
 * @file ll2.c
 * @brief The implementation for a doubly linked list
 * 
 * This  file provides the function implementations for a doubly linked list.
 * The doubly linked contains functions to add and remove nodes, search through 
 * the linked list and return the index, return the size of the list, and 
 * destroy all nodes in the list.
 *
 * @author Ben Heberlein
 * @date September 7 2017
 * @version 1.0
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "ll2.h"

ll2_err_t ll2_destroy(ll2_node_t **head) {
    if (head == NULL) {
        return LL2_NULLPTR;
    }

    if (*head == NULL) {
        return LL2_SUCCESS;
    }

    ll2_node_t *temp_node = *head;
    ll2_node_t *temp_node_2 = *head;

    while(temp_node != NULL) {
        temp_node_2 = temp_node->next;
        free(temp_node);
        temp_node = temp_node_2;
    }

    *head = NULL;

    return LL2_SUCCESS;
}

ll2_err_t ll2_add_node(ll2_node_t **head, uint32_t data, uint16_t index) {
    if (head == NULL) {
        return LL2_NULLPTR;
    }

    uint16_t temp = 0;
    ll2_node_t *temp_node = NULL;

    /* Special case for index = 0 */
    if (index == 0) {
        temp_node = (ll2_node_t *) malloc(sizeof(ll2_node_t));
        if (temp_node == NULL) {
            return LL2_MEM;
        }
        temp_node->prev = NULL;

        /* This might be the only node */
        if (*head == NULL) {
            temp_node->next = NULL;
        } else {
            (*head)->prev = temp_node;
            temp_node->next = *head;
        }
        temp_node->data = data;
        *head = temp_node;
        return LL2_SUCCESS;
    }

    temp_node = *head;

    /* Iterate through list */
    while(temp < index-1) {
        /* Make sure it is a valid index */
        if (temp_node->next == NULL) {
            return LL2_INDEX;
        }

        /* Jump nodes */
        temp_node = temp_node->next;
        temp++;
    }

    /* Insert new node */
    ll2_node_t *insert = (ll2_node_t *) malloc(sizeof(ll2_node_t));
    if (insert == NULL) {
        return LL2_MEM;
    }
    insert->prev = temp_node;
    insert->next = temp_node->next;
    insert->data = data;
    if (temp_node->next != NULL) {
        temp_node->next->prev = insert;
    }
    temp_node->next = insert;

    return LL2_SUCCESS;
}

ll2_err_t ll2_remove_node(ll2_node_t **head, uint16_t index) {
    if (head == NULL) {
        return LL2_NULLPTR;
    }

    /* Must have some data */
    if (*head == NULL) {
        return LL2_INDEX;
    }

    uint16_t temp = 0;
    ll2_node_t *temp_node = *head;

    /* Special case for index = 0 */
    if (index == 0) {
        if (temp_node->next == NULL) {
            free(temp_node);
            *head = NULL;
        } else {
            ll2_node_t *t = temp_node->next;
            t->prev = NULL;
            free(temp_node);
            *head = t;            
        }

        return LL2_SUCCESS;
    }

    /* Iterate through list */
    while(temp < index) {
        /* Jump nodes */
        temp_node = temp_node->next;
        temp++;
 
        /* Make sure it is a valid index */
        if (temp_node == NULL) {
            return LL2_INDEX;
        }
   }

    /* Remove node */
    ll2_node_t *t = temp_node->prev;
    t->next = temp_node->next;
    if (temp_node->next != NULL) {
        temp_node->next->prev = t;
    }
    free(temp_node);

    return LL2_SUCCESS;
}

ll2_err_t ll2_search(ll2_node_t **head, uint32_t data, uint16_t *index) {
    if (head == NULL) {
        *index = -1;
        return LL2_NULLPTR;
    } 
    
    if (*head == NULL) {
        *index = -1;
        return LL2_DATA;
    }

    uint16_t temp = 0;
    ll2_node_t *temp_node = *head;
    
    while(temp_node != NULL) {
        if (temp_node->data == data) {
            *index = temp;
            return LL2_SUCCESS;
        }
        temp_node = temp_node->next;
        temp++;
    }

    *index = -1;
    return LL2_DATA;
}

uint16_t ll2_size(ll2_node_t **head) {
    if (head == NULL) {
        return 0;
    }

    if (*head == 0) {
        return 0;
    }

    uint16_t ctr = 0;
    ll2_node_t *temp_node = *head;
    
    while(temp_node != NULL) {
        temp_node = temp_node->next;
        ctr++;
    }

    return ctr;
}



