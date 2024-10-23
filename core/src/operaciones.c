#include <string.h>
#include "../include/operaciones.h"

float obten_resultado(char* operacion, float argumento1, float argumento2){
    if (strcmp(operacion,"suma") == 0){
        return argumento1 + argumento2;
    }
    else{
        if (strcmp(operacion,"resta") == 0){
            return argumento1 - argumento2;
        }
        else{
            if (strcmp(operacion,"multiplicacion") == 0){
                return argumento1 * argumento2;
            }
            else{
                return argumento1 / argumento2;
            }
        }
    }
}