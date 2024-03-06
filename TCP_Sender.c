#include "TCP_Sender.h"

int get_params(int argc, char *argv[], int *port, char *ip, char *algo);
char *util_generate_random_data(unsigned int size);
char *stringify(int size);

int main(int argc, char *argv[])
{
    if (argc < 7)
    {
        printf("Usage: Must send 3 valid flags\n");
        return 1;
    }

    int port;
    char ip[MAX_LEN];
    char algo[MAX_LEN];

    if (get_params(argc, argv, &port, ip, algo) == -1)
    {
        perror("Invalid flags\n");
        exit(1);
    }

    struct sockaddr_in address;
    int client_socket;
    char buffer[BUFFER] = {0};

    // creating the socket with IPv4 , TCP secure connection and the PROTOCOL
    if ((client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
    {
        perror("Socket failed\n");
        exit(1);
    }

    printf("Socket created successfully\n");

    // Set address to IPv4 and Sets the port number
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    // convert to binary form
    if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0)
    {
        perror("Invalid address\n");
        close(client_socket);
        exit(1);
    }

    // connect to the server
    if (connect(client_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("failed to connect server\n");
        exit(1);
    }
    printf("Connected successfully\n");

    int resend = TRUE;
    char ans;

    while (resend)
    {
        char *data = util_generate_random_data(FILE_SIZE);
        char *data_size_str = stringify(FILE_SIZE);
        printf("data_size_str = %s\n", data_size_str);
        if (send(client_socket, data_size_str, strlen(data_size_str) + 1, 0) <= 0)
        {
            perror("Unable to send size to client\n");
            close(client_socket);
            exit(1);
        }
        printf("File size sent\n");

        static char temp = 0;

        if (send(client_socket, data, FILE_SIZE, 0) <= 0)
        {
            perror("Unable to send file to client");
            close(client_socket);
            exit(1);
        }

        printf("Message sent successfully\n");

        printf("Resend the file? [y/n]: ");
        scanf("%c", &ans);

        printf("ans = %c\n", ans);
        printf("equal y ? %d\n", ans == 'y');
        printf("equal n ? %d\n", ans == 'n');

        switch (ans)
        {
        case 'y':
            send(client_socket, &ans, sizeof(char), 0);
            printf("Sends another file\n");
            resend = TRUE;
            break;

        case 'n':
            send(client_socket, &ans, sizeof(char), 0);
            resend = FALSE;
            break;

        default:
            printf("Resend the file? [y/n]: ");
            scanf("%c", &ans);
            break;
        }
    }

    close(client_socket);

    printf("Socket connection is closed, exiting program\n");

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

    if (*port < 0 || *port > 65535 || (strcmp(algo, CUBIC_TCP) != 0 && strcmp(algo, RENO_TCP) != 0))
        return -1;

    return 0;
}

char *util_generate_random_data(unsigned int size)
{
    char *buffer = NULL;

    if (size == 0)
        return NULL;

    buffer = (char *)calloc(size, sizeof(char));

    if (buffer == NULL)
        return NULL;

    srand(time(NULL));

    for (unsigned int i = 0; i < size; i++)
        *(buffer + i) = ((unsigned int)rand() % 256);

    return buffer;
}

char *stringify(int size)
{
    int counter = 0;
    int temp = size;

    while (temp != 0)
    {
        temp /= 10;
        counter++;
    }

    char *return_str = (char *)malloc(counter + 1);
    sprintf(return_str, "%d", size);

    return return_str;
}
