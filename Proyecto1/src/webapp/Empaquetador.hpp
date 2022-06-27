#ifndef EMPAQUETADOR_HPP
#define EMPAQUETADOR_HPP
#include "HttpResponse.hpp"
#include <cstdint>  
#include <cstdlib>  
#include "Assembler.hpp"
#include "Consumer.hpp"
#include "cola.hpp"


class Empaquetador : public Assembler<cola_t*, shared_data_t*> {
  private:
    /* data */

  public:

    Empaquetador(/* args */);

    shared_data_t* local_shared_data;

    void consume(shared_data_t* shared_data);

    int run() override;

    ~Empaquetador();

};

#endif  // EMPAQUETADOR_HPP
