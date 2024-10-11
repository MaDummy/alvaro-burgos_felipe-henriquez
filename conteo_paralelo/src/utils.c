#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % __INT_MAX__;
}


void escribe_hashmap(const char *const ruta_hash, const char *const ruta_inputs, const char *const extension){
    struct dirent *entrada;
    DIR *directorio = opendir(ruta_inputs);
    FILE *hash_file = fopen(ruta_hash, "w");

    if (directorio == NULL) {
        perror("No se pudo abrir el directorio");
        return;
    }

    // Se lee cada archivo del directorio
    while ((entrada = readdir(directorio)) != NULL) {
        // Verifica que cada archivo exista y tenga la extension especificada
        if (strstr(entrada->d_name, extension) != NULL) {
            unsigned char *archivo = (unsigned char *)entrada->d_name;
            int hash_pos = (int)hash(archivo);
            fprintf(hash_file, "%s, %d\n", archivo, hash_pos);
        }
    }

    //Se cierran todos los archivos/directorios
    closedir(directorio); 
    fclose(hash_file);
    return;
}


void filtra_stopword(const char *const texto, const char *const stopwords, const char *const path_copys){
    return;
}