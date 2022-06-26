// Copyright Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0
#include <iostream>
#include <sstream>
#include <cinttypes>
#include <cstdint>
#include <cmath>
#include "unistd.h"
#include "regex"
#include "SumGoldbachSolver.hpp"
#include "nodo.hpp"

//  Constructor
SumGoldbachSolver::SumGoldbachSolver(){

}

//Destructor
SumGoldbachSolver::~SumGoldbachSolver(){

}
//  procedure goldBach(cola):
void SumGoldbachSolver::goldBach(cola_t * cola) {
  //  declare nodo :=  first nodo of cola
  nodo_t * nodo = cola->first;
  //  while nodo != null do
  while (nodo) {
    //  Calculate golbach sums for nodo
    //  declare sums := 0
    int sumas = 0;
    //  if number of nodo is even do
    if (nodo_getNumber(nodo) % 2 == 0) {
      //  sumas := sumas + conjeturaFuerte(nodo)
      sumas+=  conjeturaFuerte(nodo_getNumber(nodo), nodo,
      nodo_getSigno(nodo));
    } else {
      sumas+=  conjeturaDebil(nodo_getNumber(nodo), nodo,
      nodo_getSigno(nodo));
    }  //  end else
    nodo_setSumas(nodo, sumas);
    //  nodo := nodo next
    nodo = nodo->next;
  }
}

//  procedure conjeturaDebil(num, vector_nodo, signo):
int SumGoldbachSolver::conjeturaDebil(int64_t numero , nodo_t* vector_nodo , char signo) {
  //  declare primes as an array of integers := primes numbers until num
  int64_t  numeros_Primos[numero];


  // declare len = length of primes
  int64_t longitud = 0;


  for (int64_t i=2 ; i < numero; ++i) {
    if ( esPrimo(i) ) {
      numeros_Primos[longitud++] = i;
    }
  }
  // declare sums := 0
  int esSuma = 0;
  // declare number1 := 0
  // for number1 to len do
  for (int64_t sumando1 = 0 ; sumando1 < longitud ; ++sumando1) {
      // declare number2 := 0
      // for number2 to len do
      for (int64_t sumando2 = sumando1 ; sumando2  < longitud ; ++sumando2) {
        // declare number3 := 0
        // for number3 to len do
        for (int64_t sumando3 = sumando2 ; sumando3 < longitud ; ++sumando3) {
          //  if primes[number1] + primes[number2] + primes[number3] == num do
          if ( numeros_Primos[sumando1] + numeros_Primos[sumando2] +
          numeros_Primos[sumando3] == numero) {
            // if show sums == true do
            if (signo  ==  '-') {
              // save the number1, number2, number3 in vector_nodo
              nodo_addDesglose(vector_nodo ,  numeros_Primos[sumando1]);
              nodo_addDesglose(vector_nodo ,  numeros_Primos[sumando2]);
              nodo_addDesglose(vector_nodo ,  numeros_Primos[sumando3]);
            }  // end if
            // sums := sums + 1
            esSuma++;
          }  // end if
        }  // end for
      }  // end for
    }  // end for
  // return sums
  return esSuma;
}  // end procedure



// procedure conjeturaFuerte(num, vector_nodo, signo):
int SumGoldbachSolver::conjeturaFuerte(int64_t numero , nodo_t* vector_nodo , char signo) {
  // declare primes as an array of integers := prime numbers until num
  int64_t  numeros_Primos[numero];

  // declare len = length of primes
  int64_t longitud = 0;

  for (int64_t i=2 ; i < numero; ++i) {
    if ( esPrimo(i) ) {
      numeros_Primos[longitud++] = i;
    }
  }
  // declare sums := 0
  int esSuma = 0;
  // declare number1 := 0
  // for number1 to len do
  for (int64_t sumando1 = 0 ; sumando1 < longitud ; ++sumando1) {
    // declare number2 := 0
    // for number2 to len do
    for (int64_t sumando2 = sumando1 ; sumando2  < longitud ; ++sumando2) {
      // if primes[number1] + primes[number2] == num do
      if ( numeros_Primos[sumando1] + numeros_Primos[sumando2] == numero ) {
        // if show sums == true do
        if (signo  ==  '-') {
          // save the number1, number2 in vector_nodo
          nodo_addDesglose(vector_nodo , numeros_Primos[sumando1]);
          nodo_addDesglose(vector_nodo ,  numeros_Primos[sumando2]);
        }  // end if
        // sums := sums + 1
        esSuma++;
      }  // end for
    }  // end for
  }  // end for
  // return sumas
  return esSuma;
}  // end procedure

/**
 @brief Verifica si un numero es primo
 @param numero Contiene el valor a verificar
 @return Retorna:
   0 si un numero no es primo
   1 si un numero es primo
*/

// procedure esPrimo(num):
int SumGoldbachSolver::esPrimo(int64_t numero) {
  // declare answer := 1
  int respuesta = 1;
  // if num == 1 do
  if (numero == 1) {
    // answer := 0
    respuesta = 0;
  }  // end if

  // declare i := 2
  // for i to num and answer == 1 do
  for (int i = 2; i < numero && respuesta  == 1 ; i++) {
    // if num mod i == 0 do
    if  ( numero % i  == 0 ) {
      // answer := 0
      respuesta = 0;
    }  // end if
  }  // end for
  // return answer
  return respuesta;
}  // end procedure

