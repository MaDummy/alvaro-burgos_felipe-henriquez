#include "../include/utils.h"
#include "../include/file_utils.h"
#include "../include/menu.h"
#include <stdlib.h>


int main(int argc, char **argv){
    
    if (argc != 2) {
        fprintf(stderr, "Error al llamar indice_invertido, se requiere 1 parametro y se pasaron %d", argc - 1);
        return 1;
    }

    char *path_index = argv[1];

    exporta_env();

    char *path_output = getenv("PATH_OUTPUT");
    char *mapa_archivos = getenv("MAPA_ARCHIVOS");
    char *extension = getenv("EXTENSION");

    TablaHash tabla;
    tabla.palabrasDiferentesTabla = 0;
    for (int i = 0; i < TAMANO_TABLA_HASH; i++) {
        tabla.tabla[i] = NULL;
    }

    char nombres_archivos[MAX_ARCHIVOS][MAX_NOM_ARCHIVO];
    int ids[MAX_ARCHIVOS];
    int cantidad_archivos;

    leerMapaArchivos(mapa_archivos, nombres_archivos, ids, &cantidad_archivos);

    procesarArchivosOutput(&tabla, path_output, extension, nombres_archivos, ids, cantidad_archivos);

    escribirIndiceInvertido(path_index, &tabla);

    mensaje(path_index);

    return 0;
}