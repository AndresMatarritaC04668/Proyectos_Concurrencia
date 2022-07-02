// Copyright 2022 Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include "unistd.h"
#include "utility"
#include "Empaquetador.hpp"
#include "Despachador.hpp"
#include "SumGoldbachSolver.hpp"

#include "GoldbachWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

GoldbachWebApp::GoldbachWebApp() {
  //  agregamos las 3 keys de la App
  this->keys.push_back("/goldbach");
  this->keys.push_back("/");
  this->keys.push_back("/noEncontrada");
}

GoldbachWebApp::~GoldbachWebApp() {
}

void GoldbachWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
  
  //  crear urlMiedo aqui
  decodeURL = new DecodeURL();
  decodeURL->setProducingQueue(&urlProduct);
  decodeURL->setConsumingQueue(&this->solicitudes);
  decodeURL->startThread();
   
  goldbachThreads.resize(sysconf(_SC_NPROCESSORS_ONLN));
  for (int i = 0; i < sysconf(_SC_NPROCESSORS_ONLN); i++) {
    SumGoldbachSolver* golNue = new SumGoldbachSolver(&urlProduct,
      &solversProduct);
    goldbachThreads[i] = golNue;
    goldbachThreads[i]->startThread();
  }
  
  
  empaquetador = new Empaquetador();
  empaquetador->setProducingQueue(&empaquetadorProduct);
  empaquetador->setConsumingQueue(&solversProduct);
  empaquetador->startThread();
  despachador = new Despachador();
  despachador->setConsumingQueue(&empaquetadorProduct);
  despachador->startThread();
}

void GoldbachWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
  this->solicitudes.push(std::pair<HttpRequest*, HttpResponse*>());
  decodeURL->waitToFinish();
  delete decodeURL;
   
  int number_CPU= sysconf(_SC_NPROCESSORS_ONLN);
  shared_data_t* condicionParada = 0;

  for (int i = 0; i < number_CPU ; i++) {
    this->urlProduct.push(condicionParada);
  }
  for (int i= 0; i < number_CPU ; i++) {
    // std::cout<< "hilo: "<<index<<"\n";
    goldbachThreads[i]->waitToFinish();
    delete goldbachThreads[i];
  }

  this->solversProduct.push(condicionParada);
  this->empaquetador->waitToFinish();
  delete empaquetador;
  
  cola_t* condicionParadaCola = 0;
  this->empaquetadorProduct.push(condicionParadaCola);
  despachador->waitToFinish();
  delete despachador;
}

// procedure handleHttpRequest(httpRequest, httpResponse):
bool GoldbachWebApp::handleHttpRequest(HttpRequest& httpRequest,
  HttpResponse& httpResponse) {
  (void) httpRequest;
  (void) httpResponse;

   return 1;
}  // end procedure
