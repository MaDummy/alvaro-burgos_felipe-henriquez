#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/cache_funcs.h"

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

    //Socket de cliente para motor de busqueda
    struct sockaddr_in motor_address;
    int motor_socket = socket(AF_INET, SOCK_STREAM, 0);

    motor_address.sin_family = AF_INET;
    motor_address.sin_port = htons(puerto_motor_busqueda);

    inet_pton(AF_INET, "127.0.0.1", &motor_address.sin_addr);

    connect(motor_socket, (struct sockaddr *)&motor_address, sizeof(motor_address)); 

    //Inicializacion del cache
    Cache *cache = inicializarCache(memory_size);
    char *resultado;
    while(running){
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
            if (new_socket < 0) {
                continue; // Se salta el while interno hasta crear una conexion
            }
        while(1){
            memset(buffer, 0, BUFFER_SIZE);
            memset(buffer2, 0, BUFFER_SIZE);    

            int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
            if (bytes_read == 0) {  // Significa que el buscador cerro el socket
                close(new_socket); // Tambien cierra el socket
                break; // Sale del while interno
            }

            if(strcmp(buffer,"SALIR AHORA\n") == 0){
                running = 0; // Para que el while externo se termine
                send(motor_socket, buffer, BUFFER_SIZE, 0); // Para enviar el mensaje de termino a motor de busqueda
                break; // Para terminar salirse del while interno
            }
            else{
                printf("soy la cache y estoy enviando: %s\n", buffer);
                // Se escribe la salida en el buffer2
                resultado = buscarEntrada(cache, buffer);
                if(strcmp(resultado, "-1") != 0){
                    snprintf(buffer2, BUFFER_SIZE, "%s", resultado); // existe por temas de depuracion
                    send(new_socket, buffer2, BUFFER_SIZE, 0); // Envia mensaje a buscador
                }else{
                    send(motor_socket, buffer, BUFFER_SIZE, 0); // Envia mensaje recibido de buscador a motor de busqueda
                    read(motor_socket, buffer2, BUFFER_SIZE); // Lee mensaje recibido de motor de busqueda
                    agregarEntrada(cache, buffer, buffer2);
                }

                memset(buffer2, 0, BUFFER_SIZE); // Resetea el buffer2 para reutilizarlo
            }

        }
    }
    printf("soy la cache y me voy a cerrar\n"); // Para depurar
    sleep(5); // Para depurar
    close(new_socket);
    close(server_fd);
    close(motor_socket);
    return(0);


}