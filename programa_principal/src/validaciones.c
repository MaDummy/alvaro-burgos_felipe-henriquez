#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utils.h"

bool validUser(char *user, char *contexto){
    if(strlen(user) < 3){
        if(strcmp(contexto, "anade") == 0){
            return false;
        }else{
        fprintf(stderr, "Error: El largo del nombre de usuario debe ser de mínimo 3 letras.\n");
        exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < strlen(user); i++){
        if (!isalpha(user[i])){
            if(strcmp(contexto, "anade") == 0){
                return false;
            }else{
            fprintf(stderr, "Error: El nombre de usuario solo debe contener letras.\n");
            exit(EXIT_FAILURE);
            }
        }
    }
    return true;
}


char *validPass(char *user, char *password){
    if(strlen(password) < 6){
        fprintf(stderr, "Fallo al iniciar sesión. Intente nuevamente.\n");
        exit(EXIT_FAILURE);
    }
    return verifica_usuario(user, password);
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