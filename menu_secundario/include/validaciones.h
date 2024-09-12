#ifndef VALIDACIONES_H
#define VALIDACIONES_H


/// @brief Valida la extension ingresada
/// @param extension Texto con la extension
void validExtention(char *extension);


/// @brief Valida el directorio ingresado
/// @param path Ruta al directorio
void validDir(char *path);


/// @brief Valida que el directorio tenga archivos con la extension dada
/// @param path Ruta al directorio
/// @param extention Texto con la extension
void validDirWithExtention(char *path, char *extention);

#endif