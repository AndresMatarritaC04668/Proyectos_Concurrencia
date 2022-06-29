#ifndef DESPACHADOR_HPP
#define DESPACHADOR_HPP
#include "HttpResponse.hpp"
#include <cstdint>  
#include <cstdlib>  
#include "Assembler.hpp"
#include "Consumer.hpp"
#include "cola.hpp"


class Despachador : public Consumer<shared_data_t*> {
  private:
    /* data */
  public:

    Despachador(/* args */);

    void consume(shared_data_t* shared_data) override;

    bool sendResponse(shared_data_t* shared_data);

    int run() override;

    ~Despachador();


};

#endif  // DESPACHADOR_HPP
