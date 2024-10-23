#ifndef UTILS_H
#define UTILS_H
#include "file_utils.h"

void crea_mensaje(char mensaje[MAX_LARGO_PROCESO], 
                int id_core, 
                int id_proceso,
                char *operacion, 
                float argumento1,
                float argumento2,
                float resultado);

#endif