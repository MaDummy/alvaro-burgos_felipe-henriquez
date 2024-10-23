#ifndef UTILS_H
#define UTILS_H

void procesar_mensaje_planificador(char *mensaje, int *id_core, int *id_proceso, char *operacion, float *numero1, float *numero2);

void ejecuta_core(char *path_core, int id_core, int id_proceso, char *operacion, float numero1, float numero2);

void procesar_mensaje_core(char *mensaje, int *id_core, int *id_proceso, char *operacion, float *numero1, float *numero2, float *respuesta);

#endif