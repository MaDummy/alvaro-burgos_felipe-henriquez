#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void exporta_env() {
    FILE *file = fopen(".env", "r");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char *delimiter = strchr(line, '=');
        if (delimiter != NULL) {
            *delimiter = '\0';
            char *key = line;
            char *value = delimiter + 1;

            setenv(key, value, 1);
        }
    }
    fclose(file);
}


void remover_extension(char *nombreArchivo) {
    int len = strlen(nombreArchivo);
    int i;

    for (i = len - 1; i >= 0; i--) {
        if (nombreArchivo[i] == '.') {
            nombreArchivo[i] = '\0'; 
            break;
        }
    }
}
