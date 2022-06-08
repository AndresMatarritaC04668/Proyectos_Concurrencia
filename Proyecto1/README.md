# Goldbach Server

## Problema a resolver

Se tiene un codigo previo en C++ el cual es un servidor que utiliza el **paradigma de programacion serial**, este codigo no realiza los calculos ni la prevencion de errores en la entrada, solo se conecta a un puerto, por default el 8080. El problema a resolver es lograr que el servidor pueda calcular la Conjetura de Goldbach a distintos numeros.

## Objetivo del software

Para este primer avance se busca hacer que el servidor pueda calcular y mostrar al usuario la sumas de Goldbach de distintos numeros y asi un buen manejo de errores para las entradas no validas. Para desarrollar este servidor Goldbach de la primera etapa se va a utilizar el paradignma de programacion serial y el lenguaje de programacion C++.

## Design

### Diagrama del servidor

![Server](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/design/Diagrama_Server_Parte1.png)

La imagen da un vistazo general de como es el funcionamiento del servidor, cuando el cliente realiza un request, primero se presenta la creacion de los sockets, se almacenan en un contenedor, el WebServer se encarga de manejar estos request para luego ser enviados a la WebApp en este caso la **GoldbachWebApp** para calcular la conjetura.

### UML

![UML](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/design/Uml.png)

Este es el diagrama UML, el cual es muy util a la hora de moverse al codigo, muestra las clases que se necesitan para el funcionamiento y como estas interaccionan entre ellas mismas por lo que facilita la implementacion en codigo, para este trabajo se va a utilizar el lenguaje de **programacion C++**.

## Manual de uso

### Como compilar?

Para compilar el programa se hace uso del archivo Makefile que se encuentra en dentro del directorio
llamado Proyecto1, por lo que lo primero que hay que hacer es abrir una terminal y dirigirse a este directorio **Proyecto1/** , luego de esto se aplica el comando make, este va a dirigirse al directorio llamado **src/** y va a tomar los archivos punto c y h para crear los archivos objeto (.o) y va a dejar un archivo ejecutable dentro del directorio llamado **bin/**.

![make](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/Makefile_make.png)

### Correr y finalizar el ejecutable

Una vez dentro del directorio Proyecto1 es muy sencillo, como se dijo anteriormente este ejecutable se encuentra dentro del directorio **bin/** y se llamma **Proyecto1**, por lo que en la terminal se agrega esa ruta, **bin/Proyecto1**. Se puede agregar un puerto o si no se agrega se toma por default el **puerto 8080**, para agregar uno en especifico es muy sencillo, la ruta quedaria de la siguiente manera **bin/Proyecto1 puerto**.

Al ejecutar la ruta anterior, la terminal debe de estar de la siguiente manera:

![bin](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/ejecutable.png)

Seguidamente de esto se abre un navegador de internet, en este caso de utilza firefox, y se tiene que dirigir a **localhost:8080/**, porque se utilizo el puerto por default, sino fue asi, dirigirse al puerto elegido.

Para terminar el programa se puede finalizar de 2 maneras:

**Ctrl+C**: debe de ingresar en la terminal donde se esta corriendo el server un Ctrl + c, la respuesta del programa es que ya no va a recibir mas conecciones con el usuario por lo que finalizaria y se cierra el server.

**kill**: ...

### Prueba

Se le va a ingregar al server un input de numeros para que resuelva la conjetura de goldbach, tres numeros y un cuarto que no es un numero por lo que debe de decir que el ingreso no fue valido.

![consulta](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/consulta_Goldbach.png)

Y la respuesta que genera el servidor es la siguiente

![respuesta](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/img/Respuesta_Goldbach.png)

## Creditos

**Estudiante1:** Gabriel Chacon segundo_apellido **Carne:** C*****

**Estudiante2:** Andres Matarrita Miranda **Carne:** C04668

**Estudiante3:** Esteban Mora Garcia **Carne:** C05126
