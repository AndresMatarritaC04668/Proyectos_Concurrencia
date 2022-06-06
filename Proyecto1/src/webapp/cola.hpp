// "Copyright 2022 <Andres Matarrita>"
#ifndef TAREAS_GOLDBACH_SERIAL_SRC_COLA_H_
#define TAREAS_GOLDBACH_SERIAL_SRC_COLA_H_
#include <inttypes.h>
#include "nodo.hpp"


typedef struct {  //!< Incluye clase nodo
    nodo_t* first;  //!< Rerencia a nodo
    nodo_t* last;  //!< Rerencia a nodo
} cola_t;


cola_t* cola_init();  //!< Inicializa atributos de la cola
nodo_t* cola_getNodo(cola_t* cola , int64_t);  //!<   Devuelve un nodo
int cola_delete(cola_t* cola);  //!< Elimina primer nodo de la cola
void cola_destroy(cola_t* cola);  //!< Destruye y libera cola
void cola_print(cola_t* cola);  //!< LLama imprimir de cada nodo si existe este
int cola_add(cola_t* cola ,  int64_t , int , char , int64_t , std::string);  //!< Agrega un nuevo nodo
char cola_getSigno(cola_t* cola);  //!< Retorna el char signo del nodo
int64_t cola_getNumber(cola_t* cola);  //!< Retorna el number del nodo
void cola_addDesglose(cola_t* cola , int64_t);  //!<  Agrega al desglose
void cola_setSumas(cola_t * cola , int);  //!< Cambia el valor sumas del nodo

#endif  // TAREAS_GOLDBACH_SERIAL_SRC_COLA_H_
