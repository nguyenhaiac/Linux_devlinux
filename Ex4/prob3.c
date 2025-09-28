#include "pthread.h"
#include <bits/pthreadtypes.h>
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
#include "unistd.h"
#define MAX_LOOP 10

pthread_mutex_t lock;
static int random_num;
pthread_cond_t cond;

void* thread_handler(void *arg){
    printf("This is the thread_handler: \n");
    for(int i=0; i< MAX_LOOP; i++){
        sleep(1);
        pthread_mutex_lock(&lock);
        random_num = rand();
        printf("random_num: %d\n", random_num);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        
    }
    pthread_exit(NULL);
}

int main(){
    printf("this is the main thread\n");
    int ret_val;
    pthread_t tid;
    ret_val = pthread_create(&tid, NULL, thread_handler, NULL);
    if(ret_val){
        printf("error number %d: \n", ret_val);
    }
    pthread_mutex_lock(&lock);
    while(1){
        pthread_cond_wait(&cond, &lock);
        printf("this is the random number: %d\n", random_num);
    }
    pthread_mutex_unlock(&lock);
    pthread_join(tid, NULL);
}
