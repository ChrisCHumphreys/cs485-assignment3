/**
 * Function definitions and logic for assignment 3 in CS485.  This library of
 * functions allows the user to utilize two threads and see how they con work
 * together and against each other.
 *
 * @author Chris Humphreys
 * @file threads.c
 * @date 02/01/19
 * @brief Demonstration of multi-threading for CS485.
 */

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define MAX 10 /**< integer representing the number of times deposits and
                  withdrawls should be made. */

pthread_mutex_t the_mutex, bal_mutex; 
pthread_cond_t condc, condp;
int bank_account = 0; /**< bank account balance */

const int NUMBER_OF_THREADS = 2; /**< The number of threads */
int balance = 0;            /**< Global balance variable */

/** @struct thread_info
 *  @brief Defines the threads we are using.
 */
struct thread_info {         /**< Used as argument to thread_start */
  pthread_t thread_id;       /**< ID returned by pthread_create() */
  int       thread_num;      /**< From NUMBER_OF_THREADS */
  char      thread_name[32]; /**< Arbitrary Name for testing */
  int       mode;            /**< 1 for question 1,  2 for question 2 */
};

void *producer(void *tid) {
  struct thread_info *tinfo = tid; /**< a thread pointer */

  for (int i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);
    while(bank_account != 0) pthread_cond_wait(&condp, &the_mutex);
    bank_account = 100;
    printf("%s did it's thing\nCurrent account balance: %d\n\n",
           tinfo->thread_name, bank_account);
    pthread_cond_signal(&condc);
    pthread_mutex_unlock(&the_mutex);
  }
  pthread_exit(0);
}

void *consumer(void *tid) {
  struct thread_info *tinfo = tid;
  int i;

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);
    while(bank_account == 0) pthread_cond_wait(&condc, &the_mutex);
    bank_account = 0;
    printf("%s did it's thing\nCurrent account balance: %d\n\n",
           tinfo->thread_name, bank_account);
    pthread_cond_signal(&condp);
    pthread_mutex_unlock(&the_mutex);
  }
  pthread_exit(0);
}

void update_balance(void* tid) {
  struct thread_info *tinfo = tid;
  printf("%s Team Go!\n", tinfo->thread_name);

  pthread_mutex_lock(&bal_mutex);  // Mutex locks out other threads while in 
                                   // critical region
  int read_balance = balance;
  read_balance += 10;

  usleep(1);

  balance = read_balance;

  pthread_mutex_unlock(&bal_mutex); // Unlocks after out of critical region

  printf("%s Team Balance after update is: %d\n\n",
	tinfo->thread_name, balance);
}

static void * run_thread(void* arg) {
  struct thread_info *tinfo = arg;
  char *uname;  /* Have to return a value for create_thread to work */

  printf("Thread number %d has been created.\n", tinfo->thread_num);
  printf("Thread Name: %s\n", tinfo->thread_name);
  printf("Thread ID: %lu\n\n", tinfo->thread_id);

  if (tinfo->mode == 1) {
    update_balance(tinfo);
  } else {
    printf("thread name: %s\n\n", tinfo->thread_name);
    if (strncmp(tinfo->thread_name, "Deposit Thread", 14) == 0) {
      producer(tinfo);
    } else {
      consumer(tinfo);
    }
  }

  return uname;
}

void create_and_run_threads(int mode_selector) {
  int num_threads, tnum;
  pthread_attr_t attr;
  char * name[NUMBER_OF_THREADS];
  struct thread_info *tinfo;
  void *res;

  /* Must supply a number of names equal to NUMBER_OF_THREADS */

  if (mode_selector == 1) {
    name[0] = "Alpha";
    name[1] = "Bravo";
  } else {
    name[0] = "Deposit Thread";
    name[1] = "Withdraw Thread";
  }

  num_threads = NUMBER_OF_THREADS;

  /* Initialize thread creation attributes */
  pthread_attr_init(&attr);

  tinfo = malloc(num_threads * (sizeof(struct thread_info)));

  /* Create a number of threads equal to NUMBER_OF_THREADS */
  for (tnum = 0; tnum < num_threads; tnum++) {
    tinfo[tnum].mode = mode_selector;
    tinfo[tnum].thread_num = tnum + 1;
    strcpy(tinfo[tnum].thread_name, name[tnum]);

    /* The pthread_create() call stores the thread IDes into corresponding
       element of tinfo[] */
    pthread_create(&tinfo[tnum].thread_id, &attr,
		       &run_thread, &tinfo[tnum]);
  }

  /* Destroy the threaded attributes object, since it is no longer needed */
  pthread_attr_destroy(&attr);
  

  /* Joining threads to ensure memory is freed properly */
  for (tnum = 0; tnum < num_threads; tnum++) {
    pthread_join(tinfo[tnum].thread_id, &res);

    free(res);
  }
  free(tinfo);
}
