//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#ifndef SIMULADORPLACAS_H_
#define SIMULADORPLACAS_H_

#include <string.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "structs.hpp"
using std::string;
using std::ifstream;


/**
 @brief  Abre el archivo .txt y obtiene los valores
         importantes de las simulaciones
 @param nombreArchivo nomnre del archivo .txt con 
                      los datos de la simulacion
 @param numeroDeHilos cantidad de hilos a crear
 @param directorio directorio del archivo
 @return retorna un 1 si termina correctamente
*/
int abrir_archivo(string nombreArchivo, string directorio, int numeroDeHilos);

/**
 @brief encuentra el punto de calor optimo
        de una placa para determinado epsilon
 @param simulador contiene las matrices y demas informacion
  de una placa
*/
void simulacion_HeatTransfer(simuladorPlacas_t* simulador);


/**
 @brief Devuelve el valor de la posicion de una placa
        en una respectiva fila y columna
 @param simulador contiene las matrices y demas informacion
                  de una placa
 @param fila numero de fila a trabajar
 @param columna numero de columna a trabajr
 @return retorna double con el valor de espacio de la placa
*/
double simuladorPlacas_getCelda(simuladorPlacas_t* simulador,
    double fila, double columna);

/**
 @brief  Obtiene el valor de la suma total de los valores 
         de las celdas adyacentes a la celda especificada 
         de la lamina original
 @param simulador contiene las matrices y demas informacion
                  de una placa
 @param fila numero de fila a trabajar
 @param columna numero de columna a trabajr
 @return double con el resultado de la suma
*/
double simuladorPlacas_sumarCruz(simuladorPlacas_t* simulador,
    double fila, double columna);

/**
 @brief Guarda y calcula la cantidad de años, meses que dura cada
        simulacion  para imprimirlo en el .tsv
 @param simuladorInfo ccontiene la informacion de cada
                      simulacion
*/
void generar_Resultado(simuladorInfo_t * simuladorInfo);

/**
 @brief Organiza y mapea el calculo de todas las simulaciones
        allmacenadas de manera dinamica
 @param vectorData vector que almacena todas las simulaciones
 @param numeroDeHilos cantidad de hilos a crear
*/
void run(vector<simuladorInfo> * vectorData , int numeroDeHilos);

/**
 @brief verifica si todos los valores de la matriz
        son mayores a un epsilon
 @param simulador contiene las matrices y demas informacion
                  de una placa
 @return si hay un solo valor de la placa menor al epsilon
         devueve un 1
         de lo contrario devuelve un 2
*/
int verificar_diferencia(simuladorPlacas_t* simulador);

/**
 @brief Crea el .tsv con los datos obtenidos de las simulaciones
        con su respectivo tiempo e iteraciones "k"
 @param nombreArchivo nombre del .tsv donde se guardaran los
                      resultados
 @param vectorData vector que almacena todas las simulaciones
 @return devuelve un 1 si termina correctamente
*/
int imprimir_Resultado(string nombreArchivo,
    std::vector<simuladorInfo>*  vectorData);

/**
 @brief Crea el archivo binario con el resultado de la placa 
        nueva
 @param  simuladorPlacas struct con la placa y su informacion
                         la nueva lamina con su punto de calor optimo
 @param  nombreLamina nombre de la lamina a imprimir en un .bin
*/
void imprimir_laminas(string nombreLamina, simuladorPlacas_t * simuladorPlacas);

#endif
