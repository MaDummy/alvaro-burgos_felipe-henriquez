#include <stdio.h>
#include "../../conteo_paralelo/include/cuenta_pal.h"
#include "../../conteo_paralelo/include/utils.h"
#include "../../conteo_paralelo/include/menu.h"
#include "../../conteo_paralelo/include/stopwords.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// Ejecutar como ./main <ruta_tests> <ruta_outputs> <extension> <array_threads> <mapa_archivos> <stop_words> <ruta_copias> 
//                      <repeticiones> <arch_datos> <arch_grafico> <>
int main(int argc, char *argv[]){
    const char *const ruta_tests = argv[1], *const ruta_outputs = argv[2], *const extension = argv[3],
    *const arch_hash = argv[5], *const arch_stopwords = argv[6], *const copy_path = argv[7],
    *const arch_datos = argv[9], *const arch_grafico = argv[10];

    const int repeticiones = atoi(argv[8]);
    const char *array_threads = argv[4];
    int cant_tests = 0;
    clock_t inicio, fin;
    char comando[2048] = "";

    system("clear");
    printf("════ ∘◦Conteo de Palabras en paralelo, distintos threads◦∘ ════\n");
    printf("PID: %d\n", getpid());

    if(repeticiones < 2){
        printf("Error. La cantidad de repeticiones deben ser menor o igual a 2.\n");
        regresa_menu();
    }

    while(*array_threads){
        if(*array_threads == ','){
            cant_tests++;
        }
        array_threads++;
    }
    cant_tests++;
    int *threads = malloc(cant_tests * sizeof(int));

    char *num = strtok((char *)array_threads, ",");
    int i = 0;
    while(num != NULL){
        threads[i++] = atoi(num);
        num = strtok(NULL, ",");
    }
    
    printf("Procesando archivos con: \n");
    for(int i = 0; i < cant_tests; i++){
        for(int j = 0; j < repeticiones; j++){
            printf("%d thread(s). Repetición n°: %d...", i, j);
            procesamiento_archivos(copy_path, extension, ruta_outputs, threads[i]);
        }
    }

    free(threads);
    regresa_menu();
}