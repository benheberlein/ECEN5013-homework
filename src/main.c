#include <stdint.h>
#include <stdio.h>
#include "circbuf.h"
#include "ll2.h"

int main() {
    /* Test circular buffer */

    circbuf_t *cb = NULL;
    circbuf_err_t err;

    err = circbuf_allocate(100, &cb);

    if (err == ERR_SUCCESS) {    
        printf("Successfully allocated circbuf.\n");
    } else {
        printf("Could not allocate circbuf. Error code %d\n", err);
    }

    for (int i = 0; i < 100; i++) {
        err = circbuf_add(i, cb);
    }

    err = circbuf_dump(cb);    
    printf("Size of circular buffer is %d\n", circbuf_size(cb));

    uint32_t temp = 0;
    for (int i = 0; i < 10; i++) {
        err = circbuf_remove(&temp, cb);
        printf("Removed %d\n", temp);
    }

    err = circbuf_dump(cb);
    printf("Size of circular buffer is %d\n", circbuf_size(cb));

    for (int i = 0; i < 5; i++) {
        err = circbuf_add(i, cb);
    }

    err = circbuf_dump(cb);
    printf("Size of circular buffer is %d\n", circbuf_size(cb));

    err = circbuf_destroy(cb);

    if (err == ERR_SUCCESS) {
        printf("Successfully destroyed circular buffer.\n");
    } else {
        printf("Could not destroy circular buffer.\n");
    }

    /* Test doubly linked list */
    ll2_node_t *head = NULL;
    ll2_err_t e;

    /* List should be 117, 17, 100, 1 */
    e = ll2_add_node(&head, 17, 0);
    e = ll2_add_node(&head, 100, 1);
    e = ll2_add_node(&head, 117, 0);
    e = ll2_add_node(&head, 1, 3);
    
    /* List should be 17, 1 */
    e = ll2_remove_node(&head, 0);
    e = ll2_remove_node(&head, 1);

    return 0;
}
