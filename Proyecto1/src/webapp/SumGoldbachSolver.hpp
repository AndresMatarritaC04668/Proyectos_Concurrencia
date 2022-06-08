// Copyright Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0
#ifndef GOLDBACHSOLVER_HPP_
#define  GOLDBACHSOLVER_HPP_

#include <cstdint>
#include <cinttypes>
#include <string>
#include "nodo.hpp"
#include "cola.hpp"
#include "SumGoldbachSolver.hpp"

/**
 * @brief This method is the general conjecture, is gets a 
 * cola, then fill it with the numbers, calculate the conjecture 
 * and the return it
 * 
 * @param cola is the conteiner to storege the data
 * @return cola_t* with the Conjecture calculates in that cola 
 */
cola_t * goldBach(cola_t* cola);

/**
 * @brief If the number is odd, this is the method that
 * calculate the conjecture
 * it needs 3 primes numbers
 * 
 * @param numero ready to be calculated
 * @param vector_nodo will storage the sums of the number
 * @param signo flag if it has to show sums or not
 * @return int the amount of sums
 */
int conjeturaDebil(int64_t numero , nodo_t* vector_nodo, char signo);

/**
 * @brief If the number is even, this is the method that
 * calculate the conjecture
 * it needs 2 primes numbers
 * 
 * @param numero ready to be calculated
 * @param vector_nodo will storage the sums of the number
 * @param signo flag if it has to show sums or not
 * @return int the amount of sums
 */
int conjeturaFuerte(int64_t numero , nodo_t* vector_nodo, char signo);

/**
 * @brief Find out if the number is prime or not
 * 
 * @param numero number to be analized
 * @return int 1 if it is prime, 0 if it is not prime
 */
int esPrimo(int64_t numero);

#endif
