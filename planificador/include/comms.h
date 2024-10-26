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


/// @brief Funcion para iniciar una cola de mensajes entre planificador y core
/// @return El identificador de la cola
int crear_cola_mensajes_core();


/// @brief Funcion para iniciar una cola de mensajes entre planificador y distribuidor
/// @return El identificador de la cola
int crear_cola_mensajes_distribuidor();


/// @brief Funcion para cerrar una cola de mensajes
/// @param id_cola Identificador de la cola
void cerrar_cola_mensajes(int id_cola);


/// @brief Funcion para leer un mensaje proveniente de una cola de mensajes con core
/// @param id_cola Identificador de la cola
/// @param core_id Entero donde guardar el identificador del core
void leer_mensaje_core(int id_cola, int *core_id);


/// @brief Funcion para leer un mensaje proveniente de una cola de mensajes con distribuidor
/// @param id_cola Identificador de la cola
/// @param mensaje String donde guardar el mensaje
void enviar_mensaje_distribuidor(int id_cola, const char* mensaje);

#endif