

#ifndef GOLDBACHSOLVER_HPP_
#define  GOLDBACHSOLVER_HPP_

#include <cstdint>
#include <cinttypes>
#include <string>
#include "nodo.hpp"
#include "SumGoldbachSolver.hpp"


std::string createResponse(nodo* nodo);
std::string  goldBach(int64_t valor);
int conjeturaDebil(int64_t numero , nodo_t* , char);
int conjeturaFuerte(int64_t numero , nodo_t*  , char);
int esPrimo(int64_t numero);

#endif 
