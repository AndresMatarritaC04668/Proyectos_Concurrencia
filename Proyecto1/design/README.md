### Parte 1
### Diagrama del servidor

![Server](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/design/Diagrama_Server_Parte1.png)

La imagen da un vistazo general de como es el funcionamiento del servidor, cuando el cliente realiza un request, primero se presenta la creacion de los sockets, se almacenan en un contenedor, el WebServer se encarga de manejar estos request para luego ser enviados a la WebApp en este caso la **GoldbachWebApp** para calcular la conjetura.

### UML

![UML](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto1/design/Uml.png)

Este es el diagrama UML, el cual es muy util a la hora de moverse al codigo, muestra las clases que se necesitan para el funcionamiento y como estas interaccionan entre ellas mismas por lo que facilita la implementacion en codigo, para este trabajo se va a utilizar el lenguaje de **programacion C++**.

### Parte 2
### Diagrama del servidor 1.2

![Server](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/blob/main/Proyecto1/design/Diagrama_Server_Parte1.2.png)

En la parte 2 fue necesario volver concurrente la aplicacion Web, para lograr esto se decidio crear varias clases para repartir el trabajo a realizar, se creo una clase capaz de analizar las solicitudes que entran a la WebApp **(decodeSolver)**, las calculadores fueron convertidos en hilos de trabajo **(solvers)**, una clase se encarga de revisar que todo el trabajo de una solicitud fuera realizado **(Empaquetador)** y otra se encarga de mostrar la respuesta a la solicitud **(despachador)**

