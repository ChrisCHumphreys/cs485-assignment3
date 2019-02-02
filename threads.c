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
#include <errno.h>


const int NUMBER_OF_THREADS = 2;
int balance = 0;            /* Global balance variable */

struct thread_info {        /* Used as argument to thread_start */
  pthread_t thread_id;      /* ID returned by pthread_create() */
  int       thread_num;     /* From NUMBER_OF_THREADS */
  char      thread_name[32]; /* Arbitrary Name for testing */
};

/* Update Balance function: Reads the balance, increases it by 10, sleeps, and
   then updates the balance.  When usleep is set to 1 the value does not always
   update properly. */

void update_balance(void* tid) {
  struct thread_info *tinfo = tid;
  printf("%s Team Go!\n", tinfo->thread_name);

  int read_balance = balance;
  read_balance += 10;

  /* If usleep is set to 1, results are inconsistent because of a race 
     condition */
  
  /* usleep(); */
  
  balance = read_balance;

  printf("%s Team Balance after update is: %d\n\n",
	 tinfo->thread_name, balance);
}

static void * run_thread(void* arg) {
  struct thread_info *tinfo = arg;
  char *uname;  /* Have to return a value for create_thread to work */

  printf("Thread number %d has been created.\n", tinfo->thread_num);
  printf("Thread Name: %s\n", tinfo->thread_name);
  printf("Thread ID: %lu\n\n", tinfo->thread_id);

  update_balance(tinfo);

  return uname;
}

void create_and_run_threads() {
  int num_threads, tnum;
  pthread_attr_t attr;
  char * name[NUMBER_OF_THREADS];
  struct thread_info *tinfo;
  void *res;

  /* Must supply a number of names equal to NUMBER_OF_THREADS */
  
  name[0] = "Alpha";
  name[1] = "Bravo";
  
  num_threads = NUMBER_OF_THREADS;

  /* Initialize thread creation attributes */
  pthread_attr_init(&attr);

  tinfo = malloc(num_threads * (sizeof(struct thread_info)));
  
  /* Create a number of threads equal to NUMBER_OF_THREADS */
  for (tnum = 0; tnum < num_threads; tnum++) {
    tinfo[tnum].thread_num = tnum + 1;
    strcpy(tinfo[tnum].thread_name, name[tnum]);

    /* The pthread_create() call stores the thread IDes into corresponding 
       element of tinfo[] */
    pthread_create(&tinfo[tnum].thread_id, &attr,
		       &run_thread, &tinfo[tnum]);
  }

  /* Destroy the threaded attributes object, since it is no longer needed */
  pthread_attr_destroy(&attr);

  /* Joing threads to ensure memory is freed properly */
  for (tnum = 0; tnum < num_threads; tnum++) {
    pthread_join(tinfo[tnum].thread_id, &res);

    free(res);
  }

  free(tinfo);
}
