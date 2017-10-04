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
 * @file procmod.c
 * @brief Kernel module to list all kernel threads
 * 
 * This is a kernel module that uses the internal linked structure of Linux
 * processes to list all kernel threads.
 *
 * @author Ben Heberlein
 * @date October 3 2017
 * @version 1.0
 *
 */

#include <linux/module.h>    
#include <linux/kernel.h>  
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/sched/signal.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ben Heberlein");
MODULE_DESCRIPTION("Lists kernel threads with detailed information");

/**
 * @brief Dummy function to create a kthread
 * 
 * We create a dummy kthread in order to be able to access kthreadd (parent
 * of all kthreads. From there we can traverse down and print info about all
 * currently running kthreads without seeing any user thread information.
 *
 * @return Nothing, returns 0
 */ 
static int __dummy(void *data) {
    return 0;
}

/**
 * @brief Recursively goes through all children and prints task info
 * 
 * @return Void
 */ 
static void __recursive_search(struct task_struct *t) {
    if (&t->children == NULL) {
        printk(KERN_INFO "procmod: %s\t[%d]\t%ld\t%d\n", t->comm, t->pid, t->state, 0);
    } else {
        struct list_head *list;
        struct task_struct *task;
        int numch = 0;
        list_for_each(list, &t->children) {
            task = list_entry(list, struct task_struct, sibling);
            __recursive_search(task);
            numch++;
        } 
        printk(KERN_INFO "procmod: %s\t[%d]\t%ld\t%d\n", t->comm, t->pid, t->state, numch);     
    }
}

/**
 * @brief Initialization function
 * 
 * This function prints information about all kernel threads to the kernel log.
 *
 * @return A kernel error code from errno.h or errno-base.h
 */
static int __init procmod_init(void) {

    struct task_struct *task;
    struct task_struct *thread;
    //task = current;
    thread = kthread_run(__dummy, NULL, "kthread_dummy");
    task = thread;

    printk(KERN_INFO "procmod: name\t[PID]\tSTATUS\tCHILDREN\n");

    /* move to kthreadd */
    while(task->parent->pid != 0) {
        task = task->parent;
    }

    __recursive_search(task);

    kthread_stop(thread);

    printk(KERN_INFO "procmod: module successfully loaded and initialized.\n");
    return 0;
}

/**
 * @brief Exit function
 * 
 * This function prints an exit message to the kernel log.
 *
 * @return void
 */
static void __exit procmod_cleanup(void) {
    printk(KERN_INFO "procmod: module successfully removed.\n");
}

module_init(procmod_init);
module_exit(procmod_cleanup);
