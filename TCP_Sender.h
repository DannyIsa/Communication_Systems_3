#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h>
#include <netinet/tcp.h>

#define MAX_LEN 100
#define RENO_TCP "reno"
#define CUBIC_TCP "cubic"
#define BUFFER 1024
#define FILE_SIZE 2000000 // size of file divided by size of int
#define FILE_SIZE_LENGTH 7
#define TRUE 1
#define FALSE 0

char *util_generate_random_data(unsigned int size);
int get_params(int argc, char *argv[], int *port, char *ip, char *algo);
char *stringify(int size);
