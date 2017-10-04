/******************************************************************************
* Copyright (C) 2017 by Ben Heberlein
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. This file
* was created for the University of Colorado Boulder course Advanced Practical
* Embedded Software Development. Ben Heberlein and the University of Colorado 
* are not liable for any misuse of this material. This file is released under
* the GNU General Public License.
*
*******************************************************************************/
/**
 * @file kthread_mod.c
 * @brief Kthread profile module
 * 
 * This is a kernel module that can be used to benchmark the kthread_create
 * function to compare to other thread functions.
 *
 * @author Ben Heberlein
 * @date October 2 2017
 * @version 1.0
 *
 */

#include <linux/module.h>    
#include <linux/kernel.h>  
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/kmod.h>
#include <linux/time.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ben Heberlein");
MODULE_DESCRIPTION("Kthread profile module");

static struct task_struct *thread;

static int thread_function(void *data) {
    char * envp[] = { "HOME=/", NULL };
    char * argv[] = { "/bin/ls", "-al", NULL };

    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
    return 0;
}

static int __init kthread_mod_init(void) {

    struct timespec start;
    struct timespec end;
    getnstimeofday(&start);

    thread = kthread_run(thread_function, NULL, "thread_profile");

    getnstimeofday(&end);

    printk(KERN_INFO "kthread_mod: took %ld nanoseconds to create thread.\n", (end.tv_nsec-start.tv_nsec));

    return 0;
}

static void __exit kthread_mod_cleanup(void) {
//    int ret = kthread_stop(thread);
    printk(KERN_INFO "kthread_mod: module successfully removed.\n");
}

module_init(kthread_mod_init);
module_exit(kthread_mod_cleanup);
