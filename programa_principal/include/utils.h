#ifndef UTILS_H
#define UTILS_H

/// @brief Asigna las variables de entorno del archivo .env
void exporta_env();


/// @brief Busca al usuario en el archivo JSON.
/// @param user Usuario a buscar.
/// @param pass Contrasena del usuario.
/// @return Rol del usuario.
char *verifica_usuario(char *user, char *pass);


/// @brief Crea un vector de enteros a partir de un texto previamente validado.
/// @param vector Cadena de caracteres con enteros separados por ';'.
/// @param tamano Tamano del vector
/// @return Vector de enteros.
int *crea_vector(char *vector, int *tamano);


/// @brief Convierte el n a double.
/// @param n Numero a convertir.
/// @return n convertido a double.
double convierte_n(char *n);

#endif