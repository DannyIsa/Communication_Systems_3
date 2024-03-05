#include "TCP_Receiver.h"

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        perror("args must have 2 valid flags");
        return 1;
    }

    int port;
    char algo[MAX_LEN];

    if (get_params_rec(argc, argv, &port, algo) == -1)
    {
        perror("Invalid flags");
        exit(1);
    }

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;

    memset(&server_address, 0, sizeof(server_address));

    char buffer[BUFFER] = {0};

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
        perror("Socket creation failed");
        exit(1);
    }
    printf("Socket created\n");

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    // binding the socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Binding failed");
        close(server_socket);
        exit(1);
    }
    printf("Socket bound successfully\n");

    // listening for connections
    if (listen(server_socket, 1) < 0)
    {
        perror("Listening failed");
        close(server_socket);
        exit(1);
    }
    printf("Listening for connections\n");

    // accepting connections
    socklen_t client_address_len = sizeof(client_address);
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len)) < 0)
    {
        perror("Accept failed");
        close(server_socket);
        exit(1);
    }
    printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    ssize_t read_size;
    while ((read_size = read(client_socket, buffer, sizeof(buffer))) > 0)
    {
        printf("Message received: %s\n", buffer);
        const char *response = "Message received";
        send(client_socket, response, strlen(response), 0);
        memset(buffer, 0, sizeof(buffer));
    }

    if (read_size == 0)
    {
        printf("Client disconnected\n");
    }
    else if (read_size == -1)
    {
        perror("Read failed");
    }

    close(client_socket);
    close(server_socket);

    return 0;
}

int get_params_rec(int argc, char *argv[], int *port, char *algo)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0)
        {
            *port = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-algo") == 0)
        {
            strcpy(algo, argv[i + 1]);
        }
    }
    if (*port == 0 || (strcmp(algo, CUBIC_TCP) != 0 && strcmp(algo, RENO_TCP) != 0))
    {
        return -1;
    }

    return 0;
}

// #include "TCP_Receiver.h"

// int main(int argc, char *argv[])
// {
//     if (argc < 5)
//     {
//         perror("args must have 2 valid flags");
//         return 1;
//     }

//     int port;
//     char algo[MAX_LEN];

//     if (get_params_rec(argc, argv, &port, algo) == -1)
//     {
//         perror("Invalid flags");
//         exit(1);
//     }

//     int server_socket, client_socket;
//     struct sockaddr_in server_address, client_address;

//     memset(&server_address, 0, sizeof(server_address));
//     memset(&client_socket, 0, sizeof(client_socket));

//     char buffer[BUFFER] = {0};

//     if (server_socket = socket(AF_INET, SOCK_STREAM, 0) <= 0)
//     {
//         perror("Socket creation failed");
//         exit(1);
//     }
//     printf("socket created");

//     if (setsockopt())

//     server_address.sin_family = AF_INET;
//     server_address.sin_addr.s_addr = INADDR_ANY;
//     server_address.sin_port = htons(port);

//     // binding the socket
//     if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) <= 0)
//     {
//         perror("binding failed");
//         exit(1);
//     }

//     // listening for connections
//     if (listen(server_socket, 1) < 0)
//     {
//         perror("Listening failed");
//         exit(1);
//     }

//     printf("Listening to server");

//     // accepting connections
//     socklen_t client_address_len = sizeof(client_address);
//     if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len)) < 0)
//     {
//         perror("Accept failed");
//         exit(1);
//     }
//     printf("Connection accepted");

//     ssize_t read_size;
//     while ((read_size = read(client_socket, buffer, sizeof(buffer))) > 0)
//     {
//         printf("Message received");
//         const char *response = "Message received";
//         send(client_socket, response, strlen(response), 0);
//         memset(buffer, 0, sizeof(buffer));
//     }
//     if (read_size == 0)
//     {
//         printf("Client disconnected\n");
//     }
//     else if (read_size == -1)
//     {
//         perror("read failed");
//     }
//     close(client_socket);
//     close(server_socket);

//     return 0;
// }

// int get_params_rec(int argc, char *argv[], int *port, char *algo)
// {
//     for (int i = 0; i < argc; i++)
//     {
//         if (strcmp(argv[i], "-p") == 0)
//         {
//             *port = atoi(argv[i + 1]);
//         }
//         else if (strcmp(argv[i], "-algo") == 0)
//         {
//             strcpy(algo, argv[i + 1]);
//         }
//     }
//     if (*port == 0 || (strcmp(algo, CUBIC_TCP) != 0 && strcmp(algo, RENO_TCP) != 0))
//         return -1;

//     return 0;
// }