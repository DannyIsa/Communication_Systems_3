#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>

#define RENO_TCP "reno"
#define CUBIC_TCP "cubic"

int get_params_rec(int argc, char *argv[], int *port, char *algo);