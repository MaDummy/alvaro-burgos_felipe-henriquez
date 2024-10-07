#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/utils.h"
#include "../include/file_utils.h"

void contar_palabras(FILE *archivoEntrada, FILE *archivoSalida, int *palabrasDiferentes) {
    char buffer[BUFFER_LINEA];
    int i;
    int max_palabras = 10000;
    char *token;
    char delimitadores[] = " \t\n\r\v\f;,";

    struct {
        char palabra[MAX_PALABRA];
        int ocurrencias;
    } conteo_palabras[max_palabras];

    int num_palabras = 0;


    while (fgets(buffer, sizeof(buffer), archivoEntrada)) {

        token = strtok(buffer, delimitadores);
        while (token != NULL) {

            int encontrada = 0;
            for (i = 0; i < num_palabras; i++) {
                if (strcmp(conteo_palabras[i].palabra, token) == 0) {
                    conteo_palabras[i].ocurrencias++;
                    encontrada = 1;
                    break;
                }
            }

            if (!encontrada && num_palabras < max_palabras) {
                strcpy(conteo_palabras[num_palabras].palabra, token);
                conteo_palabras[num_palabras].ocurrencias = 1;
                num_palabras++;
            }
            token = strtok(NULL, delimitadores);
        }
    }

    *palabrasDiferentes = num_palabras;

    for (i = 0; i < num_palabras; i++) {
        fprintf(archivoSalida, "%s; %d\n", conteo_palabras[i].palabra, conteo_palabras[i].ocurrencias);
    }
}


void procesar_archivos(char *directorioEntrada, char *extension, char *directorioSalida, char *pathArchivosSalida[MAX_ARCHIVOS], int cantidadPalabras[MAX_ARCHIVOS], int *contadorArchivos) {
    DIR *dir;
    struct dirent *archivoActual;
    FILE *archivoEntrada, *archivoSalida;
    char rutaEntrada[MAX_PATH], rutaSalida[MAX_PATH];
    int cont = 0;

    for (int i = 0; i < MAX_ARCHIVOS; i++) {
        pathArchivosSalida[i] = malloc(MAX_PATH * sizeof(char)); 
        if (pathArchivosSalida[i] == NULL) {
            fprintf(stderr, "Error al asignar memoria para la ruta de archivo %d\n", i);
            exit(EXIT_FAILURE);
        }
    }   

    dir = opendir(directorioEntrada);
    if (dir == NULL) {
        fprintf(stderr, "Error: no se puede abrir el directorio\n");
        exit(EXIT_FAILURE);
    }

    while ((archivoActual = readdir(dir)) != NULL) {
        if (strstr(archivoActual->d_name, extension) != NULL) {
            snprintf(rutaEntrada, sizeof(rutaEntrada), "%s/%s", directorioEntrada, archivoActual->d_name);

            remover_extension(archivoActual->d_name);

            snprintf(rutaSalida, sizeof(rutaSalida), "%s/%s.txt", directorioSalida, archivoActual->d_name);

            archivoEntrada = fopen(rutaEntrada, "r");
            if (archivoEntrada == NULL) {
                continue;
            }

            archivoSalida = fopen(rutaSalida, "w");
            if (archivoSalida == NULL) {
                fclose(archivoEntrada);
                continue;
            }

            contar_palabras(archivoEntrada, archivoSalida, &cantidadPalabras[cont]);

            fclose(archivoEntrada);
            fclose(archivoSalida);

            strncpy(pathArchivosSalida[cont], rutaSalida, MAX_PATH); 
            pathArchivosSalida[cont][MAX_PATH] = '\0';
            cont++;
        }
    }

    *contadorArchivos = cont;

    closedir(dir);
}

