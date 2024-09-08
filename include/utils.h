#ifndef UTILS_H
#define UTILS_H

/// @brief Asigna las variables de entorno del archivo .env
void exporta_env();


/// @brief Busca al usuario entre las variables de entorno
/// @param user Usuario a buscar.
/// @return "Indice" del usuario en la variable de entorno que lo contiene.
int busca_usuario_env(char *user);


/// @brief Verifica la contrasena del usuario en las variables de entorno.
/// @param password Contrasena a verificar.
/// @param indice Indice de la contrasena en la variable de entorno que la contiene.
void verifica_contrasena_env(char *password, int indice);
double convierte_n(char *n);

#endif