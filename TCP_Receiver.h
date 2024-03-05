#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define RENO_TCP "reno"
#define CUBIC_TCP "cubic"
#define IP_ADD
#define MAX_LEN 100
#define BUFFER 1024

int get_params_rec(int argc, char *argv[], int *port, char *algo);