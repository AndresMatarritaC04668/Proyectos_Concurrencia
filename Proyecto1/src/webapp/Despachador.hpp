//  "Copyright [2022] <Equipo Dinamita>"
#ifndef DESPACHADOR_HPP
#define DESPACHADOR_HPP
#include <cstdint>
#include <cstdlib>
#include "Assembler.hpp"
#include "Consumer.hpp"
#include "cola.hpp"
#include "HttpResponse.hpp"


class Despachador : public Consumer<cola_t*> {
 private:
    /* data */
 public:
    /**
     * @brief Construye un nuevo objeto Despachador
     * 
     */
    Despachador(/* args */);

    /**
     * @brief Destruye un nuevo objeto Despachador
     * 
     */
    ~Despachador();

    /**
     * @brief override del consume, se encarga de trabajar con
     * los nodos dentro de la cola, este le da cuerpo al response con
     * los resultados obtenidos
     *
     * @param cola que el contenedor de los numeros ingresados por le usuario
     */
    void consume(cola_t* cola) override;

    /**
     * @brief Realiza un llamado al metodo send del http response
     * 
     * @param cola que contiene el httpresponse
     * @return true / false 
     */
    bool sendResponse(cola_t* cola);

    /**
     * @brief Override de run del consumer de la clase Assembler
     * y se encarga de consumir para siempre hasta encontrar una condicion de 
     * parada
     * @return int que fue exitoso
     */
    int run() override;

    /**
     * @brief Se encarga de agregar un + entre los numeros para la 
     *  respuesta final
     * 
     * @param httpResponse resultado final que va a ver el usuario
     * @param nodo nodo para trabajar
     * @param i posicion del nodo 
     */
    void addToResults(HttpResponse& httpResponse ,
    nodo_t* nodo, int& i);
};

#endif  // DESPACHADOR_HPP
