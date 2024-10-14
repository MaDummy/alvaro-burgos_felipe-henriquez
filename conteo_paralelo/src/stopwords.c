#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <semaphore.h>
#include <pthread.h>
#include "../include/utils.h"
#include "../include/menu.h"

#define MAX_ARCHIVOS 1024
#define MAX_STOPWORDS 400
#define MAX_LENGTH_STOPWORDS 10

sem_t semaphore; // Semaforo para controlar la cantidad de threads activos
pthread_mutex_t file_mutex;

// Estructura para pasar los argumentos al thread 
typedef struct {
    char *ruta_archivo;
    char **stopwords;
    char *ruta_copia_archivo;
} ThreadArgs;


char *escribe_copia(const char *const ruta_orig, const char *const path_copys){
    char *ruta_completa_copia = malloc(100); // Buffer para la ruta completa del archivo copia

    // Extraer el nombre del archivo de la ruta 'input'
    const char *nombre = strrchr(ruta_orig, '/'); // Busca la última aparición de '/'
    nombre++;

    snprintf(ruta_completa_copia, 100, "%s/%s", path_copys, nombre);
    return ruta_completa_copia;
}


void escribe_hashmap(const char *const ruta_hash, const char *const ruta_inputs, const char *const extension){
    struct dirent *entrada;
    DIR *directorio = opendir(ruta_inputs);
    FILE *hash_file = fopen(ruta_hash, "w");

    if (directorio == NULL) {
        perror("No se pudo abrir el directorio");
        regresa_menu();
    }

    // Verifica que existen los archivos, filtrando por extensión
    while((entrada = readdir(directorio)) != NULL) {
        if (strstr(entrada->d_name, extension) != NULL) {
            // Preprocesamiento del archivo para quitarle la extension antes de guardarlo en el mapeo
            char *archivo = (char *)entrada->d_name;
            quita_extension(archivo);
            
            int hash_pos = (int)hash(archivo);
            fprintf(hash_file, "%s, %d\n", archivo, hash_pos);

        }
    }

    //Se cierran todos los archivos/directorios
    closedir(directorio); 
    fclose(hash_file);
}

int is_stopword(char *word, char **stopwords){
    for(int i = 0; stopwords[i][0] != 0; i++){
        for(int j = 0; word[j]; j++){
            word[j] = tolower(word[j]);
        }
        if(strcmp(word, stopwords[i]) == 0){
            return 1;
        }
    }
    return 0;
}


char **crea_arr_stopwords(const char *const path_stopwords){
    FILE *stopwords_file = fopen(path_stopwords, "r");
    char line[256];
    char **stopwords = malloc(MAX_STOPWORDS * sizeof(char *));
    for (int i = 0; i < MAX_STOPWORDS; i++) {
        stopwords[i] = malloc(MAX_LENGTH_STOPWORDS * sizeof(char));
    }
    int i = 0;
    
    if(!stopwords_file){
        printf("No se encontró el archivo con las stopwords\n");
        regresa_menu();
    }

    while(fgets(line, sizeof(line), stopwords_file) != NULL){
        line[strcspn(line, "\n")] = 0;
        strcpy(stopwords[i++], line);
    }
    stopwords[i][0] = '\0';

    return stopwords;
}

void *filtra_stopword(void *args){
    ThreadArgs *arg = (ThreadArgs *)args;
    char *texto = arg->ruta_archivo;
    printf("Filtrando: %s\n", texto);
    char **stopwords = arg->stopwords;
    char *path_copys = arg->ruta_copia_archivo;

    char *word;
    FILE *text = fopen(texto, "r");
    char line[256];
    if(!text){
        fprintf(stderr, "No se encontró el texto a filtrar en la ruta: %s.\n", texto);
        sem_post(&semaphore);  // Garantizamos liberar el semáforo en caso de error
        free(arg->ruta_archivo);
        free(arg);
        pthread_exit(NULL);  // Terminamos el thread
    }

    char *ruta_copia = escribe_copia(texto, path_copys);

    pthread_mutex_lock(&file_mutex);
    FILE *copia = fopen(ruta_copia, "w");
    free(ruta_copia);

    while(fgets(line, sizeof(line), text) != NULL){
        word = strtok(line, " ");
        while(word != NULL){
            if(!is_stopword(word, stopwords)){
                if(strcmp(word, "\n") != 0)
                    fprintf(copia, "%s ", word);
                else
                    fprintf(copia, "\n");
            }
            word = strtok(NULL, " ");
        }
    }
    fclose(text);
    fclose(copia);

    pthread_mutex_unlock(&file_mutex);

    sem_post(&semaphore);
    free(arg->ruta_archivo);
    free(arg);
    pthread_exit(NULL);
}

void filtra_stopwords_threads(const char *const ruta_inputs, char **stopwords, const char *const path_copys, const int MAX_THREADS, const char *const extension){
    sem_init(&semaphore, 0, MAX_THREADS);
    pthread_mutex_init(&file_mutex, NULL);

    char *temp_route = malloc(150);
    pthread_t threads[MAX_THREADS];
    int thread_count = 0;

    DIR *directorio = opendir(ruta_inputs);
    if (!directorio){
        fprintf(stderr, "El directorio de inputs no se encontró\n");
        regresa_menu();
    }
    struct dirent *entrada;

    while((entrada = readdir(directorio)) != NULL) {
        if (strstr(entrada->d_name, extension) != NULL) {
            sem_wait(&semaphore);
            ThreadArgs *args = malloc(sizeof(ThreadArgs));

            snprintf(temp_route, 257, "%s/%s", ruta_inputs, entrada->d_name);
            args->ruta_archivo = strdup(temp_route);
            args->ruta_copia_archivo = (char *)path_copys;
            args->stopwords = stopwords;
            pthread_create(&threads[thread_count++], NULL, filtra_stopword, (void *)args);

            if(thread_count >= MAX_THREADS){
                for(int i = 0; i < thread_count; i++)
                    pthread_join(threads[i], NULL);
                thread_count = 0;
            }
        }

    }
    for (int i = 0; i < thread_count; i++) 
        pthread_join(threads[i], NULL);
    
    free(temp_route);
    closedir(directorio);
    sem_close(&semaphore);
    pthread_mutex_destroy(&file_mutex);
}
