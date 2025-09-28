#include "pthread.h"
#include <bits/pthreadtypes.h>
#include <stdio.h>

pthread_mutex_t my_mutex;
static int shared = 0;

void *thr_handler(void *arg) {
    while (shared < 1000) {
        shared++;
        printf("calculated by %s and shared data is: %d\n", (char *)arg,
               shared);
    }
    printf("calculated by %s and shared data is: %d\n", (char *)arg, shared);
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thr_handler, (void *)"THREAD 1");
    pthread_create(&tid2, NULL, thr_handler, (void *)"THREAD 2");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}
