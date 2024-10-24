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

int crear_cola_mensajes_core() {
    key_t key = ftok("progfile3", 65); 
    int msgid = msgget(key, 0666 | IPC_CREAT); 
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

int crear_cola_mensajes_distribuidor() {
    key_t key = ftok("progfile1", 75);  
    int msgid = msgget(key, 0666 | IPC_CREAT); 
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
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

void leer_mensaje_core(int id_cola, int *core_id) {
    mensaje_core msg;

    if (msgrcv(id_cola, &msg, sizeof(msg) - sizeof(long), 3, 0) == -1) {
        perror("Error al recibir mensaje de finalización desde el core");
        sleep(10);
        exit(EXIT_FAILURE);
    }

    *core_id = msg.core_id;
}

void enviar_mensaje_distribuidor(int id_cola, const char* mensaje) {
    mensaje_distribuidor msg;
    msg.mtype = 1;  
    strncpy(msg.text, mensaje, MAX_TEXT - 1);  
    msg.text[MAX_TEXT - 1] = '\0'; 


    if (msgsnd(id_cola, &msg, sizeof(msg.text), 0) == -1) {
        perror("Error al enviar mensaje a distribuidor");
        exit(EXIT_FAILURE);
    }
}