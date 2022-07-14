//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#include "simuladorPlacas.hpp"

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

double simuladorPlacas_getCelda(simuladorPlacas_t* simulador, 
double fila, double columna) {
    if(fila < simulador->filas && columna < simulador->columnas){
        return simulador->placa[fila][columna];
    } else {
        return 0.0;
    }
}