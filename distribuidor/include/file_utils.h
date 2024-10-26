#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#define MAX_PROCESOS 100000
#define MAX_PATH 512
#define BUFFER_LINEA 2048
#define MAX_LARGO_PROCESO 512

/// @brief Toma una respuesta, cambia su formato y la guarda en un archivo
/// @param archivo Puntero al archivo 
/// @param respuesta Respuesta
void escribe_respuesta_archivo(FILE *archivo, char *respuesta);

#endif