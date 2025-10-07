#include "stdio.h"
#include "sys/select.h"
#include <bits/types/struct_timeval.h>
#include <signal.h>
#include <unistd.h>


void sigin_handler(int sig){
    printf("Sigint received\n");
}


int main(){
    fd_set readfds;
    char buffer[128];
    
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO,&readfds);
    int retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timer);
    if(retval == -1){
        perror("select()\n");
    } else if(retval){
        int n = read(STDERR_FILENO, buffer, sizeof(buffer) - 1);
        if( n > 0 ){
            buffer[n] = '\0';
            printf("%s\n",buffer);
        } else if (n == 0 ){
            printf("EOF \n");
        } else {
            perror("read()\n");
        }
    }

    
}
