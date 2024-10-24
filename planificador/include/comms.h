#ifndef COMMS_H
#define COMMS_H

#define MAX_TEXT 512

typedef struct {
    long mtype;  // Tipo de mensaje.
    int core_id;  // Identificador del core que envía el mensaje.
} mensaje_core;

typedef struct {
    long mtype;             
    char text[MAX_TEXT];    
} mensaje_distribuidor;

int crear_cola_mensajes_core();

int crear_cola_mensajes_distribuidor();

void cerrar_cola_mensajes(int id_cola);

void leer_mensaje_core(int id_cola, int *core_id);

void enviar_mensaje_distribuidor(int id_cola, const char* mensaje);

#endif