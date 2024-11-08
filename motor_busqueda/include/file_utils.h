#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>

#define BUFFER_LINEA 2048
#define BUFFER_SIZE 1024
#define MAX_PALABRA 128
#define TAMANO_TABLA_HASH 100003

typedef struct ID_Ocurrencias {
    int ID;
    int cant_ocurrencias;
    struct ID_Ocurrencias *next; 
} ID_Ocurrencias;

typedef struct NodoPalabra {
    char palabra[MAX_PALABRA];
    ID_Ocurrencias *ocurrencias;
    struct NodoPalabra *next; 
} NodoPalabra;

typedef struct {
    NodoPalabra *tabla[TAMANO_TABLA_HASH];
    int palabrasDiferentesTabla;
} TablaHash;

typedef struct NodoInterseccion {
    int id_documento;
    int suma_ocurrencias;
    int contador;
    struct NodoInterseccion *next;
} NodoInterseccion;



/// @brief Funcion hashing para strings
/// @param str String del que se desea obtener valor hash
unsigned long hashstring(unsigned char *str);


/// @brief Toma una TablaHash inicializada e inserta las ocurrencias de un apalabra en un cierto documento
/// @param tabla TablaHash inicializada
/// @param palabra Palabra a ingresar
void insertarPalabra(TablaHash *tabla, char *palabra);


/// @brief Rellena la tabla hash con informacion del archivo index
/// @param archivo_index Archivo index abierto para lectura
/// @param tabla TablaHash inicializada
void rellenarTablaHash(FILE *archivo_index, TablaHash *tabla);


/// @brief Para una palabra, la busca en la tabla hash y actualiza la lista enlazada de intersecciones
/// @param tabla TablaHash inicializada
/// @param palabra Palabra a buscar
/// @param puntajes Lista enlazada de intersecciones
/// @param contador_interseccion Se usa para saber cuantas veces deberian aparecer los documentos de la interseccion
void buscarPalabra(TablaHash *tabla, char *palabra, NodoInterseccion **puntajes, int *contador_interseccion, int topK);


/// @brief Recibe las palabras y las busca en el hashtable, actualizando la lista enlazada puntajes
/// @param tabla TablaHash inicializada
/// @param puntajes Estructura donde se guarda interseccion de documentos con suma de ocurrencias
/// @param palabras Palabras a buscar, un string de palabras separadas por " "
void procesarPalabras(TablaHash *tabla, NodoInterseccion **puntajes, char palabras[BUFFER_SIZE], int topK);


char *formatearResultado(NodoInterseccion *puntajes, char *palabras);

#endif