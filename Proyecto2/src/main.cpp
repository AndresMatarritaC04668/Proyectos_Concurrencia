//  Copyright 2022 Equipo Dinamita Universidad De Costa Rica
#include <iostream>
#include <string>
#include <unistd.h>

int main (int argc, char* argv[]){
    std::cout<<"bienvenido al programa de transferencia de calor de placas";
    //  nombre del archivo de prueba
    std::string nomArchivo = " ";
    int numeroDeHilos = sysconf(_SC_NPROCESSORS_ONLN);
    if(argc >= 2){
        nomArchivo = argv[1];
        if (argc >= 3) {
            //    numeroDeHilos := argv[2]
            if (sscanf(argv[2], "%", &numeroDeHilos) == 1) {

            } else {
                std::cout<<"La cantidad de hilos introducida no es valida";
                return EXIT_FAILURE;
            }
           
        }
        std::cout<<"Se trabajara con "<< numeroDeHilos <<" hilos";
        //  creamos los objetos como el controladorDeArchivos 
    }

}
