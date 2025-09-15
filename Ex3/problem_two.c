#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/wait.h"
#include "unistd.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [args...]\n", argv[0]);
        return 1;
    }
    char command[20] = "";
    char **argv_child;
    argv_child = argv + 1;
    setenv("MY_PROGRAM", argv[1], 1);
    pid_t pid = fork();

    if (pid == 0) {
        char *my_program = getenv("MY_PROGRAM");
        execvp(my_program, argv_child);
    } else {
        wait(NULL);
        printf("child finished");
    }
    return 0;
}
