#include <stdio.h>
#include "../../conteo_paralelo/include/cuenta_pal.h"
#include "../../conteo_paralelo/include/utils.h"
#include "../../conteo_paralelo/include/menu.h"
#include "../../conteo_paralelo/include/stopwords.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
// Ejecutar como ./main <ruta_tests> <ruta_outputs> <extension> <array_threads> <mapa_archivos> <stop_words> <ruta_copias> 
//                      <repeticiones> <arch_datos> <arch_grafico> <llamada_conteo> <llamada_analizador>
int main(int argc, char *argv[]){
    const char *const ruta_tests = argv[1], *const ruta_outputs = argv[2], *const extension = argv[3],
    *const arch_hash = argv[5], *const arch_stopwords = argv[6], *const copy_path = argv[7],
    *const arch_datos = argv[9], *const arch_grafico = argv[10], *const llamada_conteo = argv[11], *const llamada_analizador = argv[12];

    const int repeticiones = atoi(argv[8]);
    const char *array_threads = argv[4];
    int cant_tests = 0;
    char comando[512] = "";
    char comando_analizador[512] = "";

    system("clear");
    printf("════ ∘◦Conteo de Palabras en paralelo, distintos threads◦∘ ════\n");
    printf("PID: %d\n", getpid());

    if(repeticiones < 2){
        printf("Error. La cantidad de repeticiones deben ser menor o igual a 2.\n");
        regresa_menu();
    }
    // Se catchean la cantidad de threads
    const char *threads_aux = array_threads;

    while(*threads_aux){
        if(*threads_aux == ','){
            cant_tests++;
        }
        threads_aux++;
    }
    cant_tests++;
    int *threads = malloc(cant_tests * sizeof(int));

    char *num = strtok((char *)array_threads, ",");
    int i = 0;
    
    while(num != NULL){
        threads[i++] = atoi(num);
        num = strtok(NULL, ",");
    }

    FILE *arch_tiempos = fopen(arch_datos, "w");
    for(int i = 0; i < cant_tests; i++){
        printf("%d, ", threads[i]);
    }

    struct timeval inicio, fin;

    for(int i = 0; i < cant_tests; i++){
        fprintf(arch_tiempos, "%d;", threads[i]);
        for(int j = 0; j < repeticiones; j++){
            snprintf(comando, sizeof(comando), "%s %s %s %s %d %s %s %s 1",
                    llamada_conteo,
                    ruta_tests,
                    ruta_outputs,
                    extension,
                    threads[i],
                    arch_hash,
                    arch_stopwords,
                    copy_path);
            
            gettimeofday(&inicio, NULL);
            system(comando);
            gettimeofday(&fin, NULL);
            double tiempo = (fin.tv_sec - inicio.tv_sec) + (fin.tv_usec - inicio.tv_usec) / 1000000.0;
            fprintf(arch_tiempos, "%f", tiempo);
            if(j != repeticiones-1) fprintf(arch_tiempos, ",");
        }
        if(i != cant_tests-1) fprintf(arch_tiempos, "\n");
    }

    fprintf(comando_analizador, "%s %s %s", llamada_analizador, arch_datos, arch_grafico);
    system(comando_analizador);

    free(threads);
    regresa_menu();
}