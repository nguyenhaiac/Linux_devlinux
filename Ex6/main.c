#include "main.h"
#include "pthread.h"
#include "string.h"
#include "sys/socket.h"
#include "thread_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

command_t commands[] = {{"connect", connect2peer}, {"help", printhelp}};

int main() {
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int *fd_arg = malloc(sizeof(server_fd));
    *fd_arg = server_fd;
    pthread_t server_tid;
    pthread_create(&server_tid, NULL, open_server, fd_arg);
    pthread_detach(server_tid);
    char buffer[1024];
    while (1) {
        int n = read(STDERR_FILENO, buffer, sizeof(buffer) - 1);
        printf("%d\n", n);
        if (n > 1) {
            buffer[n] = '\0';
            buffer[strcspn(buffer, "\r\n")] = '\0';
            int count = 0;
            char **argv = tokenization(buffer, &count);
            for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
                if(strcmp(commands[i].name, argv[0]) == 0){
                    commands[i].func(argv);
                }
            }
        }
    }
}

char **tokenization(char *buffer, int *count) {
    char **argv = malloc(sizeof(char *) * MAX_ARGC);
    char *token = strtok(buffer, " ");
    int internal_count = 0;
    while (token != NULL && internal_count < MAX_ARGC) {
        argv[internal_count] = token;
        token = strtok(NULL, " ");
        internal_count++;
    }
    *count = internal_count;
    return argv;
}
