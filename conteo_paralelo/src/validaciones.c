#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "../include/menu.h"
#include <unistd.h>

void validDir(char *path) {
    DIR *directorio = opendir(path);
    
    if (directorio) {
        closedir(directorio);
    } else {
        path[0] = '\0';
        system("clear");
        printf("PID: %d.\n\n", getpid());
        printf("════ ∘◦Conteo en paralelo con threads◦∘ ════\n\n");
        printf("El directorio no existe\n");
        regresa_menu();
    }
}

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
        printf("════ ∘◦Menu de Conteo en paralelo◦∘ ════\n\n");
        printf("PID: %d.\n\n", getpid());
        printf("La extension no es valida\n");
        regresa_menu();
    }
}