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

static void * run_thread();
void create_and_run_threads();
void update_balance(void* tid);

#endif //THREADS_H
