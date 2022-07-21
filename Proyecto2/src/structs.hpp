// Copyright 2022 Dinamita

#ifndef STRUCS_HPP_
#define STRUCS_HPP_
#include <string>
#include <vector>
#include <fstream>
using std::string; using std::vector;
using std::ifstream; using std::fstream;

using namespace std;
/**
 @brief struct con datos de una simulacion
*/
typedef struct simuladorInfo {
  std::string nombreLamina;
    double epsilon;
    double altoH;
    double deltaT;
    double disTermA;
    int64_t estadok;
  std::string resultado;
} simuladorInfo_t;

typedef struct simuladorPlacas {
    double epsilon;
    double altoH;
    double deltaT;
    double disTermA;
    int64_t filas;
    int64_t columnas;
    int64_t estadok;
    std::vector<std::vector<double>> placa;
    std::vector<std::vector<double>> placaKPlus;
} simuladorPlacas_t;

bool read_bin(std::string nombre_bin , simuladorPlacas_t* simuladorPlacas);

simuladorPlacas_t* simuladorPlacas_Create(double deltaT,
double disTermA, double altoH, double epsilon);

void simuladorPlacas_destroy(simuladorPlacas* simulador);

#endif  // STRUCS_HPP_


