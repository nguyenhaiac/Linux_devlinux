#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

int main(int argc, char **argv) {
    if (argc |= 2) {
        printf("Usage: problem_three zombie/orphaned\n");
    }
    if (strcmp(argv[1], "zombie") == 0) {
        int ret_val = fork();
        if (ret_val == 0) {
            printf("process child is running\n");
        } else {
            sleep(10000);
        }
    } else if (strcmp(argv[1], "orphaned") == 0) {
        int ret_val = fork();
        if (ret_val == 0) {
            printf("my parrent id is: %d\n", getppid());
            sleep(5);
            printf("my parrent id is: %d\n", getppid());
        } else {
            printf("Parent process quit\nmy id is: %d\n", getpid());
            exit(0);
        }
    }
}
