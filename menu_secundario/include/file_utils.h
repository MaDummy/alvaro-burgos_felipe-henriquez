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
    struct NodoPalabra *next; 
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
/// @param palabrasDiferentes puntero a entero que guarda cuantas palabras diferentes se encontraron en el archivo
void contar_palabras(FILE *archivo_entrada, FILE *archivo_salida, int *palabrasDiferentes);


/// @brief Cuenta las ocurrencias de cada palabra en un archivo y las guarda en un archivo txt
/// @param archivo_entrada Direccion del archivo donde se contaran las palabras
/// @param extension Extension de los archivos que se revisaran
/// @param archivo_salida Direccion del archivo txt donde se guardan las ocurrencias
/// @param pathArchivosSalida Arreglo que guarda los path donde se escribieron los resultados
/// @param cantidadPalabras Arreglo que guarda cantidad de palabras unicas para elementos de pathArchivosSalida de mismo indice
/// @param contadorArchivos Puntero a entero que guarda sobre cuantos archivos se conto palabras
void procesar_archivos(char *directorio_entrada, char *extension, char *directorio_salida, char *pathArchivosSalida[MAX_ARCHIVOS], int cantidadPalabras[MAX_ARCHIVOS], int *contadorArchivos);


#endif