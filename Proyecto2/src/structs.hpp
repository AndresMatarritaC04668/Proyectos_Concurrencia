// Copyright 2022 Dinamita

#ifndef STRUCS_HPP_
#define STRUCS_HPP_
#include <string>
#include <vector>
#include <fstream>
using std::string; using std::vector;
using std::ifstream; using std::fstream;

/**
 @brief struct con datos de una simulacion
*/
typedef struct simuladorInfo {
  std::string nombreLamina; /**< Archivo bin */
    double epsilon;  /**< Epsilon */
    double altoH;  /**< Altura y anchura  */
    double deltaT;  /**< Tiempre entre etapa */
    double disTermA;  /**< Difusividad termica */
    int64_t estadok;  /**< Iteraciones */
  std::string resultado; /**< Resultado del tiempo  y demas */
} simuladorInfo_t;

/**
 @brief struct con datos 
 y vectores de una placa
*/
typedef struct simuladorPlacas {
    double epsilon;  /**< Epsilon */
    double altoH;  /**< Altura y anchura  */
    double deltaT;  /**< Tiempre entre etapa */
    double disTermA;  /**< Difusividad termica */
    int64_t filas;  /**< Filas  */
    int64_t columnas;  /**< Columnas */
    int64_t estadok;  /**< Iteraciones */
    std::vector<std::vector<double>> placa;  /**< Placa original */
    std::vector<std::vector<double>> placaKPlus;  /**< Placa temporal */
} simuladorPlacas_t;

/**
 @brief Lee un archivo binario que contiene
 una lamina con valores binario
 @param nombre_bin nombre del archivo binario
 @param simuladorPlacas struct donde se
 guardara la matriz del archivo binario
 @return devuelve un true si termina
*/
bool read_bin(std::string nombre_bin , simuladorPlacas_t* simuladorPlacas);


/**
 @brief Constructor del struct simuladorPLacas
        inicializa la matriz y variables
        por parametros
 @param deltaT Tiempo entre cada etapa
 @param disTermA  Disividad
 @param altoH  Altura y anchura
 @param epsilon  Epsilon a trabajar
 @return retorna el struct inicializado
 @return retorna un 1 si termina correctamente
*/
simuladorPlacas_t* simuladorPlacas_Create(double deltaT,
double disTermA, double altoH, double epsilon);

/**
 @brief Destructor del strcut simuladorPLaca
 @param simulador Placa a destruir
*/
void simuladorPlacas_destroy(simuladorPlacas* simulador);

#endif  // STRUCS_HPP_


