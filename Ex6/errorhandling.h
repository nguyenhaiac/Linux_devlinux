#ifndef ERRORHANDLING_H_
#define ERRORHANDLING_H_

#include "stdio.h"
#include "stdlib.h"
#define CHECK(cond, msg)                                                       \
  do {                                                                         \
    if (cond) {                                                                \
      perror(msg);                                                             \
      return -1;                                                               \
    }                                                                          \
  } while (0)

#define CHECK_DIE(cond, msg)                                                   \
  do {                                                                         \
    if (cond) {                                                                \
      perror(msg);                                                             \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

#endif // ERRORHANDLING_H_
