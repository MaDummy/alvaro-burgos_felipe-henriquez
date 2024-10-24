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

int crear_cola_mensajes_planificador() {
    key_t key = ftok("progfile1", 75);  
    int msgid = msgget(key, 0666 | IPC_CREAT); 
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

int crear_cola_mensajes_core() {
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

void recibir_mensaje_planificador(int id_cola, char *buffer, int buffer_size) {
    mensaje_planificador msg;
    memset(buffer, 0, buffer_size);  

    if (msgrcv(id_cola, &msg, sizeof(msg.text), 1, 0) == -1) {
        perror("Error al recibir mensaje desde planificador");
        exit(EXIT_FAILURE);
    }

    strncpy(buffer, msg.text, buffer_size);  
}

void recibir_mensaje_core(int id_cola, char *buffer, int buffer_size) {
    mensaje_core_distribuidor msg;
    memset(buffer, 0, buffer_size);  

    if (msgrcv(id_cola, &msg, MAX_TEXT, 2, 0) == -1) {
        perror("Error al recibir mensaje desde un Core en el Distribuidor");
        exit(EXIT_FAILURE);
    }

    strncpy(buffer, msg.text, buffer_size);  
}

