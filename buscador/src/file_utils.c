#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/utils.h"
#include "../include/file_utils.h"

unsigned long hashstring(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TAMANO_TABLA_HASH;
}

void contar_palabras(FILE *archivoEntrada, FILE *archivoSalida, int *palabrasDiferentes) {
    char buffer[BUFFER_LINEA];
    int i;
    int max_palabras = TAMANO_TABLA_HASH;
    char *token;
    char delimitadores[] = " \t\n\r\v\f;,";

    TablaHash tabla;
    for (int i = 0; i < TAMANO_TABLA_HASH; i++) {
        tabla.tabla[i] = NULL; // Inicializar punteros a NULL
    }
    tabla.palabrasDiferentesTabla = 0; // Inicializar el contador

    int num_palabras = 0;


    while (fgets(buffer, sizeof(buffer), archivoEntrada)) {

        token = strtok(buffer, delimitadores);
        while (token != NULL) {

            int encontrada = 0;

            unsigned long indice_hash = hashstring((unsigned char *)token);
            NodoPalabra *nodo_actual = tabla.tabla[indice_hash];

            while (nodo_actual != NULL) {
                if (strcmp(nodo_actual->palabra, token) == 0) {
                    nodo_actual->ocurrencias++;
                    break;
                }
                nodo_actual = nodo_actual->next;
            }

            if (nodo_actual == NULL) {
                NodoPalabra *nuevo_nodo = malloc(sizeof(NodoPalabra));
                if (nuevo_nodo == NULL) {
                    fprintf(stderr, "Error al asignar memoria para una nueva palabra\n");
                    exit(EXIT_FAILURE);
                }
                strcpy(nuevo_nodo->palabra, token);
                nuevo_nodo->ocurrencias = 1;
                nuevo_nodo->next = tabla.tabla[indice_hash];
                tabla.tabla[indice_hash] = nuevo_nodo;

                tabla.palabrasDiferentesTabla++;
            }

            token = strtok(NULL, delimitadores);
        }
    }

    *palabrasDiferentes = tabla.palabrasDiferentesTabla;

    for (int i = 0; i < TAMANO_TABLA_HASH; i++) {
        NodoPalabra *nodo_actual = tabla.tabla[i];
        while (nodo_actual != NULL) {
            fprintf(archivoSalida, "%s; %d\n", nodo_actual->palabra, nodo_actual->ocurrencias);
            nodo_actual = nodo_actual->next;
        }
    }

    for (int i = 0; i < TAMANO_TABLA_HASH; i++) {
        NodoPalabra *nodo_actual = tabla.tabla[i];
        while (nodo_actual != NULL) {
            NodoPalabra *temp = nodo_actual;
            nodo_actual = nodo_actual->next;
            free(temp);
        }
    }
}


void procesar_archivos(char *directorioEntrada, char *extension, char *directorioSalida, char *pathArchivosSalida[MAX_ARCHIVOS], int cantidadPalabras[MAX_ARCHIVOS], int *contadorArchivos) {
    DIR *dir;
    struct dirent *archivoActual;
    FILE *archivoEntrada, *archivoSalida;
    char rutaEntrada[MAX_PATH], rutaSalida[MAX_PATH];
    int cont = 0;

    for (int i = 0; i < MAX_ARCHIVOS; i++) {
        pathArchivosSalida[i] = malloc(MAX_PATH * sizeof(char)); 
        if (pathArchivosSalida[i] == NULL) {
            fprintf(stderr, "Error al asignar memoria para la ruta de archivo %d\n", i);
            exit(EXIT_FAILURE);
        }
    }   

    dir = opendir(directorioEntrada);
    if (dir == NULL) {
        fprintf(stderr, "Error: no se puede abrir el directorio\n");
        exit(EXIT_FAILURE);
    }

    while ((archivoActual = readdir(dir)) != NULL) {
        if (strstr(archivoActual->d_name, extension) != NULL) {
            snprintf(rutaEntrada, sizeof(rutaEntrada), "%s/%s", directorioEntrada, archivoActual->d_name);

            remover_extension(archivoActual->d_name);

            snprintf(rutaSalida, sizeof(rutaSalida), "%s/%s.txt", directorioSalida, archivoActual->d_name);

            archivoEntrada = fopen(rutaEntrada, "r");
            if (archivoEntrada == NULL) {
                continue;
            }

            archivoSalida = fopen(rutaSalida, "w");
            if (archivoSalida == NULL) {
                fclose(archivoEntrada);
                continue;
            }

            contar_palabras(archivoEntrada, archivoSalida, &cantidadPalabras[cont]);

            fclose(archivoEntrada);
            fclose(archivoSalida);

            strncpy(pathArchivosSalida[cont], rutaSalida, MAX_PATH); 
            pathArchivosSalida[cont][MAX_PATH] = '\0';
            cont++;
        }
    }

    *contadorArchivos = cont;

    closedir(dir);
}

char *reemplazaTexto(char *input_text, char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char *result = strdup(input_text);
    char line[256];
    char doc_name[256];
    char hash[20];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, " %[^,], %s", doc_name, hash) == 2) {
            // Construir la cadena de búsqueda
            char search_str[30];
            snprintf(search_str, sizeof(search_str), "(%s;", hash);
            
            char *pos = strstr(result, search_str);
            if (pos != NULL) {
                // Construir la cadena de reemplazo
                char replace_str[256];
                snprintf(replace_str, sizeof(replace_str), "(%s;", doc_name);
                
                // Calcular el tamaño necesario para el nuevo resultado
                size_t prefix_len = pos - result;
                size_t suffix_start = prefix_len + strlen(search_str);
                size_t new_size = strlen(result) - strlen(search_str) + strlen(replace_str) + 1;
                
                char *new_result = malloc(new_size);
                if (new_result == NULL) {
                    perror("Error de memoria");
                    fclose(file);
                    free(result);
                    return NULL;
                }
                
                // Copiar la parte anterior al hash
                strncpy(new_result, result, prefix_len);
                new_result[prefix_len] = '\0';
                
                // Agregar el reemplazo
                strcat(new_result, replace_str);
                
                // Agregar el resto del string original
                strcat(new_result, result + suffix_start);
                
                free(result);
                result = new_result;
            }
        }
    }

    fclose(file);
    return result;
}