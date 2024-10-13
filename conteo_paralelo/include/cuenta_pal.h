#ifndef CUENTA_PAL_H
#define CUENTA_PAL_H
#include <stdio.h>

#define MAX_ARCHIVOS 1024
#define MAX_PATH 512
#define BUFFER_LINEA 2048
#define MAX_PALABRA 512
#define TAMANO_TABLA_HASH 100003

/// @brief Funcion principal que cuenta palabras
/// @param archivoEntrada Archivo al que se le contaran las palabras
/// @param archivoSalida Archivo que sale de contar las palabras
/// @param palabrasDiferentes Cantidad de palabras diferentes
void contar_palabras(FILE *archivoEntrada, FILE *archivoSalida, int *palabrasDiferentes);

/// @brief Funcion principal que procesa los archivos de forma paralela
/// @param directorioEntrada Directorio en el cual se procesaran los archivos
/// @param extension Extension de los archivos a procesar
/// @param directorioSalida Directorio en donde saldran los output de los archivos procesados
/// @param pathArchivosSalida Puntero que apunta al path de los archivos de salida
/// @param cantidadPalabras Puntero que apunta a la cantidad de palabras
/// @param contadorArchivos Puntero que cuenta los archivos
/// @param MAX_THREADS Cantidad maxima de threads activos
void procesar_archivos_paralelo(const char *const directorioEntrada, const char *const extension, const char *const directorioSalida, char *pathArchivosSalida[MAX_ARCHIVOS], int cantidadPalabras[MAX_ARCHIVOS], int *contadorArchivos, const int MAX_THREADS);

/// @brief Funcion que llama a procesar_archivos_paralelo
/// @param directorioEntrada Directorio en donde se procesaran los archivos
/// @param extension Extension de los archivos a procesar
/// @param directorioSalida Directorio en donde saldran los output de los archivos procesados
/// @param MAX_THREADS Cantidad maxima de threads activos
void procesamiento_archivos(const char *const directorioEntrada, const char *const extension, const char *const directorioSalida, const int MAX_THREADS);

#endif