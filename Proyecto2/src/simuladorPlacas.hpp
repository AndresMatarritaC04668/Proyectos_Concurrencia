//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#ifndef SIMULADORPLACAS_H_
#define SIMULADORPLACAS_H_

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string.h>
#include <cmath>
#include "structs.hpp"
using std::string;
using std::ifstream;

 

int abrir_archivo(string nombreArchivo, string directorio, int numeroDeHilos);

void simulacion_HeatTransfer(simuladorPlacas_t* simulador);

bool simuladorPlacas_loadJobFile(simuladorPlacas_t* simulador, std::string nombreArchivo, 
double delta, double h, double epsilon);

double simuladorPlacas_getCelda(simuladorPlacas_t* simulador, 
double fila, double columna);

double simuladorPlacas_sumarCruz(simuladorPlacas_t* simulador, 
double fila, double columna);

void simuladorPlacas_simular(simuladorPlacas_t* simulador);

void generar_Resultado( simuladorInfo_t * simuladorInfo );

void run(vector<simuladorInfo> * vectorData , vector<simuladorPlacas_t*> * vectorPlaca);

int verificar_diferencia(simuladorPlacas_t* simulador);

int imprimir_Resultado(string nombreArchivo, std::vector<simuladorInfo>*  vectorData);

void imprimir_laminas(string nombreLamina , simuladorPlacas_t * simuladorPlacas);

#endif
