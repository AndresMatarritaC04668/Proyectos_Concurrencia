//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#include "simuladorPlacas.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::setfill;
using std::to_string;
using std::fstream;

void imprimir(simuladorPlacas_t  *  simuladorPlacas){
    printf("\n");
    for (int64_t i = 0; i < simuladorPlacas->filas; i++) {
      for (int64_t j = 0; j < simuladorPlacas->columnas; j++) {
        printf("%f ", simuladorPlacas->placa[i][j]);
       }
       printf("\n");
    }

}


int abrir_archivo(string nombreArchivo, string directorio, int numeroDeHilos){
    int error = EXIT_SUCCESS ;
    ifstream archivo;
    archivo.open(nombreArchivo , ifstream::in);
    if(archivo.is_open()){
      vector<simuladorInfo_t>  vectorData;
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
                    //cout<<""stod(palabraActual)<<endl;
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
    
    run(&vectorData );
    for(int i = 0 ; i < vectorData.size(); i++){
        generar_Resultado(&vectorData[i]);
    }
    imprimir_Resultado(nombreArchivo, &vectorData);
} else {
  fprintf(stderr, "Error: No se pudo abrir el archivo\n");
  return EXIT_FAILURE;
}
return 1;
}
  
int imprimir_Resultado(string nombreArchivo, vector<simuladorInfo>*  vectorData) {
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
    cout<<nombreArchivo;
    return error;
}

void generar_Resultado( simuladorInfo_t * simuladorInfo ) {
    stringstream resultado;

    resultado << setfill(' ') << setw(6) << simuladorInfo->estadok  << "\t";
    double segundos = simuladorInfo->estadok * simuladorInfo->deltaT; // segundos totales

    int temporal= 0;  // Guarda cantidad de años, meses temporalmente
    
    temporal= segundos/ 31104000;  // segundos en un año =  año
    segundos = segundos-static_cast<double>(temporal * 31104000);  //  año
    resultado << setfill('0') << setw(4)<< temporal<< "/";
    
    temporal= segundos/ 2592000 ;  // mes
    segundos = segundos-static_cast<double>(temporal *  2592000); // mes
    resultado << setfill('0') << setw(2)<< temporal<< "/";
    

    temporal= segundos/86400;  // dia
    segundos = segundos-static_cast<double>(temporal * 86400);
    resultado << setfill('0') << setw(2)<< temporal<< "\t";
    
    temporal= segundos/ 3600;  // hora
    segundos = segundos-static_cast<double>(temporal * 3600);
    resultado << setfill('0') << setw(2)<< temporal<< ":";
    
    temporal= segundos/ 60;  // minutos
    segundos = segundos-static_cast<double>(temporal * 60);
    resultado << setfill('0') << setw(2)<< temporal<< ":";
    
    temporal= static_cast<int>(segundos);  // segundo
    
    resultado << setfill('0') << setw(2)<< temporal;
    
    simuladorInfo->resultado = resultado.str(); // cambia valor del resultado
    
 }

void imprimir_laminas(string nombreLamina, simuladorPlacas * simuladorPlacas){
  string tira_extra = string("-")+ to_string(simuladorPlacas->estadok);  // archivo de reporte
  int64_t agregarApartir = nombreLamina.find_last_of("."); //  Despues del punto agregue(posicion)
  string nuevoNombre = nombreLamina; 
  nuevoNombre.insert(agregarApartir,tira_extra);

    ofstream lamina(nuevoNombre, fstream::out | fstream::binary);
    if (!lamina) {
        cout << "No se puede abrir el binario." << endl;
    } else {
        
      lamina.write(reinterpret_cast<char*>(&nombreLamina),
        sizeof(int));
      // Se lee columnas
      lamina.write(reinterpret_cast<char*>(&simuladorPlacas->columnas),
      sizeof(simuladorPlacas->columnas));
  
      for (int fila = 0;simuladorPlacas->filas < fila; ++fila) {
       for (int columna = 0; simuladorPlacas->columnas < columna; ++columna) {
        lamina.write(reinterpret_cast<char*>(&simuladorPlacas->placa[fila][columna]),
                       sizeof(simuladorPlacas->placa[fila][columna]));
       }
        
      }
      lamina.close();

    }
}
 


void run(vector<simuladorInfo> * vectorData ){
    for (auto it = vectorData->begin(); it != vectorData->end(); ++it) {
        simuladorPlacas_t * simuladorPlacas = simuladorPlacas_Create(it->deltaT,
        it->disTermA, it->altoH, it->epsilon);  
       if(read_bin( it->nombreLamina , simuladorPlacas)){
          simulacion_HeatTransfer(simuladorPlacas);
          it->estadok = simuladorPlacas->estadok;
          imprimir_laminas(it->nombreLamina , simuladorPlacas);
          simuladorPlacas->placa.clear();
          simuladorPlacas->placaKPlus.clear();
          free(simuladorPlacas);

       }  
    }      
}


void simulacion_HeatTransfer(simuladorPlacas_t* simulador) {
  int continuar = 1;
  double resultadoultado = 0.0;
  while (continuar == 1) {
    for (int64_t i = 1; i < simulador->filas - 1; i++) {
      for (int64_t j = 1; j < simulador->columnas - 1; j++) {
        
        resultadoultado = simuladorPlacas_sumarCruz(simulador,i,j);
        simulador->placaKPlus[i][j] = resultadoultado;
         
       }
    }
      simulador->placa.swap(simulador->placaKPlus);
      continuar = verificar_diferencia(simulador);
      ++simulador->estadok;
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
    //  resultadoultado := 0.0
    double resultadoultado = 0.0;
    //  actual := valor actual de la celda
    double actual = simuladorPlacas_getCelda(simulador, fila, columna);
    //  se suma la energia de las inmediaciones
    resultadoultado = resultadoultado + simuladorPlacas_getCelda(simulador, fila, columna+1) 
        + simuladorPlacas_getCelda(simulador, fila, columna - 1);
    resultadoultado = resultadoultado + simuladorPlacas_getCelda(simulador, fila+1, columna) 
        + simuladorPlacas_getCelda(simulador, fila-1,columna);
    //  se resultadota la energia perdida y distribuida a las otras celdas    
    resultadoultado = resultadoultado - 4*actual;

    //  multiplicamos por el tiempo y difusividad termica entre alto de la celda al cuadrado
    double tiDiAl = ((simulador->deltaT * simulador->disTermA)/(simulador->altoH*simulador->altoH));
    resultadoultado = resultadoultado * tiDiAl;

    //  agregamos el estado actual de la celda
    resultadoultado = resultadoultado + actual;
    // retornamos el estado k+1 de la celda almacenado en resultadoultado
    return resultadoultado;
}