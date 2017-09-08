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
 * @file main.c
 * @brief The main function that demonstrates ll2 and circbuf
 * 
 * This  file provides a demonstration/test of the circbuf implementation and 
 * ll2 implementation for Advanced Practical Embedded Software Development 
 * homework 1. This file is by no means supposed to be an exhaustive test
 * suite, but should be enough to demonstrate basic functionality. A proper 
 * set of unit tests should be implemented to show that the two libraries work
 * as intended.
 *
 * @author Ben Heberlein
 * @date September 7 2017
 * @version 1.0
 *
 */

#include <stdint.h>
#include <stdio.h>
#include "circbuf.h"
#include "ll2.h"

int main() {
    /* Test circular buffer */

    circbuf_t *cb = NULL;
    circbuf_err_t err;

    /* Allocate circbuf */
    err = circbuf_allocate(100, &cb);

    if (err == ERR_SUCCESS) {    
        printf("Successfully allocated circbuf.\n");
    } else {
        printf("Could not allocate circbuf. Error code %d\n", err);
    }

    /* Add data */
    for (int i = 0; i < 100; i++) {
        err = circbuf_add(i, cb);
    }

    err = circbuf_dump(cb);    
    printf("Size of circular buffer is %d\n", circbuf_size(cb));

    /* Remove data */
    uint32_t temp = 0;
    for (int i = 0; i < 10; i++) {
        err = circbuf_remove(&temp, cb);
        printf("Removed %d\n", temp);
    }

    err = circbuf_dump(cb);
    printf("Size of circular buffer is %d\n", circbuf_size(cb));

    /* Add more data to show loop around */
    for (int i = 0; i < 5; i++) {
        err = circbuf_add(i, cb);
    }

    err = circbuf_dump(cb);
    printf("Size of circular buffer is %d\n", circbuf_size(cb));

    /* Free the buffer */
    err = circbuf_destroy(cb);

    if (err == ERR_SUCCESS) {
        printf("Successfully destroyed circular buffer.\n");
    } else {
        printf("Could not destroy circular buffer.\n");
    }

    /* Test doubly linked list */
    ll2_node_t *head = NULL;
    ll2_err_t e;

    printf("Size of list is: %d\n", ll2_size(&head));
    
    /* List should be 117, 17, 100, 1, verify with GDB*/
    e = ll2_add_node(&head, 17, 0);
    e = ll2_add_node(&head, 100, 1);
    e = ll2_add_node(&head, 117, 0);
    e = ll2_add_node(&head, 1, 3);    
    printf("Size of list is: %d\n", ll2_size(&head));
    
    uint16_t i = 0;
    e = ll2_search(&head, 100, &i);
    printf("100 found at index %d\n", i);
    e = ll2_search(&head, 1, &i);
    printf("1 found at index %d\n", i);
    
    /* Should not work, return index 0 */
    e = ll2_search(&head, 52, &i);
    if (e == LL2_DATA) {
        printf("52 not found\n");
    } else {
        printf("Somehow found 52 at index %d\n", i);
    }

    /* List should be 17, 1, verify with GDB*/
    e = ll2_remove_node(&head, 0);
    e = ll2_remove_node(&head, 1);
    printf("Size of list is: %d\n", ll2_size(&head));

    /* Should be empty */
    e = ll2_destroy(&head);
    if (head == NULL) {
        printf("Destroyed list\n");
    } else {
        printf("Did not destroy list\n");
    }

    return 0;
}
