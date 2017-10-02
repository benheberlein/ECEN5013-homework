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
 * @file thread_example.c
 * @brief Examples for Linux threads
 * 
 * This file contains some documentation and examples for Linux Pthreads.
 *
 * @author Ben Heberlein
 * @date October 1 2017
 * @version 1.0
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

/* Instance of pthread_mutex */
pthread_mutex_t example_mutex;

/* Instance of condition variable and associated mutex */
pthread_cond_t example_cond;
pthread_mutex_t example_cond_mutex;

/* Example return value */
int retval = 0xAA;

void *print_function(void *arg) {
    /* This function will print based on the example_cond variable. It is
       signaled when the main function has joined the two example threads 
       and verified the data count. It uses a condition variable and 
       associated mutex to signal. */

    /* The pthread_cond_wait function waits on a signal from another thread
       through a condition variable. In this case, this thread will be
       signaled by the main thread when we have collected all data. */
    pthread_mutex_lock(&example_cond_mutex);
    pthread_cond_wait(&example_cond, &example_cond_mutex);
    printf("Recieved all data. Count is %d.\n", *((int*)arg));
    pthread_mutex_unlock(&example_cond_mutex);

    /* Exit thread, passing return code to join. */
    pthread_exit(&retval);
}

void *example_function(void *arg) {
    /* We will add 500 and exit early. */

    printf("Starting example function.\n");

    /* The function pthread_self returns the ID of the calling thread. This
       function does not return an error because it always succeeds. This 
       will match the valud of example_thread returned from pthread_create 
       in the main function. */
    printf("Example thread has ID %lu.\n", pthread_self());

    int *temp = (int *) arg;

    for (int i = 0; i < 1000; i++) {
        /* This locks the condition mutex for signaling counts of 100. */

        if (i >= 500) {
   
            /* The call to pthread_exit terminates the thread early and passes 
               a return value to pthread_join by reference. */
            pthread_exit(&retval);
        }
  
        /* This demonstrates locking and unlocking shared data with a mutex. 
           The mutex was initialized in the main function. The call to 
           pthread_mutex_lock blocks until the lock is obtained. This could
           potentially lead to deadlock if not used correctly. If the needed
           behaivior should try once and give up, the pthread_mutex_trylock 
           function should be used instead of pthread_mutex_lock. The trylock
           function will not block, and will continue execution with a success
           or error code return value. */
        pthread_mutex_lock(&example_mutex);
        (*temp)++;
        pthread_mutex_unlock(&example_mutex);

   }

    printf("Finished example function.\n");

    return NULL;
}

int main(void) {
    int ret = 0;
    int joinret = 0;
    int *joinptr = 0;
    joinptr = &joinret;
    int arg = 0;
    int policy = 0;

    /* This creates a thread instance */
    pthread_t example_thread_1;
    pthread_t example_thread_2;
    pthread_t print_thread;

    /* This creates an attributes variable */
    pthread_attr_t example_attr;

    /* Before creating any threads, we should initialize the mutex used in the
       example function. We do this with the pthread_mutex_init function. The
       second parameter is attributes, which we initialize to default. */
    ret = pthread_mutex_init(&example_mutex, NULL);
    if (ret) {
        printf("The call to pthread_mutex_init failed.\n");
    }

    /* Also initialize condition variable and associated mutex for print
       function demonstration. */
    ret = pthread_mutex_init(&example_cond_mutex, NULL);
    if (ret) {
        printf("The call to pthread_mutex_init failed.\n");
    }
    ret = pthread_cond_init(&example_cond, NULL);
    if (ret) {
        printf("The call to pthread_cond_init failed.\n");
    }

    /* The pthread_create function starts a new thread from the current process
       running the supplied function (in this case, example_function). The
       new thread will terminate when the function returns. */
    ret = pthread_create(&example_thread_1, NULL, example_function, &arg);
    if (ret) {
        printf("The call to pthread_create failed.\n");
    }

    /* The pthread_attr_init function sets the attribute structure to have 
       default attributes. We can pass in attributes to pthread_create in the 
       second parameter if we want to change any. */
    ret = pthread_attr_init(&example_attr);
    if (ret) {
        printf("The call to pthread_attr_init failed.\n");
    }

    /* This shows how we can pass in modified attributes to pthread_create.
       Note that this call to pthread_create shares data with the first call
       to pthread_create. We ensure data integrity with a mutex in the example
       funcion. In this case we are modifying the scheduling policy. */
    ret = pthread_attr_setschedpolicy(&example_attr, SCHED_OTHER);
    if (ret) {
        printf("Could not set scheduling policy.\n");
    }
    ret = pthread_attr_getschedpolicy(&example_attr, &policy);
    if (ret) {
        printf("Could not get scheduling policy.\n");
    }
    ret = pthread_create(&example_thread_2, &example_attr, example_function, &arg);
    if (ret) {
        printf("Call to pthread_create failed.\n");
    }

    /* This thread demonstrates signaling through condition variables. The
       thread will print every time the example_functions increment the shared
       data 100 times. */
    ret = pthread_create(&print_thread, NULL, print_function, &arg);
    if (ret) {
        printf("The call to pthread_create failed.\n");
    }

    /* The pthead_join function will wait until a thread terminates and then
       will resume execution in the current process. */
    ret = pthread_join(example_thread_1, (void**) &joinptr);
    if (ret) {
        printf("The call to pthread_join failed.\n");
    }    
    printf("Main thread was joined with first thread. Example thread returned with exit code %d.\n", *joinptr);
 
    /* The pthead_join function for the second thread. */
    ret = pthread_join(example_thread_2, (void**) &joinptr);
    if (ret) {
        printf("The call to pthread_join failed.\n");
    }    
    printf("Main thread was joined with second thread. Example thread returned with exit code %d.\n", *joinptr);

    /* Signal to the print function that we have collected all the data */
    if (arg == 1000) {
       pthread_mutex_lock(&example_cond_mutex);
       pthread_cond_signal(&example_cond);
       pthread_mutex_unlock(&example_cond_mutex);    
    }

    /* The pthread_join function for the print thread. */
    ret = pthread_join(print_thread, (void **) &joinptr);
    if (ret) {
        printf("The call to pthread_join failed.\n");
    }    
    printf("Main thread was joined with print thread. Print thread returned with exit code %d.\n", *joinptr);

    /* When we are done using the lock, we will want to destroy it with
       pthread_destroy. */
    ret = pthread_mutex_destroy(&example_mutex);
    if (ret) {
        printf("Could not destroy mutex.\n");
    }

    /* Also destroy condition variable and associated mutex when done. */
    ret = pthread_mutex_destroy(&example_cond_mutex);
    if (ret) {
        printf("Could not destroy mutex.\n");
    }
    ret = pthread_cond_destroy(&example_cond);
    if (ret) {
        printf("Could not destroy condition.\n");
    }

    return 0;
}
