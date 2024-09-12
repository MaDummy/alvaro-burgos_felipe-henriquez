#include <stdio.h>
#include <stdlib.h>
#include "opciones.h"
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>

void menu(char *texto, int *vector, int tamano, double n, char *usuario, char *rol){
    pid_t pid;
    int opcion;
    bool opcion_valida = true;
    do{
        system("clear");
        printf("PID: %d\n", pid);
        printf("Usuario: %s\n", usuario);
        printf("Rol: \"%s\"\n\n", rol);
        printf("════ ∘◦Menu◦∘ ════\n\n");
        printf("Escoja una opción:\n");
        printf("1: Detectar palindrome\n");
        printf("2: Contar vocales\n");
        printf("3: Contar cantidad de letras\n");
        printf("4: Promedio y sumatoria del vector\n");
        printf("5: Calcular f(x) = 5x*x + 1/x\n");
        if(strcmp(rol, "admin") == 0){
            printf("6: Agregar usuario\n");
            printf("7: Listar usuarios\n");
            printf("8: Eliminar usuario\n");
        }
        printf("0: SALIR\n\n");
        if(opcion_valida)
            printf("Escoja una opción: ");
        else{
            printf("Ingrese una opción válida: ");
            opcion_valida = true;
        }
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
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
                system("../../menu_secundario/main");
                break;
            case 0:
                printf("Saliendo del programa...\n");
                exit(0);
                break;
            case 7:
                if(strcmp(rol, "admin") == 0){
                    anade_usuario();
                    break;
                }
            case 8:
                if(strcmp(rol, "admin") == 0){
                    listar_usuarios();
                    break;
                    }
            case 9:
                if(strcmp(rol, "admin") == 0){
                    elimina_usuario();
                    break;
                    }
            default:
                opcion_valida = false;
        }
    } while (opcion != 0);
}


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