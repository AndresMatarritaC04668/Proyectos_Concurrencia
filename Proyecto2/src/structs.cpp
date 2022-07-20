#include "structs.hpp"
#include <ostream>
#include <string>
#include <iostream>
#include <vector>
using std::string; using std::vector;
using std::ifstream; using std::fstream;

simuladorPlacas_t* simuladorPlacas_Create( double deltaT,
double disTermA, double altoH, double epsilon){
    simuladorPlacas_t *simulador = (simuladorPlacas_t *)calloc(1, sizeof(simuladorPlacas_t));
    if(simulador){
        simulador->placa.reserve(50);
        simulador->placa.resize(50);
        simulador->placaKPlus.reserve(50);
        simulador->placaKPlus.resize(50);
        for (int i = 0; i < 50; i++) {
            simulador->placa[i].reserve(50);
            simulador->placaKPlus[i].reserve(50);
        }
        simulador->epsilon = epsilon;
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

        simuladorPlacas->filas = filas;
        simuladorPlacas->columnas = columnas;

        archivo_bin.close();
    }
    return true;
}
