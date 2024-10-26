#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
        while (getchar() != '\n')
        switch(opcion){
            case 1:
                break;
            case 0:
                printf("Saliendo del programa... :(\n");
                exit(0);
                break;
            default:
                printf("Error. Ingrese una opción válida: ");
        }
    }while(opcion != 1 && opcion != 0);
}

void mensaje_progreso(){
    system("clear");
    printf("════ ∘◦Simulador de planificador◦∘ ════\n\n");
    printf("PID: %d.\n\n", getpid());
    printf("Se estan Ejecutando los procesos\n");
}

void mensaje(char *ruta_resultados){
    system("clear");
    printf("════ ∘◦Simulador de planificador◦∘ ════\n\n");
    printf("PID: %d.\n\n", getpid());
    printf("Se terminaron todos los procesos\n");
    printf("La ruta es de resultados es: %s ", ruta_resultados);
    regresa_menu();
}



