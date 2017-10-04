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
 * @file profiling.c
 * @brief Compares the time it takes to create threads
 * 
 * This thread compares execution times for different methods of creating
 * processes. There is an associated kernel module in kernel_profiling.c that
 * will look at execution time for kthread_create.
 *
 * @author Ben Heberlein
 * @date October 2 2017
 * @version 1.0
 *
 */

#define _GNU_SOURCE

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>

static int retval;

double time_fork_exec = 0;
double time_pthread_create = 0;

static void *__pthread_helper(void *arg) {
    
    system("/bin/ls -al");

    retval = 0;

    return &retval;
}

void fork_exec() {
    clock_t start = clock();
    
    pid_t pid = fork();
    
    if (pid == 0) {
        execl("/bin/ls", "ls", "-al", (char *) 0);
        
    } else {
        int result = 0;
        waitpid(pid, &result, 0);
    }

    clock_t end = clock();

    time_fork_exec = (double) (end-start) / CLOCKS_PER_SEC;

    return;
}

void pthread_create_thread() {
    int joinret = 0;
    int *joinptr = 0;

    int arg;
    pthread_t thread;   
 
    clock_t start = clock();
    pthread_create(&thread, NULL, __pthread_helper, &arg);
    pthread_join(thread, (void **) &joinptr);
    clock_t end = clock();
    
    time_pthread_create = (double) (end-start) / CLOCKS_PER_SEC;

    return;
}

int main(void) {
    printf("fork_exec\n");
    /* a new process using fork and exec */
    fork_exec();   
    printf("fork exec took %f seconds.\n", time_fork_exec);

    printf("pthread_create_thread\n");
    /* A new thread with pthread_create */
    pthread_create_thread();
    printf("pthread_create took %f seconds.\n", time_pthread_create);

    /* A new thread using kThread_create can be found in /kern/modules/kthread_mod.c */

    return 0;
}
