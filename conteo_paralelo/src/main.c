#include <stdio.h>

// ejecutar como ./main <cantidad> <mapa_archivos> <stop_words>
int main(int argc, char *argv[]){
    const int cantidad_threads = (int)argv[0];
    const char *const arch_hash = argv[1];
    const char *const arch_stopwords = argv[2];

    printf("Cantidad de threads: %d\nRuta del archivo hash: %s\nRuta archivo stopwords: %s\n", cantidad_threads, arch_hash, arch_stopwords);

    return 0;
}