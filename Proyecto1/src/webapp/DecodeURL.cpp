//  "Copyright [2022] <Equipo Dinamita>"
#include "DecodeURL.hpp"
#include <unistd.h>
#include <regex>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility>
#include <Log.hpp>


DecodeURL::DecodeURL() {}

bool DecodeURL::serveDecodeURL(HttpRequest& httpRequest,
  HttpResponse& httpResponse) {
  (void)httpRequest;

    // Set HTTP response metadata (headers)
    setHeaderResponse(httpResponse);

    // init cola
    std::smatch matches;
    std::regex inQuery;
    std::string uri = workingURL(httpRequest, inQuery);
    if (std::regex_search(uri, matches, inQuery)) {
      assert(matches.length() >= 3);
      cola_t* cola = cola_init();
      StructureResponse * structureResponse = new
        StructureResponse(httpResponse);
      cola->structureResponse = structureResponse;
      pthread_mutex_t  can_access;
      pthread_mutex_init(&can_access , NULL);

      const std::regex re("([0-z]+)|(-?\\d+)");
      // declare endIter := null
      std::sregex_iterator end;
      // declare actualIter := first position in URL
      std::sregex_iterator iter(uri.begin()+matches.position(2), uri.end(), re);
      // storageData(endIter, actualIter, cola);
      storageData(end, iter, cola);

      nodo original;

      int contador = cola->cantidadNumeros;
      int i = 0;
      //  while nodo != null do
      while (i < contador) {
        //  Inicializa el shared_data
        nodo_t* nodo = &original;
        nodo = cola_getNodo(cola, i);
        shared_data_t* shared_data = new shared_data_t();
        shared_data->cola = cola;
        shared_data->nodo = nodo;
        shared_data->can_access = can_access;
        this->produce(shared_data);
        //  nodo := nodo next
        i++;
      }
    } else {
      // Build the body for an invalid request
      std::string title = "Invalid request";
      htmlResponse(httpResponse, title, nullptr, 2);
      return 0;
    }
    return 1;
}

void DecodeURL::consume(std::pair<HttpRequest*, HttpResponse*> request) {
    // Este es el entero que se le pasa al metodo factorizar.
    Log::getInstance().append(Log::INFO, "goldbach/DecodeURL",
    "Decode solicitud");
    handle(*std::get<0>(request), *std::get<1>(request));
}


int DecodeURL::run() {
    this->consumeForever();
    return EXIT_SUCCESS;
}

bool DecodeURL::handle(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the request starts with "fact/" is for this web app
  if (httpRequest.getMethod() == "GET"
  && httpRequest.getURI().rfind("/goldbach", 0) == 0) {
    return this->serveDecodeURL(httpRequest, httpResponse);
  }

  // If the home page was asked
  if (httpRequest.getMethod() == "GET"
  && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }

  // Unrecognized request
  return this->serveNotFound(httpRequest, httpResponse);
}

bool DecodeURL::serveHomepage(HttpRequest& httpRequest
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


void DecodeURL::setHeaderResponse(HttpResponse& httpResponse) {
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");
}

void DecodeURL::beginAndEndHtml(
HttpResponse& httpResponse, std::string title, int end) {
  if (!end) {
    // Start part of a HTML file
    httpResponse.body() << "<!DOCTYPE html>\n"
        << "<html lang=\"en\">\n"
      << "  <title>" << title << "</title>\n";
  }
}

void DecodeURL::htmlResponse(
  HttpResponse& httpResponse , std::string title , cola_t* cola, int option) {
  (void) cola;
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
        << "  <h1>" << title << "</h1>\n";
      }
      // set the end body of HTML file
      beginAndEndHtml(httpResponse, title, 0);
    }  // end else
  }
}  // end procedure

std::string DecodeURL::workingURL(
HttpRequest& httpRequest, std::regex& inQuery) {
  inQuery = "^/goldbach(/|\\?number=)(.*)$";
  std::string uri = httpRequest.getURI();
  // Se decodifican comas(%2C) o espacios (\\+)|(%20)
  std::regex decode("(%2C)|(\\+)|(%20)");
  return regex_replace(uri, decode, ",");
}

int64_t DecodeURL::storageData(
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

bool DecodeURL::serveNotFound(HttpRequest& httpRequest,
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

