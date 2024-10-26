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

/// @brief Crea cola de mensajes entre distribuidor y planificador
/// @return Identifiacdor de la cola
int crear_cola_mensajes_planificador();


/// @brief Crea cola de mensajes entre distribuidor y core
/// @return Identificador de la cola
int crear_cola_mensajes_core();

/// @brief Cierra la cola de mensajes
/// @return Identificador de la cola
void cerrar_cola_mensajes(int id_cola);


/// @brief Lee un mensaje de la cola de mensajes con planificador y lo guarda en un buffer
/// @param id_cola Identificador de la cola
/// @param buffer String donde guardar el mensaje
/// @param buffer_size Tamano del buffer
void recibir_mensaje_planificador(int id_cola, char* buffer, int buffer_size);


/// @brief Lee un mensaje de la cola de mensajes con core y lo guarda en un buffer
/// @param id_cola Identificador
/// @param buffer String donde guardar el mensaje
/// @param buffer_size Tamano del buffer
void recibir_mensaje_core(int id_cola, char* buffer, int buffer_size);

#endif