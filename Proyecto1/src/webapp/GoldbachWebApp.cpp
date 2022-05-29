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

bool GoldbachWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");
  
  // Build the body of the response
  std::string title = "Goldbach Conjecture";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/goldbach\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"text\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Calculate</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool GoldbachWebApp::serveGoldbach(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // If a number was asked in the form "/fact/1223"
  // or "/fact?number=1223"
  // TODO(you): URI can be a multi-value list, e.g: 100,2784,-53,200771728
  // TODO(you): Use arbitrary precision for numbers larger than int64_t
  // TODO(you): Modularize this method
  cola_t* cola = cola_init();
  std::smatch matches;
  std::regex inQuery("^/goldbach(/|\\?number=)(.*)$");
  std::string uri = httpRequest.getURI();
   // Se decodifican comas(%2C) o espacios (\\+)|(%20)
  std::regex decode("(%2C)|(\\+)|(%20)");
  uri = regex_replace(uri, decode, ",");
  if (std::regex_search(uri, matches, inQuery)) {
    assert(matches.length() >= 3);
    const std::regex re("([0-z]+)|(-?\\d+)");
    std::sregex_iterator end;
    std::sregex_iterator iter(uri.begin()+matches.position(2), uri.end(), re);
    int64_t num;

    std::stringstream log;
    while (iter != end) {
      try {
        num = std::stoll((*iter)[0].str());
        if (std::to_string(num).compare((*iter)[0].str()) != 0) {
        
        } else {
          if (num < 0) {
            char signo =' ';
            if (num < 0) {
              num += num*-2;
              signo = '-';
            }
            cola_add(cola,num,0,signo);
       
          } else {
             cola_add(cola,num,0,' ');
          } 
        }
        log << "Match" << ": " << (*iter)[0].str();
        Log::append(Log::DEBUG, "goldbach", log.str());
        log.str("");
      } catch(...) {
       
      }
      ++iter;
    }
    goldBach(cola);
    

    // TODO(you): Factorization must not be done by factorization threads
    // Build the body of the response
    
     std::string title = "Goldbach Conjecture of " + std::to_string(num);
     httpResponse.body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      <<  mensaje(cola)
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";

  } else {
    // Build the body for an invalid request
    std::string title = "Invalid request";
    httpResponse.body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << "  <h1 class=\"err\">" << title << "</h1>\n"
      << "  <p>Invalid request for Goldbach</p>\n"
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  }

  // Send the response to the client (user agent)
  return httpResponse.send();
}

std:: string GoldbachWebApp:: mensaje(cola_t* cola){
  std::ostringstream resultado;

  int64_t comparacion = 5;
    
  nodo_t* nodo = cola->first;

 
  while (nodo) {
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
                    resultado << nodo->desglose[i];
                    ++i;
                    resultado <<'+';
                    resultado << nodo->desglose[i];

                if (i < nodo-> posicion-1) {
                       resultado <<", ";
                    }
                }
            } else {
                for (int i = 0; i < nodo-> posicion ; i++) {
                  resultado << nodo->desglose[i];
                  ++i;
                  resultado <<'+';
                  resultado << nodo->desglose[i];
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
    printf("\n");
    nodo = nodo->next;
  }

  return resultado.str();
}
