#include "Despachador.hpp"
#include "HttpResponse.hpp"
#include "nodo.hpp"

#include <string>

Despachador::Despachador(/* args */) { }

bool Despachador::sendResponse(shared_data_t* shared_data) {
   return shared_data->cola->structureResponse->httpResponse.send();  
}

void Despachador::consume(shared_data_t* shared_data) {
// declare result := ""
  int64_t comparacion = 5;
  // declare nodo: first nodo of cola
  nodo_t* nodo = shared_data->cola->first;

  // while nodo != null do
  while (nodo) {
    if (nodo->error == 0) {
    shared_data->cola->structureResponse->httpResponse.body() << "  <h2>" << nodo_getSigno(nodo)
    << nodo_getNumber(nodo) << "</h2>\n";
    // if number of nodo < 5 do
    if ( nodo_getNumber(nodo)<= comparacion ) {
        // result := result + NA
        shared_data->cola->structureResponse->httpResponse.body() << "  <p> NA</p>\n";
    } else {
         //  result := result + number of nodo + sums of nodo
       shared_data->cola->structureResponse->httpResponse.body() << " " <<nodo_getSigno(nodo) << nodo_getNumber(nodo) << ": ";
        shared_data->cola->structureResponse->httpResponse.body() << "Sumas: "<< nodo->sumas;

        // if number of nodo show sums == true do
        if (nodo->signo == '-') {
            // result := result + every sum of the number of nodo
            shared_data->cola->structureResponse->httpResponse.body() << " : ";
            if (nodo-> number%2 == 0) {
                for (int i = 0; i< nodo->posicion ; i++) {
                  addToResults(shared_data->cola->structureResponse->httpResponse , nodo, i);

                if (i < nodo-> posicion-1) {
                       shared_data->cola->structureResponse->httpResponse.body() <<", ";
                    }
                }
            } else {
                for (int i = 0; i < nodo-> posicion ; i++) {
                  addToResults(shared_data->cola->structureResponse->httpResponse , nodo, i);
                  ++i;
                  shared_data->cola->structureResponse->httpResponse.body() <<'+';
                  shared_data->cola->structureResponse->httpResponse.body() << nodo->desglose[i];
                  if (i < nodo-> posicion-1) {
                        shared_data->cola->structureResponse->httpResponse.body() <<", ";
                    }
                }
            }
        }  // end if
    }  // end else
  } else {
          shared_data->cola->structureResponse->httpResponse.body() << " <h2 class=\"err\">"
          << nodo->numeroErroneo << "</h2>\n";
          shared_data->cola->structureResponse->httpResponse.body() <<  " <p> " << nodo->numeroErroneo
          << ": invalid number</p>\n";
  }
  printf("\n");
  // nodo := nodo next
  nodo = nodo->next;
  } // end while

  std::string title = "Goldbach Conjecture of the input";
  // End part of a HTML file
     shared_data->cola->structureResponse->httpResponse.body()
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  
  this->sendResponse(shared_data);

  cola_destroy(shared_data->cola);
  delete shared_data;
  
}


void Despachador::addToResults( HttpResponse& httpResponse ,
 nodo_t* nodo, int& i) {
  httpResponse .body() << nodo->desglose[i];
  ++i;
  httpResponse.body() <<'+';
  httpResponse.body() << nodo->desglose[i];
}




int Despachador::run() {
  this->consumeForever();
  return 0;
}

Despachador::~Despachador() {
}
