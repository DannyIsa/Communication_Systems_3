#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/time.h>
#include <sys/socket.h>

#define MS_PER_SEC 1000
#define RENO_TCP "reno"
#define CUBIC_TCP "cubic"
#define IP_ADD
#define MAX_LEN 100
#define BUFFER 1024
#define TRUE 1
#define FALSE 0

int get_params_rec(int argc, char *argv[], int *port, char *algo);