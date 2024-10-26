#ifndef UTILS_H
#define UTILS_H

#include "file_utils.h"


/// @brief Crea un mensaje (id_core:proceso)y lo guarda en mensaje
/// @param id_core Id del core al que enviar el proceso
/// @param proceso Proceso
/// @param mensaje String para guardar el mensaje
void crea_mensaje(int id_core, char proceso[MAX_LARGO_PROCESO], char mensaje[MAX_LARGO_PROCESO]);


/// @brief Ejecuta el proceso distribuidor en paralelo
/// @param path_distribuidor Path del proceso distribuidor
/// @param path_core Path del proceso core
/// @param path_resultados Path del archivo de resultados
void ejecuta_distribuidor(char *path_distribuidor, char *path_core, char *path_resultados);

#endif