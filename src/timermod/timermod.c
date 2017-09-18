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
 * @file timermod.c
 * @brief Timer module
 * 
 * This is a kernel module that uses a timer to wake up ever 500ms, printing a
 * count of how many times it has woken up already.
 *
 * @author Ben Heberlein
 * @date September 17 2017
 * @version 1.0
 *
 */

#include <linux/module.h>    
#include <linux/kernel.h>  
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ben Heberlein");
MODULE_DESCRIPTION("Timer counter kernel module");

/**
 * @brief Initialization function
 * 
 * This function prints an initialization message to the kernel log.
 *
 * @return A kernel error code from errno.h or errno-base.h
 */
static int __init timermod_init(void)
{
    printk(KERN_INFO "timermod: module successfully loaded\n");
    return 0;
}

/**
 * @brief Exit function
 * 
 * This function prints an exit message to the kernel log.
 *
 * @return void
 */
static void __exit timermod_cleanup(void)
{
    printk(KERN_INFO "timermod: module successfully removed.\n");
}

module_init(timermod_init);
module_exit(timermod_cleanup);
