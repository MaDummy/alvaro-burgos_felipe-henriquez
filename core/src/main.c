#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../include/file_utils.h"
#include "../include/operaciones.h"
#include "../include/utils.h"
#include "../include/comms.h"

//./main id_core id_proceso operacion argumento1 argumento2
int main(int argc, char **argv){
    if (argc != 6){
        fprintf(stderr, "Error al llamar core, se requieren 5 parametro y se pasaron %d", argc - 1);
    }

    int id_core = atoi(argv[1]);
    int id_proceso = atoi(argv[2]);
    char *operacion = argv[3];
    float argumento1 = atof(argv[4]);
    float argumento2 = atof(argv[5]);

    int msgid_planificador = crear_cola_mensajes_planificador();

    int msgid_distribuidor = crear_cola_mensajes_distribuidor();

    float resultado = obten_resultado(operacion, argumento1, argumento2);

    char mensaje_resultado[MAX_LARGO_PROCESO];

    crea_mensaje(mensaje_resultado, id_core, id_proceso, operacion, argumento1, argumento2, resultado);

    enviar_mensaje_distribuidor(msgid_distribuidor, id_core, mensaje_resultado);

    enviar_mensaje_planificador(msgid_planificador, id_core);


    return 0;

}


