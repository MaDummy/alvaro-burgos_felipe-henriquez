#ifndef STOPWORDS_H
#define STOPWORDS_H

#include <semaphore.h>
#include <pthread.h>

extern sem_t semaphore;
extern pthread_mutex_t file_mutex;

/// @brief Escribe el archivo con el hashmap especificado
/// @param ruta_hash Ruta del archivo en el que se escribirá
/// @param ruta_inputs Ruta del directorio que contiene los archivos de entrada
/// @param extension Extensión de los archivos a indexar
void escribe_hashmap(const char *const ruta_hash, const char *const ruta_inputs, const char *const extension);

/// @brief Función que filtra un texto con las stopwords creando un archivo temporal
/// @param arg Puntero a una estructura con parametros ruta_tests, stopwords y ruta_copia
void *filtra_stopword(void *arg);

/// @brief Funcion que crea un array de stopwords
/// @param path_stopwords Path donde se encuentran las stopwords
/// @return Arreglo con stopwords
char **crea_arr_stopwords(const char *const path_stopwords);

/// @brief Escribe una copia del archivo en una ruta distinta
/// @param ruta_orig Ruta original del archivo que se busca copiar
/// @param path_copys Ruta donde se busca guardar la copia del archivo
char *escribe_copia(const char *const ruta_orig, const char *const path_copys);

/// @brief Realiza en paralelo la filtracion de archivos con stopwords
/// @param ruta_inputs Ruta de tests/archivos
/// @param stopwords Array de stopwords
/// @param path_copys Ruta donde se almacenaran las copias
/// @param MAX_THREADS Threads maximos a utilizar
/// @param extension Extension de los archivos a filtrar
void filtra_stopwords_threads(const char *const ruta_inputs, char **stopwords, const char *const path_copys, const int MAX_THREADS, const char *const extension);

#endif