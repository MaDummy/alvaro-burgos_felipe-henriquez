#ifndef UTILS_H
#define UTILS_H

/// @brief Quita la extension de un archivo
/// @param nombreArchivo 
void quita_extension(char *nombreArchivo);

/// @brief Funcion hash a un string
/// @param str String al que se le aplica la funcion
/// @return Hash
unsigned long hash(unsigned char *str);

#endif