// Copyright 2022 Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <Log.hpp>

#include "GoldbachWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

GoldbachWebApp::GoldbachWebApp() {
}

GoldbachWebApp::~GoldbachWebApp() {
}

void GoldbachWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
}

void GoldbachWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}

bool GoldbachWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }

  // If the request starts with "fact/" is for this web app
  if (httpRequest.getURI().rfind("/goldbach", 0) == 0) {
    return this->serveGoldbach(httpRequest, httpResponse);
  }

  // Unrecognized request
  return false;
}

// TODO(you): Fix code redundancy in the following methods
void GoldbachWebApp::setHeaderResponse(HttpResponse& httpResponse) {
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");
}

void GoldbachWebApp:: beginAndEndHtml(HttpResponse& httpResponse, std::string title, int end) {
  if (!end) {
    httpResponse.body() << "<!DOCTYPE html>\n"
        << "<html lang=\"en\">\n"
        << "  <title>" << title << "</title>\n";
  } else {
     httpResponse.body() 
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  }
}

void GoldbachWebApp::htmlResponse(HttpResponse& httpResponse, std::string title, cola_t* cola, int option) {
  if (option >= 0 && option <= 2) {
    beginAndEndHtml(httpResponse, title, 1);
    if (!option) {
      httpResponse.body() << "  <style>body {font-family: monospace}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <form method=\"get\" action=\"/goldbach\">\n"
      << "    <label for=\"number\">Number</label>\n"
      << "    <input type=\"text\" name=\"number\" required/>\n"
      << "    <button type=\"submit\">Calculate</button>\n"
      << "  </form>\n"
      << "</html>\n";
    } else {
      if (option == 1) {
        httpResponse.body()
        << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
        << "  <h1>" << title << "</h1>\n"
        <<  mensaje(cola);
      } else {
        httpResponse.body()
        << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
        << "  <h1 class=\"err\">" << title << "</h1>\n"
        << "  <p>Invalid request for Goldbach</p>\n";
      }
        beginAndEndHtml(httpResponse, title, 0);
    }
  }
}

std::string GoldbachWebApp::decodeURI(HttpRequest& httpRequest, std::regex& inQuery) {
  inQuery = "^/goldbach(/|\\?number=)(.*)$";
  std::string uri = httpRequest.getURI();
   // Se decodifican comas(%2C) o espacios (\\+)|(%20)
  std::regex decode("(%2C)|(\\+)|(%20)");
  return regex_replace(uri, decode, ",");
}

int64_t GoldbachWebApp::storageData(std::sregex_iterator end, std::sregex_iterator iter, cola_t* cola) {
  int64_t num;
  std::stringstream log;
  while (iter != end) {    
    try {
      num = std::stoll((*iter)[0].str());
      if (std::to_string(num).compare((*iter)[0].str()) != 0) {
        cola_add(cola , 0 , 0 , ' ' , 1 , (*iter)[0].str());
      
      } else {
        if (num < 0) {
          char signo = ' ';
          if (num < 0) {
            num += num*-2;
            signo = '-';
          }
          cola_add(cola, num , 0 , signo , 0 , " ");
      
        } else {
            cola_add(cola , num , 0 , ' ' , 0 , " ");
        } 
      }
      log << "Match" << ": " << (*iter)[0].str();
      Log::append(Log::DEBUG, "goldbach", log.str());
      log.str("");
    } catch(...) {
      
      cola_add(cola , 0 , 0 , ' ' , 1 , (*iter)[0].str());
      log << "Match" << ": " << (*iter)[0].str();
      Log::append(Log::DEBUG, "goldbach", log.str());
    }
    ++iter;
  }
  return num;
}

void GoldbachWebApp::addToResults(std::ostringstream& resultado, nodo_t* nodo, int& i) {
  resultado << nodo->desglose[i];
  ++i;
  resultado <<'+';
  resultado << nodo->desglose[i];
}

bool GoldbachWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  setHeaderResponse(httpResponse);

  // Build the body of the response
  std::string title = "Goldbach Conjecture";

  htmlResponse(httpResponse, title, nullptr, 0);
  return httpResponse.send();
}

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
  cola_t* cola = cola_init();
  std::smatch matches;
  std::regex inQuery;
  std::string uri = decodeURI(httpRequest, inQuery);
  if (std::regex_search(uri, matches, inQuery)) {
    assert(matches.length() >= 3);
    const std::regex re("([0-z]+)|(-?\\d+)");
    std::sregex_iterator end;
    std::sregex_iterator iter(uri.begin()+matches.position(2), uri.end(), re);
    
    storageData(end, iter, cola);
    goldBach(cola);
    
    // TODO(you): Factorization must not be done by factorization threads
    // Build the body of the response
    
    std::string title = "Goldbach Conjecture of the input";
    htmlResponse(httpResponse, title, cola, 1);

  } else {
    // Build the body for an invalid request
    std::string title = "Invalid request";
    htmlResponse(httpResponse, title, nullptr, 2);
  }
  cola_destroy(cola);

  // Send the response to the client (user agent)
  return httpResponse.send();
}

std:: string GoldbachWebApp:: mensaje(cola_t* cola){
  std::ostringstream resultado;

  int64_t comparacion = 5;
    
  nodo_t* nodo = cola->first;

 
  while (nodo) {
   if(nodo->error == 0){
    resultado << "  <h2>" << nodo_getSigno(nodo) << nodo_getNumber(nodo) << "</h2>\n";
    if ( nodo_getNumber(nodo)<= comparacion ) {
        //  Imprime "NA" si es menor que 5;
        resultado << "  <p> NA</p>\n";
    } else {
         //  Imprime Informacion;
       resultado << " " <<nodo_getSigno(nodo) << nodo_getNumber(nodo) << ": ";
        resultado << "Sumas: "<< nodo->sumas; 

        if (nodo->signo == '-') {
            //  Imprime desglose si es negativo;
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
        }
    }
  
   }else{
          resultado << " <h2 class=\"err\">" << nodo->numeroErroneo << "</h2>\n";
          resultado <<  " <p> " << nodo->numeroErroneo << ": invalid number</p>\n";
   }
   printf("\n");
   nodo = nodo->next;
  }

  return resultado.str();
}
