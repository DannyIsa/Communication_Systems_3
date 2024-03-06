#include "TCP_Receiver.h"

int get_params_rec(int argc, char *argv[], int *port, char *algo);

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

    struct timeval start_time, end_time;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
    {
        perror("Socket creation failed");
        exit(1);
    }
    printf("Socket created\n");

    int options = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(int)) < 0)
    {
        printf("ERROR: Failed to define options");
        close(server_socket);
        exit(1);
    }

    socklen_t algo_len = strlen(algo); // use strlen instead of sizeof

    // Set the selected congestion algorithm.
    if (setsockopt(server_socket, IPPROTO_TCP, TCP_CONGESTION, algo, algo_len) < 0)
    {
        printf("ERROR: Didn't define the algo flag correctly");
        close(server_socket);
        exit(1);
    }

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

    int active = TRUE;

    while (active)
    {
        int receive_init = recv(client_socket, buffer, BUFFER, 0);
        if (receive_init <= 0)
        {
            perror("Failed to receive size");
        }

        int file_size = atoi(buffer);
        printf("File size: %d\n", file_size);

        int bytes_received = 0;
        int num_of_receives = 0;

        gettimeofday(&start_time, NULL);

        while (bytes_received < file_size)
        {
            int read_size = recv(client_socket, buffer, BUFFER, 0);
            if (read_size == 0)
            {
                printf("Client disconnected\n");
                exit(1);
            }
            else if (read_size == -1)
            {
                perror("Read failed");
                exit(1);
            }
            bytes_received += read_size;
            const char *response = "Message received";
            // send(client_socket, response, strlen(response), 0);
            memset(buffer, 0, sizeof(buffer));
            num_of_receives++;
        }

        gettimeofday(&end_time, NULL);

        // Calculate sending time and average bandwidth
        float elapsed_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_usec - start_time.tv_usec) / 1000;
        double elapsed_time_s = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
        double size_in_mb = (bytes_received / 1024) / 1024;
        double average_bandwidth = size_in_mb / elapsed_time_s;

        printf("File received in %f ms\n", elapsed_time_ms);
        printf("Average Bandwidth: %.2f MBps\n", average_bandwidth);

        char senderContinue;

        if (recv(client_socket, &senderContinue, sizeof(char), 0) <= 0)
        {
            perror("ERROR: need to send argument to quit/restart");
            exit(1);
        }

        if (senderContinue == 'n')
        {
            active = FALSE;
        }
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
