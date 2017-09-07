/**********************************************************
* Name: circbuf.h
*
* Date: 09/25/2016
* Modified: 09/07/2017
*
* Author: Ben Heberlein
*
* Description: This file defines a circular buffer type and
* associated functions.
*
**********************************************************/

#ifndef CIRCBUF_H
#define CIRCBUF_H

#include <stdint.h>

/**********************************************************
* This is the circular buffer state enum used in the
* circbuf_t type.
**********************************************************/
typedef enum circbuf_state {PARTIAL=0, EMPTY, FULL, INVALID} circbuf_state_t;

/*********************************************************
* This is the circular buffer error enumeration
*********************************************************/
typedef enum circbuf_err {ERR_PARTIAL=0, ERR_EMPTY=1, ERR_FULL=2, ERR_SUCCESS=3, 
                          ERR_CONFIG=-1, ERR_MEM=-2, ERR_NULLPTR=-3, ERR_UNKNOWN=-4} circbuf_err_t;

/**********************************************************
* circbuf_t
* Author: Ben Heberlein
* Date: 09/25/2016
* Description: This is the main circular buffer structure.
* It has fields for buffer memory, headm tail, capacity,
* current size, and internal state.
**********************************************************/
typedef struct circbuf {

    uint32_t *buf;
    uint32_t *head;
    uint32_t *tail;

    uint16_t capacity;
    uint16_t size;

    circbuf_state_t STATUS;

} circbuf_t;

/***********************************************************
* circbuf_is_full     : circbuf_err_t circbuf_is_full(circbuf_t *circular_buffer);
*   returns           : ERR_FULL for full (true), ERR_PARTIAL for not full (false), or other error
    circular_buffer   : The circular buffer to be checked
* Author              : Ben Heberlein
* Date                : 09/07/2017
* Description         : Check if circular buffer is full
***********************************************************/
circbuf_err_t circbuf_is_full(circbuf_t *circular_buffer);

/***********************************************************
* circbuf_is_empty     : cirbuf_err_t circbuf_is_empty(circbuf_t *circular_buffer);
*   returns            : ERR_EMPTY for empty (true), ERR_PARTIAL for not empty (false), or other error
*   circular_buffer    : The circular buffer to be checked
* Author               : Ben Heberlein
* Date                 : 09/07/2017
* Description          : Check if circular buffer is empty
***********************************************************/
circbuf_err_t circbuf_buffer_empty(circbuf_t *circular_buffer);

/***********************************************************
* circbuf_add       : circbuf_err_t circbuf_add(uint32_t data, circbuf_t *circular_buffer);
*   returns         : ERR_SUCESS for success, or other error if failure
*   data            : The data to be added
*   circular_buffer : The circular buffer to be added to
* Author            : Ben Heberlein
* Date              : 09/07/2017
* Description       : Add an item to the circular buffer
***********************************************************/
circbuf_err_t circbuf_add(uint32_t data, circbuf_t *circular_buffer);

/***********************************************************
* circbuf_remove      : circbuf_err_t circbuf_remove(uint32_t *data, circbuf_t *circular_buffer);
*   returns           : ERR_SUCCESS for sucess, or other error
*   data              : Pointer to where to put data
*   circular_buffer   : The circular buffer to get data from
* Author              : Ben Heberlein
* Date                : 09/07/2017
* Description         : Remove an item from the circular buffer
***********************************************************/
circbuf_err_t circbuf_remove(uint32_t *data, circbuf_t *circular_buffer);

/***********************************************************
* circbuf_allocate   : circbuf_err_t circbuf_allocate(uint16_t capacity, circbuf_t **circular_buffer);
*   returns          : ERR_SUCCESS if successful, or another error if failed with *circular_buffer set to NULL
*   capacity		 : Capacity of the buffer
* Author             : Ben Heberlein
* Date               : 9/7/2017
* Description        : Initialize a new circular buffer and put it at the location of circular_buffer
***********************************************************/
circbuf_err_t circbuf_allocate(uint16_t capacity, circbuf_t **circular_buffer);

/***********************************************************
* circbuf_destroy    : circbuf_err_t circbuf_destroy(circbuf_t *circular_buf);
*   returns          : ERR_SUCCESS for successful destroy or other error
*   circular_buf     : Circular buffer to destroy
* Author             : Ben Heberlein
* Date               : 9/7/2017
* Description        : Destroy an existing circular buffer
***********************************************************/
circbuf_err_t circbuf_destroy(circbuf_t *circular_buf);

/***********************************************************
* circbuf_dump       : circbuf_err_t circbuf_dump(circbuf_t *circular_buf);
*   returns          : ERR_SUCCESS for success or other error code
*   circular_buf     : Circular buffer to dump
* Author             : Ben Heberlein
* Date               : 09/07/2017
* Description        : Prints the contents of the circular buffer
***********************************************************/
circbuf_err_t circbuf_dump(circbuf_t *circular_buf);

/***********************************************************
* circbuf_size       : uint16_t circbuf_size(circbuf_t *circular_buf);
*   return           : current_number of items stored
*   circular)buf     : Circular buffer to get size of
* Author             : Ben Heberlein
* Date               : 09/07/2017
* Description        : Returns the size of the given circular buffer
***********************************************************/
uint16_t circbuf_size(circbuf_t *circular_buf);

#endif
