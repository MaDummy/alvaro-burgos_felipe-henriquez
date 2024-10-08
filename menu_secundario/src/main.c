#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "../include/validaciones.h"
#include "../include/file_utils.h"
#include "../include/opciones.h"

#define EXTENSION_SIZE 20

int main() {
        bool opcion_valida = 1;
        char extension[EXTENSION_SIZE] = "\0";
        char ruta_entrada[MAX_PATH] = "\0";
        char ruta_salida[MAX_PATH] = "\0";
        int opcion;
        bool salir = false;

    do {
        system("clear");
        printf("PID: %d.\n\n", getpid());
        printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
        printf("1: Ingresar extensión de los archivos (ej: .txt)\n");
        printf("2: Ingresar ruta de la carpeta de entrada\n");
        printf("3: Ingresar ruta de la carpeta de salida\n");
        printf("4: Ejecutar conteo de palabras\n\n");
        printf("0: SALIR\n\n");
        printf("-Extension actual: %s\n",extension);
        printf("-Ruta carpeta de entrada actual: %s\n",ruta_entrada);
        printf("-Ruta carpeta de salida actual: %s\n\n",ruta_salida);

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

        switch (opcion) {
            case 1:
                system("clear");
                printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
                printf("PID: %d.\n\n", getpid());
                printf("Ingrese la extensión de los archivos (ej: .txt): ");

                getchar();

                fgets(extension, EXTENSION_SIZE, stdin);

                extension[strcspn(extension, "\n")] = '\0'; 

                validExtention(extension);
                break;
            case 2:
                system("clear");
                printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
                printf("PID: %d.\n\n", getpid());
                printf("Ingrese la ruta de la carpeta de entrada: ");

                getchar();

                fgets(ruta_entrada, MAX_PATH, stdin);

                ruta_entrada[strcspn(ruta_entrada, "\n")] = '\0'; 

                validDir(ruta_entrada);
                break;
            case 3:
                system("clear");
                printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
                printf("PID: %d.\n\n", getpid());
                printf("Ingrese la ruta de la carpeta de salida: ");

                getchar();

                fgets(ruta_salida, MAX_PATH, stdin);

                ruta_salida[strcspn(ruta_salida, "\n")] = '\0'; 

                validDir(ruta_salida);
                break;
            case 4:
                procesamiento_archivos(ruta_entrada, extension, ruta_salida);
                break;
            case 0:
                salir = true;
                break;
            default:
                opcion_valida = false;
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (!salir);

     exit(0);
    
}