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
 * @file memsort_test.c
 * @brief A program for testing the memsort system call
 * 
 * This program tests the memsort sytsem call. Check the dmesg logs for
 * system call output.
 *
 * @author Ben Heberlein
 * @date September 17 2017
 * @version 1.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>

#define MEMSORT_NUM 500
#define BUF_SIZE 512
#define ABS_RAND 4096 

int main() {
    int32_t buf[BUF_SIZE];
    int32_t sbuf[BUF_SIZE];
    int32_t size = BUF_SIZE;

    printf("About to call memsort system call with null source pointer...\n");
    int32_t ret = syscall(MEMSORT_NUM, NULL, size, sbuf);
    printf("Returned from memsort system call with error %d...\n", ret);
    
    printf("About to call memsort system call with null destination pointer...\n");
    ret = syscall(MEMSORT_NUM, buf, size, NULL);
    printf("Returned from memsort system call with error %d...\n", ret);
 
    printf("About to call memsort system call with negative size...\n");
    ret = syscall(MEMSORT_NUM, buf, -100, sbuf);
    printf("Returned from memsort system call with error %d...\n", ret);
 
    /* Populate data */
    for(int i = 0; i < size; i++) {
        buf[i] = rand() % (ABS_RAND*2) - ABS_RAND;
    }

    printf("About to call memsort system call...\n");
    ret = syscall(MEMSORT_NUM, buf, size, sbuf);
    printf("Returned from memsort system call with error %d...\n", ret);
    
    return 0;
}
