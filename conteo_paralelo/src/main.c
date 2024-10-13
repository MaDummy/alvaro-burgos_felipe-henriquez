#include <stdio.h>
#include <stdlib.h>
#include "../include/cuenta_pal.h"
#include "../include/stopwords.h"

// ejecutar como ./main <ruta_tests> <ruta_outputs> <extension> <cantidad> <mapa_archivos> <stop_words> <ruta_copias>
int main(int argc, char *argv[]){
    if(argc != 8){
        printf("Error al ejecutar conteo paralelo.\n");
        return 1;
    }

    const char *const ruta_tests = argv[1], *const ruta_outputs = argv[2], *const extension = argv[3], *const arch_hash = argv[5], *const arch_stopwords = argv[6], *const copy_path = argv[7];
    const int cantidad_threads = atoi(argv[4]);

    
    escribe_hashmap(arch_hash, ruta_tests, extension);
    char **stopwords = crea_arr_stopwords(arch_stopwords);
    filtra_stopwords_threads(ruta_tests, stopwords, copy_path, cantidad_threads, extension);
    procesamiento_archivos(ruta_tests, extension, ruta_outputs, cantidad_threads);

    return 0;
}