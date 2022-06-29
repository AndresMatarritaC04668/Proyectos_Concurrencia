// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>
#include <utility>

#include "HttpApp.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"

// TODO(you): Implement connection handlers argument
const char* const usage =
  "Usage: webserv [port] [handlers]\n"
  "\n"
  "  port        Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  handlers     Number of connection handler theads\n";

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

HttpServer& HttpServer::getInstance() {
  static HttpServer server;
  return server;
}

void HttpServer::handleClientConnection(Socket& client) {
  // TODO(you): Make this method concurrent. Store client connections (sockets)
  // into a collection (e.g thread-safe queue) and stop
  // almacenamos el socket en la cola
  this->sockets_server.push(client);
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
  if(distriSolicitudes == nullptr){
    distriSolicitudes = new distribuidor(&colaDRequest);
  }
  // guardamos las solicitudes en el mapa del distribuidor
  for(size_t keyNum = 0; keyNum < application->keys.size(); keyNum++) {
    this->distriSolicitudes->registerRedirect
      (application->keys[keyNum],application->getConsumingQueue());
  }
}

int HttpServer::start(int argc, char* argv[]) {
  bool stopApps = false;
  //  por la convecion singleton
  HttpServer();
  try {
    if (this->analyzeArguments(argc, argv)) {
      // Start the log service
      Log::getInstance().start();

      // Start all web applications
      for (size_t index = 0; index < this->applications.size(); ++index) {
        this->applications[index]->start();
      }
      stopApps = true;

      // inicializamos el vector de Handlers del Server
      for (size_t in = 0; in < this->max_connections; in++) {
        HttpConnectionHandler* nuevo =
        new HttpConnectionHandler(&this->sockets_server , &colaDRequest);
        vHandler.push_back(nuevo);
        vHandler[in]->aplicaciones = this->applications;
        vHandler[in]->startThread();
      }

      distriSolicitudes->startThread();

      // Start waiting for connections
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver", "Listening on " + address.getIP()
        + " port " + std::to_string(address.getPort()));

      // Accept all client connections
      this->acceptAllConnections();
    }
  } catch (const std::runtime_error& error) {
    Log::append(Log::INFO, "Programa",
      std::string("no es posible aceptar mas conexiones de usuario"));
    std::cerr << "error: " << error.what() << std::endl;
  }

  //  se agregan los sockets vacios que marcan el final del server
  //  se utilizan para detener el consumo de estos y dar tiempo a cualquier
  //  operacion sin finalizar
  for (size_t u = 0; u < this->max_connections; u++) {
    this->sockets_server.push(Socket());
  }

  // agregamos a la colaDRequest lo necesario para finalizar su utilizacion
  this->colaDRequest.push(std::pair<HttpRequest*, HttpResponse*>());
  for (size_t in = 0; in < this->max_connections; in++) {
    vHandler[in]->waitToFinish();
    delete vHandler[in];
  }
  //  limpiamos la memoria utilizada en los vHandlers
  this->vHandler.clear();

  // If applications were started
  if (stopApps) {
    // Stop web applications. Give them an opportunity to clean up
    for (size_t index = 0; index < this->applications.size(); ++index) {
      this->applications[index]->stop();
    }
  }

  // Stop the log service
  Log::getInstance().stop();

  return EXIT_SUCCESS;
}

bool HttpServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 2) {
    this->port = argv[1];
    if (argc >= 3) {
      //  hacemos un atoi para pasar de char* a int
      //  y cambiar el maximo de clientes
      this->max_connections = atoi(argv[2]);
    }
  }

  return true;
}

void HttpServer::stop() {
  // Stop listening for incoming client connection requests
  //  adaptado para seguir el patron singleton
  HttpServer::getInstance().stopListening();
}
