/**
 * Function prototyes and documentation for the threads.c file which
 * demonstrates different uses of threading in C.
 * @file threads.h
 * @author Chris Humphreys
 * @date 02/01/19
 * @brief Function prototypes for the threads.c file.
 */

#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include "threads.c"

/**
 * Prints info about threads, and calls threaded functions based on mode.
 *
 * This function first prints out information on the threads so as to ensure
 * everything is running properly.  Then based on the mode selected by the user
 * it sends the thread to the appropriate function.
 *
 * param arg a pointer to the thread being directed by the function.
 * return uni
 */
static void * run_thread(void* arg);

/**
 *  Creates and runs threads based on mode.
 *
 *  This function creates two different threads, and updates their struct values
 *  based on which mode the program is being run in.  It then sends them off to
 *  do their work.  Finally, it joins them all, and frees up all the memory and
 *  resources that were being used.
 *
 *  param mode_selector an integer corresponding to a homework question.
 *  return none
 */
void create_and_run_threads(int mode_selector);

/**
 * Reads the balance, increases it by 10, sleeps, and then updates the balance.
 * 
 * As directed in the homework, I initially set usleep to 1, and this caused all
 * sorts of race conditions, that stopped the program from running as it should.
 * When usleep is set to 1 the value does not always update properly.
 *
 * param tid a pointer to a thread id.
 * return none 
 */
void update_balance(void* tid);

/**
 * Adds 100 to bank account
 *
 * This function takes in a pointer to a thread, and directs that thread to
 * increase the total in the bank account by 100.  It is then to sleep until the
 * account is back down to 0.  At this point it repeats for a total of MAX
 * times.
 *
 * param ptr a pointer to a thread
 * return none
 */
void *producer(void *ptr);

/**
 * Subtracts 100 from bank account
 *
 * This function takes in a pointer to a thread, and directs that thread to
 * decrease the total in the bank account by 100.  It is then to sleep until the
 * account is back up to 100.  At this point it repeats for a total of MAX
 * times.
 *
 * param ptr a pointer to a thread
 * return none
 */
void *consumer(void *ptr);

#endif //THREADS_H
