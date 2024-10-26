#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "../include/file_utils.h"
#include "../include/utils.h"


void escribe_respuesta_archivo(FILE *archivo, char *respuesta){
    int id_core;
    int id_proceso;
    char operacion[20];
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

    if (fprintf(archivo, "%s\n", salida) < 0) {
        printf("no pude escribir en el archivo\n");
    }
}