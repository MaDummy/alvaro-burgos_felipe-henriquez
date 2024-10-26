#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "../include/file_utils.h"

void leeProcesos(char *path_procesos, char **array_procesos, int *cont) {
    FILE *archivo = fopen(path_procesos, "r");
    if (archivo == NULL) {
        fprintf(stderr, "Error al abrir archivo de procesos\n");
        return;
    }

    char buffer[BUFFER_LINEA];

    while (fgets(buffer, sizeof(buffer), archivo)) {
        size_t len = strcspn(buffer, "\n");

        strncpy(array_procesos[*cont], buffer, len);
        array_procesos[*cont][len] = '\0';

        (*cont)++;
    }

    fclose(archivo);
}