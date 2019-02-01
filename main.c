/**
 * @file main.c
 * @author Chris Humphreys
 * @date 01 Feb 2019
 * @brief Main Driver for C Threads Program
 *
 * Main driver for the threading assignment for CS485, which simply demonstrates
 * the usage of proper threading in C. 
 *
 */

#include <stdio.h>
#include "threads.h"

int main () {
  printf("Hello World");
  hello();
  return 0;
};
