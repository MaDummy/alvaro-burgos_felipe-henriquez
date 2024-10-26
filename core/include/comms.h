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

/// @brief Crea una cola de mensajes entre core y distribuidor
/// @return Identificador de la cola
int crear_cola_mensajes_distribuidor();


/// @brief Crea una cola de mensajes entre core y distribuidor
/// @return Identificador de la cola
int crear_cola_mensajes_planificador();


/// @brief Cierra una cola de mensajes
/// @param id_cola Identificador de la cola
void cerrar_cola_mensajes(int id_cola);


/// @brief Envia un mensaje a planificador con identificador del core
/// @param id_cola Identificador de la cola de mensajes
/// @param core_id Identificador del core
void enviar_mensaje_planificador(int id_cola, int core_id);


/// @brief Envia un mensaje a distribuidor con resultado de una operacion
/// @param id_cola Identifiador de la cola
/// @param core_id Identificador del core
/// @param resultado Resultado
void enviar_mensaje_distribuidor(int id_cola, int core_id, const char* resultado);

#endif