#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include "../include/menu.h"  // Incluye la funcion regresa_menu
#include "../include/file_utils.h"
#include "../include/validaciones.h"


void procesamiento_archivos(char *directorioEntrada, char *extension, char *directorioSalida){
    system("clear");
    if(extension[0] == '\0' || directorioEntrada[0] == '\0' || directorioSalida[0] == '\0'){
        system("clear");
        printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
        printf("PID: %d.\n\n", getpid());
        printf("No se puede ejecutar si no ha ingresado valores o alguno es invalido");
        regresa_menu();
        return;
    }

    if(strcmp(directorioEntrada, directorioSalida) == 0){
        system("clear");
        printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
        printf("PID: %d.\n\n", getpid());
        printf("El directorio de entrada no puede ser igual al de salida");
        regresa_menu();
        return;
    }

    validDirWithExtention(directorioEntrada, extension);

    char* pathArchivosSalida[1024];
    int cantidadPalabras[1024];

    int cantidadArchivos;

    procesar_archivos(directorioEntrada, extension, directorioSalida, pathArchivosSalida, cantidadPalabras, &cantidadArchivos);

    system("clear");
    printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
    printf("PID: %d.\n\n", getpid());
    printf("Archivos resultantes:\n\n");

    for(int i = 0; i < cantidadArchivos; i++){
        printf("%s : %d\n",pathArchivosSalida[i], cantidadPalabras[i]);
    }
    regresa_menu();
    
}
