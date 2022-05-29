#include <iostream>
#include <sstream>
#include <cinttypes>
#include <cstdint>
#include <cmath>
#include "SumGoldbachSolver.hpp"
#include "nodo.hpp"
cola_t * goldBach(cola_t * cola) {
   
   nodo_t * nodo = cola->first;

   while(nodo){

    //  Calculate golbach sums for nodo
    int sumas = 0;
    if (nodo_getNumber(nodo) % 2 == 0) {
      sumas+=  conjeturaFuerte(nodo_getNumber(nodo), nodo, 
      nodo_getSigno(nodo));
    } else {
      sumas+=  conjeturaDebil(nodo_getNumber(nodo), nodo, 
      nodo_getSigno(nodo));
    }
    nodo_setSumas(nodo, sumas);
    nodo = nodo->next;
   }

  return cola ;
}

//  procedure conjeturaDebil:
int conjeturaDebil(int64_t numero , nodo_t* vector_nodo , char signo) {
  // Crea un vector para almacenar numeros primos
  int64_t* numeros_Primos = (int64_t*) calloc(numero, sizeof(int64_t));

  // Cantidad de numeros primos en el vector
  int64_t longitud = 0;

  //  Crea un vector con los numeros primos de ese numero
  for (int64_t i=2 ; i < numero; ++i) {
    if ( esPrimo(i) ) {
      numeros_Primos[longitud++] = i;
    }
  }
  // Definir sumas como entero;
  int esSuma = 0;
  // Para i = 2 Hasta i < numero Con Paso 1 Hacer
  for (int64_t sumando1 = 0 ; sumando1 < longitud ; ++sumando1) {
      // Para sumando2= sumando1 Hasta sumado1+2 < numero Con Paso 1 Hacer
      for (int64_t sumando2 = sumando1 ; sumando2  < longitud ; ++sumando2) {
        // Para sumando3= sumando2 Hasta sumado1+2+3 < numero Paso 1 Hacer
        for (int64_t sumando3 = sumando2 ; sumando3 < longitud ; ++sumando3) {
          //  Si esPrimo(i) && sumando1 + sumando2 +i = numero entonces
          if ( numeros_Primos[sumando1] + numeros_Primos[sumando2] +
          numeros_Primos[sumando3] == numero) {
            if (signo  ==  '-') {
              // guardar suma en cola;
              nodo_addDesglose(vector_nodo ,  numeros_Primos[sumando1]);
              nodo_addDesglose(vector_nodo ,  numeros_Primos[sumando2]);
              nodo_addDesglose(vector_nodo ,  numeros_Primos[sumando3]);
            }

            // Incrementar suma;
            esSuma++;
          }
        }
      }
    }

  free(numeros_Primos);
  // Devuelve sumas
  return esSuma;
}
// end procedure



// procedure conjeturas:
int conjeturaFuerte(int64_t numero , nodo_t* vector_nodo , char signo) {
  // Crea un vector para almacenar numeros primos
  int64_t* numeros_Primos = (int64_t*) calloc(numero, sizeof(int64_t));

  // Cantidad de numeros primos en el vector
  int64_t longitud = 0;

  //  Crea un vector con los numeros primos de ese numero
  for (int64_t i=2 ; i < numero; ++i) {
    if ( esPrimo(i) ) {
      numeros_Primos[longitud++] = i;
    }
  }
  // Definir sumas como entero;
  int esSuma = 0;
  // Para i = 2 Hasta i < numero Con Paso 1 Hacer
  for (int64_t sumando1 = 0 ; sumando1 < longitud ; ++sumando1) {
    // Para sumando2= sumando1 Hasta sumado1+2 < numero Con Paso 1 Hacer
    for (int64_t sumando2 = sumando1 ; sumando2  < longitud ; ++sumando2) {
      //  Si esPrimo(i) && sumando1 + sumando2 +i = numero entonces
      if ( numeros_Primos[sumando1] + numeros_Primos[sumando2] == numero ) {
        if (signo  ==  '-') {
          // guardar suma en cola;
          nodo_addDesglose(vector_nodo , numeros_Primos[sumando1]);
          nodo_addDesglose(vector_nodo ,  numeros_Primos[sumando2]);
        }

        // Incrementar suma;
        esSuma++;
      }
    }
  }

  free(numeros_Primos);
  // Devuelve sumas
  return esSuma;
}
// end procedure

/**
 @brief Verifica si un numero es primo
 @param numero Contiene el valor a verificar
 @return Retorna:
   0 si un numero no es primo
   1 si un numero es primo
*/

// procedure esPrimo:
int esPrimo(int64_t numero) {
  // si es primo devuelve un 1;// si es primo devuelve un 1;
  int respuesta = 1;

  if (numero == 1) {
    respuesta = 0;
  }

  // verifica si numero es primo;
  for (int i = 2; i < numero && respuesta  == 1 ; i++) {
    if  ( numero % i  == 0 ) {
      // sino devuelve un 0;
      respuesta = 0;
    }
  }

  return respuesta;
}
// end procedure

