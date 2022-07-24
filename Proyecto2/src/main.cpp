//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#include <unistd.h>
#include <string>
#include <iostream>
#include "simuladorPlacas.hpp"
#include "structs.hpp"

int main(int argc, char* argv[]) {
    std::cout << "Bienvenido al programa de transferencia de calor de placas";
    //  nombre del archivo de prueba
    std::string nombreArchivo;
    std::string directorio = "";
    int error = 0;
    int numeroDeHilos = sysconf(_SC_NPROCESSORS_ONLN);
    if (argc >= 2) {
        nombreArchivo = argv[1];
        if (argc >= 3) {
            //    numeroDeHilos := argv[2]
            if (sscanf(argv[2], "%d", &numeroDeHilos) == 1) {
            } else {
                std::cout << "La cantidad de hilos introducida no es valida\n";
                return EXIT_FAILURE;
            }
        }
        std::cout << "\n Se trabajara con " << numeroDeHilos << " hilos";
        //  creamos los objetos como el controladorDeArchivos
    } else {
       fprintf(stderr,
            "\nError: Debe agregar el nombre del archivo por parametro\n");
            return EXIT_FAILURE;
    }

    error = abrir_archivo(nombreArchivo, directorio, numeroDeHilos);
    return error;
}
