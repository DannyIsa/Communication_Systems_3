#include "TCP_Receiver.h"

int main(int argc , char *argv[])
{
    if(argc < 7)
    {
        perror("args must have 2 valid flags");
        return 1;
    }

    int port;
    char algo[100];

    if(get_params_rec(argc , argv ,&port , algo) == -1)
    {
        perror("Invalid flags");
        return 2;
    }
    struct sockaddr_in sender;
    struct sockaddr_in receiver;

  
    memset(&sender , 0 , sizeof(sender));
    memset(&receiver , 0 , sizeof(receiver));
    

    int sock = -1;
    sock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);


    return 0;
}

int get_params_rec(int argc , char *argv[] , int *port , char *algo){
    for (int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-p") == 0)
        {
            *port = atoi(argv[i + 1]);
        }
        else if(strcmp(argv[i], "-algo") == 0)
        {
            strcpy(algo , argv[i + 1]);
        }
    }
    if(*port == 0 || strcmp(algo, "") == 0) return -1;
    return 0;
}