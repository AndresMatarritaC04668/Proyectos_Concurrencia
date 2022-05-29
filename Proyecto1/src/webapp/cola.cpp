  //  "Copyright 2022 <Andres Matarrita>"
  #include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "cola.hpp"



/**
 @brief Crea una nueva cola dinamicamente ,  inicializa los atributos de la cola en null
 @return Retorna el puntero de la nueva cola creada
*/
  // procedure cola_init:
cola_t* cola_init() {
  // Inicializa atributos a cero;
  cola_t* cola = (cola_t*) malloc(1*sizeof(cola_t));
  cola->first = NULL;
  cola-> last = NULL;
  return cola;
}
  // end procedure

/**
 @brief Crea un nodo nuevo y lo agrega a la cola ,  primero lo inicializa
 @param cola Referencia de la cola a la que se va agregar el nodo
 @param sumas Cantidad de sumas posibles encontradas
 @param signo Char que identifica si un numero es negativo ('-')
 @param nuevoValor Numero a demostrar con goldbach
 @return Retorna un Exit_Success si termina correctamente
*/
  // procedure cola_add:
int cola_add(cola_t* cola  ,  int64_t nuevoValor , int sumas  ,  char signo) {
  // crea un nuevo nodo con los valores de parametros;
  nodo_t* newOne = nodo_init(nuevoValor , sumas , signo);

  if (cola->first == NULL) {
  cola->first = newOne;
  } else {
  cola->last->next = newOne;
  }

  // Agrega el nuevo nodo a la cola;
  cola->last = newOne;
  return EXIT_SUCCESS;
}
  // end procedure

/**
 @brief Imprime los datos del nodo y si es negativo imprime
  el desglose de sumas del numero
 @param cola  Cola que contiene los datos que se van a imprimir 
 */
  // procedure cola_print:
void cola_print(cola_t* cola) {
  nodo_t* actual = cola->first;

  // Verifica si existe nodo;
  while (actual) {
  // Llama el print del nodo;
  nodo_print(actual);
  actual = actual->next;
  }
}
  // end procedure

/**
 @brief Elimina el primer nodo de la cola 
 @param cola Cola a la que se le elimina el primer nodo
 @return devuelve
 * un 1 si termina correctamente
 * un 0 si presenta alguna falla
 */
  // procedure delete:
int cola_delete(cola_t* cola) {
  // Verifica si existe el primer nodo de la cola;
  if (cola->first != NULL) {
    nodo_t* victima = cola->first;
    cola->first = cola->first->next;
    // Destruye primer nodo de la cola;
    nodo_destroy(victima);
    return EXIT_SUCCESS;

  } else {
    return EXIT_FAILURE;
  }
}
  //  end procedure

/**
 @brief Itera hasta encontrar el nodo solicitado
 @param cola Referencia de la cola en la que se busca el nodo
 @param posicion Posicion que tiene el nodo en la cola
 @return Retorna el nodo que se solicita
*/
  //  procedure cola_getNodo(cola_t* cola , int64_t posicion)
nodo_t* cola_getNodo(cola_t* cola , int64_t posicion) {
  // Guarda el primer nodo de la cola en una variable
  nodo_t* nodo = cola->first;
  //  Crea un centinela para encontrar nodo
  int64_t i = 0;
  //  Busca al nodo
  while (i < posicion) {
    nodo = nodo->next;
    i++;
  }
  //  Retorna nodo
  return nodo;
}
  // end procedure

/**
 @brief Libera a la cola y sus nodos
 @param cola Cola_t que se va a liberar
*/
  // procedure cola_destroy:
void cola_destroy(cola_t* cola) {
  // Libera todos los nodos;
  while (cola->first) {
  cola_delete(cola);
  }

  // Libera cola;
  free(cola);
}
  // end procedure


/**
 @brief Devuelve el char signo de un numero
 @param cola  Contiene el nodo que tiene el char a devolver
 @return Retorna un char:
 '-' Si el numero es negativo
 ' ' Si el numero es positivo
*/
  // procedure cola_getSigno:
char cola_getSigno(cola_t* cola) {
  nodo_t* nodo = cola->first;

  // retorna atributo signo del nodo
  char signo = nodo_getSigno(nodo);

  return signo;
}
  // end procedure


/**
 @brief Devuelve el numero  int64_t  de un nodo 
 @param cola Cola que tiene el nodo que posee el numero a devolver del nodo

 @return Retorna el valor del atributo number del nodo 
 */
  // procedure cola_getNumber:
int64_t cola_getNumber(cola_t* cola) {
  nodo_t* nodo = cola->first;

  // retorna atributo Numero del nodo;
  return nodo_getNumber(nodo);
}
  // end procedure


/**
 @brief Agrega al vector deslose un numero que forma parte de las posibles sumas
 *  del teorema de golbach
 @param cola Cola que tiene al nodo  al que se le cambiaran los valores
 @param digito Numero que se almacenara en el vector desglose del nodo
 @return Retorna un char:
 */
  // procedure cola_addDesglose:
void cola_addDesglose(cola_t* cola , int64_t digito) {
  // Agrega un numero int al vector desglose del nodo;
  // Incrementa posicionVector del nodo;
  nodo_t* nodo = cola->last;
  nodo_addDesglose(nodo , digito);
}
  // end procedure


/**
 @brief Cambia el valor del atributo "sumas" de un nodo que esta dentro de una cola
 @param cola Cola que tiene el nodo al que se aplicara el cambio
 @param sumas int que contiene el nuevo valor de sumas del nodo
*/
  // procedure cola_setSumas:
void cola_setSumas(cola_t* cola , int sumas) {
  // Iguala atributo sumas del nodo al parametro recibido;
  nodo_t* nodo = cola->last;
  nodo_setSumas(nodo , sumas);
}
  // end procedure
