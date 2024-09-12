#ifndef OPCIONES_H
#define OPCIONES_H

/// @brief Imprime un vector
/// @param vector Vector de enteros
/// @param tamano Tamano del vector
void imprime_vector(int *vector, int tamano);


/// @brief Crea un vector de enteros a partir de un texto previamente validado.
/// @param vector Cadena de caracteres con enteros separados por ';'.
/// @param tamano Tamano del vector
/// @return Vector de enteros.
int *crea_vector(char *vector, int *tamano);


/// @brief Opcion 4: Suma y promedio de un vector.
/// @param vector Vector de enteros
/// @param tamano Tamano del vector
void suma_promedio_vector(int *vector, int tamano);


/// @brief Opcion 1: Verifica si un texto es o no palindromo.
/// @param text Texto a chequear.
void es_palindromo(char *text);


/// @brief Opcion 2: Cuenta las vocales de un texto.
/// @param text Texto a chequear.
void cuenta_vocales(char *text);


/// @brief Opcion 1: Cuenta las letras de un texto.
/// @param text Texto a chequear.
void cuenta_letras(char *text);


/// @brief Opcion 5: Funcion lineal sobre n.
/// @param n Numero entero o flotante.
void funcion_lineal(double n);


/// @brief Opcion 6 (admin): Añade un usuario a la base de datos
void anade_usuario();


/// @brief Opcion 7 (admin): Lista los usuarios registrados en la base de datos.
void listar_usuarios();


/// @brief Opcion 8 (admin): Elimina a un usuario con el rol "generico"
void elimina_usuario();

#endif