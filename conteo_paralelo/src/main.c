#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

// ejecutar como ./main <ruta_tests> <ruta_outputs> <extension> <cantidad> <mapa_archivos> <stop_words>
int main(int argc, char *argv[]){
    if(argc != 7){
        printf("Error al ejecutar conteo paralelo.\n");
        return 1;
    }

    const char *const ruta_tests = argv[1], *const ruta_outputs = argv[2], *const extension = argv[3], *const arch_hash = argv[5], *const arch_stopwords = argv[6];
    const int cantidad_threads = atoi(argv[4]);

    
    escribe_hashmap(arch_hash, ruta_tests, extension);
    

    return 0;
}