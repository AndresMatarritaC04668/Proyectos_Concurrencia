// Copyright 2022 Dinamita

#ifndef STRUCS_HPP_
#define STRUCS_HPP_
#include <string>

/**
 @brief struct con datos de una simulacion
*/
typedef struct simuladorInfo {
  std::string nombreLamina;
    double epsilon;
    double altoH;
    double deltaT;
    double disTermA;
  std::string resultado;
} simuladorInfo_t;

typedef struct simuladorPlacas {
    double epsilon;
    double altoH;
    double deltaT;
    double disTermA;
    int64_t filas;
    int64_t columnas;
    std::vector<std::vector<double>> placa;
    std::vector<std::vector<double>> placaKPlus;
} simuladorPlacas_t;

#endif  // STRUCS_HPP_