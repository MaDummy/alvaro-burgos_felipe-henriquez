#ifndef CACHE_FUNCS_H
#define CACHE_FUNCS_H

#include <time.h>
#include "../../menu_secundario/include/file_utils.h"

#define BUFFER_SIZE 1024

typedef struct CacheEntry {
    char *query;
    char *response;
    unsigned long hash;
} CacheEntry;

typedef struct Cache {
    CacheEntry *entries;
    int max_size;
} Cache;


unsigned long hashstring(unsigned char *str);

Cache* inicializarCache(int max_size_inicial);

void agregarEntrada(Cache *cache, char *entrada, char *respuesta);

void liberaCache(Cache *cache);

char *buscarEntrada(Cache *cache, char *entrada);

#endif