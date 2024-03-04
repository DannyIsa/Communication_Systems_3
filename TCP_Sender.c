#include "TCP_Sender.h"
// defult IP address
#define SERVER_IP "127.0.0.1"
// default port set
#define SERVER_PORT 5060
// buffer to store received message
#define BUFFER_SIZE 2048

int main(int argc, char *argv[])
{
    if (argc < 7)
    {
        printf("Usage: %s Must send 3 valid flags\n", argv[0]);
        return 1;
    }

    int port;
    char ip[100];
    char algo[100];

    if (get_params(argc, argv, &port, ip, algo) == -1)
    {
        printf("Invalid flags");
        return 2;
    }

    printf("port = %d\n", port);
    printf("ip = %s\n", ip);
    printf("algo = %s\n", algo);

    return 0;
}

int get_params(int argc, char *argv[], int *port, char *ip, char *algo)
{

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-ip") == 0)
        {
            strcpy(ip, argv[i + 1]);
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            *port = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-algo") == 0)
        {
            strcpy(algo, argv[i + 1]);
        }
    }

    if (*port == 0 || strcmp(ip, "") == 0 || strcmp(algo, "") == 0)
        return -1;

    return 0;
}

char *util_generate_random_data(unsigned int size)
{
    char *buffer = NULL;
    // Argument check.
    if (size == 0)
        return NULL;
    buffer = (char *)calloc(size, sizeof(char));
    // Error checking.
    if (buffer == NULL)
        return NULL;
    // Randomize the seed of the random number generator.
    srand(time(NULL));
    for (unsigned int i = 0; i < size; i++)
        *(buffer + i) = ((unsigned int)rand() % 256);
    return buffer;
}