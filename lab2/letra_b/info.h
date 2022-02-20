#ifndef _LAB2_SOCKETS
#define _LAB2_SOCKETS

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define QLEN 12

typedef struct {
    int vetor_len;
    float *vetor_val;
} vetor;

#endif
