#ifndef GOLDBACHSOLVER_HPP_
#define  GOLDBACHSOLVER_HPP_

#include <cstdint>
#include <cinttypes>
#include <string>
#include "nodo.hpp"
#include "cola.hpp"
#include "SumGoldbachSolver.hpp"

cola_t * goldBach(cola_t* cola);
int conjeturaDebil(int64_t numero , nodo_t* , char);
int conjeturaFuerte(int64_t numero , nodo_t*  , char);
int esPrimo(int64_t numero);

#endif 
