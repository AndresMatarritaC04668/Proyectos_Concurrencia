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
#include <Log.hpp>

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
   
  goldbachThreads.resize(sysconf(_SC_NPROCESSORS_ONLN));
  for (int i = 0; i < sysconf(_SC_NPROCESSORS_ONLN); i++) {
    SumGoldbachSolver* golNue = new SumGoldbachSolver(&urlProduct,
      &solversProduct);
    goldbachThreads[i] = golNue;
    goldbachThreads[i]->startThread();
  }
  
  decodeURL = new DecodeURL();
  decodeURL->setProducingQueue(&urlProduct);
  decodeURL->setConsumingQueue(&this->solicitudes);
  decodeURL->startThread();
  empaquetador = new Empaquetador();
  empaquetador->createOwnQueue();
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
   
  int number_CPU= sysconf(_SC_NPROCESSORS_ONLN);
  shared_data_t* condicionParada = 0;

  for (int i = 0; i < number_CPU ; i++) {
     goldbachThreads[i]->getConsumingQueue()->push(condicionParada);
  }

  for(int i = 0; i < number_CPU; i++){
    if(i == 0){
      goldbachThreads[0]->produce(condicionParada);
    }
  }

  this->empaquetador->getProducingQueue()->push(condicionParada);
  this->empaquetador->waitToFinish();

  for (int i= 0; i < number_CPU ; i++) {
    // std::cout<< "hilo: "<<index<<"\n";
    goldbachThreads[i]->waitToFinish();

    delete goldbachThreads[i];
  }

  despachador->waitToFinish();
  delete despachador;

  decodeURL->waitToFinish();
  delete decodeURL;
  //delete empaquetador;

 
}

// procedure handleHttpRequest(httpRequest, httpResponse):
bool GoldbachWebApp::handleHttpRequest(HttpRequest& httpRequest,
  HttpResponse& httpResponse) {
  (void) httpRequest;
  (void) httpResponse;

   return 1;
}  // end procedure
