#include <stdio.h>
//#include <bits/getopt_core.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/opciones.h"
#include "../include/menu.h"
#include "../include/validaciones.h"
#include "../include/utils.h"


// ./main texto vector tamano_vector n usuario rol
int main(int argc, char **argv){
    if (argc != 7){
        fprintf(stderr, "Error al llamar menu_principal, se requieren 6 parametros y se pasaron %d", argc - 1);
        sleep(5);
    }
    
    char *texto = argv[1];
    int tamano;
    int *vector = crea_vector(argv[2],&tamano);
    double n = convierte_n(argv[4]);
    char *usuario = argv[5];
    char *rol = argv[6];

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
        printf("9: Simulacion planificador\n");
        printf("10: Ejecutar conteo paralelo con distintos threads\n");
        printf("20: Buscador\n");
        if(es_admin){
            printf("11: Agregar usuario\n");
            printf("12: Listar usuarios\n");
            printf("13: Eliminar usuario\n");
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
            case 9:
                simular_planificador();
                break;
            case 10:
                llama_ejecutador();
                break;
            case 20:
                buscador();
                break;
            case 0:
                printf("Saliendo del programa...\n");
                exit(0);
                break;
            case 11:
                if(es_admin){
                    anade_usuario();
                    break;
                }
            case 12:
                if(es_admin){
                    listar_usuarios();
                    break;
                    }
            case 13:
                if(es_admin){
                    elimina_usuario();
                    break;
                    }
            default:
                opcion_valida = false;
        }
    } while (opcion != 0);
}