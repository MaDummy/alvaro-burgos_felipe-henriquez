#include "../include/file_utils.h"

void crea_mensaje(char mensaje[MAX_LARGO_PROCESO], 
                int id_core, 
                int id_proceso,
                char *operacion, 
                float argumento1,
                float argumento2,
                float resultado){
                    
    snprintf(mensaje, MAX_LARGO_PROCESO, "%d:%d;%s;%f,%f,%f", id_core,
                                                            id_proceso,
                                                            operacion,
                                                            argumento1,
                                                            argumento2,
                                                            resultado);
}