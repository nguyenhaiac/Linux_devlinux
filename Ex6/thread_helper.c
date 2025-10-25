#include "thread_helper.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "stdio.h"
#include "stdlib.h"
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "errorhandling.h"

void *open_server(void *arg) {
  int server_fd = *(int*)arg;
  printf("open %d\n", server_fd);
  CHECK_DIE(server_fd < 0, "socket error");
  struct sockaddr_in address;

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = 0;
  socklen_t socketlen = sizeof(address);
  if(bind(server_fd,(struct sockaddr*)&address,socketlen) < 0){
      perror("bind");
      close(server_fd);
      free(arg);
      exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

  if(getsockname(server_fd, (struct sockaddr*)&address, &socketlen) < 0){
      perror("getsockname");
      close(server_fd);
      free(arg);
      exit(EXIT_FAILURE);
  }
  printf("Waiting for connection at: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
  fflush(stdout);
  while(1){
      int client_fd;
      struct sockaddr_in client_address;
      client_fd = accept(server_fd, (struct sockaddr*)&client_address, &socketlen);
      if(client_fd < 0) continue;
      int* fd_ptr = malloc(sizeof(int));
      *fd_ptr = client_fd;
      pthread_t client_tid;
      pthread_create(&client_tid, NULL, listen2peer, fd_ptr);
      pthread_detach(client_tid);
  }
  return NULL;
}

void *listen2peer(void *arg){
    printf("client connected: %d\n", *(int*)arg);
    return NULL;
}


int printhelp(char** argv){
    printf("This is help: %s\n",argv[1]);
    return 0;
}

int connect2peer(char** argv){
    int peer_fd;
    int sock = 0;
    if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket");
        return -1;
    }
    struct sockaddr_in address;
    address.sin_port = htons(strtol(argv[2], NULL, 10));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &address.sin_addr);
    printf("%s\n", argv[1]);
    printf("%ld\n",strtol(argv[2], NULL, 10));
    if(connect(sock,(struct sockaddr*)&address, sizeof(address)) < 0){
        perror("connect");
    }
    return 0;
}
