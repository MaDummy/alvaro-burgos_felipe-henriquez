#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>

#define MAX_ARCHIVOS 1024
#define MAX_PATH 512
#define MAX_NOM_ARCHIVO 512
#define BUFFER_LINEA 2048
#define MAX_PALABRA 512
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


/// @brief Funcion hashing para strings
/// @param str String del que se desea obtener valor hash
unsigned long hashstring(unsigned char *str);


/// @brief Funcion que lee mapa_archivos y guarda su informacion en dos arrays
/// @param mapa_archivos_path Path a mapa_archivos
/// @param nombre_archivos Array que contendra los nombre de archivos de mapa_archivos
/// @param ids Array que guarda los id de los archivos de nombre_archivos de respectivo indice
/// @param cantidad_archivos Puntero a un entero que guarda la cantidad de archivos leidos
void leerMapaArchivos(char *mapa_archivos_path, char nombres_archivos[MAX_ARCHIVOS][MAX_NOM_ARCHIVO], int ids[MAX_ARCHIVOS], int *cantidad_archivos);


/// @brief Toma una TablaHash inicializada e inserta las ocurrencias de un apalabra en un cierto documento
/// @param tabla TablaHash inicializada
/// @param palabra Palabra a ingresar
/// @param cant_ocurrencias Cuantas veces aparece en el documento
/// @param ID_Documento ID del documento
void insertarPalabra(TablaHash *tabla, char *palabra, int cant_ocurrencias, int ID_Documento);


/// @brief Funcion que crea una TablaHash en base de los archivos de output y mapa_archivos dados
/// @param tabla TablaHash inicializada
/// @param path_output Path donde estan los archivos output a procesar
/// @param extension Extension de los archivos output
/// @param nombres_archivos Array de string con nombres de los archivos
/// @param ids Array de enteros que corresponden a los nombres_archivos
/// @param cantidad_archivos Cantidad de archivos a procesar
void procesarArchivosOutput(TablaHash *tabla, char *path_output, char *extension, char nombres_archivos[MAX_ARCHIVOS][MAX_PATH], int ids[MAX_ARCHIVOS], int cantidad_archivos);


/// @brief Escribe los contenidos de la TablaHash en el archivo dado
/// @param inverted_index_path Path al archivo INDEX donde se guardara informacion
/// @param tabla TablaHash previamente llenada
void escribirIndiceInvertido(char *inverted_index_path, TablaHash *tabla);



#endif