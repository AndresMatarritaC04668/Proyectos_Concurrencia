//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#include "simuladorPlacas.hpp"
#include <iostream>

simuladorPlacas_t* simuladorPlacas_Create(void){
    simuladorPlacas_t *simPla = (simuladorPlacas_t *)calloc(1, sizeof(simuladorPlacas_t));
    if(simPla){
        double epsilon = 0.0;
        double h = 0.0;
        double deltaT = 0.0;
        int64_t filas = 0;
        int64_t columnas = 0;
        int64_t disTermA = 0;
        simPla->placa.reserve(50);
        simPla->placaKPlus.reserve(50);
        for (int i = 0; i < 50; i++) {
            simPla->placa[i].reserve(50);
            simPla->placaKPlus[i].reserve(50);
        }
    }
    return simPla;
}

bool simuladorPlacas_openFile(simuladorPlacas_t* simulador, std::string filename, double deltat,
    int64_t disTermA, double h, double epsilon) {
    std::ifstream filePlaca(filename, std::fstream::in | std::fstream::binary);
    if (!filePlaca) {
        printf("ERROR: No se pudo abrir el archivo binario\n");
        return false;
    } else {
        //  Se lee la cantidad de filas
        filePlaca.read(reinterpret_cast<char*>
            (&simulador->filas), sizeof(simulador->filas));
        //  Se lee la cantidad de columnas
        filePlaca.read(reinterpret_cast<char*>
            (&simulador->columnas), sizeof(simulador->columnas));
        simulador->placa.resize(simulador->filas);
        simulador->placaKPlus.resize(simulador->columnas);
        for(int64_t i = 0; i < simulador->filas; ++i) {
            simulador->placa[i].resize(simulador->columnas);
            simulador->placaKPlus[i].resize(simulador->columnas);
        }
        double valorNuevo = 0.0;
        for(int64_t fila = 0; fila < simulador->filas; ++fila) {
            for(int64_t columna = 0; columna < simulador->columnas; ++columna) {
                filePlaca.read(reinterpret_cast<char*>(&valorNuevo),
                    sizeof(valorNuevo));
                simulador->placa[fila][columna] = valorNuevo;
            }
        }

        filePlaca.close();

        //  Copiar valores
        simulador->deltaT = deltat;
        simulador->disTermA = disTermA;
        simulador->altoH = h;
        simulador->epsilon = epsilon;
    }
    return true;
}

void loadWork(double *work) {
    
}

double simuladorPlacas_getCelda(simuladorPlacas_t* simulador, 
double fila, double columna) {
    if(fila < simulador->filas && columna < simulador->columnas){
        return simulador->placa[fila][columna];
    } else {
        return 0.0;
    }
}

double simuladorPlacas_sumarCruz(simuladorPlacas_t* simulador, 
double fila, double columna) {
    //  resultado := 0.0
    double resultado = 0.0;
    //  actual := valor actual de la celda
    double actual = simuladorPlacas_getCelda(simulador, fila, columna);
    //  se suma la energia de las inmediaciones
    resultado = resultado + simuladorPlacas_getCelda(simulador, fila, columna+1) 
        + simuladorPlacas_getCelda(simulador, fila, columna - 1);
    resultado = resultado + simuladorPlacas_getCelda(simulador, fila+1, columna) 
        + simuladorPlacas_getCelda(simulador, fila-1,columna);
    //  se resta la energia perdida y distribuida a las otras celdas    
    resultado = resultado - 4*actual;

    //  multiplicamos por el tiempo y difusividad termica entre alto de la celda al cuadrado
    double tiDiAl = ((simulador->deltaT * simulador->disTermA)/(simulador->altoH*simulador->altoH));
    resultado = resultado * tiDiAl;

    //  agregamos el estado actual de la celda
    resultado = resultado + actual;
    // retornamos el estado k+1 de la celda almacenado en resultado
    return resultado;
}