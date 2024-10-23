#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "../include/file_utils.h"
#include "../include/utils.h"

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

void escribe_respuesta_archivo(FILE *archivo, char *respuesta){
    int id_core;
    int id_proceso;
    char *operacion;
    float numero1;
    float numero2;
    float val_respuesta;

    procesar_mensaje_core(respuesta,
                        &id_core,
                        &id_proceso,
                        operacion,
                        &numero1,
                        &numero2,
                        &val_respuesta);

    char salida[512];

    snprintf(salida, sizeof(salida), "(%d:%d;%s;%f,%f)=>%f", id_core,
                                                            id_proceso,
                                                            operacion,
                                                            numero1,
                                                            numero2,
                                                            val_respuesta);

    fprintf(archivo, "comanod\n");
}