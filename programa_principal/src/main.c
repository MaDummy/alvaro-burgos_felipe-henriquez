#include <stdio.h>
//#include <bits/getopt_core.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/validaciones.h"
#include "../include/utils.h"


int main(int argc, char* argv[]){
    int tamano, opt, *vector;
    double n;
    bool has_u = false, has_p = false, has_t = false, has_v = false, has_n = false;
    char *user = NULL, *password = NULL, *text = NULL, *text_vector = NULL, *text_n = NULL, *endptr, *rol;
    opterr = 0;

    while((opt = getopt(argc, argv, "u:p:t:v:n:")) != -1){
        switch(opt){
            case 'u':
                user = optarg;
                validUser(user, "login");
                has_u = true;
                break;
            case 'p':
                password = optarg;
                rol = validPass(user, password);
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

    exporta_env();
    /*
    //Inicia cache
    char *path_cache = getenv("PATH_CACHE");
    char *puerto_cache = getenv("PUERTO_CACHE");
    char *puerto_motor_busqueda = getenv("PUERTO_MOTOR_BUSQUEDA");
    char *memory_size = getenv("MEMORY_SIZE");
    char comando[1024] = {0};
    snprintf(comando, 1024, "%s %s %s %s&", path_cache, puerto_cache, puerto_motor_busqueda, memory_size);
    system(comando);


    //Inicia motor de busqueda
    char *path_motor_busqueda = getenv("PATH_MOTOR_BUSQUEDA");
    char *topk = getenv("TOPK");
    char *inverted_index = getenv("INVERTED_INDEX");
    memset(comando, 0, sizeof(comando));
    snprintf(comando, 1024, "%s %s %s %s&", path_motor_busqueda, puerto_motor_busqueda, topk, inverted_index);
    system(comando);
    */

    //Inicia menu principal
    char *path_menu_princpial = getenv("PATH_MENU_PRINCIPAL");
    char comando[1024] = {0};
    snprintf(comando, 1024, "%s %s %s %d %f %s %s", path_menu_princpial, text, text_vector, tamano, n, user, rol);
    system(comando);
    
    return 0;
}