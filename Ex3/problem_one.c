#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pid;
    int a = 10;
    printf("Initial value of a: %d\n", a);

    pid = fork();
    if (pid == 0) {
        pid_t self_pid = getpid();
        printf("child process running: child is a copy of parent, the pid of "
               "child process: %d\n",
               self_pid);
        exit(5);
    } else {
        int status;
        int child_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("child process %d exitted with code %d\n", child_pid,
                   WEXITSTATUS(status));
        }
    }
}
