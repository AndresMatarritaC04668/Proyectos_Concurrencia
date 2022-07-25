### Diagrama del Simulador de Placas

![SimuladorPlaca](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/Diagrama_Funcionamiento_Proyecto02.png)

La imagen da un vistazo general de como es el funcionamiento general del programa de simulacion de placas, cuando el usuario introduce los datos mediante un archivo de texto, como los encontrados en la carpeta test, primero se analiza si el archivo introducido existe y si se introdujo un tercer argumento para los hilos, acto seguido se llama los metodos de la clase **simuladorPlacas**, la cual a su vez utilizan los struct contenidos en **structs**, para crear las laminas de trabajo y devolver los resultados en forma de laminas en archivos bin y un reporte en formato .tsv

### UML

![UML](https://git.ucr.ac.cr/JOSE.MATARRITAMIRANDA/proyectos/-/raw/main/Proyecto2/design/Diagrama_De_Estructuras_Proyecto02.png)

Este es el diagrama UML, el cual es muy util a la hora de moverse al codigo, muestra las clases que se necesitan para el funcionamiento, los metodos y variables que las componen, y como estas interaccionan entre si para producir los resultados buscados, para este trabajo se va a utilizar el lenguaje de **programacion C++**.

