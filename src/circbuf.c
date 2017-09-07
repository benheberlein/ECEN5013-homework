/**********************************************************
* Name: circbuf.c
*
* Date: 09/25/2016
* Modfied: 09/07/2017
*
* Author: Ben Heberlein
*
* Description: This file implements several functions to
* manage a circular_buffer.
*
**********************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "circbuf.h"

#define MAX_CAP 1024

/***********************************************************
* circbuf_is_full     : circbuf_err_t circbuf_buffer_full(circbuf_t *circular_buffer);
*   returns           : ERR_FULL for full (true), ERR_PARTIAL for not full (false), or other error
    circular_buffer   : The circular buffer to be checked
* Author              : Ben Heberlein
* Date                : 09/07/2017
* Description         : Check if circular buffer is full
***********************************************************/
circbuf_err_t circbuf_is_full(circbuf_t *circular_buffer) {
    // Check if valid buffer
    if (circular_buffer == NULL) {
        return ERR_NULLPTR;
    }

    if (circular_buffer->STATUS == FULL) {
        return ERR_FULL;
    } else {
        return ERR_PARTIAL;
    }
}

/***********************************************************
* circbuf_is_empty     : cirbuf_err_t circbuf_is_empty(circbuf_t *circular_buffer);
*   returns            : ERR_EMPTY for empty (true), ERR_PARTIAL for not empty (false), or other error
*   circular_buffer    : The circular buffer to be checked
* Author               : Ben Heberlein
* Date                 : 09/07/2017
* Description          : Check if circular buffer is empty
***********************************************************/
circbuf_err_t circbuf_is_empty(circbuf_t *circular_buffer) {
    // Check if valid buffer
    if (circular_buffer == NULL) {
        return ERR_NULLPTR;
    }

    if (circular_buffer->STATUS == EMPTY) {
        return ERR_EMPTY;
    } else {
        return ERR_PARTIAL;
    }
}

/***********************************************************
* circbuf_add       : circbuf_err_t circbuf_add(uint32_t data, circbuf_t *circular_buffer);
*   returns         : ERR_SUCCESS for success, or other error if failure
*   data            : The data to be added
*   circular_buffer : The circular buffer to be added to
* Author            : Ben Heberlein
* Date              : 09/07/2017
* Description       : Add an item to the circular buffer
***********************************************************/
circbuf_err_t circbuf_add(uint32_t data, circbuf_t *circular_buffer) {
    // Check if valid buffer
    if (circular_buffer == NULL) {
        return ERR_NULLPTR;
    }

    // Check if full
    if (circular_buffer->STATUS == FULL) {
        return ERR_FULL;
    }

    // Set data
    *(circular_buffer->head) = data;

    // Increment head and check for wrap
    circular_buffer->head++;
    if ((circular_buffer->head - circular_buffer->buf) >= circular_buffer->capacity) {
        circular_buffer->head -= circular_buffer->capacity;
    }
    circular_buffer->size++;

    // Set new state
    if (circular_buffer->size == circular_buffer->capacity ||
        circular_buffer->head == circular_buffer->tail) {
        circular_buffer->STATUS = FULL;
    } else {
        circular_buffer->STATUS = PARTIAL;
    }

    return ERR_SUCCESS;
}

/***********************************************************
* circbuf_remove      : circbuf_err_t circbuf_remove(uint32_t *data, circbuf_t *circular_buffer);
*   returns           : ERR_SUCCESS for sucess, or other error
*   data              : Pointer to where to put data
*   circular_buffer   : The circular buffer to get data from
* Author              : Ben Heberlein
* Date                : 09/07/2017
* Description         : Remove an item from the circular buffer
***********************************************************/
circbuf_err_t circbuf_remove(uint32_t *data, circbuf_t *circular_buffer) {
    // Check if valid buffer
    if (circular_buffer == NULL) {
        return ERR_NULLPTR;
    }

    // Check if empty
    if (circular_buffer->STATUS == EMPTY) {
        return ERR_EMPTY;
    }

    // Get data
    *data = *(circular_buffer->tail);

    // Increment tail and check for wrap
    circular_buffer->tail++;
    if ((circular_buffer->tail - circular_buffer->buf) >= circular_buffer->capacity) {
        circular_buffer->tail -= circular_buffer->capacity;
    }
    circular_buffer->size--;

    // Set new state
    if (circular_buffer->size == 0) {// || circular_buffer->head == circular_buffer->tail) {
        circular_buffer->STATUS = EMPTY;
    } else {
        circular_buffer->STATUS = PARTIAL;
    }

    return ERR_SUCCESS;
}


/***********************************************************
* circbuf_allocate   : circbuf_err_t circbuf_allocate(uint16_t capacity, circbuf_t **circular_buffer);
*   returns          : ERR_SUCCESS if successful, or another error if failed with *circular_buffer set to NULL
*   capacity         : Capacity of the buffer
* Author             : Ben Heberlein
* Date               : 9/7/2017
* Description        : Initialize a new circular buffer and put it at the location of circular_buffer
***********************************************************/
circbuf_err_t circbuf_allocate(uint16_t capacity, circbuf_t **init)  {

  //check zero case
  if(capacity == 0) return ERR_CONFIG;

  // check maximum
  if (capacity > MAX_CAP) return ERR_CONFIG;

	*init = (circbuf_t *) malloc(sizeof(circbuf_t));
	if (*init == NULL) {
		return ERR_MEM;
	}

	(*init)->buf = NULL;
	(*init)->buf = (uint32_t *) malloc(capacity * sizeof(uint32_t));
	if ((*init)->buf == NULL) {
		free(*init);
		return ERR_MEM;
	}

	(*init)->head = (*init)->buf;
	(*init)->tail = (*init)->buf;
	(*init)->capacity = capacity;
	(*init)->size = 0;
	(*init)->STATUS = EMPTY;

	return ERR_SUCCESS;
}

/***********************************************************
* circbuf_destroy    : circbuf_err_t circbuf_destroy(circbuf_t *circular_buf);
*   returns          : ERR_SUCCESS for successful destroy or other error
*   circular_buf     : Circular buffer to destroy
* Author             : Ben Heberlein
* Date               : 9/7/2017
* Description        : Destroy an existing circular buffer
***********************************************************/
circbuf_err_t circbuf_destroy(circbuf_t *circular_buf) {
	if (circular_buf == NULL) {
		return ERR_NULLPTR;
	}

	if (circular_buf->buf == NULL) {
		free(circular_buf);
		return ERR_NULLPTR;
	}

	free(circular_buf->buf);
	free(circular_buf);
	return ERR_SUCCESS;
}

/***********************************************************
* circbuf_dump       : circbuf_err_t circbuf_dump(circbuf_t *circular_buf);
*   returns          : ERR_SUCCES for sueccess or other error code
*   circular_buf     : Circular buffer to dump
* Author             : Ben Heberlein
* Date               : 09/07/2017
* Description        : Prints the contents of the circular buffer
***********************************************************/
circbuf_err_t circbuf_dump(circbuf_t *circular_buf) {
    if (circular_buf == NULL) {
        return ERR_NULLPTR;
    }

    if (circular_buf->buf == NULL) {
        return ERR_NULLPTR;
    }

    uint32_t *temp = circular_buf->tail;
    uint16_t ctr = 0;

    printf("Circular buffer from tail to head:\n");

    while (ctr < circular_buf->size) {
        printf("%d\n", *temp);        
        temp++;
        ctr++;
        if (temp >= circular_buf->buf + circular_buf->capacity) {
            temp = circular_buf->buf;
        }
    }

    return ERR_SUCCESS;
}

/*********************************************************** 
* circbuf_size       : uint16_t circbuf_size(circbuf_t *circular_buf); 
*   return           : current_number of items stored 
*   circular)buf     : Circular buffer to get size of 
* Author             : Ben Heberlein 
* Date               : 09/07/2017 
* Description        : Returns the size of the given circular buffer 
***********************************************************/ 
uint16_t circbuf_size(circbuf_t *circular_buf) {
    if (circular_buf == NULL) {
        return (uint16_t) ERR_NULLPTR;
    }

    return circular_buf->size;
}

