//  Copyright 2022 Equipo Dinamita. UCR. CC BY 4.0
#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP

#include <vector>
#include <utility>
#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "Socket.hpp"
#include "Log.hpp"
#include "Queue.hpp"
#include "NetworkAddress.hpp"

//  por inclusion cruzada
class HttpServer;

/*  se eligio la clase assembler por suplir el rol de trabajador
de la linea de asamblaje, siendo productor y consumidor al mismo tiempo */
/**
 * @brief constructor de la clase HttpConnectionHandler
 * @param colaDSockets cola donde se almacenan los sockets del server y la cola donde se consumen
 * @param colaDRequest cola donde se almacenan el request y response de cada solicitud, es donde se producen
 * @param aplicaciones vector que contiene las aplicaciones de cada Handler, 
  siendo las mismas que las dispuestas por el servidor
 */
class HttpConnectionHandler : public Assembler
<Socket, std::pair<HttpRequest*, HttpResponse*>> {
 public:
    std::vector<HttpApp*> aplicaciones;
    explicit HttpConnectionHandler(Queue<Socket>* colaDSockets,
      Queue<std::pair<HttpRequest*,
      HttpResponse*>>* colaDRequest):
      Assembler<Socket, std::pair<HttpRequest*, HttpResponse*>>(colaDSockets,
       colaDRequest) {}
    // el constructor toma una forma similar al constructor del Assembler

    //  destructor de la clase
    virtual ~HttpConnectionHandler() {}

    /**
     * @brief Override de run del consumer de la clase Assembler
     y se encarga de consumir los sockets que tiene
     * @return int 
     */
    int run() override;

    /**
     * @brief override del consume, permite analizar los datos
     del sockets de un cliente.
     * @param datos socket del cliente a procesar
     */
    void consume(Socket datos) override;

    //  los siguientes metodos fueron sacados del HTTP server
    //  para lograr la paralelizacion

    /**
     * @brief procesa las peticiones realizadas por un cliente 
     * @param usuario socket donde se encuentra la informacion del cliente
     */
    void procesarCliente(Socket usuario);

    /**
     * @brief Called each time an HTTP request is received. Web server should analyze
      the request object and assemble a response with the response object.
      Finally send the response calling the httpResponse.send() method.
     * 
     * @param httpRequest httpRequest con la peticion del usuario
     * @param httpResponse httpResponse utilizado para la respuesta
     * @return true on success and the server will continue handling further
     */
    bool handleHttpRequest(HttpRequest& httpRequest,
      HttpResponse& httpResponse);

    /**
     * @brief Route, that provide an answer according to the URI value
      For example, home page is handled different than a number
     * 
     * @param httpRequest httpRequest con la peticion del usuario
     * @param httpResponse httpResponse utilizado para la respuesta
     * @return true si logra encontrar la app a redireccionar
     */
    bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
};
#endif
