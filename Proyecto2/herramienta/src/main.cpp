// Copyright 2022 Equipo Dinamita Universidad de Costa Rica. CC BY 4.0
#include <math.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>

/**
 * @brief Se encarga de comparar dos placas y luego de 
 *      analizarlas imprime en pantalla si las placas son
 *      iguales o sino lo son
 * 
 * @param placa1 nombre de la primera placa
 * @param placa2 nombre de la segunda placa
 * @param epsilon  valor utiliza de referencia para la resta
 * @return 1 si son iguales 0 no lo son
 */
int compararPlacas(std::string placa1, std::string placa2, double epsilon);

int main(int argc, char* argv[]) {
  std::string placa1;
  std::string placa2;
  std::string epsilonString;
  double epsilon = 0.0;

  if (argc == 4) {
    placa1 = std::string(argv[1]);
    placa2 = std::string(argv[2]);
    epsilonString = std::string(argv[3]);
    try {
      epsilon = std::stod(epsilonString);
    } catch (...) {
      fprintf(stderr, "ERROR: valor invalido de epsilon \n");
    }
  } else {
    fprintf(stderr, "ERROR: no se proporciono todos los argumentos\n");
    return EXIT_FAILURE;
  }
  return compararPlacas(placa1, placa2, epsilon);
}

int compararPlacas(std::string placa1, std::string placa2, double epsilon) {
  std::ifstream archivoPlaca1(placa1, std::fstream::in | std::fstream::binary);
  std::ifstream archivoPlaca2(placa2, std::fstream::in | std::fstream::binary);
  if (!archivoPlaca1 && !archivoPlaca2) {
    std::cout << "No se pudo abrir el archivo binario" << std::endl;
    return 0;
  } else {
    int64_t filas1;
    int64_t filas2, columnas1, columnas2;
    // Se lee el archivo 1
    archivoPlaca1.read(reinterpret_cast<char*>(&filas1), sizeof(filas1));
    archivoPlaca1.read(reinterpret_cast<char*>(&columnas1), sizeof(columnas1));
    // Se lee el archivo 2
    archivoPlaca2.read(reinterpret_cast<char*>(&filas2), sizeof(filas2));
    archivoPlaca2.read(reinterpret_cast<char*>(&columnas2), sizeof(columnas2));
    double valorCeldaPlaca1 = 0.0;
    double valorCeldaPlaca2 = 0.0;
    if ((filas1 == filas2) && (columnas1 == columnas2)) {
      for (int64_t fila = 0; fila < filas1; fila++) {
        for (int64_t columna = 0; columna < columnas1; columna++) {
          archivoPlaca1.read(reinterpret_cast<char*>(&valorCeldaPlaca1),
                           sizeof(valorCeldaPlaca1));
          archivoPlaca2.read(reinterpret_cast<char*>(&valorCeldaPlaca2),
                           sizeof(valorCeldaPlaca2));
          if (fabs(valorCeldaPlaca1 - valorCeldaPlaca2) > epsilon) {
            std::cout << "Las laminas son diferentes" << std::endl;
            archivoPlaca1.close();
            archivoPlaca2.close();
            return 0;
          }
        }
      }
      std::cout << "Las laminas son iguales" << std::endl;
      return 1;
    } else {
      std::cout << "Las laminas son de tamanio distinto" << std::endl;
      return 0;
    }
    archivoPlaca1.close();
    archivoPlaca2.close();
  }
  return 1;
}
