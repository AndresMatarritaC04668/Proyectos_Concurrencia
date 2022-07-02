#include "Empaquetador.hpp"
#include "HttpResponse.hpp"

Empaquetador::Empaquetador(/* args */) {}

Empaquetador::~Empaquetador() {}

void Empaquetador::consume(shared_data_t* shared_data) {
  pthread_mutex_lock(&shared_data->cola->can_access);
  local_shared_data = shared_data;
  // Aumenta la variable para comparar si ha procesado todos los numeros.
  local_shared_data->cola->numerosProcesados++;
  if (local_shared_data->cola->numerosProcesados ==
    local_shared_data->cola->cantidadNumeros) {
    // Una vez verifica que ha procesado todos los numeros, produce.
    produce(local_shared_data);
  }
  local_shared_data = nullptr;
  pthread_mutex_unlock(&shared_data->cola->can_access);
}



int Empaquetador::run() {
  this->consumeForever();
  return 0;
}