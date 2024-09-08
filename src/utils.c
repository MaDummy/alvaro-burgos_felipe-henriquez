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

            setenv(key, value, 1);
        }
    }
    fclose(file);
}

int busca_usuario_env(char *user){
    bool existe = false;
    int indice = 0;

    char *usuarios_env = getenv("USERS");
    char *usuarios = strtok(usuarios_env, ",");

    while(usuarios != NULL){
        if(strcmp(usuarios, user) == 0){
            existe = true;
            break;
        }
        indice++;
        usuarios = strtok(NULL, ",");
    }
    
    if(!existe){
        printf("Fallo al iniciar sesión, intente nuevamente.\n");
        exit(EXIT_FAILURE);
    }
    return indice;
}

void verifica_contrasena_env(char *password, int indice){
    char *contras_env = getenv("PASSWORDS");

    char *contras = strtok(contras_env, ",");
    
    for(int i = 0; i < indice; i++){
        contras = strtok(NULL, ",");
        }

    if((strcmp(contras, password) != 0)){
        printf("Fallo al iniciar sesión, intente nuevamente.\n");
        exit(EXIT_FAILURE);
    }
}

double convierte_n(char *n){
    double nuevo_n = strtod(n, NULL);

    return nuevo_n;
}