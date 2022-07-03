#include "Empaquetador.hpp"
#include "HttpResponse.hpp"

Empaquetador::Empaquetador(/* args */) {}

Empaquetador::~Empaquetador() {}

void Empaquetador::consume(shared_data_t* shared_data) {
  int borrar = 0;
  pthread_mutex_lock(&shared_data->can_access);
  // Aumenta la variable para comparar si ha procesado todos los numeros.
  shared_data->cola->numerosProcesados++;
  if (shared_data->cola->numerosProcesados ==
      shared_data->cola->cantidadNumeros) {
    // Una vez verifica que ha procesado todos los numeros, produce.
    produce(shared_data->cola);
    borrar = 1;
  }
  pthread_mutex_unlock(&shared_data->can_access);
  
  if(borrar == 1 ){
    pthread_mutex_destroy(&shared_data->can_access);
  }
  delete shared_data;
  


     
}



int Empaquetador::run() {
  this->consumeForever();
  return 0;
}