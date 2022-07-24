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
      fprintf(stderr, "ERROR: Invalid epsilon value\n");
    }
  } else {
    fprintf(stderr, "ERROR: could not get the file name\n");
    return EXIT_FAILURE;
  }

  return compararPlacas(placa1, placa2, epsilon);
}

int compararPlacas(std::string placa1, std::string placa2, double epsilon) {
  std::ifstream archivoPlaca1(placa1, std::fstream::in | std::fstream::binary);
  std::ifstream archivoPlaca2(placa2, std::fstream::in | std::fstream::binary);
  if (!archivoPlaca1 && !archivoPlaca2) {
    std::cout << "Could not open the binary file" << std::endl;
    return 0;
  } else {
    uint64_t filas1, filas2, columnas1, columnas2;
    // Se lee filas
    archivoPlaca1.read(reinterpret_cast<char*>(&filas1), sizeof(filas1));
    archivoPlaca2.read(reinterpret_cast<char*>(&filas2), sizeof(filas2));
    // Se lee columnas
    archivoPlaca1.read(reinterpret_cast<char*>(&columnas1), sizeof(columnas1));
    archivoPlaca2.read(reinterpret_cast<char*>(&columnas2), sizeof(columnas2));
    double valorCeldaPlaca1 = 0.0;
    double valorCeldaPlaca2 = 0.0;
    if ((filas1 == filas2) && (columnas1 == columnas2)) {
      for (uint64_t fila = 0; fila < filas1; fila++) {
        for (uint64_t columna = 0; columna < columnas1; columna++) {
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
      std::cout << "Las laminas son diferentes" << std::endl;
      return 0;
    }
    archivoPlaca1.close();
    archivoPlaca2.close();
  }
  return 1;
}
