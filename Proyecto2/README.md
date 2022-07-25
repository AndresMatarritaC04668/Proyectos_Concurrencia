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

Los diagramas del design y la explicacion pueden ser encontrados en: [Design](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/blob/main/Proyecto2/design/README.md)

## Build

Lo primero que se debe hacer para compilar el codigo es dirigirse al directorio donde se encuentra el proyecto, en este caso **Proyecto2**, dentro de este directorio se encuentran otros de gran importancia como es el **src**, **design** entre otros. El archivo que realiza la mayor parte del built es el **Makefile**, este tiene una funcion **make** para la contruccion de los archivos punto objeto y el ejecutable.

Una vez en la ruta de directorio correcta se utiliza el comando del Makefile que se menciono anteriormente, seria **.../Proyecto2$ make** 

En la terminal seria de la siguiente manera:

![make](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/imgReadmePrincipal/make.png)

Ademas para el correcto funcionamiento de este programa es importante la creacion de una carpeta con el nombre **output** en la direccion anteriormente mencionada, ya que aqui se almacena los archivos binarios de respuesta y el reporte tsv.

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

### OpenMP
En primer lugar se realizo una implementacion serial del programa en la cual se priorizo una solucion eficaz que una solucion rapida o alguna optimizacion, sin embargo al realizar pruebas es posible ver que casos como el contenido en el Job003 llegan a tardar varios minutos, por lo cual se decidio volver al programa algo concurrente utilizando OpenMP, aprovechando las ventajas en sencillez y gran manejo de paralelismo de datos que esta herramienta prevee. Para realizar la implementacion de la mejora concurrente fue necesario seguir el proceso de profilling y optimizacion.

Para los primeros pasos se utilizo el codigo serial del proyecto con el caso **job003.txt**, el cual tuvo una duracion de **260.03 segundos**, acto seguido se utilizo la herramienta callgrind y kcachegrind para asi encontrar las zona del codigo donde mas se consumen recursos, el reporte del kcachegrind fue el siguiente:

![Kcachegrind](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/report/KcachegrindProyecto.png)

Podemos ver entonces que la seccion mas pesada del codigo es la relacionada a con el metodo Run, el cual contiene el metodo HeatTransfer que produce gran carga trabaja al realizar el metodo sumarCruz de manera constante y repetitiva, es importante destacar que este Run() se encarga de llamar a los metodos necesarios para calcular y simular el funcionamiento de una lamina .bin, por lo cual se considera oportuno la implementacion de openMP en esta seccion del codigo, para que cada hilo creado trabaje con una lamina por aparte, realizando las operaciones necesarias para alcanzar la estabilidad calorica, por esto mismo se usara el apartado schedule() para repartir las laminas de trabajo.  

El rendimiento obtenido de esta implementacion utilizando un schedule estatico por bloque corresponde con:  

**SpeedUp:** 2.10  
**Eficiencia:** 0.27  

El rendimiento obtenido de esta implementacion utilizando un schedule dinamico es el siguiente:  

**SpeedUp:** 4.45  
**Eficiencia:** 0.56  

Es posible ver como la implementacion de OpenMP permite obtener un speedUP del doble a 4 veces mas rapido que la version serial del mismo codigo, siendo la version con mapeo dinamico la que proporciona un mayor rendimiento al programa, debido a su naturaleza de aprovechar las capacidades de tener varios CPUs de mejor manera.  

### Analisis de rendimiento
A la hora de discutir sobre cómo los resultados de la implementación concurrente del código mediante OpenMP y el rendimiento obtenido de esta es importante considerar las diversas ventajas que esta herramienta presenta, como lo puede ser su sencilla e intuitiva implementación, su manejo eficiente de hilos mediante diversos mapeos, por lo cual no debe resultar una sorpresa los resultados obtenidos y el incremento de eficiencia del programa. Tal como se mencionó anteriormente el método Run() resultaba ser una parte poco eficiente para el funcionamiento general del programa, debido a que este trabajaba una por una las diversas láminas de cada Job, y al ser cada una de estas trabajadas como un vector de vectores, una matriz, los datos, operaciones y asignaciones a realizar resultaban en tareas repetitivas que cargaban el sistema, por esto OpenMP, al ser muy útil para el manejo de grandes cantidades de datos, resultó en una mejora significativa.

Para realizar las mediciones correspondientes y analizar los resultados, se decidió tomar el caso de Job 003.txt debido a que este presenta una combinación de placas pequeñas y grandes, las cuales producen que la carga de trabaja se encuentre dispersa a lo largo de todo el caso, en el gráfico siguiente es posible ver la diferencia en SpeedUp y Eficacia que el uso correcto de OpenMP puede producir:

![grafico](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/report/ComparacionSpeedUp-Eficiencia.png)

Podemos ver que en la versión serial la eficiencia y SpeedUp resultan ser de 1, si se compara con la versión estática el SpeedUp es el doble que su antecesor por lo que termina el doble de rápido sus tareas, sin embargo, al utilizar 8 hilos la eficiencia de esta versión resulta ser algo pobre en comparación a los recursos invertidos. En el caso de la versión concurrente es posible ver que el SpeedUp vuelve a ser el doble que su versión anterior, 4 veces más que la versión serial, y su eficiencia también aumenta sin alcanzar niveles considerables.

Para este gráfico se decidió utilizar 3 casos en vez de los 2 sugeridos en las instrucciones para dar un mejor panorama del rendimiento, y en el caso de la versión concurrente se eligió el mapeo dinámico ya que resultó la mejor opción.

Es posible concluir que el uso de herramientas que permitan la concurrencia como lo es OpenMP, resultan ser algo de gran utilidad a la hora de incrementar el rendimiento general del programa, permitiendo que la solución a casos de prueba más extremos puedan ser resueltos sin invertir tanto tiempo.

## Creditos

**Estudiante1:** Gabriel Antonio Chacon Garro **Carne:** C02063

**Estudiante2:** Andres Matarrita Miranda **Carne:** C04668

**Estudiante3:** Esteban Mora Garcia **Carne:** C05126
