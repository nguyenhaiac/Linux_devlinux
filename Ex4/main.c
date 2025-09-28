#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"

void *thr_handler(void *arg) {
    int *result = malloc(sizeof(int));
    *result = 20 + *(int *)arg;
    return result;
}

int main() {
    pthread_t tid1;
    pthread_t tid2;
    int arg1 = 15;
    int arg2 = 20;
    pthread_create(&tid1, NULL, thr_handler, (void *)&arg1);
    pthread_create(&tid2, NULL, thr_handler, (void *)&arg2);
    void *retval1;
    void *retval2;
    pthread_join(tid1, &retval1);
    pthread_join(tid2, &retval2);
    int *res1 = (int *)retval1;
    int *res2 = (int *)retval2;
    printf("result of first thread %d\n", *res1);
    printf("result of first thread %d\n", *res2);
}
