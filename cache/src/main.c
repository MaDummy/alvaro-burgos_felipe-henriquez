#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

// ./main puerto_cache puerto_motor_busqueda memory_size
int main(int argc, char **argv){
    if (argc != 4){
        fprintf(stderr, "Error al llamar cache, se requieren 3 parametros y se pasaron %d", argc - 1);
        sleep(5);
        return 1;
    }

    int puerto_cache = atoi(argv[1]);
    int puerto_motor_busqueda = atoi(argv[2]);
    int memory_size = atoi(argv[3]);
    char buffer[BUFFER_SIZE] = {0};
    char buffer2[BUFFER_SIZE] = {0};
    int running = 1;

    //Socket de servidor para buscador
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(puerto_cache);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 2);

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    //Socket de cliente para motor de busqueda
    struct sockaddr_in motor_address;
    int motor_socket = socket(AF_INET, SOCK_STREAM, 0);

    motor_address.sin_family = AF_INET;
    motor_address.sin_port = htons(puerto_motor_busqueda);

    inet_pton(AF_INET, "127.0.0.1", &motor_address.sin_addr);

    connect(motor_socket, (struct sockaddr *)&motor_address, sizeof(motor_address)); 

    while(running){
        memset(buffer, 0, BUFFER_SIZE);
        memset(buffer2, 0, BUFFER_SIZE);
        read(new_socket, buffer, 1024);

        if(strcmp(buffer,"SALIR AHORA\n") == 0){
            running = 0;
            send(motor_socket, buffer, BUFFER_SIZE, 0);
        }

        else{
            snprintf(buffer2,BUFFER_SIZE, "soy la cache y recibi: %s\n", buffer);

            send(motor_socket, buffer2, BUFFER_SIZE, 0);

            memset(buffer2, 0, BUFFER_SIZE);

            read(motor_socket, buffer2, BUFFER_SIZE);

            send(new_socket, buffer2, BUFFER_SIZE, 0);
        }


    }
    printf("soy la cache y me voy a cerrar\n");
    sleep(5);
    close(new_socket);
    close(server_fd);
    close(motor_socket);
    return(0);


}