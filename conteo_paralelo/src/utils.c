#include <string.h>
#define TAMANO_TABLA_HASH 100003

void quita_extension(char *nombreArchivo) {
    int len = strlen(nombreArchivo);
    int i;

    for (i = len - 1; i >= 0; i--) {
        if (nombreArchivo[i] == '.') {
            nombreArchivo[i] = '\0'; 
            break;
        }
    }
}

unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TAMANO_TABLA_HASH;
}