// Copyright Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0
#ifndef EMPAQUETADOR_HPP
#define EMPAQUETADOR_HPP
#include <cstdint>
#include <cstdlib>
#include "Assembler.hpp"
#include "cola.hpp"
#include "HttpResponse.hpp"

class Empaquetador : public Assembler<shared_data_t*, cola_t*> {
 private:
    /* datos */

 public:
    /**
     * @brief Construye un nuevo objeto Empaquetador
     * 
     */
    Empaquetador(/* args */);

    /**
     * @brief Destruye un nuevo objeto Empaquetador
     * 
     */
    ~Empaquetador();

   /**
    * @brief Analiza la cantidad de numeros procesados, una vez que 
    *  los proceso a todos, hace un llamado a produce
    * 
    * @param shared_data contiene un mutex para evir data race
    */
    void consume(shared_data_t* shared_data) override;

    /**
     * @brief Override de run del consumer de la clase Assembler
     * y se encarga de consumir para siempre hasta encontrar una condicion de 
     * parada
     * @return int que fue exitoso
     */
    int run() override;
};
#endif  // EMPAQUETADOR_HPP
