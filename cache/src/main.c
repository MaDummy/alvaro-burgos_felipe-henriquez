#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/cache_funcs.h"

#define BUFFER_SIZE 1024

void exporta_env();
// ./main puerto_cache puerto_motor_busqueda memory_size
// ./main 8080 8081 10
int main(int argc, char **argv){
    exporta_env();
    char *puerto_cache_env = getenv("PUERTO_CACHE");
    char *puerto_motor_env = getenv("PUERTO_MOTOR_BUSQUEDA");
    char *memory_size_env = getenv("MEMORY_SIZE");

    if (puerto_cache_env == NULL || puerto_motor_env == NULL || memory_size_env == NULL) {
        fprintf(stderr, "Error: Una variable de enotrno no funciono.\n");
        exit(EXIT_FAILURE);
    }

    int puerto_cache = atoi(puerto_cache_env);
    int puerto_motor_busqueda = atoi(puerto_motor_env);
    int memory_size = atoi(memory_size_env);

    char buffer[BUFFER_SIZE] = {0};
    char buffer2[BUFFER_SIZE] = {0};
    int running = 1;

    //Socket de servidor para buscador
    int server_fd, new_socket;
    struct sockaddr_in serverAddress;
    int addrlen = sizeof(serverAddress);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error al crear el socket del servidor\n");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(puerto_cache);

    if (bind(server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error al enlazar el socket\n");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) == -1) {
        perror("Error al escuchar\n");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //Socket de cliente para motor de busqueda
    struct sockaddr_in motor_address;
    int motor_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (motor_socket == -1) {
        perror("Error al crear el socket del cliente\n");
        exit(EXIT_FAILURE);
    }

    motor_address.sin_family = AF_INET;
    motor_address.sin_port = htons(puerto_motor_busqueda);

    inet_pton(AF_INET, "127.0.0.1", &motor_address.sin_addr);

    if (connect(motor_socket, (struct sockaddr *)&motor_address, sizeof(motor_address)) == -1) {
        perror("Error al conectar al servidor\n");
        close(motor_socket);
        exit(EXIT_FAILURE);
    } 

    //Inicializacion del cache
    Cache *cache = inicializarCache(memory_size);
    char *resultado;
    printf("cache entro al while\n");
    while(running){
        new_socket = accept(server_fd, (struct sockaddr *)&serverAddress, (socklen_t*)&addrlen);
            if (new_socket < 0) {
                continue; // Se salta el while interno hasta crear una conexion
            }
        while(1){
            memset(buffer, 0, BUFFER_SIZE);
            memset(buffer2, 0, BUFFER_SIZE);    

            int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
            //printf("cache recibio %s\n", buffer);
            //sleep(3);
            if (bytes_read == 0) {  // Significa que el buscador cerro el socket
                printf("soy la cache y voy a cerrar el socket con buscador\n");
                close(new_socket); // Tambien cierra el socket
                break; // Sale del while interno
            }

            if(strcmp(buffer,"SALIR AHORA\n") == 0){
                running = 0; // Para que el while externo se termine
                send(motor_socket, buffer, BUFFER_SIZE, 0); // Para enviar el mensaje de termino a motor de busqueda
                close(new_socket);
                break; // Para terminar salirse del while interno
            }
            else{
                // Se escribe la salida en el buffer2
                resultado = buscarEntrada(cache, buffer);
                if(strcmp(resultado, "-1") != 0){
                    snprintf(buffer2, BUFFER_SIZE, "%s", resultado); // existe por temas de depuracion
                    send(new_socket, buffer2, BUFFER_SIZE, 0); // Envia mensaje a buscador
                }else{
                    printf("cache envia %s a motor\n", buffer);
                    int bytes_sent = send(motor_socket, buffer, BUFFER_SIZE, 0);
                    if (bytes_sent < 0) {
                        printf("Error al enviar datos a motor de busqueda");
                        break; // Manejo de error y salir del bucle
                    }
                    // Envia mensaje recibido de buscador a motor de busqueda
                    read(motor_socket, buffer2, BUFFER_SIZE); // Lee mensaje recibido de motor de busqueda
                    printf("cache recibio %s de motor\n", buffer2);
                    printf("cache envia %s a buscador\n", buffer2);
                    send(new_socket, buffer2, BUFFER_SIZE, 0);
                    agregarEntrada(cache, buffer, buffer2);
                }

                memset(buffer2, 0, BUFFER_SIZE); // Resetea el buffer2 para reutilizarlo
            }

        }
    }
    printf("soy la cache y me voy a cerrar\n"); 
    close(server_fd);
    close(motor_socket);
    return(0);


}

void exporta_env() {
    FILE *file = fopen(".env", "r");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char *delimiter = strchr(line, '=');
        if (delimiter != NULL) {
            *delimiter = '\0';
            char *key = line;
            char *value = delimiter + 1;

            setenv(key, value, 1);
        }
    }
    fclose(file);
}