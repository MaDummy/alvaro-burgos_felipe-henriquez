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
    char *token = strtok(palabra, ";");
    char palabra_hash[BUFFER_LINEA];
    strcpy(palabra_hash, token);

    unsigned long indice = hashstring((unsigned char *)palabra_hash);

    NodoPalabra *nuevoNodo = malloc(sizeof(NodoPalabra));

    int id_documento, ocurrencias;

    strcpy(nuevoNodo->palabra, token);

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

int compara_ocurrencias(const void *a, const void *b) {
    NodoInterseccion *nodoA = *(NodoInterseccion **)a;
    NodoInterseccion *nodoB = *(NodoInterseccion **)b;
    return nodoB->suma_ocurrencias - nodoA->suma_ocurrencias;
}

void disminuye_a_topk(NodoInterseccion **puntajes, int topk) {
    int count = 0;
    NodoInterseccion *current = *puntajes;
    
    while (current) {
        count++;
        current = current->next;
    }
    
    if (count <= topk) return;
    
    NodoInterseccion **array = malloc(count * sizeof(NodoInterseccion *));
    current = *puntajes;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }
    
    qsort(array, count, sizeof(NodoInterseccion *), compara_ocurrencias);
    
    *puntajes = array[0];
    NodoInterseccion *last = *puntajes;
    for (int i = 1; i < topk; i++) {
        last->next = array[i];
        last = last->next;
    }
    last->next = NULL;

    for (int i = topk; i < count; i++) {
        free(array[i]);
    }
    free(array);
}

void buscarPalabra(TablaHash *tabla, char *palabra, NodoInterseccion **puntajes, int *contador_interseccion, int topk) {
    size_t len = strlen(palabra);
    if (len > 0 && palabra[len - 1] == '\n') {
        palabra[len - 1] = '\0';
    }
    unsigned long indice = hashstring((unsigned char *)palabra);
    NodoPalabra *nodo = tabla->tabla[indice];

    while(nodo != NULL && (strcmp(nodo->palabra, palabra) != 0)) {
        nodo = nodo->next;
    }

    if (nodo == NULL) {
        if (*contador_interseccion == 1) {
            *puntajes = NULL;
        }
        return;
    }

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
        disminuye_a_topk(puntajes, topk);
        return;
    }

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

    disminuye_a_topk(puntajes, topk);
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

    snprintf(resultado, buffer_size, "%s", palabras);

    NodoInterseccion *current = puntajes;
    while (current != NULL) {
        char temp[64];
        snprintf(temp, sizeof(temp), ";(%d;%d)", current->id_documento, current->suma_ocurrencias);

        if (strlen(resultado) + strlen(temp) + 1 >= buffer_size) {
            buffer_size *= 2;
            resultado = realloc(resultado, buffer_size);
            if (resultado == NULL) {
                fprintf(stderr, "Error: Could not reallocate memory for the result string.\n");
                return NULL;
            }
        }
        strcat(resultado, temp);
        
        current = current->next;
    }

    return resultado;
}