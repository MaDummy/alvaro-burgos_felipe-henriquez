#ifndef UTILS_H
#define UTILS_H

/// @brief Escribe el archivo con el hashmap especificado
/// @param ruta_hash Ruta del archivo en el que se escribirá
/// @param ruta_inputs Ruta del directorio que contiene los archivos de entrada
/// @param extension Extensión de los archivos a indexar
void escribe_hashmap(const char *const ruta_hash, const char *const ruta_inputs, const char *const extension);

/// @brief Valida que el directorio exista
/// @param path Ruta del archivo a validar
void validDir(char *path);

#endif