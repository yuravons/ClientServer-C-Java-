#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <string.h> 

#define BUFFER_SIZE 20
#define PORT 8080
#define CONNECTION_COUNT 5

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

int main(int argc, char** argv)
{
    int my_socket = socket(AF_INET, SOCK_STREAM, 0), connect_socket;
    if (my_socket == 0) {
        printf("Error.\n");
        return 0;
    }

    sockaddr_in my_address;
    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = INADDR_ANY;
    my_address.sin_port = htons(PORT);

    int address_len = sizeof(my_address);

    int status = bind(my_socket, (sockaddr*) &my_address, address_len);
    if (status < 0) {
        printf("Error.\n");
        return 0;
    }    

    status = listen(my_socket, CONNECTION_COUNT);
    if (status < 0) {
        printf("Error.\n");
        return 0;
    }
    
    while (1) {
        connect_socket = accept(my_socket, (sockaddr*) &my_address, (socklen_t*)&address_len);
        if (connect_socket < 0) {
             printf("Error.\n");
        }
        int pid = fork();
        if (pid < 0) {
            printf("Error.\n");
        }
        if (pid == 0) {
            close(my_socket);
            char *buffer = (char*)malloc(sizeof(char));
            scanf("%c", &buffer[0]);
            send(connect_socket, buffer, strlen(buffer), 0);
            exit(0);
        }
        else {
            close(connect_socket);
        }
        close(connect_socket);
    }
    return 0;
}