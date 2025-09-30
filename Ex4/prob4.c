#include "pthread.h"
#include "stdio.h"
#include "unistd.h"
#include <bits/pthreadtypes.h>
#define MAX_VALUE 30

#define NUM_ITER 20
#define NUM_READER 5
#define NUM_WRITER 2

pthread_rwlock_t rwlock;
int shared_data;

void *datawrite(void *arg) {
  int id = *(int *)arg;
  for (int i = 0; i < NUM_ITER; i++) {
    pthread_rwlock_wrlock(&rwlock);
    shared_data++;
    printf("[Writer %d is writing: %d]\n", id, shared_data);
    pthread_rwlock_unlock(&rwlock);
    usleep(100000);
  }
  pthread_exit(NULL);
}

void *dataread(void *arg) {
  int id = *(int *)arg;
  for (int i = 0; i < NUM_ITER; i++) {
    pthread_rwlock_rdlock(&rwlock);
    printf("Reader [%d] start reading\n", id);
    usleep(250000);
    printf("[Reader %d is stoped reading: %d]\n", id, shared_data);
    pthread_rwlock_unlock(&rwlock);
  }
  pthread_exit(NULL);
}

int main() {

  pthread_t readers[NUM_READER];
  pthread_t writers[NUM_WRITER];
  int w_id[NUM_WRITER], r_id[NUM_READER];
  pthread_rwlock_init(&rwlock, NULL);

  for (int i = 0; i < NUM_WRITER; i++) {
    w_id[i] = i;
    if (pthread_create(&writers[i], NULL, datawrite, (void *)&w_id[i]) != 0) {
      perror("thread create writer");
    };
  }

  for (int i = 0; i < NUM_READER; i++) {
    r_id[i] = i;
    if (pthread_create(&readers[i], NULL, dataread, (void *)&r_id[i]) != 0) {
      perror("thread create reader");
    };
  }
  
  for (int i = 0; i < NUM_WRITER; i++) {
    pthread_join(writers[i], NULL);
  }

  for (int i = 0; i < NUM_READER; i++) {
    pthread_join(readers[i], NULL);
  }

  
  
  pthread_rwlock_destroy(&rwlock);
}
