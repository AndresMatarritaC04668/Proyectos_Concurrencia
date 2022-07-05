//  Copyright 2022 Equipo Dinamita. UCR. CC BY 4.0
#include <string>
#include <utility>
#include "HttpConnectionHandler.hpp"

int HttpConnectionHandler::run() {
    //  se consumen los todos los datos
    this->consumeForever();
    return 0;
}

void HttpConnectionHandler::consume(Socket datos) {
    //  llamamos al metodo para procesar el socket
    this->procesarCliente(datos);
}

bool HttpConnectionHandler::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
    // Print IP and port from client
    const NetworkAddress& address = httpRequest.getNetworkAddress();
    Log::append(Log::INFO, "connection",
        std::string("connection established with client ") + address.getIP()
        + " port " + std::to_string(address.getPort()));
  // Print HTTP request
  Log::append(Log::INFO, "request", httpRequest.getMethod()
    + ' ' + httpRequest.getURI()
    + ' ' + httpRequest.getHttpVersion());

  std::pair<HttpRequest*, HttpResponse*> nuevaSolicitud;
  std::get<0>(nuevaSolicitud) = &httpRequest;
  std::get<1>(nuevaSolicitud) = &httpResponse;
  produce(nuevaSolicitud);
  return true;
}

void HttpConnectionHandler::procesarCliente(Socket cliente) {
  // este metodo fue movido para hacer que el server
  // trabaje de manera concurrente
  while (true) {
    // Create an object that parses the HTTP request from the socket
    HttpRequest *httpRequest = new HttpRequest(cliente);

    // If the request is not valid or an error happened
    if (!httpRequest->parse()) {
      delete httpRequest;
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse *httpResponse = new HttpResponse(cliente);

    // Give subclass a chance to respond the HTTP request
    const bool handled = handleHttpRequest(*httpRequest, *httpResponse);

    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest->getHttpVersion() == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      delete httpRequest;
      cliente.close();
      delete httpResponse;
      break;
    }
    //  eliminamos el break para que todas las solicitudes sean trabajadas
  }
}
