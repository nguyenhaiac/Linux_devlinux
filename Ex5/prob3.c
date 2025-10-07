#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "sys/wait.h"
#include "unistd.h"

static pid_t pid;
static int tick = 0;
void timer_handler(int sig) { tick = 1; }

void sigusr_handler(int sig) {
  static int count = 0;
  count++;
  if (count == 10) {
    printf("Received signal from parent, count: %d\n. Child Shutdown....",
           count);
    exit(0);
  }
  printf("Received signal from parent, count: %d\n", count);
}

int main() {
  pid = fork();
  if (pid == -1) {
    printf("error fork");
    return 1;
  }
  if (pid == 0) {
    signal(SIGUSR1, sigusr_handler);
    while (1) {
    }
  } else {
    int status = 0;
    signal(SIGALRM, timer_handler);
    struct itimerval timer = {.it_value.tv_sec = 1,
                              .it_value.tv_usec = 0,
                              .it_interval.tv_sec = 1,
                              .it_interval.tv_usec = 0};
    setitimer(ITIMER_REAL, &timer, NULL);
    while (1) {
      pause();
      if (tick) {
        tick = 0;
        kill(pid, SIGUSR1);
      }
      pid_t child = waitpid(pid,&status, WNOHANG);
      if(child == pid){
          printf("child is terminated\n");
          break;
      }
    }
    printf("Parent shutdown\n");
  }
}
