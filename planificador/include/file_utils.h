#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#define MAX_PROCESOS 100000
#define MAX_PATH 512
#define BUFFER_LINEA 2048
#define MAX_LARGO_PROCESO 512

void leeProcesos(char *path_procesos, char **array_procesos, int *cont);

#endif