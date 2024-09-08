#include <stdio.h>
#include <stdlib.h>
#include "../include/opciones.h"
#include <stdbool.h>

void menu(char *texto, int *vector, int tamano, double n){
    int opcion;
    bool opcion_valida = true;
    do{
        system("clear");
        printf("════ ∘◦Menu◦∘ ════\n\n");
        printf("Escoja una opción:\n");
        printf("1: Detectar palindrome\n");
        printf("2: Contar vocales\n");
        printf("3: Contar cantidad de letras\n");
        printf("4: Promedio y sumatoria del vector\n");
        printf("5: Calcular f(x) = 5x*x + 1/x\n");
        printf("6: SALIR\n\n");
        if(opcion_valida)
            printf("Escoja una opción: ");
        else{
            printf("Ingrese una opción válida: ");
            opcion_valida = true;
        }
        if (scanf("%d", &opcion) != 1) {
            // Si scanf no pudo leer un número, limpiar el buffer y marcar la opción como no válida
            while (getchar() != '\n'); // Limpia el buffer de entrada
            opcion_valida = false;
            continue;
        }

        switch (opcion){
            case 1:
                es_palindromo(texto);
                break;
            case 2:
                cuenta_vocales(texto);
                break;
            case 3:
                cuenta_letras(texto);
                break;
            case 4:
                suma_promedio_vector(vector, tamano);
                break;
            case 5:
                funcion_lineal(n);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                exit(0);
                break;
            default:
                opcion_valida = false;
        }
    } while (opcion != 6);
}


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