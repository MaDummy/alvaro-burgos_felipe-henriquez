#ifndef UTILS_H
#define UTILS_H

/// @brief Asigna las variables de entorno del archivo .env
void exporta_env();

/// @brief Remueve la extension de strings 
/// @param nombreArchivo String al cual se removera la extension
void remover_extension(char *nombreArchivo);

#endif