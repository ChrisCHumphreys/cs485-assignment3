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
#include <unistd.h>
#include "threads.h"

int main (int argc, char * argv[]) {
  int flags, opt;
  int times_to_run;

  if (argc != 2) {
    fprintf(stderr, "Error: Usage - Expected single option after %s\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  while ((opt = getopt(argc, argv, ":12")) != -1) {
    switch(opt) {
    case '1':
      flags = 1;
      break;
    case '2':
      flags = 2;
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-1 or -2]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  
  int mode_selector = flags;
  create_and_run_threads(mode_selector);
  exit(EXIT_SUCCESS);
};
