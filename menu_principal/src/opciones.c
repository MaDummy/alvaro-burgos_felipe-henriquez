#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h> // Para usar booleanos
#include <ctype.h>   // Para funciones de caracteres (isdigit, tolower)
//#include <bits/getopt_core.h> // Tira error si no se implementa ojo piojo
#include "../include/menu.h"  // Incluye la funcion regresa_menu
#include "../include/validaciones.h"
#include "../include/utils.h"

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
    float sumatoria = 0;
    for(int i = 0; i < tamano; i++)
        sumatoria += vector[i];
    printf("Vector ingresado: ");
    imprime_vector(vector, tamano);
    printf("\n\n");
    if((sumatoria/tamano - (int)sumatoria/tamano) == 0){
        int sumatoria_int = (int)sumatoria;
        printf("La sumatoria del vector es de %.0f.\nEl promedio es de %d.", sumatoria, sumatoria_int/tamano);
    }
    else
        printf("La sumatoria del vector es de %.0f.\nEl promedio es de %.3f.", sumatoria, sumatoria/tamano);
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


void anade_usuario(){
    exporta_env();
    char *filename = getenv("ARCH_USUARIOS");
    char user[50], pass[50], rol[50], linea[150];
    bool user_val = false, pass_val = false, rol_val = false;
    system("clear");
    printf("════ ∘◦Opcion 8◦∘ ════\n\n");
    do{
        printf("Ingrese un usuario de largo minimo 3, sin numeros ni caracteres especiales: ");
        scanf("%s", user);
        user_val = validUser(user, "anade");
    }while(!user_val);

    do{
        printf("Ingrese contraseña de mínimo 6 caracteres: ");
        scanf("%s", pass);
        if(strlen(pass) > 5) pass_val = true;
    }while(!pass_val);

    do{
        printf("Ingrese nuevo rol (generico/admin): ");
        scanf("%s", rol);
        if(strcmp(rol, "generico") == 0 || strcmp(rol, "admin") == 0) rol_val = true;
    }while(!rol_val);

    FILE *file = fopen(filename, "a");
    fprintf(file, "%s; %s; %s\n", user, pass, rol);

    fclose(file);

    printf("\nUsuario añadido con éxito.");
    regresa_menu();
}


void listar_usuarios(){
    exporta_env();
    char *filename = getenv("ARCH_USUARIOS");
    // Abrir el archivo en modo de lectura
    FILE *file = fopen(filename, "r");
    char line[100];
    int i = 1;

    system("clear");
    printf("════ ∘◦Opcion 9◦∘ ════\n\n");
    // Leer el archivo línea por línea
    while (fgets(line, sizeof(line), file)) {
        // Eliminar el salto de línea al final de la línea, si existe
        line[strcspn(line, "\n")] = '\0';
        // Verificar si la línea es vacía
        if (strlen(line) == 0) {
            continue;  // No imprimir líneas vacías
        }
        char *user = strtok(line, "; ");
        strtok(NULL, ";");
        char *rol = strtok(NULL, "; ");

        // Imprimir la línea
        printf("%d. \"%s\", Rol: %s\n", i++, user, rol);
    }
    regresa_menu();

    // Cerrar el archivo
    fclose(file);
}


void elimina_usuario(){
    exporta_env();
    char *user, *pass, *rol, usuario[50];
    char *filename = getenv("ARCH_USUARIOS");
    char *temp_filename = getenv("ARCH_TEMP");
    FILE *file = fopen(filename, "r");

    // Archivo temporal para reescribir los usuarios que no se borrarán
    FILE *temp_file = fopen(temp_filename, "w");

    char line[100];
    bool se_elimino = false;
    
    system("clear");
    printf("════ ∘◦Opcion 10◦∘ ════\n\n");
    printf("Ingrese usuario a eliminar: ");
    scanf("%s", usuario);

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        user = strtok(line, "; ");
        pass = strtok(NULL, "; ");
        rol = strtok(NULL, "; ");

        if (strcmp(user, usuario) == 0 && strcmp(rol, "generico") == 0) {
            printf("Usuario %s eliminado.", user);
            se_elimino = true;
            continue;
        }
        // Si no se eliminó, escribir la línea en el archivo temporal
        fprintf(temp_file, "%s;%s;%s\n", user, pass, rol);
    }

    fclose(file);
    fclose(temp_file);

    if (se_elimino) {
        remove(filename);
        rename(temp_filename, filename);
    } else {
        remove(temp_filename);
        printf("No se encontró el usuario \"%s\" o es administrador.\n", usuario);
    }
    regresa_menu();
}