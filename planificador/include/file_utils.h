#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#define MAX_PROCESOS 100000
#define MAX_PATH 512
#define BUFFER_LINEA 2048
#define MAX_LARGO_PROCESO 512

/// @brief Funcion para leer un archivo de procesos y guardarlos en un array
/// @param path_procesos Path al archivo con procesos
/// @param array_procesos Array que guarda los procesos como strings
/// @param cont Entero que guarda la cantidad de procesos
void leeProcesos(char *path_procesos, char **array_procesos, int *cont);

#endif