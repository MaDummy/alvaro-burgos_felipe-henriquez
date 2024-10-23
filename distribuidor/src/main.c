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


#define MAX_TEXT 512

typedef struct {
    long mtype;             
    char text[MAX_TEXT];    
} mensaje_planificador;

typedef struct {
    long mtype;             
    char text[MAX_TEXT];
} mensaje_core;


int crear_cola_mensajes_planificador();
int crear_cola_mensajes_core();
void recibir_mensaje_planificador(int id_cola, char* buffer, int buffer_size);
void recibir_mensaje_core(int id_cola, char* buffer, int buffer_size);

//./main path_programa_core path_resultados
int main(int argc, char **argv) {
    if (argc != 3){
        fprintf(stderr, "Error al llamar indice_invertido, se requieren 2 parametro y se pasaron %d", argc - 1);
        return;
    }

    char *path_core = argv[1];
    char *path_resutlados = argv[2];

    FILE *archivo = fopen(path_resutlados, "w");
    if (archivo == NULL) {
        fprintf(stderr, "Error al llamar indice_invertido, se requieren 2 parametro y se pasaron %d", argc - 1);
        return;
    }


    int msgid_planificador = crear_cola_mensajes_planificador();
    char *mensaje_planificador[MAX_TEXT];

    int msgid_core = crear_cola_mensajes_core();
    char *mensaje_core[MAX_TEXT];

    int id_core;
    int id_proceso;
    char *operacion;
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

    fclose(archivo);

    return 0;
}

int crear_cola_mensajes_planificador() {
    key_t key = ftok("progfile", 75);  // Genera una clave única
    int msgid = msgget(key, 0666 | IPC_CREAT); // Crea la cola de mensajes
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

int crear_cola_mensajes_core() {
    key_t key = ftok("progfile_core", 66); // Genera una clave única para la cola entre Cores y Distribuidor
    int msgid = msgget(key, 0666 | IPC_CREAT); // Crea la cola de mensajes
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes Core-Distribuidor");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

void recibir_mensaje_planificador(int id_cola, char *buffer, int buffer_size) {
    mensaje_planificador msg;
    memset(buffer, 0, buffer_size);  // Inicializa el buffer

    // Recibe el mensaje de la cola (mtype = 1)
    if (msgrcv(id_cola, &msg, sizeof(msg.text), 1, 0) == -1) {
        perror("Error al recibir mensaje desde planificador");
        exit(EXIT_FAILURE);
    }

    // Copia el contenido del mensaje al buffer proporcionado
    strncpy(buffer, msg.text, buffer_size);  // Solo contenido
}

void recibir_mensaje_core(int id_cola, char *buffer, int buffer_size) {
    mensaje_core msg;
    memset(buffer, 0, buffer_size);  // Inicializa el buffer

    // Recibe el mensaje de los "Cores"
    if (msgrcv(id_cola, &msg, sizeof(msg.text), 3, 0) == -1) {
        perror("Error al recibir mensaje desde un Core en el Distribuidor");
        exit(EXIT_FAILURE);
    }

    // Copia el contenido del mensaje al buffer proporcionado
    strncpy(buffer, msg.text, buffer_size);  
}