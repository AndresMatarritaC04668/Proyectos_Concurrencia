//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#ifndef SIMULADORPLACAS_H_
#define SIMULADORPLACAS_H_

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string.h>
#include "structs.hpp"
using std::string;
using std::ifstream;

simuladorPlacas_t* simuladorPlacas_Create(void);
 
int abrir_archivo(string nombreArchivo, string directorio, int numeroDeHilos);

void simulacion_HeatTransfer(simuladorPlacas_t* simulador,double epsilon);

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

int writeTheResult(string nombreArchivo, vector<simuladorInfo> vectorData);

#endif
