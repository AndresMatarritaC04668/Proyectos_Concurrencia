#include "Despachador.hpp"
#include "HttpResponse.hpp"
#include "nodo.hpp"

#include <string>

Despachador::Despachador(/* args */) { }

bool Despachador::sendResponse(shared_data_t* shared_data) {
  return shared_data->httpResponse->send();
}

void Despachador::consume(shared_data_t* shared_data) {
  nodo_t* actual = shared_data->cola->first;
  int64_t comparacion = 5;
  while (actual) {
    shared_data->httpResponse->body() << "<br>"
      << "</br>";  // Cambios de linea
    shared_data->httpResponse->body() << "<span>";
      
    if ( nodo_getNumber(actual)<= comparacion ) {
        //  Imprime "NA" si es menor que 5;
        shared_data->httpResponse->body() << "<span>"
        << nodo_getSigno(actual) << nodo_getNumber(actual) << ": NA" 
        << "</span>\n";  // \n No influye
    } else {
        //  Imprime Informacion;
      shared_data->httpResponse->body() << "<span>"
      << nodo_getSigno(actual) << nodo_getNumber(actual) << ": " << actual->sumas
      << " sums";

      if (actual->signo == '-') {
          //  Imprime desglose si es negativo;
          shared_data->httpResponse->body() << ": ";
          if (actual-> number%2 == 0) {
            for (int i = 0; i< actual->posicion ; i++) {
              shared_data->httpResponse->body() << actual->desglose[i]
              << " + ";
              ++i;
              shared_data->httpResponse->body() << actual->desglose[i];
              if (i < actual-> posicion-1) {
                shared_data->httpResponse->body() << ", ";
              } else {
                shared_data->httpResponse->body() << "</span>\n";  // \n No influye
              }
            }
          } else {
            for (int i = 0; i < actual-> posicion ; i++) {
              shared_data->httpResponse->body() << actual->desglose[i]
              << " + ";
              ++i;
              shared_data->httpResponse->body() << actual->desglose[i]
              << " + ";
              ++i;
              shared_data->httpResponse->body() << actual->desglose[i];
              if (i < actual-> posicion-1) {
                shared_data->httpResponse->body() << ", ";
              } else {
                shared_data->httpResponse->body() << "</span>\n";
              }
            }
          }
      }
    }
  }
  shared_data->httpResponse->body()
    << "  <hr><p><a href=\"/\">Back</a></p>\n"
    << "</html>\n";
  this->sendResponse(shared_data);

  pthread_mutex_lock(&shared_data->cola->can_access);
  pthread_mutex_unlock(&shared_data->cola->can_access);
  pthread_mutex_destroy(&shared_data->cola->can_access);
  delete shared_data->httpResponse;
  delete shared_data;
}




int Despachador::run() {
  this->consumeForever();
  return 0;
}

Despachador::~Despachador() {
}
