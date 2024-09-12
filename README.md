README - Menú de opciones en C

DESCRIPCIÓN
Este programa está diseñado para ejecutarse en sistemas Unix/Linux/Mac y permite al usuario interactuar con varias funcionalidades a través de un menú. Existen dos roles: admin y generico. Las opciones varían según el rol del usuario.

Para usuarios con el rol "generico":

0. SALIR: Salir del programa.
1. Detectar palíndromos: Verifica si el texto ingresado es un palíndromo o no.
2. Contar vocales: Cuenta la cantidad de vocales en el texto ingresado.
3. Contar cantidad de letras: Cuenta la cantidad de letras en el texto ingresado.
4. Suma y promedio de un vector: Muestra el vector ingresado, además de la suma y el promedio de los componentes de este.
5. Función lineal: Calcula la función lineal f(x) = 5x^2 + 1/x para el número proporcionado.
Para usuarios "admin": Además de las opciones anteriores, los administradores tienen tres opciones adicionales:

6. Agregar usuario: Permite agregar un nuevo usuario al sistema. Se solicita el nombre, contraseña y rol del usuario a agregar.
7. Listar usuarios: Muestra una lista con los nombres y roles de todos los usuarios.
8. Eliminar usuario: Elimina un usuario del sistema si el usuario a eliminar tiene el rol "generico". El programa solicita el nombre del usuario para proceder.

*COMPILACIÓN PASO A PASO

1. Clonar el repositorio.

2. Abrir el archivo desde la carpeta raíz, en donde se encuentra el archivo Makefile.

3. Una vez en la carpeta, ejecutar 'make' en la consola. Esto compilará todos los archivos fuente y generará el ejecutable main.

Los archivos fuente (.c) se encuentran en la carpeta src
Los archivos objetos (.o) se almacenan en la carpeta obj
El ejecutable final (main) se generará en la carpeta raíz (misma altura del makefile)

Para eliminar los archivos objeto y el ejecutable, utilizar 'make clean'.

*EJECUCIÓN

Ejecutar el programa de la siguiente manera

./main -u <usuario> -p <contraseña> -t "<texto>" -v "<vector>" -n <numero entero o flotante>

NOTAR que el texto y el vector van entre comillas dobles.

Consideraciones:
- El nombre de usuario -u solo debe tener letras, y es de largo mínimo 3. Los usuarios validados son aquellos que se encuentran en el archivo users.txt en la carpeta '/data'

- La contraseña -p contiene al menos 6 caracteres alfanuméricos. Las contraseñas válidas son aquellas que se encuentran en el archivo users.txt. La contraseña que se le asigna a cada usuario va junto al nombre, separado por un ';' en el archivo users.txt.

- El texto -t debe ser no vacío. Fuera de eso, el texto puede contener todo tipo de caracteres.

- El vector -v debe ser ingresado como valores numéricos ENTEROS separados por ';', ejemplo: -v "1;2;3;4".

- El valor -n debe ser un número entero o flotante (decimal).

- TODOS los parámetros son obligatorios.
