#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h> // Para usar booleanos
#include <ctype.h>   // Para funciones de caracteres (isdigit, tolower)
#include <bits/getopt_core.h> // Tira error si no se implementa ojo piojo
#include "../include/menu.h"  // Incluye la funcion regresa_menu


void imprime_vector(int *vector, int tamano){
    printf("[");
    for(int i = 0; i < tamano-1; i++){
        printf("%d, ", vector[i]);
    }
    printf("%d]", vector[tamano-1]);
}


int *crea_vector(char *vector, int *tamano){
    bool busca_numero = true;
    int j = 0;
    *tamano = 1;

    // Primero se determina el tamano del vector
    for(int i = 0; vector[i] != '\0'; i++)
        if (vector[i] == ';'){
            (*tamano) ++;
        }
    
    int *vector_nuevo = (int*)malloc(*tamano * sizeof(int));

    char *num = strtok(vector, ";");
    while(num != NULL){
        vector_nuevo[j++] = atoi(num);
        num = strtok(NULL, ";");
    }
    
    return vector_nuevo;
}


void suma_promedio_vector(int *vector, int tamano){
    system("clear");
    printf("════ ∘◦Opcion 4◦∘ ════\n\n");
    int sumatoria = 0;
    for(int i = 0; i < tamano; i++)
        sumatoria += vector[i];
    printf("Vector ingresado: ");
    imprime_vector(vector, tamano);
    printf("\n\n");
    printf("La sumatoria del vector es de %d.\nEl promedio es de %d.", sumatoria, sumatoria/tamano);
    regresa_menu();
}


void es_palindromo(char *text){
    system("clear");
    printf("════ ∘◦Opcion 1◦∘ ════\n");
    bool si_es = true; // variable que almacena si el texto es o no palindrome
    // preprocesamiento del texto para quitarle los espacios entre medio y transformar el texto a minusculas
    char texto_nuevo[strlen(text)];
    int j = 0;
    for(int i = 0; i < strlen(text); i++){
        if(isspace(text[i])) continue;
        texto_nuevo[j] = tolower(text[i]);
        j++;
    }
    texto_nuevo[j] = '\0';

    // caso texto vacio => Excepcion
    if (strlen(text) == 0){
        return;
    }

    // por cada índice, checa si el caracter del indice contrario es igual, si no, retorna falso
    //amo a la blanca paloma
    for(int i = 0; i < (strlen(texto_nuevo)/2) && si_es; i++){
        if(texto_nuevo[i] != texto_nuevo[strlen(texto_nuevo)-i-1]){
            si_es = false;
            break;
        }
    }
    if(si_es)
        printf("\nEl texto '%s' es palindromo.", text);
    else
        printf("\nEl texto '%s' no es palindromo.", text);

    regresa_menu();
}


void cuenta_vocales(char* text){
    system("clear");

    printf("════ ∘◦Opcion 2◦∘ ════\n");
    int contador = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        switch (tolower(text[i])){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                contador ++;
                break;
            }
    }
    printf("\nLa cantidad de vocales del texto '%s' es de %d.", text, contador);

    regresa_menu();
}


void cuenta_letras(char *text){
    system("clear");
    printf("════ ∘◦Opcion 3◦∘ ════\n");
    int contador = 0;
    for(int i = 0; i < strlen(text); i++)
        contador = isalpha(text[i]) ? contador + 1 : contador;
    
    printf("\nCantidad de letras en '%s' = %d", text, contador);
    regresa_menu();
}


void funcion_lineal(double n){
    system("clear");
    printf("════ ∘◦Opcion 5◦∘ ════\n");
    if(n == 0){
        printf("\nError: división por cero no permitida.");
    }else{
        if(n - (int)n == 0){
            int m = (int)n;
            printf("\nf(%d) = 5(%d*%d) + 1/(%d)", m, m, m, m);
            printf("\nf(%d) = %.2f", m, 5*n*n + 1/n);
        }else{
            printf("\nf(%.3f) = 5(%.3f*%.3f) + 1/(%.3f)", n, n, n, n);
            printf("\nf(%.3f) = %.3f", n, 5*n*n + 1/n);
        }
    }
    regresa_menu();
}