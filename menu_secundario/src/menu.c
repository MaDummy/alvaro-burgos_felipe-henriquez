#include <stdio.h>
#include <stdlib.h>
#include "../include/opciones.h"
#include <stdbool.h>
#include <unistd.h>
#include "../include/validaciones.h"
#include "../include/file_utils.h"


void regresa_menu(){
    bool opcion_valida = true;
    int opcion;
    printf("\n\n\n");
    printf("1: Regresar al menú\n");
    printf("2: SALIR\n\n");
    printf("Escoja una opción: ");
    do{ 
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                break;
            case 2:
                printf("Saliendo del programa... :(\n");
                exit(0);
                break;
            default:
                printf("Error. Ingrese una opción válida: ");
        }
    }while(opcion != 1 && opcion != 2);
}

