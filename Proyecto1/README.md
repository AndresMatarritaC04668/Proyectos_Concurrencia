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


