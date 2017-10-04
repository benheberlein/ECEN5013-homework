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
 * @file mtfile.c
 * @brief Examples for of multithreaded file IO
 * 
 * This file contains an example of multithreaded file IO. There are three
 * threads. The main thread gets a name from the command line, opens a the
 * associated file, and then opens the other two threads. It also handles 
 * graceful termination of the program. The second thread will read the file, 
 * wait on a USR1 signal, and then take statistics. The third thread will wait 
 * on the USR2 signal, and then pring statisics.
 *
 * @author Ben Heberlein
 * @date October 3 2017
 * @version 1.0
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_LINESIZE 128
#define MAX_LINES 32

static int word_count = 0;
static int char_count = 0;
static int line_count = 0;

static FILE *file;

pthread_t stat_thread;
pthread_t print_thread;

pthread_mutex_t stat_lock;
pthread_mutex_t print_lock;
pthread_mutex_t data_lock;

char buf[MAX_LINES][MAX_LINESIZE];

void __main_handler(int sig) {

    if (sig == SIGUSR1) {
        /* Mutex allows status thread to continue */
        pthread_mutex_unlock(&stat_lock);
        printf("Recieved SIGUSR1 signal.\n");
    } else if (sig == SIGUSR2) {
        /* Mutex allows print thread to continue */
        pthread_mutex_unlock(&print_lock);
        printf("Recieved SIGUSR2 signal.\n");
    } else {
        /* Terminate nicely */
        printf("Recieved SIGINT signal. Exiting gracefully.\n");
        pthread_cancel(stat_thread);
        pthread_cancel(print_thread);
        fclose(file);
        exit(1);
    }
}

void *__print_func(void *data) {
    printf("Creating print thread.\n");

    int temp_l = 0;
    int temp_w = 1;
    int temp_c = 2;

    while (1) {
        /* Wait on SIGUSR2 */
        pthread_mutex_lock(&print_lock);

        /* Print statistics */
        pthread_mutex_lock(&data_lock);
        temp_l = line_count;
        temp_w = word_count;
        temp_c = char_count;
        pthread_mutex_unlock(&data_lock);

        printf("Statistics for file:\n");
        printf("Chars:\t%d\n", temp_c);
        printf("Words:\t%d\n", temp_w);
        printf("Lines:\t%d\n", temp_l);
    }

    return NULL;
}

void * __stat_func(void *data) {
    printf("Creating statistics thread.\n");

    int temp_c = 0;
    int temp_w = 0;
    int temp_l = 0;
    char ch = 0;

    while (1) {
        /* Wait on SIGUSR2 */
        pthread_mutex_lock(&stat_lock);
        printf("Calculating statistics...\n");

        /* Take statistics on file, code modified from example from
           http://www.opentechguides.com/how-to/article/c/72/c-file-counts.html */
        if (file) {
            temp_c = 0;
            temp_w = 0;
            temp_l = 0;

            for(int i = 0; i < MAX_LINES; i++) {
                for (int j = 0; j < MAX_LINESIZE; j++) {

                    ch = buf[i][j];
        
                    /* Skip null terminators from user input */
                    if (ch == '\0') {
                        continue;
                    }

                    /* write to file */
                    fputc(ch, file);

                    /* Count characters */
                    temp_c++;

                    /* Count words */
                    if (ch == ' ' || ch == '\n') {
                        temp_w++;
                    }

                    /* Count lines */
                    if (ch == '\n') {
                        temp_l++;
                    }
                }
            }
        }

        /* Save to shared data */
        pthread_mutex_lock(&data_lock);
        word_count = temp_w;
        line_count = temp_l;
        char_count = temp_c;    
        pthread_mutex_unlock(&data_lock);

    }

    return NULL;
}

int main(int argc, void *argv[]) {
    int ret = 0;
    int arg = 0;

    /* Check argument */
    if (argc != 2) {
        printf("Program needs a file name as an argument.\n");
        exit(-1);
    }

    /* Open file */
    file = fopen(argv[1], "w+");
    if (file == NULL) {
        printf("Invalid file.\n");
        exit(-2);
    }

    /* Create progress mutexes */
    ret = pthread_mutex_init(&stat_lock, NULL);
    if (ret) {
        printf("The call to pthread_mutex_init failed.\n");
        exit(-7);
    }
    ret = pthread_mutex_init(&print_lock, NULL);
    if (ret) {
        printf("The call to pthread_mutex_init failed.\n");
        exit(-7);
    }

    /* Initially locked so that threads don't progress */
    pthread_mutex_lock(&stat_lock);
    pthread_mutex_lock(&print_lock);
    
    /* Create shared data mutex */
    ret = pthread_mutex_init(&data_lock, NULL);
    if (ret) {
        printf("The call to pthread_mutex_init failed.\n");
        exit(-7);
    }

    /* Create statistics thread */
    ret = pthread_create(&stat_thread, NULL, __stat_func, &arg);
    if (ret) {
        printf("The call to pthread_create failed.\n");
        exit(-3);
    }

    /* Create print thread */
    ret = pthread_create(&print_thread, NULL, __print_func, &arg);
    if (ret) {
        printf("The call to pthread_create failed.\n");
        exit(-4);
    }
    
    /* Set up signal handler */
    if (signal(SIGINT, __main_handler) == SIG_ERR) {
        printf("Could not register SIGINT handler.\n");
        exit(-5);
    }
    if (signal(SIGUSR1, __main_handler) == SIG_ERR) {
        printf("Could not register SIGUSR1 handler.\n");
        exit(-5);
    }
    if (signal(SIGUSR2, __main_handler) == SIG_ERR) {
        printf("Could not register SIGUSR2 handler.\n");
        exit(-5);
    }

    /* Get user signals */
    int num = 0;
    for (int i = 0; i < MAX_LINES; i++) {
        fgets(buf[i], MAX_LINESIZE, stdin);
    }

    ret = pthread_join(stat_thread, NULL);
    if (ret) {
        printf("The call to pthread_join failed.\n");
    }    

    ret = pthread_join(print_thread, NULL);
    if (ret) {
        printf("The call to pthread_join failed.\n");
    }    

    return 0;
}
