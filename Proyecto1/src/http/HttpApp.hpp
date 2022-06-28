// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPAPP_H
#define HTTPAPP_H

#include <string>
#include <vector>
#include "common.hpp"
#include "Assembler.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "cola.hpp"

/**
  *@brief Base class for all web applications that can be registered with the
  web server.
  *@param keys vector de strings con todas las "direcciones" de la app
  como '/' y 'Goldbach'
*/

class HttpApp : public Assembler
<std::pair<HttpRequest*, HttpResponse*>, shared_data_t*>  {
  /// Web application objects are usually complex. This base class does not
  /// require child classes to allow copying
  DISABLE_COPY(HttpApp);

 public:
  /// Constructor
  HttpApp() = default;
  /// Destructor
  ~HttpApp() = default;

  std::vector<std::string> keys;

  /**
    * @brief Override de run del consumer de la clase Assembler
    y se encarga de consumir todos los pair de Request y Response que recibe
    * @return int 
    */
  int run() override;

  /**
    * @brief override del consume, llama al metodo handleHttpRequest para trabajar
    con la solicitudes
    * @param datos pair que contiene la solicitud con la que haremos goldbach
    */
  void consume(std::pair<HttpRequest*, HttpResponse*> datos) override;

  /// Called by the web server when the web server is started
  virtual void start();
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it
  virtual bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) = 0;
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  virtual void stop();
};

#endif  // HTTPAPP_H
