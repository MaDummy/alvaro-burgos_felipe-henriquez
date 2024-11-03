#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

// ./main puerto_motor_busqueda topk
int main(int argc, char **argv){
    if (argc != 3){
        fprintf(stderr, "Error al llamar motor_busqueda, se requieren 2 parametros y se pasaron %d", argc - 1);
        sleep(5);
    }

    int port = atoi(argv[1]);
    int topk = atoi(argv[2]);

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char buffer2[BUFFER_SIZE] = {0};

    int running = 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 2);

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    while(running){
        memset(buffer, 0, BUFFER_SIZE);
        memset(buffer2, 0, BUFFER_SIZE);

        read(new_socket, buffer, 1024);

        if(strcmp(buffer,"SALIR AHORA\n") == 0){
            running = 0;
        }
        else{
            snprintf(buffer2,BUFFER_SIZE, "soy el motor_busqueda y recibi: %s\n", buffer);

            send(new_socket, buffer2, BUFFER_SIZE, 0);

        }
    }

    printf("soy el motor de busqueda y me voy a cerrar\n");
    close(new_socket);
    close(server_fd);
    return(0);


}