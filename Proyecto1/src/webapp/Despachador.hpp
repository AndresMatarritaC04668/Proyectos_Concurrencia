#ifndef DESPACHADOR_HPP
#define DESPACHADOR_HPP
#include "HttpResponse.hpp"
#include <cstdint>  
#include <cstdlib>  
#include "Assembler.hpp"
#include "Consumer.hpp"
#include "cola.hpp"


class Despachador : public Consumer<cola_t*> {
  private:
    /* data */
  public:

    Despachador(/* args */);

    void consume(cola_t* cola) override;

    bool sendResponse(cola_t* cola);

    int run() override;

     void addToResults(HttpResponse& httpResponse ,
    nodo_t* nodo, int& i);


    ~Despachador();


};

#endif  // DESPACHADOR_HPP
