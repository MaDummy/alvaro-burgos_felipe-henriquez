#ifndef MENU_H
#define MENU_H

/// @brief Funcion principal. Despliega un menu con 6 opciones.
/// @param texto Texto ingresado al ejecutar.
/// @param vector Vector de enteros.
/// @param tamano Tamano del vector.
/// @param n N ingresado al ejecutar.
void menu(char *texto, int *vector, int tamano, double n);


/// @brief Opciones para volver al menu principal o salir.
void regresa_menu();

#endif