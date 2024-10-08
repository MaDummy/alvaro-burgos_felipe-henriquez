#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>

#define MAX_ARCHIVOS 1024
#define MAX_PATH 512
#define BUFFER_LINEA 2048
#define MAX_PALABRA 512
#define TAMANO_TABLA_HASH 100003

typedef struct NodoPalabra {
    char palabra[MAX_PALABRA];
    int ocurrencias;
    struct NodoPalabra *next; // Para manejar colisiones con listas enlazadas
} NodoPalabra;

typedef struct {
    NodoPalabra *tabla[TAMANO_TABLA_HASH];
    int palabrasDiferentesTabla;
} TablaHash;


/// @brief Funcion hashing para strings
/// @param str String del que se desea obtener valor hash
unsigned long hashstring(unsigned char *str);

/// @brief Cuenta las ocurrencias de cada palabra en un archivo y las guarda en un archivo txt
/// @param archivo_entrada Direccion del archivo donde se contaran las palabras
/// @param archivo_salida Direccion del archivo txt donde se guardan las ocurrencias
void contar_palabras(FILE *archivo_entrada, FILE *archivo_salida, int *palabrasDiferentes);


/// @brief Cuenta las ocurrencias de cada palabra en un archivo y las guarda en un archivo txt
/// @param archivo_entrada Direccion del archivo donde se contaran las palabras
/// @param archivo_salida Direccion del archivo txt donde se guardan las ocurrencias
void procesar_archivos(char *directorio_entrada, char *extension, char *directorio_salida, char *pathArchivosSalida[MAX_ARCHIVOS], int cantidadPalabras[MAX_ARCHIVOS], int *contadorArchivos);


#endif