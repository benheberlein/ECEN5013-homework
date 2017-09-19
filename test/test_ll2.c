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
 * @file test_ll2.c
 * @brief The unit tests for doubly linked list implementation
 * 
 * This file contains unit tests for the doubly linked list implementation. 
 * This file should be updated with new tests as bugs are discovered.
 *
 * @author Ben Heberlein
 * @date September 18 2017
 * @version 1.0
 *
 */

#include "ll2.h"
#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <limits.h>

void test_ll2_add_node(void) {
    ll2_node_t *head = NULL;
    ll2_err_t e;

    /* Insert at end of list */
    e = ll2_add_node(&head, 17, 0);
    assert_true(e == LL2_SUCCESS);
    assert_true(head != NULL);
    assert_true(head->data == 17);
    assert_true(ll2_size(&head) == 1);
    
    e = ll2_add_node(&head, 100, 1);
    assert_true(e == LL2_SUCCESS);
    assert_true(head->next != NULL);
    assert_true(head->next->data == 100);
    assert_true(ll2_size(&head) == 2);
    
    e = ll2_add_node(&head, 117, 2);
    assert_true(e == LL2_SUCCESS);
    assert_true(head->next->next != NULL);
    assert_true(head->next->next->data == 117);
    assert_true(ll2_size(&head) == 3);

    /* Insert at beginning of list */
    e = ll2_add_node(&head, 200, 0);
    assert_true(e == LL2_SUCCESS);
    assert_true(head != NULL);
    assert_true(head->data == 200);
    assert_true(ll2_size(&head) == 4);

    /* NULL pointer */
    e = ll2_add_node(NULL, 0, 0);
    assert_true(e == LL2_NULLPTR);

    /* Out of bounds */
    e = ll2_add_node(&head, 100, 1000);
    assert_true(e == LL2_INDEX);    

}

void test_ll2_remove_node(void) {
    ll2_node_t *head = NULL;
    ll2_err_t e;

    /* Populate */    
    e = ll2_add_node(&head, 17, 0);
    e = ll2_add_node(&head, 100, 1);
    e = ll2_add_node(&head, 117, 2);
    e = ll2_add_node(&head, 200, 0);

    /* Remove at the beginning */
    e = ll2_remove_node(&head, 0);
    assert_true(e == LL2_SUCCESS);
    assert_true(head != NULL);
    assert_true(head->data == 17);
    assert_true(ll2_size(&head) == 3);

    /* Remove at the end */
    e = ll2_remove_node(&head, 2);
    assert_true(e == LL2_SUCCESS);
    assert_true(head != NULL);
    assert_true(head->next->data == 100);
    assert_true(ll2_size(&head) == 2);

    /* NULL pointer */
    e = ll2_remove_node(NULL, 0);
    assert_true(e == LL2_NULLPTR);
    
    /* Out of bounds */
    e = ll2_remove_node(&head, 99);
    assert_true(e = LL2_INDEX);

}

void test_ll2_search(void) {
    ll2_node_t *head = NULL;
    ll2_err_t e;

    /* Populate */    
    e = ll2_add_node(&head, 17, 0);
    e = ll2_add_node(&head, 100, 1);
    e = ll2_add_node(&head, 117, 2);
    e = ll2_add_node(&head, 200, 0);

    /* Find data */
    uint16_t i = 0;
    e = ll2_search(&head, 100, &i);
    assert_true(e == LL2_SUCCESS);
    assert_true(i == 2);

    e = ll2_search(&head, 17, &i);
    assert_true(e == LL2_SUCCESS);
    assert_true(i == 1);

    e = ll2_search(&head, 117, &i);
    assert_true(e == LL2_SUCCESS);
    assert_true(i == 3);

    /* Not present */
    e = ll2_search(&head, 91, &i);
    assert_true(e == LL2_DATA);
    assert_true(i == USHRT_MAX);

}

void test_ll2_size(void) {
    ll2_node_t *head = NULL;
    ll2_err_t e;

    /* Add a ton of nodes */
    for (int i = 1; i <= 100; i++) {
        e = ll2_add_node(&head, 2*i, 0);
        assert_true(ll2_size(&head) == i);
    }

    /* Remove a ton of nodes */
    for (int i = 99; i >= 0; i--) {
        e = ll2_remove_node(&head, 0);
        assert_true(ll2_size(&head) == i);
    }

}

void test_ll2_destroy(void) {
    ll2_node_t *head = NULL;
    ll2_err_t e;

    /* Destroy an empty list */
    e = ll2_destroy(&head);
    assert_true(e == LL2_SUCCESS);

    /* Populate */    
    e = ll2_add_node(&head, 17, 0);
    e = ll2_add_node(&head, 100, 1);
    e = ll2_add_node(&head, 117, 2);
    e = ll2_add_node(&head, 200, 0);

    /* Destroy list */
    e = ll2_destroy(&head);
    assert_true(head == NULL);
    assert_true(e == LL2_SUCCESS);

    /* NULL pointer */
    e = ll2_destroy(NULL);
    assert_true(e == LL2_NULLPTR);
    
}

int main(void) {

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ll2_add_node),
        cmocka_unit_test(test_ll2_remove_node),
        cmocka_unit_test(test_ll2_search),
        cmocka_unit_test(test_ll2_size),
        cmocka_unit_test(test_ll2_destroy),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
