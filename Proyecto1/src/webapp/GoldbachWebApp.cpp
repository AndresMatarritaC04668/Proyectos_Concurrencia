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
  this->createOwnQueue();
  this->setProducingQueue(&appProduct);
}

GoldbachWebApp::~GoldbachWebApp() {
}

void GoldbachWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
  empaquetador = new Empaquetador();
  empaquetador->createOwnQueue();
  empaquetador->setProducingQueue(&empaquetadorProduct);
  empaquetador->setConsumingQueue(&solversProduct);
  empaquetador->startThread();

  
   
  goldbachThreads.resize(sysconf(_SC_NPROCESSORS_ONLN));
  for (int i = 0; i < sysconf(_SC_NPROCESSORS_ONLN); i++) {
    SumGoldbachSolver* golNue = new SumGoldbachSolver(this->getProducingQueue(),
      &solversProduct);
    goldbachThreads[i] = golNue;
  
    goldbachThreads[i]->startThread();

  }
  despachador = new Despachador();
  despachador->setConsumingQueue(&empaquetadorProduct);
  
  despachador->startThread();
 
}

void GoldbachWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
   
  int number_CPU= sysconf(_SC_NPROCESSORS_ONLN);

  for (int i = 0; i < number_CPU ; i++) {
     shared_data_t* paradaCondicion = nullptr; 
     goldbachThreads[i]->getConsumingQueue()->push(paradaCondicion);
  }

  for (int i= 0; i < number_CPU ; i++) {
    shared_data_t* paradaCondicion = nullptr; 
    if ( i == 0) {
      goldbachThreads[0]->produce(paradaCondicion);
    }
  }

  shared_data_t  * condicionDespachador = nullptr;
  this->empaquetador->getProducingQueue()->push(condicionDespachador);
  this->empaquetador->waitToFinish();

  for (int i= 0; i < number_CPU ; i++) {
    // std::cout<< "hilo: "<<index<<"\n";
    goldbachThreads[i]->waitToFinish();

    delete goldbachThreads[i];
  }

  despachador->waitToFinish();
  delete despachador;
  delete empaquetador;
}

// procedure handleHttpRequest(httpRequest, httpResponse):
bool GoldbachWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the home page was asked
  // if getMethod from httpRequest == "GET"
  // and getURI from httpRequest == "/" do
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    // return serverHomepage(httpRequest, httpResponse)
    return this->serveHomepage(httpRequest, httpResponse);
  }  // end if

  // If the request starts with "/goldbach" is for this web app
  // if "/goldbach" in getURI do
  if (httpRequest.getURI().rfind("/goldbach", 0) == 0) {
    // return serverGoldbach(httpRequest, httpResponse)
    return this->serveGoldbach(httpRequest, httpResponse);
  }  // end if

  // Unrecognized request
  return this->serveNotFound(httpRequest, httpResponse);
}  // end procedure

// TODO(you): Fix code redundancy in the following methods
void GoldbachWebApp::setHeaderResponse(HttpResponse& httpResponse) {
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");
}

void GoldbachWebApp:: beginAndEndHtml(
HttpResponse& httpResponse, std::string title, int end) {
  if (!end) {
    // Start part of a HTML file
    httpResponse.body() << "<!DOCTYPE html>\n"
        << "<html lang=\"en\">\n"
        << "  <title>" << title << "</title>\n";
  } else {
    // End part of a HTML file
     httpResponse.body()
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  }
}

// procedure htmlResponse(httpResponse, title, cola, option):
void GoldbachWebApp::htmlResponse(
  HttpResponse& httpResponse , std::string title , cola_t* cola, int option) {
  if (option >= 0 && option <= 2) {
    // set the begining body of HTML file
    beginAndEndHtml(httpResponse, title, 1);
    // if option == 0 do
    if (!option) {
      // htmlResponse.body := set the HTML body of homepage
      httpResponse.body() << "  <style>body {font-family: monospace}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <form method=\"get\" action=\"/goldbach\">\n"
      << "    <label for=\"number\">Number</label>\n"
      << "    <input type=\"text\" name=\"number\" required/>\n"
      << "    <button type=\"submit\">Calculate</button>\n"
      << "  </form>\n"
      << "</html>\n";
    } else {
      // if option == 1 do
      if (option == 1) {
        // htmlResponse.body := set the HTML body to print
        // the results of cola
        httpResponse.body()
        << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
        << "  <h1>" << title << "</h1>\n"
        <<  mensaje(cola);
      } else {
        // htmlResponse.body := set the HTML body for a invalid request
        httpResponse.body()
        << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
        << "  <h1 class=\"err\">" << title << "</h1>\n"
        << "  <p>Invalid request for Goldbach</p>\n";
      }  // end else
      // set the end body of HTML file
      beginAndEndHtml(httpResponse, title, 0);
    }  // end else
  }
}  // end procedure

std::string GoldbachWebApp::decodeURI(
HttpRequest& httpRequest, std::regex& inQuery) {
  inQuery = "^/goldbach(/|\\?number=)(.*)$";
  std::string uri = httpRequest.getURI();
  // Se decodifican comas(%2C) o espacios (\\+)|(%20)
  std::regex decode("(%2C)|(\\+)|(%20)");
  return regex_replace(uri, decode, ",");
}

// procedure storageData(endIter, actualIter, cola):
int64_t GoldbachWebApp::storageData(
std::sregex_iterator end, std::sregex_iterator iter, cola_t* cola) {
  // declare num := 0
  int64_t num;
  std::stringstream log;
  // while endIter != actualIter do
  while (iter != end) {
    try {
      // num := get the number from actualIter
      num = std::stoll((*iter)[0].str());
      if (std::to_string(num).compare((*iter)[0].str()) != 0) {
        cola_add(cola , 0 , 0 , ' ' , 1 , (*iter)[0].str());

      } else {
        // if num < 0 do
        if (num < 0) {
          // add to cola num, has to show the sums
          char signo = ' ';
          if (num < 0) {
            num += num*-2;
            signo = '-';
          }
          cola_add(cola, num , 0 , signo , 0 , "nul");
        } else {
          // add to cola num, DON'T has to show the sums
          cola_add(cola , num , 0 , ' ' , 0 , "nul");
        }  // end else
      }
      log << "Match" << ": " << (*iter)[0].str();
      Log::append(Log::DEBUG, "goldbach", log.str());
      log.str("");
    } catch(...) {
      cola_add(cola , 0 , 0 , ' ' , 1 , (*iter)[0].str());
      log << "Match" << ": " << (*iter)[0].str();
      Log::append(Log::DEBUG, "goldbach", log.str());
    }
    //  actualIter := actualIter + 1
    ++iter;
  }  //  end while
  return num;
}  //  end procedure

void GoldbachWebApp::addToResults(std::ostringstream& resultado,
 nodo_t* nodo, int& i) {
  resultado << nodo->desglose[i];
  ++i;
  resultado <<'+';
  resultado << nodo->desglose[i];
}

// procedure serveHomepage(httpRequest, httpResponse):
bool GoldbachWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  setHeaderResponse(httpResponse);

  // Build the body of the response
  std::string title = "Goldbach Conjecture";

  // htmlResponse(httpResponse, "Goldbach Conjecture")
  htmlResponse(httpResponse, title, nullptr, 0);
  // return  send the httpRequest
  return httpResponse.send();
}  // end procedure

// procedure serveGoldbach(httpRequest, htmlResponse):
bool GoldbachWebApp::serveGoldbach(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  setHeaderResponse(httpResponse);

  // If a number was asked in the form "/fact/1223"
  // or "/fact?number=1223"
  // TODO(you): URI can be a multi-value list, e.g: 100,2784,-53,200771728
  // TODO(you): Use arbitrary precision for numbers larger than int64_t
  // TODO(you): Modularize this method
  // init cola
  cola_t* cola = cola_init();
  std::smatch matches;
  std::regex inQuery;
  std::string uri = decodeURI(httpRequest, inQuery);
  if (std::regex_search(uri, matches, inQuery)) {
    assert(matches.length() >= 3);
    const std::regex re("([0-z]+)|(-?\\d+)");
    // declare endIter := null
    std::sregex_iterator end;
    // declare actualIter := first position in URL
    std::sregex_iterator iter(uri.begin()+matches.position(2), uri.end(), re);
    // storageData(endIter, actualIter, cola);
    storageData(end, iter, cola);
    // Calculte Goldbach Conjecture to the number in cola
  
    nodo_t* nodo = cola->first;
   //  while nodo != null do
   while (nodo) {
    //  Inicializa el shared_data
    shared_data_t* shared_data =  new shared_data_t();
    shared_data->cola = cola;
    shared_data->nodo = nodo;
    this->produce(shared_data);
    //  nodo := nodo next
    nodo = nodo->next;
   }
  
    

    // TODO(you): Factorization must not be done by factorization threads
    // Build the body of the response

    std::string title = "Goldbach Conjecture of the input";
    // htmlResponse(httpResponse, title, cola, 1);
    htmlResponse(httpResponse, title, cola, 1);

  } else {
    // Build the body for an invalid request
    std::string title = "Invalid request";
    htmlResponse(httpResponse, title, nullptr, 2);
  }
  // destroy cola
  cola_destroy(cola);

  // Send the response to the client (user agent)
  // return send the httpResponse
  return httpResponse.send();
}  // end procedure

// procedure mensaje(cola):
std:: string GoldbachWebApp:: mensaje(cola_t* cola) {
  // declare result := ""
  std::ostringstream resultado;
  int64_t comparacion = 5;
  // declare nodo: first nodo of cola
  nodo_t* nodo = cola->first;

  // while nodo != null do
  while (nodo) {
    if (nodo->error == 0) {
    resultado << "  <h2>" << nodo_getSigno(nodo)
    << nodo_getNumber(nodo) << "</h2>\n";
    // if number of nodo < 5 do
    if ( nodo_getNumber(nodo)<= comparacion ) {
        // result := result + NA
        resultado << "  <p> NA</p>\n";
    } else {
         //  result := result + number of nodo + sums of nodo
       resultado << " " <<nodo_getSigno(nodo) << nodo_getNumber(nodo) << ": ";
        resultado << "Sumas: "<< nodo->sumas;

        // if number of nodo show sums == true do
        if (nodo->signo == '-') {
            // result := result + every sum of the number of nodo
            resultado << " : ";
            if (nodo-> number%2 == 0) {
                for (int i = 0; i< nodo->posicion ; i++) {
                  addToResults(resultado, nodo, i);

                if (i < nodo-> posicion-1) {
                       resultado <<", ";
                    }
                }
            } else {
                for (int i = 0; i < nodo-> posicion ; i++) {
                  addToResults(resultado, nodo, i);
                  ++i;
                  resultado <<'+';
                  resultado << nodo->desglose[i];
                  if (i < nodo-> posicion-1) {
                        resultado <<", ";
                    }
                }
            }
        }  // end if
    }  // end else
  } else {
          resultado << " <h2 class=\"err\">"
          << nodo->numeroErroneo << "</h2>\n";
          resultado <<  " <p> " << nodo->numeroErroneo
          << ": invalid number</p>\n";
  }
  printf("\n");
  // nodo := nodo next
  nodo = nodo->next;
  }  // end while

  return resultado.str();
}  // end procedure

bool GoldbachWebApp::serveNotFound(HttpRequest& httpRequest,
HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(404);
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Not found";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <p>El recurso pedido no fue encontrado en este server ratilla.</p>\n"
    << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}