#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>

/// @brief Cuenta las ocurrencias de cada palabra en un archivo y las guarda en un archivo txt
/// @param archivo_entrada Direccion del archivo donde se contaran las palabras
/// @param archivo_salida Direccion del archivo txt donde se guardan las ocurrencias
void contar_palabras(FILE *archivo_entrada, FILE *archivo_salida);


/// @brief Cuenta las ocurrencias de cada palabra en un archivo y las guarda en un archivo txt
/// @param archivo_entrada Direccion del archivo donde se contaran las palabras
/// @param archivo_salida Direccion del archivo txt donde se guardan las ocurrencias
void procesar_archivos(const char *directorio, const char *extension, const char *directorio_salida, char *pathArchivosSalida[1024], int cantidadPalabras[1024], int *contadorArchivos);


#endif