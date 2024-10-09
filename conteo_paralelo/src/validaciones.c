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