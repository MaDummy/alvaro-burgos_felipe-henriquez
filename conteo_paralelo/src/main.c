#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/cuenta_pal.h"
#include "../include/stopwords.h"
#include "../include/menu.h"


// ejecutar como ./main <ruta_tests> <ruta_outputs> <extension> <cantidad> <mapa_archivos> <stop_words> <ruta_copias> <contexto>
int main(int argc, char *argv[]){
    if(argc != 8){
        printf("Error al ejecutar conteo paralelo.\n");
        return 1;
    }

    const char *const ruta_tests = argv[1], *const ruta_outputs = argv[2], *const extension = argv[3], *const arch_hash = argv[5], *const arch_stopwords = argv[6], *const copy_path = argv[7];
    const int cantidad_threads = atoi(argv[4]);
    system("clear");
    printf("════ ∘◦Conteo de Palabras en paralelo, %d threads.◦∘ ════\n\n", cantidad_threads);
    printf("PID: %d.\n\n", getpid());
    printf("Escribiendo mapeo_archivos..\n");
    escribe_hashmap(arch_hash, ruta_tests, extension);
    
    printf("Leyendo stopwords..\n");
    char **stopwords = crea_arr_stopwords(arch_stopwords);

    printf("Filtrando documentos con stopwords..\n");
    filtra_stopwords_threads(ruta_tests, stopwords, copy_path, cantidad_threads, extension);

    printf("Procesando conteo de palabras..\n\n");
    procesamiento_archivos(copy_path, extension, ruta_outputs, cantidad_threads);

    printf("Proceso realizado con éxito!");

    regresa_menu();
    return 0;
}