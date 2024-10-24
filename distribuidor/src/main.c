#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../include/utils.h"
#include "../include/file_utils.h"
#include "../include/comms.h"

//./main path_programa_core path_resultados
int main(int argc, char **argv) {
    printf("hola, existo, soy el distribuidor\n");
    if (argc != 3){
        fprintf(stderr, "Error al llamar distribuidor, se requieren 2 parametro y se pasaron %d", argc - 1);
        return 1;
    }

    char *path_core = argv[1];
    char *path_resultados = argv[2];

    FILE *archivo = fopen(path_resultados, "w");
    if (archivo == NULL) {
        fprintf(stderr, "Error al abrir archivo en distribuidor");
        return 1;
    }

    int msgid_planificador = crear_cola_mensajes_planificador();
    char mensaje_planificador[MAX_TEXT];

    int msgid_core = crear_cola_mensajes_core();
    char mensaje_core[MAX_TEXT];

    int id_core;
    int id_proceso;
    char operacion[20];
    float numero1;
    float numero2;

    while (1) {
        recibir_mensaje_planificador(msgid_planificador, mensaje_planificador, MAX_TEXT);

        if(strcmp(mensaje_planificador, "termina") == 0){
            break;
        }

        procesar_mensaje_planificador(mensaje_planificador,
                                    &id_core,
                                    &id_proceso,
                                    operacion,
                                    &numero1,
                                    &numero2);

        ejecuta_core(path_core, id_core, id_proceso, operacion, numero1, numero2);

        recibir_mensaje_core(msgid_core, mensaje_core, MAX_TEXT);

        escribe_respuesta_archivo(archivo, mensaje_core);
    }

    cerrar_cola_mensajes(msgid_planificador);
    cerrar_cola_mensajes(msgid_core);
    fclose(archivo);

    return 0;
}