#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../include/utils.h"
#include "../include/menu.h"
#include "../include/comms.h"

int crear_cola_mensajes_planificador() {
    key_t key = ftok("progfile3", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT); 
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

int crear_cola_mensajes_distribuidor() {
    key_t key = ftok("progfile2", 66);
    int msgid = msgget(key, 0666 | IPC_CREAT); 
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes Core-Distribuidor");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

void cerrar_cola_mensajes(int id_cola) {
    if (msgctl(id_cola, IPC_RMID, NULL) == -1) {
        perror("Error al cerrar la cola de mensajes");
        exit(EXIT_FAILURE);
    }
}

void enviar_mensaje_planificador(int id_cola, int core_id) {
    mensaje_planificador msg;
    msg.mtype = 3; 
    msg.core_id = core_id; 

    if (msgsnd(id_cola, &msg, sizeof(mensaje_planificador) - sizeof(long), 0) == -1) {
        perror("Error al enviar mensaje de finalización a planificador");
        exit(EXIT_FAILURE);
    }
}

void enviar_mensaje_distribuidor(int id_cola, int core_id, const char* resultado) {
    mensaje_core_distribuidor msg;
    msg.mtype = 2; 
    strncpy(msg.text, resultado, MAX_TEXT - 1); 
    msg.text[MAX_TEXT - 1] = '\0';

    if (msgsnd(id_cola, &msg, MAX_TEXT, 0) == -1) {
        perror("Error al enviar mensaje desde Core a Distribuidor");
        exit(EXIT_FAILURE);
    }
}