#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
char *util_generate_random_data(unsigned int size);
int get_params(int argc, char *argv[], int *port, char *ip, char *algo);