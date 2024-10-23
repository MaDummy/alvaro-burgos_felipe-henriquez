#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../include/file_utils.h"

void crea_mensaje(int id_core, char proceso[MAX_LARGO_PROCESO], char mensaje[MAX_LARGO_PROCESO]){
    snprintf(mensaje, MAX_LARGO_PROCESO, "%d:%s", id_core, proceso);
}

void ejecuta_distribuidor(char *path_distribuidor, char *path_core, char *path_resultados){
    char comando[512];
    snprintf(comando, sizeof(comando), "%s %s %s &", path_distribuidor, path_core, path_resultados);
    system(comando);
}