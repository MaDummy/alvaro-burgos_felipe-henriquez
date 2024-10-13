#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "../include/utils.h"
#include "../include/menu.h"
#include "../include/stopwords.h"

#define MAX_ARCHIVOS 1024
#define MAX_PALABRA 512
#define BUFFER_LINEA 2048
#define MAX_PATH 512
#define TAMANO_TABLA_HASH 100003

typedef struct Args {
    FILE *archivoEntrada;
    FILE *archivoSalida;
    int *palabrasDiferentes;
} ThreadArgs;

typedef struct NodoPalabra {
    char palabra[MAX_PALABRA];
    int ocurrencias;
    struct NodoPalabra *next; 
} NodoPalabra;

typedef struct {
    NodoPalabra *tabla[TAMANO_TABLA_HASH];
    int palabrasDiferentesTabla;
} TablaHash;


void *contar_palabras(void *args) {
    ThreadArgs *arg = (ThreadArgs *)args;
    FILE *archivoEntrada = arg->archivoEntrada;
    FILE *archivoSalida = arg->archivoSalida;
    int *palabrasDiferentes = arg->palabrasDiferentes;

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

    pthread_mutex_lock(&file_mutex);
    while (fgets(buffer, sizeof(buffer), archivoEntrada)) {

        token = strtok(buffer, delimitadores);
        while (token != NULL) {

            int encontrada = 0;

            unsigned long indice_hash = hash((unsigned char *)token);
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
    fclose(archivoEntrada);
    fclose(archivoSalida);
    pthread_mutex_unlock(&file_mutex);
    sem_post(&semaphore);
    free(arg);
    pthread_exit(NULL);
}


void procesar_archivos_paralelo(const char *const directorioEntrada, const char *const extension, const char *const directorioSalida, char *pathArchivosSalida[MAX_ARCHIVOS], int cantidadPalabras[MAX_ARCHIVOS], int *contadorArchivos, const int MAX_THREADS) {
    sem_init(&semaphore, 0, MAX_THREADS);
    pthread_mutex_init(&file_mutex, NULL);

    char *temp_route = malloc(150);
    pthread_t threads[MAX_THREADS];
    int thread_count = 0;
    
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
            sem_wait(&semaphore);
            ThreadArgs *args = malloc(sizeof(ThreadArgs));

            snprintf(rutaEntrada, sizeof(rutaEntrada), "%s/%s", directorioEntrada, archivoActual->d_name);
            quita_extension(archivoActual->d_name);

            int hash_arch = (int)hash((unsigned char *)archivoActual->d_name);
            snprintf(rutaSalida, sizeof(rutaSalida), "%s/%d.txt", directorioSalida, hash_arch);

            archivoEntrada = fopen(rutaEntrada, "r");
            if (archivoEntrada == NULL) {
                continue;
            }

            archivoSalida = fopen(rutaSalida, "w");
            if (archivoSalida == NULL) {
                fclose(archivoEntrada);
                continue;
            }

            args->archivoEntrada = archivoEntrada;
            args->archivoSalida = archivoSalida;
            args->palabrasDiferentes = &cantidadPalabras[cont];
            pthread_create(&threads[thread_count++], NULL, contar_palabras, (void *)args);

            strncpy(pathArchivosSalida[cont], rutaSalida, MAX_PATH); 
            pathArchivosSalida[cont][MAX_PATH] = '\0';
            cont++;

            if(thread_count >= MAX_THREADS){
                for(int i = 0; i < thread_count; i++)
                    pthread_join(threads[i], NULL);
                thread_count = 0;
            }
        }
    }
    for (int i = 0; i < cont; i++) 
        free(pathArchivosSalida[i]);


    for (int i = 0; i < thread_count; i++) 
        pthread_join(threads[i], NULL);

    *contadorArchivos = cont;

    closedir(dir);
    sem_close(&semaphore);
    pthread_mutex_destroy(&file_mutex);
}

void procesamiento_archivos(const char *const directorioEntrada, const char *const extension, const char *const directorioSalida, const int MAX_THREADS){
    char* pathArchivosSalida[MAX_ARCHIVOS];
    int cantidadPalabras[MAX_ARCHIVOS];

    int cantidadArchivos;

    procesar_archivos_paralelo(directorioEntrada, extension, directorioSalida, pathArchivosSalida, cantidadPalabras, &cantidadArchivos, MAX_THREADS);
}
