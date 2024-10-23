#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../include/file_utils.h"
#include "../include/operaciones.h"
#include "../include/utils.h"

#define MAX_TEXT 512


typedef struct {
    long mtype;  // Tipo de mensaje.
    int core_id;  // Identificador del core que envía el mensaje.
} mensaje_planificador;

typedef struct {
    long mtype;             // Tipo de mensaje
    char resultado[MAX_TEXT]; // Resultado de la operación
} mensaje_distribuidor;

int crear_cola_mensajes_distribuidor();
int crear_cola_mensajes_planificador();
void enviar_mensaje_planificador(int id_cola, int core_id);

//./main id_core id_proceso operacion argumento1 argumento2
int main(int argc, char **argv){
    if (argc != 6){
        fprintf(stderr, "Error al llamar indice_invertido, se requieren 5 parametro y se pasaron %d", argc - 1);
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

    enviar_mensaje_core_a_distribuidor(msgid_distribuidor, id_core, mensaje_resultado);

    enviar_mensaje_planificador(msgid_planificador, id_core);

}


int crear_cola_mensajes_planificador() {
    key_t key = ftok("progfile", 65); // Genera una clave única
    int msgid = msgget(key, 0666 | IPC_CREAT); // Crea la cola de mensajes
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

int crear_cola_mensajes_distribuidor() {
    key_t key = ftok("progfile_core", 66); // Genera una clave única para la cola entre Cores y Distribuidor
    int msgid = msgget(key, 0666 | IPC_CREAT); // Crea la cola de mensajes
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes Core-Distribuidor");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

void enviar_mensaje_planificador(int id_cola, int core_id) {
    mensaje_planificador msg;
    msg.mtype = 2;  // Un tipo genérico para mensajes de finalización.
    msg.core_id = core_id;  // Identificador del core que ha terminado.

    if (msgsnd(id_cola, &msg, sizeof(mensaje_planificador) - sizeof(long), 0) == -1) {
        perror("Error al enviar mensaje de finalización a planificador");
        exit(EXIT_FAILURE);
    }
}

void enviar_mensaje_core_a_distribuidor(int id_cola, int core_id, const char* resultado) {
    mensaje_distribuidor msg;
    msg.mtype = 3; // Tipo genérico para mensajes de "Core"
    strncpy(msg.resultado, resultado, MAX_TEXT - 1); // Copia el resultado al mensaje
    msg.resultado[MAX_TEXT - 1] = '\0'; // Asegura terminación del string

    if (msgsnd(id_cola, &msg, sizeof(mensaje_distribuidor) - sizeof(long), 0) == -1) {
        perror("Error al enviar mensaje desde Core a Distribuidor");
        exit(EXIT_FAILURE);
    }
}