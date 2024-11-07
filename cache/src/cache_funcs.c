#include "../include/cache_funcs.h"
#include <stdlib.h>
#include <string.h>

Cache* inicializarCache(int max_size) {
    Cache *cache = (Cache*)malloc(sizeof(Cache));
    cache->entries = (CacheEntry*)malloc(max_size * sizeof(CacheEntry));
    cache->max_size = max_size;
    return cache;
}

void liberaCache(Cache *cache){
    for (int i = 0; i < cache->max_size; i++) {
        if (cache->entries[i].query != NULL) {
            free(cache->entries[i].query);
        }
        if (cache->entries[i].response != NULL) {
            free(cache->entries[i].response);
        }
    }

    free(cache->entries);
    free(cache);
}

void agregarEntrada(Cache *cache, char *entrada, char *respuesta){
    CacheEntry *entradas = cache->entries;
    if(entradas){
        for(int i = (cache->max_size)-1; i > 0; i--){
            if(i == (cache->max_size)-1){
                free(entradas[i].query);
                free(entradas[i].response);
            }
            entradas[i] = entradas[i-1];
        }
    }
    entradas[0].hash = hashstring((unsigned char *)entrada);
    entradas[0].query = strdup(entrada);
    entradas[0].response = strdup(respuesta);
}

char *buscarEntrada(Cache *cache, char *entrada) {
    unsigned long hash = hashstring(entrada);
    for (int i = 0; i < cache->max_size; i++) {
        if (cache->entries[i].hash == hash) {
            return cache->entries[i].response;
        }
    }
    return "-1";
}

unsigned long hashstring(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TAMANO_TABLA_HASH;
}