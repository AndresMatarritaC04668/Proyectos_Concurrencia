  //  "Copyright 2022 <Andres Matarrita>"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string>
#include <pthread.h>
#include "cola.hpp"

// procedure cola_init:
cola_t* cola_init() {
  // Inicializa atributos a cero;
  cola_t* cola = new cola_t;
  cola->first = NULL;
  cola-> last = NULL;
  cola->cantidadNumeros = 0;
  cola->numerosProcesados = 0;
  
  return cola;
}
// end procedure


// procedure cola_add:
int cola_add(cola_t* cola  ,  int64_t nuevoValor , int sumas  ,
char signo , int64_t error , std::string numeroErroneo) {
  // crea un nuevo nodo con los valores de parametros;
  nodo_t* newOne = nodo_init(nuevoValor ,
  sumas , signo , error , numeroErroneo);
  ++cola->cantidadNumeros;

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

// procedure cola_destroy:
void cola_destroy(cola_t* cola) {
  // Libera todos los nodos;
  while (cola->first) {
  cola_delete(cola);
  }

  // Libera cola;
  delete cola;
}
// end procedure

// procedure cola_getSigno:
char cola_getSigno(cola_t* cola) {
  nodo_t* nodo = cola->first;

  // retorna atributo signo del nodo
  char signo = nodo_getSigno(nodo);

  return signo;
}
// end procedure

// procedure cola_getNumber:
int64_t cola_getNumber(cola_t* cola) {
  nodo_t* nodo = cola->first;

  // retorna atributo Numero del nodo;
  return nodo_getNumber(nodo);
}
// end procedure

// procedure cola_addDesglose:
void cola_addDesglose(cola_t* cola , int64_t digito) {
  // Agrega un numero int al vector desglose del nodo;
  // Incrementa posicionVector del nodo;
  nodo_t* nodo = cola->last;
  nodo_addDesglose(nodo , digito);
}
// end procedure


// procedure cola_setSumas:
void cola_setSumas(cola_t* cola , int sumas) {
  // Iguala atributo sumas del nodo al parametro recibido;
  nodo_t* nodo = cola->last;
  nodo_setSumas(nodo , sumas);
}
// end procedure
