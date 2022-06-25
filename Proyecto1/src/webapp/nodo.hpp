// "Copyright 2022 <Andres Matarrita>"
#ifndef TAREAS_GOLDBACH_SERIAL_SRC_NODO_H_
#define TAREAS_GOLDBACH_SERIAL_SRC_NODO_H_
#include <stdint.h>
#include <inttypes.h>
#include <string>


//! \ class Clase nodo.h

typedef struct nodo nodo_t;

/**
 * @brief struct de la clase nodo
 * @param number numero del nodo
 * @param sumas cantidad de sumas del nodo
 * @param signo signo del numero del nodo
 * @param desglose arreglo de enteros de las sumas del numero
 * @param posicion posicion del arreglo desglose
 * @param numeroErroneo guarda un numero invalido
 * @param error indica si un numero es invalido
 * @param next referencia al siguiente nodo
 */
typedef struct nodo {
  int64_t number;
  int sumas;
  char signo;
  int64_t  desglose[10000];
  int posicion;
  std::string numeroErroneo;
  int64_t error;
  nodo_t* next;
} nodo_t;

/**
 @brief Inicializa los valores del nodo al darle los valores de los parametros
 @param number Numero a demostrar con goldbach
 @param sumas Cantidad de sumas posibles encontradas
 @param signo Char que identifica si un numero es negativo ('-')
 @param error entero que muestra si el valor introducido es invalido
 @param numeroErroneo es el valor erroneo que se agrega al nodo si el numero es invalido
 @return Retorna un puntero a un nodo 
*/
nodo_t* nodo_init(int64_t number , int sumas , char signo ,
 int64_t error , std::string numeroErroneo);

/**
 @brief Libera a el nodo y sus valores
 @param nodo Nodo que se va a liberar
*/
void nodo_destroy(nodo_t* nodo);

/**
 @brief Imprime los datos del nodo y si es negativo imprime
        el desglose de sumas del numero
 @param nodo Nodo que contiene los datos que se van a imprimir 
*/
void nodo_print(nodo_t* nodo);

/**
 @brief Devuelve el char signo de un numero
 @param nodo Contiene el char a devolver

 @return Retorna un char:
 '-' Si el numero es negativo
 ' ' Si el numero es positivo
*/
char nodo_getSigno(nodo_t* nodo);

/**
 @brief Devuelve el numero int64_t de un nodo 
 @param nodo Contiene el numero a devolver

 @return Retorna el valor del atributo number
*/
int64_t nodo_getNumber(nodo_t* nodo);

/**
 @brief Agrega al vector deslose un numero que forma parte de las posibles sumas
 *      del teorema de golbach
 @param nodo Nodo al que se le cambiaran los valores
 @param digito Numero que se almacenara en el vector desglose
 @return Retorna un char:
*/
void nodo_addDesglose(nodo_t* nodo , int64_t digito);

/**
 @brief Cambia el valor del atributo "sumas" de un nodo
 @param nodo Nodo al que se aplicara el cambio
 @param sumas int que contiene el nuevo valor de sumas
*/
void nodo_setSumas(nodo_t* nodo , int sumas);

#endif    // TAREAS_GOLDBACH_SERIAL_SRC_NODO_H_
