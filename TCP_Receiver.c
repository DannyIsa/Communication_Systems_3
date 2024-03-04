#include "TCP_Receiver.h"

int main(int argc , char *argv[]){
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