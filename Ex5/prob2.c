#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"

void handler(int sig){
    static int count;
    count++;
    if (count == 10){
        printf("Tick!!! count %d, Shutdown.....\n", count);
        exit(1);
    }
    printf("Tick!!! count %d\n", count);
}


int main(){
    signal(SIGALRM, handler);
    struct itimerval timer;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL,&timer, NULL);
    while(1){
        
    }

}
