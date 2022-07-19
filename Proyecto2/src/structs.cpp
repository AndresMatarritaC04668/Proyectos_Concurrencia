#include "structs.hpp"
#include <ostream>
#include <string>
#include <iostream>
#include <vector>
using std::string; using std::vector;
using std::ifstream; using std::fstream;

simuladorPlacas_t* simuladorPlacas_Create(simuladorInfo_t simuladorInfo){
    simuladorPlacas_t *simulador = (simuladorPlacas_t *)calloc(1, sizeof(simuladorPlacas_t));
    if(simulador){
        simulador->placa.reserve(50);
        simulador->placaKPlus.reserve(50);
        for (int i = 0; i < 50; i++) {
            simulador->placa[i].reserve(50);
            simulador->placaKPlus[i].reserve(50);
        }
        simulador->epsilon = simuladorInfo.epsilon;
        simulador->altoH = simuladorInfo.altoH;
        simulador->deltaT = simuladorInfo.deltaT;
        simulador->disTermA = simuladorInfo.disTermA;
    }
    return simulador;
}

bool read_bin(std::string nombre_bin , simuladorInfo_t simuladorInfo ,
simuladorPlacas_t * simuladorPlacas) {
    ifstream archivo_bin(nombre_bin, fstream::in | fstream::binary);
    if (!archivo_bin) {
        cout << "No se puede abrir el binario." << endl;
        return false;
    } else {
        int64_t filas;
        int64_t columnas;
        // Se lee filas
        archivo_bin.read(reinterpret_cast<char*>(&filas), sizeof(filas));
        // Se lee columnas
        archivo_bin.read(reinterpret_cast<char*>(&columnas), sizeof(columnas));
        simuladorPlacas->placa.resize(filas);
        simuladorPlacas->placaKPlus.resize(filas);

        for (int64_t i = 0; i < filas; i++) {
           simuladorPlacas->placa[i].resize(filas);
           simuladorPlacas->placaKPlus[i].resize(filas);
        }
        double calor;
        for (int64_t fila = 0; fila < filas; fila++) {
            for (uint64_t columna = 0; columna < columnas; columna++) {
                archivo_bin.read(reinterpret_cast<char*>(&calor),
                sizeof(calor));
                simuladorPlacas->placa[fila][columna] = calor;
            }
        }
        archivo_bin.close();

        
        simuladorPlacas->deltaT = simuladorInfo.deltaT;
        simuladorPlacas->disTermA = simuladorInfo.disTermA;
        simuladorPlacas->altoH = simuladorInfo.altoH;
        simuladorPlacas->epsilon = simuladorInfo.epsilon;
    }
    return true;
}
