//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#include "structs.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using std::string; using std::vector;
using std::ifstream; using std::fstream;
using namespace std;

simuladorPlacas_t* simuladorPlacas_Create( double deltaT,
double disTermA, double altoH, double epsilon){
    simuladorPlacas_t* simulador = new simuladorPlacas_t();
    if (simulador) {
        /*simulador->placa.resize(1);
        simulador->placaKPlus.resize(1);
        for (int i = 0; i < 1; i++) {
            simulador->placa[i].resize(1);
            simulador->placaKPlus[i].resize(1);
        }*/
        simulador->epsilon = epsilon;
        cout<< simulador->epsilon<<"\n";
        simulador->altoH = altoH;
        simulador->deltaT = deltaT;
        simulador->disTermA = disTermA;
    }
    return simulador;
}

bool read_bin(std::string nombre_bin , simuladorPlacas_t * simuladorPlacas) {
     // fstream:: in abrir archivo para leerlo
     // fstream:: binary  abre el archivo en forma de binario
    ifstream archivo_bin(nombre_bin, fstream::in | fstream::binary); 
    if (!archivo_bin) {
        cout << "No se puede abrir el binario." << endl;
        return false;
    } else {
        int64_t filas;
        int64_t columnas;
        // Se lee filas
        archivo_bin.read(reinterpret_cast<char*>(&filas), sizeof(filas));  //   
        // Se lee columnas
        archivo_bin.read(reinterpret_cast<char*>(&columnas), sizeof(columnas));

        simuladorPlacas->placa.resize(filas);
        simuladorPlacas->placaKPlus.resize(filas);

        for (int64_t i = 0; i < filas; i++) {
           simuladorPlacas->placa[i].resize(columnas);
           simuladorPlacas->placaKPlus[i].resize(columnas);
        }
        double calor;
        for (int64_t fila = 0; fila < filas; fila++) {
            for (int64_t columna = 0; columna < columnas; columna++) {
                archivo_bin.read(reinterpret_cast<char*>(&calor),
                sizeof(calor));
                simuladorPlacas->placa[fila][columna] = calor;
            }
        }
        // Se copian los datos a la matriz temporal
    std::copy(std::begin(simuladorPlacas->placa), std::end(simuladorPlacas->placa), std::begin(simuladorPlacas->placaKPlus));
        simuladorPlacas->filas = filas;
        simuladorPlacas->columnas = columnas;

        archivo_bin.close();
    }
    return true;
}

void simuladorPlacas_destroy(simuladorPlacas* simulador){
    simulador->epsilon = 0;
    simulador->altoH = 0;
    simulador->deltaT = 0;
    simulador->disTermA = 0;
    int fin = simulador->filas;
    for(int index = 0; index < fin; index++){
        simulador->placa[index].clear();
        simulador->placaKPlus[index].clear();
    }
    simulador->placa.clear();
    
    simulador->placaKPlus.clear();
    delete simulador;
}
