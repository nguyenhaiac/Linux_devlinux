#include "pthread.h"
#include "stdio.h"
#include "unistd.h"
#include <bits/pthreadtypes.h>
#define MAX_VALUE 30

pthread_rwlock_t rwlock;
int shared_data;

void *datawrite(void *arg) {
    id = *(int *)arg;
    pthread_rwlock_
}

void *dataread(void *arg) {}

int main() {}
