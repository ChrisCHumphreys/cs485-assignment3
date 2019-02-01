/**
 * Library of functions for creating and demonstrating the use of threading in 
 * C.
 * 
 * @author Chris Humphreys 
 * @file threads.c
 * @date 02/01/19
 * @brief Library for interactive shell and batch file processor.
 */

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

const int NUMBER_OF_THREADS = 2;
int balance = 0;            /* Global balance variable */

struct thread_info {        /* Used as argument to thread_start */
  pthread_t thread_id;      /* ID returned by pthread_create() */
  int       thread_num;     /* From NUMBER_OF_THREADS */
  char      thread_name[6]; /* Arbitrary Name for testing */
};

/* Update Balance function: Reads the balance, increases it by 10, sleeps, and
   then reads balance again. TODO: add documentation about printing */

static void * updateBalance(void* arg) {
  struct thread_info *tinfo = arg;
  char *uname;

  //uname = strdup(tinfo->thread_name);
  
  printf("Thread number %d has been created.\n", tinfo->thread_num);
  printf("Thread Name: %s\n\n", tinfo->thread_name);
  usleep(1);

  return uname;
}

void create_and_run_threads() {
  int num_threads, s, tnum;
  pthread_attr_t attr;
  char * name[2];
  struct thread_info *tinfo;

  name[0] = "Bravo";
  name[1] = "Alpha";
  
  num_threads = NUMBER_OF_THREADS;

  /* Initialize thread creation attributes */
  s = pthread_attr_init(&attr);

  tinfo = calloc(num_threads, sizeof(struct thread_info));
  
  /* Create a number of threads equal to NUMBER_OF_THREADS */
  for (tnum = 0; tnum < num_threads; tnum++) {
    tinfo[tnum].thread_num = tnum + 1;
    strcpy(tinfo[tnum].thread_name, name[tnum]);

    /* The pthread_create() call stores the thread IDes into corresponding 
       element of tinfo[] */
    s = pthread_create(&tinfo[tnum].thread_id, &attr,
		       &updateBalance, &tinfo[tnum]);
  }

  /* Destroy the threaded attributes object, since it is no longer needed */
  s = pthread_attr_destroy(&attr);

  free(tinfo);

}
