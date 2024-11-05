#include <stdlib.h>
#include <string.h>
#include "../include/file_utils.h"
#include<unistd.h>


unsigned long hashstring(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TAMANO_TABLA_HASH;
}

void insertarPalabra(TablaHash *tabla, char *palabra) {
    unsigned long indice = hashstring((unsigned char *)palabra);
    NodoPalabra *nuevoNodo = malloc(sizeof(NodoPalabra));

    char *token;
    int id_documento, ocurrencias;

    // Extraer la palabra inicial
    token = strtok(palabra, ";");
    strcpy(nuevoNodo->palabra,token);

    // Recorrer las tuplas y extraer valores
    while ((token = strtok(NULL, ";")) != NULL) {
        sscanf(token, "(%d,%d)", &id_documento, &ocurrencias);

        ID_Ocurrencias *nuevo = malloc(sizeof(ID_Ocurrencias));
        nuevo->cant_ocurrencias = ocurrencias;
        nuevo->ID = id_documento;
        nuevo->next = nuevoNodo->ocurrencias;
        nuevoNodo->ocurrencias = nuevo;
    }

    nuevoNodo->next = tabla->tabla[indice];
    tabla->tabla[indice] = nuevoNodo;
    tabla->palabrasDiferentesTabla++;
}


void rellenarTablaHash(FILE *archivo_index, TablaHash *tabla){
    char line[BUFFER_LINEA];
    while (fgets(line, sizeof(line), archivo_index)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        insertarPalabra(tabla, line);
    }
}

void buscarPalabra(TablaHash *tabla, char *palabra, NodoInterseccion **puntajes, int *contador_interseccion) {
    unsigned long indice = hashstring((unsigned char *)palabra);
    NodoPalabra *nodo = tabla->tabla[indice];

    // Locate the correct NodoPalabra for `palabra`
    while(nodo != NULL && (strcmp(nodo->palabra, palabra) != 0)) {
        nodo = nodo->next;
    }

    if (nodo == NULL) {
        // Only clear `puntajes` if this is the first word
        if (*contador_interseccion == 1) {
            *puntajes = NULL;
        }
        return;
    }

    // Populate puntajes for the first word
    if (*contador_interseccion == 1 && *puntajes == NULL) {
        ID_Ocurrencias *nodo_ocurrencias = nodo->ocurrencias;
        while (nodo_ocurrencias != NULL) {
            NodoInterseccion *nuevo = malloc(sizeof(NodoInterseccion));
            nuevo->id_documento = nodo_ocurrencias->ID;
            nuevo->suma_ocurrencias = nodo_ocurrencias->cant_ocurrencias;
            nuevo->contador = 1;
            nuevo->next = *puntajes;
            *puntajes = nuevo;
            nodo_ocurrencias = nodo_ocurrencias->next;
        }
        return;
    }

    // If `puntajes` is already initialized, filter for intersections
    NodoInterseccion *prev = NULL;
    NodoInterseccion *current = *puntajes;

    while (current != NULL) {
        int found = 0;
        ID_Ocurrencias *nodo_ocurrencias = nodo->ocurrencias;

        // Check if the document ID is in the list for this palabra
        while (nodo_ocurrencias != NULL) {
            if (nodo_ocurrencias->ID == current->id_documento) {
                found = 1;
                current->contador++;
                current->suma_ocurrencias += nodo_ocurrencias->cant_ocurrencias;
                break;
            }
            nodo_ocurrencias = nodo_ocurrencias->next;
        }

        if (!found) {
            // Remove from puntajes if not found
            if (prev == NULL) {
                *puntajes = current->next;
                free(current);
                current = *puntajes;
            } else {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }

    // Final pass: remove entries with `contador` less than `contador_interseccion`
    prev = NULL;
    current = *puntajes;
    while (current != NULL) {
        if (current->contador < *contador_interseccion) {
            if (prev == NULL) {
                *puntajes = current->next;
                free(current);
                current = *puntajes;
            } else {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}



void procesarPalabras(TablaHash *tabla, NodoInterseccion **puntajes, char palabras[BUFFER_SIZE]){
    char *palabra;
    palabra = strtok(palabras, " ");
    int contador_interseccion = 0;

    while (palabra != NULL) {
        contador_interseccion++;
        buscarPalabra(tabla, palabra, puntajes, &contador_interseccion);
        palabra = strtok(NULL, " ");
    }
}


char *formatearResultado(NodoInterseccion *puntajes, const char *palabras) {
    // Initial buffer for the formatted string, adjust size as needed
    int buffer_size = 2048;
    char *resultado = malloc(buffer_size);
    if (resultado == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for the result string.\n");
        return NULL;
    }

    // Start the formatted string with the searched words
    snprintf(resultado, buffer_size, "%s;", palabras);

    // Traverse the linked list of NodoInterseccion and format each entry
    NodoInterseccion *current = puntajes;
    while (current != NULL) {
        char temp[64]; // Temporary buffer for each document entry
        snprintf(temp, sizeof(temp), "(doc%d;%d)", current->id_documento, current->suma_ocurrencias);

        // Append the formatted document entry to the result string
        if (strlen(resultado) + strlen(temp) + 1 >= buffer_size) {
            // Reallocate if the buffer is too small
            buffer_size *= 2;
            resultado = realloc(resultado, buffer_size);
            if (resultado == NULL) {
                fprintf(stderr, "Error: Could not reallocate memory for the result string.\n");
                return NULL;
            }
        }
        strcat(resultado, temp);
        
        // Move to the next node
        current = current->next;
    }

    return resultado;
}