#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/// @brief Valida el usuario segun los criterios de la pauta.
/// @param user Usuario a validar.
void validUser(char *user);


/// @brief Valida la contrasena del usuario segun los criterios de la pauta.
/// @param user Usuario de quien es la contrasena
/// @param password Contrasena a validar.
void validPass(char *user, char *password);


/// @brief Valida el texto ingresado.
/// @param text Texto ingresado.
void validText(char *text);


/// @brief Valida que el vector este ingresado correctamente, con ';' entre numeros enteros.
/// @param vector Texto que contiene al vector.
void validVector(char *vector);


/// @brief Valida el n ingresado.
/// @param n Texto que tiene al n.
void validN(char *n);

#endif