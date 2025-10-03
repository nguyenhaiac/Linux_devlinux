#include "stdio.h"
#include "signal.h"
#include "unistd.h"
#include "stdlib.h"

void handler(int sig){
    static int i = 0;
    i++;
    if(i == 3){
        printf("This is thread handler of sig: %d, Count %d \n", sig, i);
        exit(1);
    }
    printf("This is thread handler of sig: %d, Count %d \n", sig, i);
}

int main(){
    signal(SIGINT, handler);
    while(1){
        printf("running.....\n");
        sleep(1);
    }
}

