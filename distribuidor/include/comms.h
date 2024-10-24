#ifndef COMMS_H
#define COMMS_H

#define MAX_TEXT 512

typedef struct {
    long mtype;             
    char text[MAX_TEXT];    
} mensaje_planificador;

typedef struct {
    long mtype;             
    char text[MAX_TEXT];
} mensaje_core_distribuidor;

int crear_cola_mensajes_planificador();

int crear_cola_mensajes_core();

void cerrar_cola_mensajes(int id_cola);

void recibir_mensaje_planificador(int id_cola, char* buffer, int buffer_size);

void recibir_mensaje_core(int id_cola, char* buffer, int buffer_size);

#endif