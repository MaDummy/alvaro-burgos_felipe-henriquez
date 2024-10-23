#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "../include/file_utils.h"

void leeProcesos(char *path_procesos, char array_procesos[MAX_PROCESOS][MAX_LARGO_PROCESO], int *cont){
    FILE *archivo = fopen(path_procesos, "r");
    if(archivo == NULL){
        fprintf(stderr, "Error al abrir archivo de procesos");
        return;
    }

    char buffer[BUFFER_LINEA];

    while (fgets(buffer, sizeof(buffer), archivo)){

        char *ptr = strchr(buffer, ';');

        strcpy(array_procesos[*cont], ptr + 1);

        (*cont)++;
    }

    fclose(archivo);
}