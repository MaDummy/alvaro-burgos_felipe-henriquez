#ifndef COMMS_H
#define COMMS_H

#define MAX_TEXT 512

typedef struct {
    long mtype;  // Tipo de mensaje.
    int core_id;  // Identificador del core que envía el mensaje.
} mensaje_planificador;

typedef struct {
    long mtype;             
    char text[MAX_TEXT];
} mensaje_core_distribuidor;

int crear_cola_mensajes_distribuidor();

int crear_cola_mensajes_planificador();

void cerrar_cola_mensajes(int id_cola);

void enviar_mensaje_planificador(int id_cola, int core_id);

void enviar_mensaje_distribuidor(int id_cola, int core_id, const char* resultado);

#endif