#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define RENO_TCP "reno"
#define CUBIC_TCP "cubic"
#define BUFFER 1024
#define FILE_SIZE 2000000
#define TRUE 1
#define FALSE 0

char *util_generate_random_data(unsigned int size);
int get_params(int argc, char *argv[], int *port, char *ip, char *algo);
int sendSock(int length, char *info, int socket);