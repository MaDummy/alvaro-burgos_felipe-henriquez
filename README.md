README - Menú de opciones en C

DESCRIPCIÓN
Este programa está diseñado para ejecutarse en sistemas Unix/Linux y permite al usuario interactuar con varias funcionalidades a través de un menú. Existen dos roles: admin y generico. Las opciones varían según el rol del usuario.

Para usuarios con el rol "generico":

0. SALIR: Salir del programa.
1. Detectar palíndromos: Verifica si el texto ingresado es un palíndromo o no.
2. Contar vocales: Cuenta la cantidad de vocales en el texto ingresado.
3. Contar cantidad de letras: Cuenta la cantidad de letras en el texto ingresado.
4. Suma y promedio de un vector: Muestra el vector ingresado, además de la suma y el promedio de los componentes de este.
5. Función lineal: Calcula la función lineal f(x) = 5x^2 + 1/x para el número proporcionado.
6. Menu conteo de palabras: Llama a un proceso externo que crea un nuevo menu con las siguientes opciones.
    1. Ingresar extensión de los archivos: Opcion para ingresar una extension como .txt.
    2. Ingresar ruta de la carpeta de entrada: Opcion para ingresar la ruta a una carpeta donde se buscaran archivos con esa extension.
    3. Ingresar ruta de la carpeta de entrada: Opcion para ingresar la ruta a una carpeta donde se dejaran .txt por cada archivo en la carpeta de entrada, que mostraran las palabras unicas y sus ocurrencias.
    4. Ejecutar conteo de palabras: Si se uso el resto de opciones para ingresar informacion correctamente esta opcion va a buscar en la carpeta de entrada archivos con la extension dada, va a contar las ocurrencias de cada palabra unica, va a crear, por cada archivo leido, un txt en la carpeta de salida con cada palabra y sus ocurrencias, y mostrara en pantalla las rutas a esos txt y la cantidad de palabras diferentes que se anotaron en cada uno.
    0. Salir: termina el proceso externo y vuelve al menu principal.
7. Conteo paralelo: Se realiza el conteo de palabras de forma paralela. La cantidad de threads están especificados en la variable de entorno "CANTIDAD_THREADS".
8. Crear indice invertido: Solo si ya se ejecuto conteo paralelo. Lee el output de este para crear un archivo .INDEX con formato palabra;(IDX,ocurrencias);(IDX2,ocurrencias2).
9. Simular planificador: Simula un planificador que lee procesos de un archivo definido en la variable de entorno PROCESOS (con formato id_core;operacion;operador1,operador2) y decide a que "core" (proceso externo que puede realizar operaciones) esta libre, para enviarle un mensaje con el proceso y el core que le ejecutara a un "distribuidor" (proceso externo) que se lo pasa a un core y recibe la respuesta para escribirla en el archivo definido en la variable de entorno RESULTADOS. La cantidad de cores que se pueden usar esta definida en la variable de entorno CANTIDAD_CORES.
20. Buscador: Requiere que se hayan ejecutado "cache_prog" y "motor" por separado, esta opcion permite ingresar una combinacion de palabras separadas por espacios para buscarlas en los textos, esta combinacion se envia al proceso cache, que busca si ya se habia buscado (en cuyo caso devuelve la respuesta guardada) o la envia al proceso motor de busqueda, que realiza la busqueda en el archivo inverted_index.INDEX y devuelve una interseccion de documentos que contenian todas las palabras y la suma de sus ocurrencias. Contiene variables de entorno que se explican en consideraciones.

Para usuarios "admin": Además de las opciones anteriores, los administradores tienen tres opciones adicionales:

9. Agregar usuario: Permite agregar un nuevo usuario al sistema. Se solicita el nombre, contraseña y rol del usuario a agregar.
10. Listar usuarios: Muestra una lista con los nombres y roles de todos los usuarios.
11. Eliminar usuario: Elimina un usuario del sistema si el usuario a eliminar tiene el rol "generico". El programa solicita el nombre del usuario para proceder.

*COMPILACIÓN PASO A PASO

1. Clonar el repositorio.

2. Abrir el archivo desde la carpeta raíz

3. usar comando "make"

Los archivos fuente (.c) se encuentran en la carpeta src
Los archivos objetos (.o) se almacenan en la carpeta obj
Para cada carpeta se genera un main, el de menu_principal mueve a la carpeta raíz

Para eliminar los archivos objeto y el ejecutable, utilizar 'make clean'.

*EJECUCIÓN

Ejecutar el programa de la siguiente manera en la carpeta raíz

./main -u <usuario> -p <contraseña> -t "<texto>" -v "<vector>" -n <numero entero o flotante>

Si quiere usar el buscador tambien debe ejecutar, terminales diferentes

./motor
./cache_prog

En ese orden

NOTAR que el texto y el vector van entre comillas dobles.

Consideraciones:
- El nombre de usuario -u solo debe tener letras, y es de largo mínimo 3. Los usuarios validados son aquellos que se encuentran en el archivo users.txt en la carpeta '/data'

- La contraseña -p contiene al menos 6 caracteres alfanuméricos. Las contraseñas válidas son aquellas que se encuentran en el archivo users.txt. La contraseña que se le asigna a cada usuario va junto al nombre, separado por un ';' en el archivo users.txt.

- El texto -t debe ser no vacío. Fuera de eso, el texto puede contener todo tipo de caracteres.

- El vector -v debe ser ingresado como valores numéricos ENTEROS separados por ';', ejemplo: -v "1;2;3;4".

- El valor -n debe ser un número entero o flotante (decimal).

- TODOS los parámetros son obligatorios.

- Para el menu de conteo de palabras no puede entregar la misma carpeta para input y output

- Conteo paralelo e indice invertido usan variables de entorno para decidir carpetas de input, output y extension de los archivos. Por defecto estas estan definidas con carpetas que vienen con el programa, se pueden modificar en el .env de la carpeta raiz. Las variables de entorno que le interesaria cambiar al usuario son:
    - CANTIDAD_THREADS: Con cuantos threads se hace el conteo paralelo
    - INVERTED_INDEX: Output donde guardar el archivo output de inverted_index, debe terminar en nombre.INDEX
    - PATH_INPUT: Path a carpeta con textos que se desean procesar en conteo de palabras paralelo
    - PATH_OUTPUT: Path a carpeta donde se desea guardar output de conteo de palabras paralelo
    - EXTENSION: Extension de los archivos que se desean procesar

- Buscador contiene las siguientes variables de entorno que le podrian interesar al usuario:
    - MEMORY_SIZE: Tamaño de respuestas que se guardaran en la cache
    - TOPK: El numero de documentos que devuelve la busqueda en motor de busqueda, se entregan los TOPK con mayor puntaje
    - PUERTO_CACHE: puerto que usa la cache para comunicarse con otros procesos, se puede cambiar si el usuario necesita usar ese puerto para otra cosa
    - PUERTO_MOTOR_BUSQUEDA: puerto que usa el motor de busqueda para comunicarse con otros procesos, se puede cambiar si el usuario necesita usar ese puerto para otra cosa