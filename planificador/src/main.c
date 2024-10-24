#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../include/file_utils.h"
#include "../include/utils.h"
#include "../include/menu.h"
#include "../include/comms.h"

//main path_procesos cant_cores path_resultados path_distribuidor path_cores
int main(int argc, char **argv){
    if (argc != 6){
        fprintf(stderr, "Error al llamar planificador, se requieren 5 parametro y se pasaron %d", argc - 1);
    }

    char *process_path = argv[1];
    int cant_cores = atoi(argv[2]);
    char *resultados_path = argv[3];
    char *path_distribuidor = argv[4];
    char *path_core = argv[5];

    ejecuta_distribuidor(path_distribuidor, path_core, resultados_path);

    char **array_procesos = malloc(MAX_PROCESOS * sizeof(char *));
    for (int i = 0; i < MAX_PROCESOS; i++) {
        array_procesos[i] = malloc(MAX_LARGO_PROCESO * sizeof(char));
    }
    int cont = 0;

    leeProcesos(process_path, array_procesos, &cont);

    int *cores_disponibles = malloc(cant_cores * sizeof(int));

    //0 = disponible
    //1 = ocupado
    for (int i = 0; i < cant_cores; i++) {
        cores_disponibles[i] = 1;  
    }

    int msgid_core = crear_cola_mensajes_core();
    int msgid_distribuidor = crear_cola_mensajes_distribuidor();

    int id_core;
    char mensaje_para_distribuidor[MAX_TEXT];

    //Usa todos los core por primera vez antes de el flujo dinamico entre todos los procesos
    for(int i = 0; i < cant_cores; i++){
        cores_disponibles[i] = 0;
        crea_mensaje(i, array_procesos[i], mensaje_para_distribuidor);
        enviar_mensaje_distribuidor(msgid_distribuidor, mensaje_para_distribuidor);
        cores_disponibles[i] = 1;
    }


    //Muere si tenemos mas core que procesos, lo arreglo despues
    for(int i = cant_cores; i < cont; i++){
        leer_mensaje_core(msgid_core, &id_core);
        cores_disponibles[id_core] = 0;

        crea_mensaje(id_core, array_procesos[i], mensaje_para_distribuidor);

        enviar_mensaje_distribuidor(msgid_distribuidor, mensaje_para_distribuidor);
        cores_disponibles[id_core] = 1;
    }

    for (int i = 0; i < MAX_PROCESOS; i++) {
        free(array_procesos[i]);
    }
    free(array_procesos);
    free(cores_disponibles);
    enviar_mensaje_distribuidor(msgid_distribuidor,"termina");
    cerrar_cola_mensajes(msgid_distribuidor);
    cerrar_cola_mensajes(msgid_core);
    mensaje(resultados_path);

    return 0;

}


