#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char *reemplazaTexto(char *input_text, char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char *result = strdup(input_text);
    char line[256];
    char doc_name[256];
    char hash[20];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, " %[^,], %s", doc_name, hash) == 2) {
            // Construir la cadena de búsqueda
            char search_str[30];
            snprintf(search_str, sizeof(search_str), "(%s;", hash);
            
            char *pos = strstr(result, search_str);
            if (pos != NULL) {
                // Construir la cadena de reemplazo
                char replace_str[256];
                snprintf(replace_str, sizeof(replace_str), "(%s;", doc_name);
                
                // Calcular el tamaño necesario para el nuevo resultado
                size_t prefix_len = pos - result;
                size_t suffix_start = prefix_len + strlen(search_str);
                size_t new_size = strlen(result) - strlen(search_str) + strlen(replace_str) + 1;
                
                char *new_result = malloc(new_size);
                if (new_result == NULL) {
                    perror("Error de memoria");
                    fclose(file);
                    free(result);
                    return NULL;
                }
                
                // Copiar la parte anterior al hash
                strncpy(new_result, result, prefix_len);
                new_result[prefix_len] = '\0';
                
                // Agregar el reemplazo
                strcat(new_result, replace_str);
                
                // Agregar el resto del string original
                strcat(new_result, result + suffix_start);
                
                free(result);
                result = new_result;
            }
        }
    }

    fclose(file);
    return result;
}

int main(){
    char buffer[1024] = "amen;(42975;12);(80091;54)";
    printf("%s\n", reemplazaTexto(buffer, "data/conteo_palabras/mapa_archivos.txt"));
}