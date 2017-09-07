#include <stdint.h>
#include <stdio.h>
#include "circbuf.h"


int main() {

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

    return 0;
}
