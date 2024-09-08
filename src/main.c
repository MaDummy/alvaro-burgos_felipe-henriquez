#include <stdio.h>
#include <bits/getopt_core.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/opciones.h"
#include "../include/menu.h"
#include "../include/validaciones.h"
#include "../include/utils.h"


int main(int argc, char* argv[]){
    int tamano, opt, *vector;
    double n;
    bool has_u = false, has_p = false, has_t = false, has_v = false, has_n = false;
    char *user = NULL, *password = NULL, *text = NULL, *text_vector = NULL, *text_n = NULL, *endptr;
    opterr = 0;

    exporta_env();

    while((opt = getopt(argc, argv, "u:p:t:v:n:")) != -1){
        switch(opt){
            case 'u':
                user = optarg;
                validUser(user);
                has_u = true;
                break;
            case 'p':
                password = optarg;
                validPass(user, password);
                has_p = true;
                break;
            case 't':  
                text = optarg;
                validText(text);
                has_t = true;
                break;
            case 'v':
                text_vector = optarg;
                vector = crea_vector(text_vector, &tamano);
                validVector(text_vector);
                has_v = true;
                break;
            case 'n':
                text_n = optarg;
                validN(text_n);
                n = convierte_n(text_n);
                has_n = true;
                break;
            default:
                fprintf(stderr, "Error. Ejecutar de forma\n./main -u <usuario> -p <contraseña> -t \"<texto>\" -v \"vector\" -n <numero>\n");
                exit(EXIT_FAILURE);
                break;
        }
    }
    if(!has_u || !has_p || !has_t || !has_v || !has_n){
        fprintf(stderr, "Error. Ejecutar de forma\n./main -u <usuario> -p <contraseña> -t \"<texto>\" -v \"vector\" -n <numero>\n");
        exit(EXIT_FAILURE);
    }

    menu(text, vector, tamano, n);

    return 0;
}