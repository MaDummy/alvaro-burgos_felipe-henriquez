#ifndef UTILS_H
#define UTILS_H

/// @brief Procesa un mensaje de planificador y guarda su informacion en variables
/// @param mensaje Mensaje
/// @param id_core Identificador del core al que mandar un proceso
/// @param id_proceso Identificador del proceso
/// @param operacion Operacion a realizar
/// @param numero1 Operador 1
/// @param numero2 Operador 2 
void procesar_mensaje_planificador(char *mensaje, int *id_core, int *id_proceso, char *operacion, float *numero1, float *numero2);


/// @brief Ejecuta un core con cierta informacion
/// @param path_core Path al proceso core
/// @param id_core Identificador del core
/// @param id_proceso Identificador del proceso
/// @param operacion Operacion a realizar
/// @param numero1 Operador 1
/// @param numero2 Operador 2 
void ejecuta_core(char *path_core, int id_core, int id_proceso, char *operacion, float numero1, float numero2);


/// @brief Procesa un mensaje de core y guarda su informacion en variables
/// @param mensaje Mensaje
/// @param id_core Identifiacdor del core que envio el proceso
/// @param id_proceso Identificador del proceso
/// @param operacion Operacion realizada
/// @param numero1 Operador 1 
/// @param numero2 Operador 2
/// @param respuesta Resultado de la operacion
void procesar_mensaje_core(char *mensaje, int *id_core, int *id_proceso, char *operacion, float *numero1, float *numero2, float *respuesta);

#endif