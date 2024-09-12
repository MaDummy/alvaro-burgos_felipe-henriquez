#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


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
            
            if(getenv(key) == NULL) setenv(key, value, 1);
        }
    }
    fclose(file);
}


char *verifica_usuario(char *nombre, char *contra){
    exporta_env();
    char *filename = getenv("ARCH_USUARIOS");
    FILE *file = fopen(filename, "r");
    char linea[100];
    char *user, *pass, *role;

    while(fgets(linea, sizeof(linea), file)){
        linea[strcspn(linea, "\n")] = 0;

        user = strtok(linea, "; ");
        pass = strtok(NULL, "; ");
        role = strtok(NULL, "; ");

        if(strcmp(user, nombre) == 0 && strcmp(pass, contra) == 0){
            fclose(file);
            char *rol = malloc(strlen(role) + 1);
            strcpy(rol, role);
            return rol;
        }
    }

    fprintf(stderr, "Fallo al iniciar sesión. Intente nuevamente.\n");
    fclose(file);
    exit(EXIT_FAILURE);
}


double convierte_n(char *n){
    double nuevo_n = strtod(n, NULL);

    return nuevo_n;
}