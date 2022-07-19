//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#include "simuladorPlacas.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
using std::string; using std::vector;
using std::ifstream;


int abrir_archivo(string nombreArchivo, string directorio, int numeroDeHilos){
    int error = EXIT_SUCCESS ;
    ifstream archivo;
    archivo.open(nombreArchivo , ifstream::in);
    if(archivo.is_open()){
      vector<simuladorInfo>  vectorData;
      string linea ;
      string condicion = " "; // Condicion de comienzo de un nuevo dato
      if(directorio.length() == 0){
        directorio = nombreArchivo.substr(0,nombreArchivo.find_last_of("/")+1);
      }
      while(getline(archivo,linea)){
        simuladorInfo_t simuladorInfo;
        size_t posicion = 0;
        string palabraActual;
        int tipoInformacion = 0;
        while((posicion = linea.find(condicion)) != string::npos){
            while(linea.find(condicion) == 0){
              linea.erase(0,1);
            }
            posicion = linea.find(condicion);
            palabraActual = linea.substr(0,posicion);
            if(palabraActual.length( ) == 0){
                tipoInformacion = 4;
            }
            switch (tipoInformacion){
            case 0:
              simuladorInfo.nombreLamina = directorio+palabraActual;
              break;
            case 1:
                try {
                    simuladorInfo.deltaT = stod(palabraActual);
                    break;
                } catch (...)  {
                    archivo.close();
                    return EXIT_FAILURE;
                }
            case 2:
                try {
                    simuladorInfo.disTermA = stod(palabraActual);
                    break;
                } catch (...)  {
                    archivo.close();
                    return EXIT_FAILURE;
                }
            case 3:
                try {
                    simuladorInfo.altoH = stod(palabraActual);
                    break;
                } catch (...)  {
                    archivo.close();
                    return EXIT_FAILURE;
                }
            case 4:
                try {
                    simuladorInfo.epsilon= stod(palabraActual);
                    break;
                } catch (...)  {
                    archivo.close();
                    return EXIT_FAILURE;
                }
            default:
                archivo.close();
                return EXIT_FAILURE;
            }
            ++tipoInformacion;
            linea.erase(0,posicion + condicion.length());
            if(linea.length() == 0) {
                archivo.close();
                return EXIT_FAILURE;
            }
        }
        if(simuladorInfo.nombreLamina.length() == 0) {
            archivo.close();
            return EXIT_FAILURE;
            break;
        } else {
            simuladorInfo.resultado = "";
            vectorData.push_back(simuladorInfo);
        }
    }
    archivo.close();
    run(vectorData);
    writeTheResult(nombreArchivo, &vectorData);
} else {
  fprintf(stderr, "Error: No se pudo abrir el archivo\n");
  return EXIT_FAILURE;
}
return 1;
}
  
void run(vector<simuladorInfo>  vectorData){
    for (auto it = vectorData.begin(); it != vectorData.end(); ++it) {
        simuladorPlacas_t * Placas = simuladorPlacas_Create(it->deltaT,
        it->disTermA, it->altoH, it->epsilon);
       if(read_bin( it->nombreLamina ,  Placas)){
        simulacion_HeatTransfer(Placas);
       }
    }
    
}



int writeTheResult(string nombreArchivo, vector<simuladorInfo>*  vectorData) {
    int error = EXIT_SUCCESS;
    std::fstream newFile;
    std::stringstream output;
    for(auto itr = vectorData->begin(); itr != vectorData->end(); itr++){
        output << itr->nombreLamina.substr
        (itr->nombreLamina.find_last_of('/')+1)
        << '\t' << itr->deltaT
        << '\t' << itr->disTermA
        << '\t' << itr->altoH
        << '\t' << itr->epsilon
        << '\t' << itr->resultado << std::endl;
    }
    size_t pos = nombreArchivo.find_last_of(".");
    nombreArchivo.erase(pos, pos+4);
    nombreArchivo.insert(pos, ".tsv");
    newFile.open(nombreArchivo, ifstream::out);
    if (newFile.is_open()) {
        newFile << output.rdbuf();
        newFile.close();
    }
    return error;
}

void simulacion_HeatTransfer(simuladorPlacas_t* simulador) {
  int continuar = 1;
  double resultado = 0.0;
  while (continuar == 1) {
    for (int64_t i = 1; i < simulador->filas - 1; i++) {
      for (int64_t j = 1; j < simulador->columnas - 1; j++) {
        
        resultado = simuladorPlacas_sumarCruz(simulador,i,j);
        simulador->placaKPlus[i][j] = resultado;
         
       }
    }
      simulador->placa.swap(simulador->placaKPlus);
      continuar = verificar_diferencia(simulador);
  }
}
 
int verificar_diferencia(simuladorPlacas_t* simulador){
    int continuar = 0 ;
    for (int64_t i = 1; i < simulador->filas - 1; i++) {
      for (int64_t j = 1; j < simulador->columnas - 1; j++) {
        if(simulador->epsilon < 
        fabs(simulador->placa[i][j] - simulador->placaKPlus[i][j])){
          continuar = 1 ;
          break;         
        }
       }
    }

    return continuar;


}

/**
bool simuladorPlacas_openFile(simuladorPlacas_t* simulador, std::string filename, double deltat,
    int64_t disTermA, double h, double epsilon) {
    std::ifstream filePlaca(filename, std::fstream::in | std::fstream::binary);
    if (!filePlaca) {
        printf("//ERROR: No se pudo abrir el archivo binario\n");
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
**/
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