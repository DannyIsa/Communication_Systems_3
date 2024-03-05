#include "TCP_Sender.h"

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
    // struct sockaddr_in server_adress, client_adress;
    char buffer[BUFFER] = {0};

    // creating the socket with IPv4 , TCP secure connectoin and the PROTOCOL
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

    char resend = TRUE;

    // Sends the info to the server with an option to repeat the sending if failed
    while (resend)
    {
        // sets the data to send
        char *data = util_generate_random_data(FILE_SIZE);

        // send the data size
        int data_size = sizeof(data);

        if (send(client_socket, &data_size, sizeof(int), 0) <= 0)
        {
            perror("Unable to send size to client\n");
            close(client_socket);
            exit(1);
        }
        printf("File size sent");

        static char temp = 0;

        if (recv(client_socket, &temp, sizeof(char), 0) <= 0)
        {
            perror("Server didnt receive");
            exit(1);
        }
        printf("Size received at server successfully\n");

        if (send(client_socket, data, data_size, 0) <= 0)
        {
            perror("Unable to send file to client");
            close(client_socket);
            exit(1);
        }

        printf("Message sent successfully\n");

        // response from server
        ssize_t read_size = read(client_socket, &buffer, sizeof(buffer));

        // determine if we wanna send again here
        if (read_size > 0)
        {
            printf("File recieved\n");
            ;
        }
        else if (read_size == 0)
        {
            printf("Disconnected\n");
            exit(1);
        }
        else
        {
            printf("Read failed sending again\n");
        }

        printf("Resend the file? [y/n]: ");
        scanf("%s", &resend);

        switch (resend)
        {
        case 'y':
            printf("Sends anothe file\n");
            resend = TRUE;
            break;

        case 'n':
            resend = FALSE;
            break;

        default:
            printf("Resend the file? [y/n]: ");
            scanf("%s", &resend);
            break;
        }
    }

    // close socket
    close(client_socket);

    printf("Socket connection is closed exiting program\n");

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

//  struct sockaddr_in sender;

//     memset(&sender, 0, sizeof(sender));

//     int sock = -1;
//     sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

//     if (sock == -1)
//     {
//         perror("Error: socket creation failed");
//         return 3;
//     }

//     if (inet_pton(AF_INET, ip, &sender.sin_addr) <= 0)
//     {
//         perror("inet_pton(3)");
//         close(sock);
//         return 1;
//     }
//     // sets the adresses to IPv4
//     sender.sin_family = AF_INET;
//     // Sets the port
//     sender.sin_port = htons(port);

//     // try to establish connection with the server
//     if (connect(sock, (struct sockaddr *)&sender, sizeof(sender)) < 0)
//     {
//         perror("connect(2)");
//         close(sock);
//         return 1;
//     }
//     // connection established (if we didnt get an error)
//     // the package info and length
//     int pakLeng;
//     char *pakInfo;
//     int re = 1;

//     while (re)
//     {
//         pakInfo = util_generate_random_data(100); // UNFINISHED NEEDS THE TRUE SIZE
//         pakLeng = 100;
//         char *temporary = "100";
//         int bytes_sent = sendSock(strlen(temporary) + 1, temporary, sock);
//         if (bytes_sent <= 0)
//         {
//             perror("Failed to send socket , 0 bytes transferred");
//             // User input if we want to retry sending the socket.
//             scanf("%d", &re);
//         }
//     }
//     // if socket was transferred ; terminate
//     close(sock);