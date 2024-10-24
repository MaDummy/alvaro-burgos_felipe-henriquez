#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void procesar_mensaje_planificador(char *mensaje, int *id_core, int *id_proceso, char *operacion, float *numero1, float *numero2) {
    int resultado = sscanf(mensaje, "%d:%d;%[^;];%f,%f", id_core, id_proceso, operacion, numero1, numero2);

    if (resultado != 5) {
        fprintf(stderr, "Error: formato de mensaje incorrecto, se esperaban 5 elementos, se leyeron %d\n", resultado);
    } else {
        printf("id_core: %d, id_proceso: %d, operacion: %s, numero1: %f, numero2: %f\n", 
               *id_core, *id_proceso, operacion, *numero1, *numero2);
    }
}

void procesar_mensaje_core(char *mensaje, int *id_core, int *id_proceso, char *operacion, float *numero1, float *numero2, float *respuesta){
    char op[20]; 
    char arg1[20], arg2[20], arg3[20]; 

    sscanf(mensaje, "%d:%d;%[^;];%[^,],%[^,],%s", id_core, id_proceso, op, arg1, arg2,arg3);

    strcpy(operacion, op);

    *numero1 = atof(arg1);
    *numero2 = atof(arg2);
    *respuesta = atof(arg3);
}

void ejecuta_core(char *path_core, int id_core, int id_proceso, char *operacion, float numero1, float numero2){
    char comando[1024];
    snprintf(comando, sizeof(comando), "%s %d %d %s %f %f", path_core,
                                                            id_core,
                                                            id_proceso,
                                                            operacion,
                                                            numero1,
                                                            numero2);

    printf("%s\n",comando);

    system(comando);
}