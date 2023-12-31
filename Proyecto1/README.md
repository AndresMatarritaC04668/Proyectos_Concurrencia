# Goldbach Server 


## Problema a resolver

Para el primer avance se tiene un codigo previo en C++ el cual es un servidor que utiliza el **paradigma de programacion serial**, este codigo no realiza los calculos ni la prevencion de errores en la entrada, solo se conecta a un puerto, por default el 8080. El problema a resolver en este proyecto es lograr que el servidor provisto por el profesor sea capaz de calcular la Conjetura de Goldbach a distintos numeros provistos y atender las solicitudes de varios usuarios al mismo tiempo, ademas de mejorar su rendimiento y seguridad en contra de entradas maliciosas y erradas.

Por otra parte , para el segundo avance se busca mejorar las desventajas que se encuentran en el primer avance.Esto debido a que para la primera entrega se construyó un servidor web que obtiene las sumas de goldbach por parte de una aplicación web serial.Por lo tanto , este diseño no es óptimo.Esto se debe a que cabe la posibilidad de que CPUs se encuentren desaprovechados mientras otro CPU  trabaja con cargas pesadas , aquí se puede notar una baja eficiencia.Por lo tanto para este segundo avance , se creará una solución donde se aprovechen más los recursos de la máquina y donde CPUs de la máquina no se encuentren desocupados cuando se trabajan con grandes cargas de trabajo.Para lograr este objetivo , se deberá crear una forma de descomposición de datos óptima que permita el correcto equilibrio de trabajo entre cada hilo. Para esto , la aplicación web tiene una función muy importante de crear tantas calculadoras de goldbach como CPUs  hay en la máquina.Para esto , se deberán convertir las calculadoras en hilos de ejecución.


## Objetivo del software

### Primer avance 

Para el primer avance se busca hacer que el servidor pueda calcular y mostrar al usuario la sumas de Goldbach de distintos numeros, brindar un buen manejo de errores para las entradas no validas y lograr la paralelizacion del servidor, para que este sea capaz de atender un numero determinado de usuarios al mismo tiempo. Para desarrollar este servidor Goldbach de la primera etapa se va a utilizar el paradignma de programacion serial y el lenguaje de programacion C++.  


### Segundo avance

En el segundo avance se busca la paralelizacion de la aplicacion web utilizada en el primer avance, implementando el modelo productor-consumidor e hilos de trabajo, todo esto con el objetivo de obtener una mejora de rendimiento significativo y realizar un mejor uso de los recursos disponibles.Para la segunda entrega se modifico el proyecto para aprovechar aun mas la concurrencia y los hilos en el servidor mediante la separacion de tareas en una 'linea de ensamblaje'.Es muy importante que para la creación  de esta línea de ensamblaje , todos los hilos tengan definidos su rol con claridad con el patrón concurrente. Esto con el fin de equilibrar mejor la carga de trabajo que se va a repartir a cada hilo de ejecución.        


## Design


## Manual de uso

### Como compilar?

Para compilar el programa se hace uso del archivo Makefile que se encuentra en dentro del directorio
llamado Proyecto1, por lo que lo primero que hay que hacer es abrir una terminal y dirigirse a este directorio **Proyecto1/** , luego de esto se aplica el comando make, este va a dirigirse al directorio llamado **src/** y va a tomar los archivos punto c y h para crear los archivos objeto (.o) y va a dejar un archivo ejecutable dentro del directorio llamado **bin/**.

![make](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/Makefile_make.png)

### Correr y finalizar el ejecutable

Una vez dentro del directorio Proyecto1 es muy sencillo, como se dijo anteriormente este ejecutable se encuentra dentro del directorio **bin/** y se llamma **Proyecto1**, por lo que en la terminal se agrega esa ruta, **bin/Proyecto1**. Se puede agregar un puerto o si no se agrega se toma por default el **puerto 8080**, para agregar uno en especifico es muy sencillo, la ruta quedaria de la siguiente manera **bin/Proyecto1 puerto**, ademas hay un segundo parametro opcioanl, este corresponde con la cantidad maxima de conecciones que puede tener el server quedando **bin/Proyecto1 puerto max_connections**.

Al ejecutar la ruta anterior, la terminal debe de estar de la siguiente manera:

![bin](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/ejecutable.png)

Seguidamente de esto se abre un navegador de internet, en este caso de utilza firefox, y se tiene que dirigir a **localhost:8080/**, porque se utilizo el puerto por default, sino fue asi, dirigirse al puerto elegido.

Para terminar el programa se puede finalizar de 2 maneras:

**Ctrl+C**: debe de ingresar en la terminal donde se esta corriendo el server un Ctrl + c, la respuesta del programa es que ya no va a recibir mas conecciones con el usuario por lo que finalizaria y se cierra el server.

**kill**: para detener el programa mediante el comando Kill, es importante abrir una segunda terminal en el mismo directivo del proyecto, acto seguido se introduce **ps -eu** en la consola, este desplegara las distintas actividades de Linux, luego debemos buscar la que tiene bin/Proyecto1 en su TIME COMMAND, nos fijamos en la columna "PID" para saber el numero de proceso, por ultimo ponemos el comando kill PID, siendo PID el numero anteriormente visto, para terminar el proceso.  
Esto se ve de la siguiente manera:

![kill](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/blob/main/Proyecto1/img/comando_Kill.png)  
En la consola donde se corrio el programa se imprimira la misma respuesta final que para el Ctrl + c

### Pruebas

Se le va a ingregar al server un input de numeros para que resuelva la conjetura de goldbach, tres numeros y un cuarto que no es un numero por lo que debe de decir que el ingreso no fue valido.

![consulta](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/consulta_Goldbach.png)

Y la respuesta que genera el servidor es la siguiente

![respuesta](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/Respuesta_Goldbach.png)

### Pruebas de Concurrencia 

Para probar la concurrencia se utilizará httperf , como en el segundo avance se tiene un mejor diseño que el primero se espera que este segundo avance sea más resistente a una prueba de estrés.Por lo tanto se hará una prueba con ambas versiones.Con los resultados se corrobora que al utilizar más concurrencia y una mejor versión en la segunda entrega , hace que sea posible aumentar los parametros del httperf(-- num-call y --rate) y poder ser capaz de responder a todas esas solicitudes.

Vamos a comprobar comprobar Httperf en la siguiente imagen con los siguientes parametros y sus resultados:

![HttperfAvance1](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/HttperfAvance1.jpeg)

#### Al usar estos parámetros obtenemos solicitudes  no correspondidas por parte del avance 1.No obstante , el avance 2 al usar estos mismos parámetros muestra 0 solicitudes no correspondidas:

![HttperfAvance2](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/HttperfAvance2.png)

### Observaciones finales
Podemos concluir con estos resultados que si bien el primer avance es concurrente , el diseño del avance 2 es más eficiente al tener más concurrencia y una mejor distribución del trabajo.


## Creditos

**Estudiante1:** Gabriel Antonio Chacon Garro **Carne:** C02063

**Estudiante2:** Andres Matarrita Miranda **Carne:** C04668

**Estudiante3:** Esteban Mora Garcia **Carne:** C05126
