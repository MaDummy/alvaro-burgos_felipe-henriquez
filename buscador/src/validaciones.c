#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "../include/utils.h"
#include "../include/menu.h"


void validExtention(char *extension){
    char *extensiones[] = {
    ".txt",   // Archivos de texto plano
    ".md",    // Archivos Markdown
    ".csv",   // Archivos de valores separados por comas
    ".log",   // Archivos de registros
    ".html",  // Archivos HTML
    };
    int arrayLength = 5;

    int valida = 0;
    for(int i = 0; i < arrayLength; i++){
        if(strcmp(extensiones[i],extension) == 0){
            valida = 1;
            break;
        }
    }
    if(valida == 0){
        extension[0] = '\0';
        system("clear");
        printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
        printf("PID: %d.\n\n", getpid());
        printf("La extension no es valida\n");
        regresa_menu();
    }
}


void validDir(char *path) {
    DIR *directorio = opendir(path);
    
    if (directorio) {
        closedir(directorio);
    } else {
        path[0] = '\0';
        system("clear");
        printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
        printf("PID: %d.\n\n", getpid());
        printf("El directorio no existe\n");
        regresa_menu();
    }
}


void validDirWithExtention(char *path, char *extention){
    DIR *dir = opendir(path);
    struct dirent *archivoActual;
    int existeArchivo = 0;

    if (dir == NULL) {
        fprintf(stderr, "Error: no se puede abrir el directorio\n");
        exit(EXIT_FAILURE);
    }

    while ((archivoActual = readdir(dir)) != NULL && existeArchivo == 0){
        if (strstr(archivoActual->d_name, extention) != NULL){
            existeArchivo = 1;
            break;
        }
    }

    if(existeArchivo == 0){
        system("clear");
        printf("════ ∘◦Menu de Conteo de Palabras◦∘ ════\n\n");
        printf("PID: %d.\n\n", getpid());
        printf("El directorio dado no tiene archivos con la extension dada\n");
        closedir(dir);
        regresa_menu();
    }

    closedir(dir);
}