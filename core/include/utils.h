#ifndef UTILS_H
#define UTILS_H

#define MAX_LARGO_PROCESO 512

/// @brief Crea un mensaje y lo guarda en mensaje
/// @param mensaje String donde guardar el mensaje
/// @param id_core Identificador del core
/// @param id_proceso Identificador del proceso
/// @param operacion Operacion realizada
/// @param argumento1 Operador 1
/// @param argumento2 Operador 2
/// @param resultado Resultado de la operacion
void crea_mensaje(char mensaje[MAX_LARGO_PROCESO], 
                int id_core, 
                int id_proceso,
                char *operacion, 
                float argumento1,
                float argumento2,
                float resultado);

#endif