#ifndef MAIN_H_
#define MAIN_H_

#define MAX_ARGC 10

char** tokenization(char* buffer, int* count);

typedef struct command {
    char* name;
    int (*func)(char** argv);
} command_t;

#endif // MAIN_H_
