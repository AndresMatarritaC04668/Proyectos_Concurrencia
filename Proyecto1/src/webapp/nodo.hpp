// "Copyright 2022 <Andres Matarrita>"
#ifndef TAREAS_GOLDBACH_SERIAL_SRC_NODO_H_
#define TAREAS_GOLDBACH_SERIAL_SRC_NODO_H_
#include <stdint.h>
#include <inttypes.h>
#include <string>


//! \ class Clase nodo.h

typedef struct nodo nodo_t;   //!< Crea un tipo


typedef struct nodo {  //!< Atributos privados
  int64_t number;   //!< Numero
  int sumas;  //!< CantidadSumas
  char signo;  //!< Signo del Numero
  int64_t  desglose[10000];   //!< Vector de int
  int posicion;  //!< Posicion del vector
  std::string numeroErroneo;  //!< Guarda un numero invalido
  int64_t error;  //!< Indica si un numero es invalido
  nodo_t* next;   //!< Referencia al siguiente nodo
} nodo_t;


nodo_t* nodo_init(int64_t , int , char ,
int64_t , std::string);  //!<  Procedimiento de inicializacion
void nodo_destroy(nodo_t* nodo);  //!< Procedimiento de eliminar
void nodo_print(nodo_t* nodo);  //!< Procedimiento de imprimir
char nodo_getSigno(nodo_t* nodo);  //!< Procedimiento getter
int64_t nodo_getNumber(nodo_t* nodo);  //!< Procedimiento getter
void nodo_addDesglose(nodo_t* , int64_t);  //!< Se agrega numero de Suma
void nodo_setSumas(nodo_t* , int);  //!< Procedimiento cambiiar suma

#endif    // TAREAS_GOLDBACH_SERIAL_SRC_NODO_H_
