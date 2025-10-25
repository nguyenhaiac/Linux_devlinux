#ifndef THREAD_HELPER_H_
#define THREAD_HELPER_H_

void* open_server(void* arg);
void *listen2peer(void *arg);
void *communicate(void *arg);

int connect2peer(char** argv);
int printhelp(char** argv);


#endif // THREAD_HELPER_H_
