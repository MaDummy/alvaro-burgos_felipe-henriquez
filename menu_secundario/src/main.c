#include <stdio.h>
#include <stdlib.h>
#include "../include/opciones.h"
#include <stdbool.h>
#include <unistd.h>
#include "../include/validaciones.h"
#include "../include/file_utils.h"

int main() {
        char extension[10] = "\0";
        char ruta_entrada[128] = "\0";
        char ruta_salida[128] = "\0";
        int opcion;
        bool salir = false;

    do {
        system("clear");
        printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
        printf("PID: %d.\n\n", getpid());
        printf("1: Ingresar extensión de los archivos (ej: .txt)\n");
        printf("2: Ingresar ruta de la carpeta de entrada\n");
        printf("3: Ingresar ruta de la carpeta de salida\n");
        printf("4: Ejecutar conteo de palabras\n");
        printf("5: SALIR\n\n");
        printf("-Extension actual: %s\n",extension);
        printf("-Ruta carpeta de entrada actual: %s\n",ruta_entrada);
        printf("-Ruta carpeta de salida actual: %s\n\n",ruta_salida);
        printf("\nSeleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                system("clear");
                printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
                printf("PID: %d.\n\n", getpid());
                printf("Ingrese la extensión de los archivos (ej: .txt): ");
                scanf("%s", extension);
                validExtention(extension);
                break;
            case 2:
                system("clear");
                printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
                printf("PID: %d.\n\n", getpid());
                printf("Ingrese la ruta de la carpeta de entrada: ");
                scanf("%s", ruta_entrada);
                validDir(ruta_entrada);
                break;
            case 3:
                system("clear");
                printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
                printf("PID: %d.\n\n", getpid());
                printf("Ingrese la ruta de la carpeta de salida: ");
                scanf("%s", ruta_salida);
                validDir(ruta_salida);
                break;
            case 4:
                procesamiento_archivos(ruta_entrada, extension, ruta_salida);
                break;
            case 5:
                salir = true;
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (!salir);

     exit(0);
    
}