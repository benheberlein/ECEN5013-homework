Unit tests for ll2.c doubly linked list and circbuff.h circular buffer.

Circular buffer tests are not written yet, but will follow a similar format
to the unit tests for ll2.c.

Ben Heberlein

*************

The following functions are tested:
    ll2_add_node
        tests insertion at the beginning, end, and middle of list
        tests case where HEAD is NULL for correct failure
        tests out of bounds insertion for correct failure

    ll2_remove_node
        tests removal at beginning, end, and middle of list
        tests case where HEAD is NULL for correct failure
        tests out of bounds removal for correct failure

    ll2_search
        tests search function
        tests not present search for correct failture
        tests case where HEAD is NULL for correct failure

    ll2_size 
        tests size function when adding a large number of nodes
        tests size function when removing a large number of nodes

    ll2_destroy
        tests destroying an empty list
        tests destroying a populated list
        tests NULL pointer condition for correct failure
