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
    // Extract only the word to hash
    char *token = strtok(palabra, ";");
    char word_to_hash[BUFFER_LINEA];
    strcpy(word_to_hash, token);

    // Now hash only the word part
    unsigned long indice = hashstring((unsigned char *)word_to_hash);

    NodoPalabra *nuevoNodo = malloc(sizeof(NodoPalabra));

    int id_documento, ocurrencias;

    // Store the word in the node
    strcpy(nuevoNodo->palabra, token);

    // Process the rest of the string (tuples of (id_documento, ocurrencias))
    while ((token = strtok(NULL, ";")) != NULL) {
        sscanf(token, "(%d,%d)", &id_documento, &ocurrencias);

        ID_Ocurrencias *nuevo = malloc(sizeof(ID_Ocurrencias));
        nuevo->cant_ocurrencias = ocurrencias;
        nuevo->ID = id_documento;
        nuevo->next = nuevoNodo->ocurrencias;
        nuevoNodo->ocurrencias = nuevo;
    }

    // Insert the node into the hash table
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

// Helper function to sort by occurrences in descending order
int compare_occurrences(const void *a, const void *b) {
    NodoInterseccion *nodoA = *(NodoInterseccion **)a;
    NodoInterseccion *nodoB = *(NodoInterseccion **)b;
    return nodoB->suma_ocurrencias - nodoA->suma_ocurrencias;
}

// Trims puntajes to the top `topk` elements
void trim_to_topk(NodoInterseccion **puntajes, int topk) {
    int count = 0;
    NodoInterseccion *current = *puntajes;
    
    // Count total elements
    while (current) {
        count++;
        current = current->next;
    }
    
    // If current size is less than or equal to topk, no trimming needed
    if (count <= topk) return;
    
    // Create an array of pointers for sorting
    NodoInterseccion **array = malloc(count * sizeof(NodoInterseccion *));
    current = *puntajes;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }
    
    // Sort the array by occurrences
    qsort(array, count, sizeof(NodoInterseccion *), compare_occurrences);
    
    // Rebuild the list with only top `topk` elements
    *puntajes = array[0];
    NodoInterseccion *last = *puntajes;
    for (int i = 1; i < topk; i++) {
        last->next = array[i];
        last = last->next;
    }
    last->next = NULL;

    // Free remaining nodes and the array
    for (int i = topk; i < count; i++) {
        free(array[i]);
    }
    free(array);
}

// Main buscarPalabra function with topk limit
void buscarPalabra(TablaHash *tabla, char *palabra, NodoInterseccion **puntajes, int *contador_interseccion, int topk) {
    size_t len = strlen(palabra);
    if (len > 0 && palabra[len - 1] == '\n') {
        palabra[len - 1] = '\0';
    }
    unsigned long indice = hashstring((unsigned char *)palabra);
    NodoPalabra *nodo = tabla->tabla[indice];

    // Locate the correct NodoPalabra for `palabra`
    while(nodo != NULL && (strcmp(nodo->palabra, palabra) != 0)) {
        nodo = nodo->next;
    }

    if (nodo == NULL) {
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
        trim_to_topk(puntajes, topk);
        return;
    }

    // If `puntajes` is already initialized, filter for intersections
    NodoInterseccion *prev = NULL;
    NodoInterseccion *current = *puntajes;

    while (current != NULL) {
        int found = 0;
        ID_Ocurrencias *nodo_ocurrencias = nodo->ocurrencias;

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

    // Trim puntajes to top `topk`
    trim_to_topk(puntajes, topk);
}



void procesarPalabras(TablaHash *tabla, NodoInterseccion **puntajes, char palabras[BUFFER_SIZE], int topK){
    char *palabra;
    palabra = strtok(palabras, " ");
    int contador_interseccion = 0;

    while (palabra != NULL) {
        contador_interseccion++;
        buscarPalabra(tabla, palabra, puntajes, &contador_interseccion, topK);
        palabra = strtok(NULL, " ");
    }
}


char *formatearResultado(NodoInterseccion *puntajes, char *palabras) {
    // Initial buffer for the formatted string, adjust size as needed
    int buffer_size = 2048;
    char *resultado = malloc(buffer_size);
    if (resultado == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for the result string.\n");
        return NULL;
    }

    size_t len = strlen(palabras);
    if (len > 0 && palabras[len - 1] == '\n') {
        palabras[len - 1] = '\0';
    }

    // Start the formatted string with the searched words
    snprintf(resultado, buffer_size, "%s", palabras);

    // Traverse the linked list of NodoInterseccion and format each entry
    NodoInterseccion *current = puntajes;
    while (current != NULL) {
        char temp[64]; // Temporary buffer for each document entry
        snprintf(temp, sizeof(temp), ";(%d;%d)", current->id_documento, current->suma_ocurrencias);

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