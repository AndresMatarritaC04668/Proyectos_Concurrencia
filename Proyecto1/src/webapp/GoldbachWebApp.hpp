// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include "HttpApp.hpp"
#include "SumGoldbachSolver.hpp"
#include "cola.hpp"
#include "nodo.hpp"
#include <regex>

/**
@brief A web application that calculates prime factors
*/
class GoldbachWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachWebApp);

 public:
 
  /// Constructor
  GoldbachWebApp();
  /// Destructor
  ~GoldbachWebApp();
  /// Called by the web server when the web server is started
  void start() override;
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;
  std:: string mensaje(cola_t* cola);
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  void stop() override;


 protected:
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Handle a HTTP request that starts with "/fact"
  /// @return true if the factorization was handled, false if it must be
  /// handled by another application
  bool serveGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /// Fix code redundancy in the following methods
  void htmlResponse(HttpResponse& httpResponse, std::string title, cola_t* cola, int option);
  void beginAndEndHtml(HttpResponse& httpResponse, std::string title, int option);
  void setHeaderResponse(HttpResponse& httpResponse);
  std::string decodeURI(HttpRequest& httpRequest, std::regex& inQuery);
  int64_t storageData(std::sregex_iterator end, std::sregex_iterator iter, cola_t* cola);
  void addToResults(std::ostringstream& resultado, nodo_t* nodo, int& i);
};

#endif  // GoldbachWebApp_HPP
