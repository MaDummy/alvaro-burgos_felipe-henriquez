#include <stdio.h>
#include <stdlib.h>
#include "opciones.h"
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>
#include "../include/utils.h"
#include <unistd.h>

void regresa_menu(){
    bool opcion_valida = true;
    int opcion;
    printf("\n\n\n");
    printf("1: Regresar al menú\n");
    printf("0: SALIR\n\n");
    printf("Escoja una opción: ");
    do{ 
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                break;
            case 0:
                printf("Saliendo del programa...\n");
                exit(0);
                break;
            default:
                printf("Error. Ingrese una opción válida: ");
        }
    }while(opcion != 1 && opcion != 0);
}