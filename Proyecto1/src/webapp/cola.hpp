// "Copyright 2022 <Andres Matarrita>"
#ifndef TAREAS_GOLDBACH_SERIAL_SRC_COLA_H_
#define TAREAS_GOLDBACH_SERIAL_SRC_COLA_H_
#include <inttypes.h>
#include <string>
#include "nodo.hpp"

/**
 * @brief struct de la clase cola, trabaja con la clase nodo
 * @param first referencia al primer nodo de la cola
 * @param last referencia al ultimo nodo de la cola
 */
typedef struct {
    nodo_t* first;
    nodo_t* last;
} cola_t;

/**
 @brief Crea una nueva cola dinamicamente ,  inicializa los atributos de la cola en null
 @return Retorna el puntero de la nueva cola creada
*/
cola_t* cola_init();

/**
 @brief Itera hasta encontrar el nodo solicitado
 @param cola Referencia de la cola en la que se busca el nodo
 @param posicion Posicion que tiene el nodo en la cola
 @return Retorna el nodo que se solicita
*/
nodo_t* cola_getNodo(cola_t* cola , int64_t posicion);

/**
 @brief Elimina el primer nodo de la cola 
 @param cola Cola a la que se le elimina el primer nodo
 @return devuelve
 * un 1 si termina correctamente
 * un 0 si presenta alguna falla
 */
int cola_delete(cola_t* cola);

/**
 @brief Libera a la cola y sus nodos
 @param cola Cola_t que se va a liberar
*/
void cola_destroy(cola_t* cola);

/**
 @brief Imprime los datos del nodo y si es negativo imprime
  el desglose de sumas del numero
 @param cola  Cola que contiene los datos que se van a imprimir 
*/
void cola_print(cola_t* cola);

/**
 @brief Crea un nodo nuevo y lo agrega a la cola ,  primero lo inicializa
 @param cola Referencia de la cola a la que se va agregar el nodo
 @param sumas Cantidad de sumas posibles encontradas
 @param signo Char que identifica si un numero es negativo ('-')
 @param nuevoValor Numero a demostrar con goldbach
 @return Retorna un Exit_Success si termina correctamente
*/
int cola_add(cola_t* cola  ,  int64_t nuevoValor , int sumas  ,
char signo , int64_t error , std::string numeroErroneo);

/**
 @brief Devuelve el char signo de un numero
 @param cola  Contiene el nodo que tiene el char a devolver
 @return Retorna un char:
 '-' Si el numero es negativo
 ' ' Si el numero es positivo
*/ 
char cola_getSigno(cola_t* cola);

/**
 @brief Devuelve el numero  int64_t  de un nodo 
 @param cola Cola que tiene el nodo que posee el numero a devolver del nodo

 @return Retorna el valor del atributo number del nodo 
 */
int64_t cola_getNumber(cola_t* cola);

/**
 @brief Agrega al vector deslose un numero que forma parte de las posibles sumas
 *  del teorema de golbach
 @param cola Cola que tiene al nodo  al que se le cambiaran los valores
 @param digito Numero que se almacenara en el vector desglose del nodo
 @return Retorna un char:
 */
void cola_addDesglose(cola_t* cola , int64_t digito);

/**
 @brief Cambia el valor del atributo "sumas" de un nodo que esta dentro de una cola
 @param cola Cola que tiene el nodo al que se aplicara el cambio
 @param sumas int que contiene el nuevo valor de sumas del nodo
*/
void cola_setSumas(cola_t* cola , int sumas);

#endif  // TAREAS_GOLDBACH_SERIAL_SRC_COLA_H_
