//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#ifndef SIMULADORPLACAS_H_
#define SIMULADORPLACAS_H_

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string.h>

typedef struct simuladorPlacas {
    double epsilon;
    double h;
    double deltaT;
    int64_t filas;
    int64_t columnas;
    int64_t disTermA;
    std::vector<std::vector<double>> placa;
    std::vector<std::vector<double>> placaKPlus;
} simuladorPlacas_t;

simuladorPlacas_t* simuladorPlacas_Create(void);

bool simuladorPlacas_loadJobFile(simuladorPlacas_t* simulador, std::string nombreArchivo, 
double delta, double h, double epsilon);

double simuladorPlacas_getCelda(simuladorPlacas_t* simulador, 
double fila, double columna);

double simuladorPlacas_sumarCruz(simuladorPlacas_t* simulador, 
double fila, double columna);

void simuladorPlacas_simular(simuladorPlacas_t* simulador);

bool simuladorPlacas_openFile(simuladorPlacas_t* simulador, std::string filename, double deltat,
int64_t disTermA, double h, double epsilon);

void loadWork(double *work);

#endif
