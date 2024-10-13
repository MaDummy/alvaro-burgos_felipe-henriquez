#include <stdio.h>
#include <stdlib.h>
#include "opciones.h"
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>
#include "../include/utils.h"
#include <unistd.h>

void menu(char *texto, int *vector, int tamano, double n, char *usuario, char *rol){
    int opcion;
    int ejecucion_conteo_paralelo = 1;
    bool opcion_valida = true;
    bool es_admin = (strcmp(rol, "admin") == 0);
    exporta_env();
    do{
        system("clear");
        printf("PID: %d\n", getpid());
        printf("Usuario: %s\n", usuario);
        printf("Rol: \"%s\"\n\n", rol);
        printf("════ ∘◦Menu◦∘ ════\n\n");
        printf("Escoja una opción:\n");
        printf("1: Detectar palindrome\n");
        printf("2: Contar vocales\n");
        printf("3: Contar cantidad de letras\n");
        printf("4: Promedio y sumatoria del vector\n");
        printf("5: Calcular f(x) = 5x*x + 1/x\n");
        printf("6: Menu conteo de palabras\n");
        printf("7: Conteo de palabras con %s threads\n", getenv("CANTIDAD_THREADS"));
        printf("8: Crear indice invertido\n");
        if(es_admin){
            printf("9: Agregar usuario\n");
            printf("10: Listar usuarios\n");
            printf("11: Eliminar usuario\n");
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
                system(getenv("ARCH_MENU"));
                break;
            case 7:
                ejecucion_conteo_paralelo = conteo_palabras_paralelo();
                break;
            case 8:
                crear_indice_invertido(ejecucion_conteo_paralelo);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                exit(0);
                break;
            case 9:
                if(es_admin){
                    anade_usuario();
                    break;
                }
            case 10:
                if(es_admin){
                    listar_usuarios();
                    break;
                    }
            case 11:
                if(es_admin){
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