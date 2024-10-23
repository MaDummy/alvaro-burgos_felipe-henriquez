#ifndef UTILS_H
#define UTILS_H

#include "file_utils.h"

void crea_mensaje(int id_core, char proceso[MAX_LARGO_PROCESO], char mensaje[MAX_LARGO_PROCESO]);

void ejecuta_distribuidor(char *path_distribuidor, char *path_core, char *path_resultados);

#endif