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
/// @param directorioEntrada 
/// @param extension 
/// @param directorioSalida 
/// @param pathArchivosSalida 
/// @param cantidadPalabras 
/// @param contadorArchivos 
/// @param MAX_THREADS
void procesar_archivos_paralelo(const char *const directorioEntrada, const char *const extension, const char *const directorioSalida, char *pathArchivosSalida[MAX_ARCHIVOS], int cantidadPalabras[MAX_ARCHIVOS], int *contadorArchivos, const int MAX_THREADS);

/// @brief Funcion que llama 
/// @param directorioEntrada 
/// @param extension 
/// @param directorioSalida 
/// @param MAX_THREADS
void procesamiento_archivos(const char *const directorioEntrada, const char *const extension, const char *const directorioSalida, const int MAX_THREADS);

#endif