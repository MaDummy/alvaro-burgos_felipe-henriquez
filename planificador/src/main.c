#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../include/file_utils.h"
#include "../include/utils.h"

#define MAX_TEXT 512


typedef struct {
    long mtype;  // Tipo de mensaje.
    int core_id;  // Identificador del core que envía el mensaje.
} mensaje_core;

typedef struct {
    long mtype;             
    char text[MAX_TEXT];    
} mensaje_distribuidor;


int crear_cola_mensajes_core();
int crear_cola_mensajes_distribuidor();
void leer_mensaje_core(int id_cola, int *core_id);
void enviar_mensaje_distribuidor(int id_cola, const char* mensaje);

//./main path_procesos cant_cores path_resultados path_distribuidor path_cores
int main(int argc, char **argv){
    if (argc != 6){
        fprintf(stderr, "Error al llamar indice_invertido, se requieren 5 parametro y se pasaron %d", argc - 1);
    }

    char *process_path = argv[1];
    int cant_cores = atoi(argv[2]);
    char *resultados_path = argv[3];
    char *path_distribuidor = argv[4];
    char *path_core = argv[5];

    ejecuta_distribuidor(path_distribuidor, path_core, resultados_path);

    //Lee archivo de procesos y los guarda en un array
    char array_procesos[MAX_PROCESOS][MAX_LARGO_PROCESO];
    int cont = 0;

    leeProcesos(process_path, array_procesos, &cont);

    //Crea un array que define que cores estan disponibles, por defecto todos
    int *cores_disponibles = malloc(cant_cores * sizeof(int));

    //0 = disponible
    //1 = ocupado
    for (int i = 0; i < cant_cores; i++) {
        cores_disponibles[i] = 1;  
    }

    int msgid_core = crear_cola_mensajes_core();
    int msgid_distribuidor = crear_cola_mensajes_distribuidor();

    int id_core;
    char mensaje_para_distribuidor[MAX_TEXT];

    //Usa todos los core por primera vez antes de el flujo dinamico entre todos los procesos
    for(int i = 0; i < cant_cores; i++){
        cores_disponibles[i] = 0;

        crea_mensaje(i, array_procesos[i], mensaje_para_distribuidor);

        enviar_mensaje_distribuidor(msgid_distribuidor, mensaje_para_distribuidor);
        cores_disponibles[i] = 1;
    }

    //Muere si tenemos mas core que procesos, lo arreglo despues
    for(int i = cant_cores; i < cont; i++){
        leer_mensaje_core(msgid_core, &id_core);
        cores_disponibles[id_core] = 0;

        crea_mensaje(id_core, array_procesos[i], mensaje_para_distribuidor);

        enviar_mensaje_distribuidor(msgid_distribuidor, mensaje_para_distribuidor);
        cores_disponibles[id_core] = 1;
    }

    free(cores_disponibles);
    enviar_mensaje_distribuidor(msgid_distribuidor,"termina");

}

int crear_cola_mensajes_core() {
    key_t key = ftok("progfile", 65); // Genera una clave única
    int msgid = msgget(key, 0666 | IPC_CREAT); // Crea la cola de mensajes
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

int crear_cola_mensajes_distribuidor() {
    key_t key = ftok("progfile", 75);  // Genera una clave única
    int msgid = msgget(key, 0666 | IPC_CREAT); // Crea la cola de mensajes
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

void leer_mensaje_core(int id_cola, int *core_id) {
    mensaje_core msg;

    // Leer el mensaje de finalización de un core (espera a que llegue).
    if (msgrcv(id_cola, &msg, sizeof(msg.core_id), 2, 0) == -1) {
        perror("Error al recibir mensaje de finalización desde el core");
        exit(EXIT_FAILURE);
    }

    // Obtener el identificador del core que ha terminado.
    *core_id = msg.core_id;
}

void enviar_mensaje_distribuidor(int id_cola, const char* mensaje) {
    mensaje_distribuidor msg;
    msg.mtype = 1;  // Tipo genérico para mensajes de Planificador -> Distribuidor
    strncpy(msg.text, mensaje, MAX_TEXT - 1);  // Copia el mensaje a la estructura
    msg.text[MAX_TEXT - 1] = '\0'; // Asegura la terminación nula

    // Envía el mensaje a la cola
    if (msgsnd(id_cola, &msg, sizeof(msg.text), 0) == -1) {
        perror("Error al enviar mensaje a distribuidor");
        exit(EXIT_FAILURE);
    }
}