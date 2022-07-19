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

void simuladorPlacas_init(simuladorPlacas_t * simulador, int64_t filas,
                          int64_t columnas, 
                          std::vector<std::vector<double>> placa,
                          std::vector<std::vector<double>> placaKPlus,
                          double epsilon, double altoH, double deltaT,
                          double disTermA) {
  simulador->columnas = columnas;
  simulador->filas = filas;
  simulador->placa = placa;
  simulador->placaKPlus = placaKPlus;
  simulador->epsilon = epsilon;
  simulador->altoH = altoH;
  simulador->deltaT = deltaT;
  simulador->disTermA = disTermA;
  
}
#endif  // STRUCS_HPP_
