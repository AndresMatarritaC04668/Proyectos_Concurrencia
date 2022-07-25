# Placas de Calor

## Problema a resolver

Con la ayuda de una simulacion por computadora se quiere encontrar el momento de equilibrio termico de una lamina rectangular, a esta se le esta inyectando calor constantemente por sus bordes, con el pasar del tiempo otras zonas de lamina recibiran calor. Es importante destacar que la lamina consiste en un rectangulo de dos dimensiones de un mismo material, para esta simulacion el rectanculo cuanta con R filas y C columnas las cuales tienen un mismo alto y ancho lo que va a generar una matriz con celdas cuadradas.

## Primer avance

Este proyecto consta de dos partes, para esta primera entrega se va a utilizar la tecnologia OpenMP para realizar el paralelismo de datos

### Objetivo del software 

Se espera que el programa utilice la tecnologia OpenMp y se vea un incremento de velocidad con la parelalizacion, que logre realizar todas las simulaciones dadas, una simulacion implica cargar la lamina como una matriz de memoria, realizarle actualizaciones a los estados hasta que se llegue al punto de equilibrio termico y realizar un reporte.

El reporte tiene las estadisticas resultantes luego de realizar la simulacion, cada vez que se ejecuta el programa este debe de crear o sobreescribir en el archivo de reporte correspondiente, un ejemplo del archivo de reporte es el siguiente:

![reporte](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/imgReadmePrincipal/ejemploReporte.png)

## Design

https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/tree/main/Proyecto2/design

## Build

Lo primero que se debe hacer para compilar el codigo es dirigirse al directorio donde se encuentra el proyecto, en este caso **Proyecto2**, dentro de este directorio se encuentran otros de gran importancia como es el **src**, **design** entre otros. El archivo que realiza la mayor parte del built es el **Makefile**, este tiene una funcion **make** para la contruccion de los archivos punto objeto y el ejecutable.

Una vez en la ruta de directorio correcta se utiliza el comando del Makefile que se menciono anteriormente, seria **.../Proyecto2$ make** 

En la terminal seria de la siguiente manera:

![make](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/imgReadmePrincipal/make.png)

## Manual de Uso

Este programa necesita de **3 parametros**, un ejecutable, seguido de este un archivo.txt y por ultimo la cantidad de hilos, **ejecutable archivo.txt hilos**, si el ultimo no se agrega entonces el programa utiliza la cantidad maxima de hilos que tenga la arquitectura. 

El Makefile creo un directorio llamado **bin/** en este se encuentra el ejecutable, se tiene otro directorio llamado **test/** donde se encuentran los archivos.txt que estan separados por directorios llamados **job---** y el numero de hilos lo pone el usuario.

Utilizando el job003 con 8 hilos, se veria de la siguiente manera: **.../Proyecto2$ bin/Proyecto02 test/job003/job003.txt 8**

En la terminal:

![correr_ejecutable](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/imgReadmePrincipal/correrPrograma.png)

### Pruebas

Se van a presentar dos casos de pruebas, el primero es el **job002**, el output que se espera es el siguiente:

![test002](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/imgReadmePrincipal/pruebaTest002.png)

Y el que genera el programa es:

![output002](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/imgReadmePrincipal/pruebaOutput002.png)

El siguiente caso es el **job003**, se muestra primero el output esperado:

![test003](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/imgReadmePrincipal/pruebaTest003.png)

Y el que muestra el programa es:

![output003](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/imgReadmePrincipal/pruebaOutput003.png)

## Creditos

**Estudiante1:** Gabriel Antonio Chacon Garro **Carne:** C02063

**Estudiante2:** Andres Matarrita Miranda **Carne:** C04668

**Estudiante3:** Esteban Mora Garcia **Carne:** C05126
