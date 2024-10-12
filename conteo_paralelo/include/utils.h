#ifndef UTILS_H
#define UTILS_H

/// @brief Escribe el archivo con el hashmap especificado
/// @param ruta_hash Ruta del archivo en el que se escribirá
/// @param ruta_inputs Ruta del directorio que contiene los archivos de entrada
/// @param extension Extensión de los archivos a indexar
void escribe_hashmap(const char *const ruta_hash, const char *const ruta_inputs, const char *const extension);

/// @brief Función hash
/// @param str Texto al que se le aplicará la función
/// @return Función hash del texto
unsigned long hash(unsigned char *str);

/// @brief Función que filtra un texto con las stopwords creando un archivo temporal
/// @param texto 
/// @param stopwords 
void filtra_stopword(const char *const texto, const char *const stopwords, const char *const path_copys);

/// @brief Funcion que crea un array de stopwords
/// @param path_stopwords Path donde se encuentran las stopwords
/// @return Arreglo con stopwords
char **crea_arr_stopwords(const char *const path_stopwords);

/// @brief Escribe una copia del archivo en una ruta distinta
/// @param ruta_orig Ruta original del archivo que se busca copiar
/// @param path_copys Ruta donde se busca guardar la copia del archivo
char *escribe_copia(const char *const ruta_orig, const char *const path_copys);

#endif