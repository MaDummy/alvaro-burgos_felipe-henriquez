#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/file_utils.h"


void imprimirIntersecciones(NodoInterseccion *puntajes) {
    printf("entre a imprimir\n");
    sleep(5);
    NodoInterseccion *actual = puntajes;
    while (actual != NULL) {
        printf("Documento ID: %d, Suma de Ocurrencias: %d, Contador: %d\n", 
               actual->id_documento, 
               actual->suma_ocurrencias, 
               actual->contador);
        sleep(5);  // Pause for 1 second between iterations
        actual = actual->next;
    }
}

// ./main puerto_motor_busqueda topk inverted_index_path
int main(int argc, char **argv){
    if (argc != 4){
        fprintf(stderr, "Error al llamar motor_busqueda, se requieren 3 parametros y se pasaron %d", argc - 1);
        sleep(5);
        return 1;
    }

    system("clear");
        printf("motor: llegue aqui1\n");
        sleep(2);

    int port = atoi(argv[1]);
    int topk = atoi(argv[2]);
    char *inverted_index_path = argv[3];

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
        system("clear");
        printf("motor: llegue aqui1\n");
        sleep(2);
        TablaHash tabla;
        memset(&tabla, 0, sizeof(TablaHash));

        memset(buffer, 0, BUFFER_SIZE);
        memset(buffer2, 0, BUFFER_SIZE);

        read(new_socket, buffer, BUFFER_SIZE);

        system("clear");
        printf("motor: llegue aqui2\n");
        sleep(2);

        if(strcmp(buffer,"SALIR AHORA\n") == 0){
            running = 0;
        }
        else{
            FILE *archivo_index = fopen(inverted_index_path, "r");
            if (archivo_index == NULL) {
                fprintf(stderr, "Error: No se pudo abrir inverted_index en motor de busqueda.\n");
                sleep(5);
                continue; 
            }
            
            system("clear");
            printf("motor: llegue aqui3\n");
            sleep(2);

            rellenarTablaHash(archivo_index, &tabla);
            fclose(archivo_index);

            system("clear");
            printf("motor: llegue aqui4\n");
            sleep(2);

            NodoInterseccion *puntajes = NULL;
            procesarPalabras(&tabla, &puntajes, buffer);

            if (puntajes == NULL) {
                printf("No hay intersecciones para imprimir.\n");
                sleep(5);
            } else {
                imprimirIntersecciones(puntajes);
            }

            system("clear");
            printf("motor: llegue aqui5\n");
            sleep(2);

            char *formatted_result = formatearResultado(puntajes, buffer);
            system("clear");
            printf("motor: llegue aqui6\n");
            sleep(2);

            snprintf(buffer2,BUFFER_SIZE, "soy el motor_busqueda y recibi: %s\n", formatted_result);

            system("clear");
            printf("motor: llegue aqui7\n");
            sleep(2);

            for (int i = 0; i < TAMANO_TABLA_HASH; i++) {
                NodoPalabra *nodo = tabla.tabla[i];
                while (nodo != NULL) {
                    NodoPalabra *temp = nodo;
                    nodo = nodo->next;

                    // Free ID_Ocurrencias
                    ID_Ocurrencias *ocurrencias = temp->ocurrencias;
                    while (ocurrencias != NULL) {
                        ID_Ocurrencias *tempOcurrencias = ocurrencias;
                        ocurrencias = ocurrencias->next;
                        free(tempOcurrencias);
                    }

                    free(temp);
                }
            }

            system("clear");
            printf("motor: llegue aqui8\n");
            sleep(2);

            send(new_socket, buffer2, BUFFER_SIZE, 0);

            system("clear");
            printf("motor: llegue aqui9\n");
            sleep(10);

        }
    }

    printf("soy el motor de busqueda y me voy a cerrar\n");
    close(new_socket);
    close(server_fd);
    return(0);


}