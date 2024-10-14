#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/utils.h"
#include "../include/file_utils.h"
#include <unistd.h>

unsigned long hashstring(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TAMANO_TABLA_HASH;
}


void leerMapaArchivos(char *mapa_archivos_path, char nombres_archivos[MAX_ARCHIVOS][MAX_NOM_ARCHIVO], int ids[MAX_ARCHIVOS], int *cantidad_archivos) {
    FILE *file = fopen(mapa_archivos_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: No se puede abrir %s\n", mapa_archivos_path);
        exit(EXIT_FAILURE);
    }

    *cantidad_archivos = 0;

    char line[BUFFER_LINEA];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // Quitar el salto de línea

        char *token = strtok(line, ",");  // Usamos solo la coma como delimitador
        if (token != NULL) {
            // Eliminar espacios al inicio y fin del nombre
            while (*token == ' ') token++;
            strncpy(nombres_archivos[*cantidad_archivos], token, MAX_NOM_ARCHIVO - 1);
            nombres_archivos[*cantidad_archivos][MAX_NOM_ARCHIVO - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            while (*token == ' ') token++;  // Eliminar espacios antes del ID
            ids[*cantidad_archivos] = atoi(token);  // Convertir ID a entero
        } else {
            ids[*cantidad_archivos] = -1;  // En caso de que no haya un ID válido
        }

        (*cantidad_archivos)++;
    }

    fclose(file);
} 


void insertarPalabra(TablaHash *tabla, char *palabra, int cant_ocurrencias, int ID_Documento) {
    unsigned long indice = hashstring((unsigned char *)palabra);
    NodoPalabra *nodo = tabla->tabla[indice];

    ID_Ocurrencias *nuevo = malloc(sizeof(ID_Ocurrencias));
    nuevo->cant_ocurrencias = cant_ocurrencias;
    nuevo->ID = ID_Documento;
    nuevo->next = NULL;


    while (nodo != NULL) {
        if (strcmp(nodo->palabra, palabra) == 0) {
            ID_Ocurrencias *ocurrencia = nodo->ocurrencias;

            while (ocurrencia->next != NULL && ocurrencia->next->ID < ID_Documento){
                ocurrencia = ocurrencia->next;
            }

            nuevo->next = ocurrencia->next;
            ocurrencia->next = nuevo;

            return;
        }
        nodo = nodo->next;
    }

    NodoPalabra *nuevoNodo = malloc(sizeof(NodoPalabra));
    strcpy(nuevoNodo->palabra, palabra);
    nuevoNodo->ocurrencias = nuevo;
    nuevoNodo->next = tabla->tabla[indice];
    tabla->tabla[indice] = nuevoNodo;
    tabla->palabrasDiferentesTabla++;
}


void procesarArchivosOutput(TablaHash *tabla, char *path_output, char *extension, char nombres_archivos[MAX_ARCHIVOS][MAX_PATH], int ids[MAX_ARCHIVOS], int cantidad_archivos) {
    char file_path[MAX_PATH];
    char palabra[MAX_PALABRA];
    int ocurrencias;

    for (int i = 0; i < cantidad_archivos; i++) {
        snprintf(file_path, sizeof(file_path), "%s/%d%s", path_output, ids[i], extension);

        FILE *file = fopen(file_path, "r");
        if (file == NULL) {
        fprintf(stderr, "Error: no se puede abrir %s\n", file_path);
        exit(EXIT_FAILURE);
    }

        char line[BUFFER_LINEA];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';

            char *token = strtok(line, "; ");
            if (token != NULL) {
                strncpy(palabra, token, MAX_PALABRA - 1);
                palabra[MAX_PALABRA - 1] = '\0';
            }

            token = strtok(NULL, "; ");
            if (token != NULL) {
                ocurrencias = atoi(token); 
            }

            insertarPalabra(tabla, palabra, ocurrencias, ids[i]);
        }

        fclose(file);
    }
}


void escribirIndiceInvertido(char *inverted_index_path, TablaHash *tabla) {
    FILE *file = fopen(inverted_index_path, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: no se puede abrir %s\n", inverted_index_path);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < TAMANO_TABLA_HASH; i++) {
        char linea[BUFFER_LINEA] = {0};
        NodoPalabra *nodo = tabla->tabla[i];
        while (nodo != NULL) {
            strcpy(linea,nodo->palabra);

            ID_Ocurrencias *ocurrencia = nodo->ocurrencias;
            while(ocurrencia != NULL){
                char temp[100];
                snprintf(temp, sizeof(temp), ";(%d,%d)", ocurrencia->ID, ocurrencia->cant_ocurrencias);
                strncat(linea, temp, BUFFER_LINEA - strlen(linea) - 1);
                ocurrencia = ocurrencia->next;

            }

            fprintf(file, "%s\n", linea);

            nodo = nodo->next;
        }
    }

    fclose(file);
}