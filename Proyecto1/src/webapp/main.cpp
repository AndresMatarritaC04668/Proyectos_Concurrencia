// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

#ifdef WEBSERVER
#include <csignal>
#include "HttpServer.hpp"
#include "FactWebApp.hpp"
#include "GoldbachWebApp.hpp"

void signalHandler(int signal) {
  //  el int signal se queda sin usar aproposito
  //  para evitar problemas con el helgrind
  //  llamamos a la funcion stop del HttpServer
  (void) signal;
  printf("\n");
  HttpServer::getInstance().stop();
}

/// Start the web server
int main(int argc, char* argv[]) {
  signal(SIGINT , signalHandler);
  signal(SIGTERM, signalHandler);
  // Create the web server
  HttpServer& httpServer = HttpServer::getInstance();
  // Create a factorization web application, and other apps if you want
  // FactWebApp factWebApp;
  GoldbachWebApp goldbachWebApp;
  // Register the web application(s) with the web server
  // httpServer.chainWebApp(&factWebApp);
  httpServer.chainWebApp(&goldbachWebApp);
  // Start the web server
  return httpServer.start(argc, argv);
}

#endif  // WEBSERVER
