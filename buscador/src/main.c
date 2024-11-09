#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/validaciones.h" //Se conserva de momento, poco probable de usar
#include "../include/file_utils.h" //Se conserva de momento, muy probable de usar
#include "../include/utils.h" //Se conserva de momento, muy probable de usar

#define BUFFER_SIZE 1024

// Ejecutar con ./main path_mapa_archivos puerto_cache
int main(int argc, char **argv) {
    if (argc != 3){
        fprintf(stderr, "Error al llamar buscador, se requieren 1 parametros y se pasaron %d", argc - 1);
        exit(EXIT_FAILURE);
    }
    exporta_env();
    char *ruta_mapa_archivo = getenv("MAPA_ARCHIVOS");
    int puerto_cache = atoi(getenv("PUERTO_CACHE"));

    bool opcion_valida = 1;
    char buffer[BUFFER_SIZE] = "\0";
    int opcion;
    bool salir = false;

    //empieza socket
    int sock = 0;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puerto_cache);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    do {
        system("clear");
        printf("PID: %d.\n\n", getpid());
        printf("════ ∘◦Buscador◦∘ ════\n\n");
        printf("1: Buscar palabras\n");
        printf("palabra: %s\n",buffer);
        printf("0: SALIR\n\n");

        if(opcion_valida)
            printf("Escoja una opción: ");
        else{
            printf("Ingrese una opción válida: ");
            opcion_valida = true;
        }

        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion_valida = false;
            continue;
        }

        if(strcmp("SALIR AHORA\n", buffer) == 0){
            salir = true;
        }

        switch (opcion) {
            case 1:
                system("clear");
                printf("PID: %d.\n\n", getpid());
                printf("════ ∘◦Buscador◦∘ ════\n\n");
                printf("*No se busca una oracion, solo que las palabras esxistan en el texto\n");
                printf("*Debe ingresar las palabras que desea buscar separadas por un espacio\n");
                printf("*Solo se devolveran textos que contengan TODAS las palabras\n");
                printf("*Inserte 'SALIR AHORA' para cerrar la cache, motor de busqueda, y esta opcion");
                printf("Ingrese palabras a buscar: ");

                getchar();

                fgets(buffer, BUFFER_SIZE, stdin);

                if (strcmp("SALIR AHORA\n", buffer) == 0) {
                    salir = true;
                } else if (strlen(buffer) > 1) { 
                    send(sock, buffer, BUFFER_SIZE, 0);
                    read(sock, buffer, BUFFER_SIZE);
                    if(!(strcmp(buffer, "No hay coincidencias") == 0)) strcpy(buffer, reemplazaTexto(buffer, ruta_mapa_archivo));
                 }
                break;
            case 0:
                salir = true;
                break;
            default:
                opcion_valida = false;
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (!salir);
    send(sock, "SALIR AHORA\n", BUFFER_SIZE, 0);
    close(sock);
    exit(0);
    
}