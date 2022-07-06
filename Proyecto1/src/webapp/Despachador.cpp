//  "Copyright [2022] <Equipo Dinamita>"
#include <string>
#include <iostream>
#include "Despachador.hpp"
#include "HttpResponse.hpp"
#include "nodo.hpp"

Despachador::Despachador(/* args */) { }

bool Despachador::sendResponse(cola_t* cola) {
  return cola->structureResponse->httpResponse.send();
}

void Despachador::consume(cola_t* cola) {
  std::string title = "Goldbach Sums";
  cola->structureResponse->httpResponse.body()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace}</style>\n"
      << "  <h1>" << title << "</h1>\n";
  // declare result := ""
  int64_t comparacion = 5;
  // declare nodo: first nodo of cola
  nodo_t* nodo = cola->first;
  // while nodo != null do
  while (nodo) {
    if (nodo->error == 0) {
    cola->structureResponse->httpResponse.body() << "  <h2>"
      << nodo_getSigno(nodo)
      << nodo_getNumber(nodo) << "</h2>\n";
    // if number of nodo < 5 do
    if ( nodo_getNumber(nodo)<= comparacion ) {
        // result := result + NA
        cola->structureResponse->httpResponse.body()
        << "  <p> NA</p>\n";
    } else {
         //  result := result + number of nodo + sums of nodo
       cola->structureResponse->httpResponse.body() << " "
        <<nodo_getSigno(nodo) << nodo_getNumber(nodo) << ": ";
        cola->structureResponse->httpResponse.body() << "Sumas: "<< nodo->sumas;

        // if number of nodo show sums == true do
        if (nodo->signo == '-') {
            // result := result + every sum of the number of nodo
            cola->structureResponse->httpResponse.body() << " : ";
            if (nodo-> number%2 == 0) {
                for (int i = 0; i< nodo->posicion ; i++) {
                  addToResults(cola->structureResponse->httpResponse , nodo, i);

                if (i < nodo-> posicion-1) {
                       cola->structureResponse->httpResponse.body() <<", ";
                    }
                }
            } else {
                for (int i = 0; i < nodo-> posicion ; i++) {
                  addToResults(cola->structureResponse->httpResponse , nodo, i);
                  ++i;
                  cola->structureResponse->httpResponse.body() <<'+';
                  cola->structureResponse->httpResponse.body()
                  << nodo->desglose[i];
                  if (i < nodo-> posicion-1) {
                        cola->structureResponse->httpResponse.body() <<", ";
                    }
                }
            }
        }  // end if
    }  // end else
  } else {
      cola->structureResponse->httpResponse.body()
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << " <h2 class=\"err\">"
      << nodo->numeroErroneo << "</h2>\n"
      <<  " <h4 class=\"err\"> " << nodo->numeroErroneo
      << ": Invalid number request for Goldbach</h4>\n";
}

  printf("\n");
  // nodo := nodo next
  nodo = nodo->next;
  }  // end while
  cola->structureResponse->httpResponse.body()
  << "  <hr><p><a href=\"/\">Back</a></p>\n"
  << "</html>\n";

  this->sendResponse(cola);
  delete &cola->structureResponse->httpResponse;
  delete cola->structureResponse;
  cola_destroy(cola);
}

void Despachador::addToResults(HttpResponse& httpResponse,
 nodo_t* nodo, int& i) {
  httpResponse.body() << nodo->desglose[i];
  ++i;
  httpResponse.body() <<'+';
  httpResponse.body() << nodo->desglose[i];
}

int Despachador::run() {
  this->consumeForever();
  return 0;
}

Despachador::~Despachador() {}
