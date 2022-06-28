// Copyright Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0
#ifndef GOLDBACHSOLVER_HPP_
#define  GOLDBACHSOLVER_HPP_

#include <cstdint>
#include <cinttypes>
#include <string>
#include "nodo.hpp"
#include "cola.hpp"
#include "SumGoldbachSolver.hpp"
#include "Assembler.hpp"


class SumGoldbachSolver : public Assembler<shared_data_t*,shared_data_t*> {
  public:

/**
 * @brief Constructor de la clase  SumGoldbachSolver
 */
 SumGoldbachSolver();

/**
 * @brief Destructor de la clase SumGoldbachSolver
 */
 ~SumGoldbachSolver();
  
  /**
   * @brief Override method from Consumer class
   * @param shared_data_t
   * @return void
   */
void consume(shared_data_t* shared_data) override;

/**
   * @brief Override method from thread class
   * @return 0;
   */
  int run() override;

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
};

#endif //  SumGoldbachSolver
