#include "Empaquetador.hpp"
#include "HttpResponse.hpp"

Empaquetador::Empaquetador(/* args */) {}

Empaquetador::~Empaquetador() {}

void Empaquetador::consume(shared_data_t* shared_data) {
  local_shared_data = shared_data;
  pthread_mutex_lock(&local_shared_data->cola->can_access);
  // Aumenta la variable para comparar si ha procesado todos los numeros.
  local_shared_data->cola->numerosProcesados++;
  if (local_shared_data->cola->numerosProcesados ==
    local_shared_data->cola->cantidadNumeros) {
    // Una vez verifica que ha procesado todos los numeros, produce.
    produce(local_shared_data->cola);
  }
  pthread_mutex_unlock(&local_shared_data->cola->can_access);
  delete local_shared_data;
}

int Empaquetador::run() {
  this->consumeForever();
  return 0;
}