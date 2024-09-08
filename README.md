README - Menú de opciones en C

*DESCRIPCION

Este programa está diseñado para ejecutarse en sistemas Unix/Linux/Mac y permite al usuario interactuar con varias funcionalidades a través de un menú. Una vez en ejecución, el usuario tiene 6 opciones disponibles más una sexta opción para salir del programa:

1. Detectar palíndromos: Verifica si el texto ingresado es palíndromo o no

2. Contar vocales: Cuenta la cantidad de vocales en el texto ingresado.

3. Contar cantidad de letras: Cuenta la cantidad de letras en el texto ingresado.

4. Suma y promedio de un vector: Muestra el vector ingresado, además de la suma y el promedio de los componentes de este.

5. Función lineal: Calcula la función lineal f(x) = 5x^2 + 1/x para el n proporcionado.

6. SALIR: Salir del programa.

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
- El nombre de usuario -u solo debe tener letras, y es de largo mínimo 3. Los usuarios validados son aquellos que se encuentran en el archivo .env en la variable USERS.

- La contraseña -p contiene al menos 6 caracteres alfanuméricos. Las contraseñas válidas son aquellas que se encuentran en el archivo .env en la variable PASSWORDS. La contraseña que se le asigna a cada usuario va en el mismo orden en el que se encuentran en la variable. (Ej: usuario = juana, contraseña = juanita2003)

- El texto -t debe ser no vacío. Fuera de eso, el texto puede contener todo tipo de caracteres.

- El vector -v debe ser ingresado como valores numéricos ENTEROS separados por ';', ejemplo: -v "1;2;3;4".

- El valor -n debe ser un número entero o flotante (decimal).

- TODOS los parámetros son obligatorios.
