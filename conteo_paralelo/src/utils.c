#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_STOPWORDS 200
#define MAX_LENGTH_STOPWORDS 10

unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % __INT_MAX__;
}


char *escribe_copia(const char *const ruta_orig, const char *const path_copys){
    char *ruta_completa_copia = malloc(100); // Buffer para la ruta completa del archivo copia

    // Extraer el nombre del archivo de la ruta 'input'
    const char *nombre = strrchr(ruta_orig, '/'); // Busca la última aparición de '/'
    nombre++;

    snprintf(ruta_completa_copia, 100, "%s/%s", path_copys, nombre);
    printf("Ruta: %s", ruta_completa_copia);
    return ruta_completa_copia;
}


void escribe_hashmap(const char *const ruta_hash, const char *const ruta_inputs, const char *const extension){
    struct dirent *entrada;
    DIR *directorio = opendir(ruta_inputs);
    FILE *hash_file = fopen(ruta_hash, "w");

    if (directorio == NULL) {
        perror("No se pudo abrir el directorio");
        return;
    }

    // Verifica que existen los archivos, filtrando por extensión
    while((entrada = readdir(directorio)) != NULL) {
        if (strstr(entrada->d_name, extension) != NULL) {
            unsigned char *archivo = (unsigned char *)entrada->d_name;
            int hash_pos = (int)hash(archivo);
            fprintf(hash_file, "%s, %d\n", archivo, hash_pos);
        }
    }

    //Se cierran todos los archivos/directorios
    closedir(directorio); 
    fclose(hash_file);
}

int is_stopword(char *word, char **stopwords){
    for(int i = 0; stopwords[i][0] != '\0'; i++){
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
        exit(EXIT_FAILURE);
    }

    while(fgets(line, sizeof(line), stopwords_file) != NULL){
        line[strcspn(line, "\n")] = 0;
        strcpy(stopwords[i++], line);
    }
    stopwords[i][0] = '\0';

    return stopwords;
}

void filtra_stopword(const char *const texto, char **stopwords, const char *const path_copys){
    char *word;
    FILE *text = fopen(texto, "r");
    char line[256];
    if(!text){
        printf("No se encontró el texto a filtrar.\n");
        exit(EXIT_FAILURE);
    }
    DIR *directorio = opendir(path_copys);
    struct dirent *entrada;

    char *ruta_copia = escribe_copia(texto, path_copys);
    FILE *copia = fopen(ruta_copia, "w");


    if(!directorio){
        fprintf(stderr, "No se pudo abrir el directorio para las copias sin stopwords.\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(line, sizeof(line), text) != NULL){
        word = strtok(line, " ");
        while(word != NULL){
            if(!is_stopword(word, stopwords)){
                fprintf(copia, "%s ", word);
            }
            word = strtok(NULL, " ");
        }
        fprintf(copia, "\n");
    }

    fclose(text);
    fclose(copia);
}