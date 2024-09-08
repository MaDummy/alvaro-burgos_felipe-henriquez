#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utils.h"


void validUser(char *user){
    if(strlen(user) < 3){
        fprintf(stderr, "Error: El largo del nombre de usuario debe ser de mínimo 3 letras.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < strlen(user); i++){
        if (!isalpha(user[i])){
            fprintf(stderr, "Error: El nombre de usuario solo debe contener letras.\n");
            exit(EXIT_FAILURE);
        }
    }
}


void validPass(char *user, char *password){
    bool es_correcta = false;

    if(strlen(password) < 6){
        fprintf(stderr, "Error: El parámetro -p debe contener mínimo 6 caracteres.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < strlen(password); i++){
        if(!isalnum(password[i])){
            fprintf(stderr, "Error: El parámetro -p debe contener sólo números y/o letras.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Verificacion de usuario en variables de entorno.
    // Primero verifica que el usuario existe y luego verifica la contrasena
    int indice = busca_usuario_env(user);
    verifica_contrasena_env(password, indice);
}


void validVector(char *vector){
    bool busca_num = true;
    int cuenta_digitos = 0, cuenta_puntocoma = 0;
    for(int i = 0; i < strlen(vector); i++){
        if(!isdigit(vector[i]) && vector[i] != ';'){
            fprintf(stderr, "Error: Los argumentos de -v deben ser números separados por ';'.\n");
            exit(EXIT_FAILURE);
        }
        if(isdigit(vector[i]) && busca_num){
            cuenta_digitos ++;
            busca_num = false;
        }
        if(vector[i] == ';' && !busca_num){
            cuenta_puntocoma ++;
            busca_num = true;
        }
    }
    if(cuenta_puntocoma != (cuenta_digitos - 1)){
        fprintf(stderr, "Error: El vector no fue ingresado correctamente.\n");
        exit(EXIT_FAILURE);
    }
}


void validText(char *text){
    if(text == NULL){
        fprintf(stderr, "Este mensaje no se imprimirá nunca\n\n");
        exit(EXIT_FAILURE); // Esta instruccion tampoco
    }
    if(*text == '\0'){
        fprintf(stderr, "Error. Ingrese un texto no vacío.\n");
        exit(EXIT_FAILURE);
    }
}


void validN(char *n){
    int cuenta_puntos = 0; // Cuenta cantidad de puntos en el texto, ej: "2.1.3" cuenta 2 puntos.

    for(int i = 0; i < strlen(n); i++){
        if(n[i] == '.'){
            cuenta_puntos ++;
            continue;
        }
        if(!isdigit(n[i])){
            fprintf(stderr, "Error: El argumento -n debe ser un número.\n");
            exit(EXIT_FAILURE);
        }
    }
    if(cuenta_puntos > 1 || n[0] == '.'){ // Manejo de intentos de burla para los flotantes
        fprintf(stderr, "Error: El argumento -n debe ser un número.\n");
        exit(EXIT_FAILURE);
    }
}