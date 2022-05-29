//  Copyright 2022 Equipo Dinamita. UCR. CC BY 4.0
#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP

#include <vector>
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
class HttpConnectionHandler : public Assembler<Socket, std::pair<HttpRequest*, HttpResponse*>> {
  public:
    std::vector<HttpApp*> aplicaciones;
    //  constructor de la clase
    //  colaDSockets cola donde se almacenan los sockets del server
    //  colaDRequest cola donde se almacenan los valores de cada solicitud
    explicit HttpConnectionHandler(Queue<Socket>* colaDSockets, 
      Queue<std::pair<HttpRequest*, HttpResponse*>>* colaDRequest):
      Assembler<Socket, std::pair<HttpRequest*, HttpResponse*>>(colaDSockets, colaDRequest){};
    // el constructor toma una forma similar al constructor del Assembler

    //  destructor de la clase
    virtual ~HttpConnectionHandler (){};

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

    //  los siguientes metodos fueron sacados del HTTP server para lograr la paralelizacion

    /**
     * @brief procesa las peticiones realizadas por un cliente 
     * @param usuario socket donde se encuentra la informacion del cliente
     */
    void procesarCliente(Socket usuario);

    /// Called each time an HTTP request is received. Web server should analyze
    /// the request object and assemble a response with the response object.
    /// Finally send the response calling the httpResponse.send() method.
    /// @return true on success and the server will continue handling further
    /// HTTP requests, or false if server should stop accepting requests from
    /// this client (e.g: HTTP/1.0)
    bool handleHttpRequest(HttpRequest& httpRequest,
      HttpResponse& httpResponse);

    /// Route, that provide an answer according to the URI value
    /// For example, home page is handled different than a number
    bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);

    /// Sends a page for a non found resouce in this server. This method is called
    /// if none of the registered web applications handled the request.
    /// If you want to override this method, create a web app, e.g NotFoundWebApp
    /// that reacts to all URIs, and chain it as the last web app
    bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);
};
#endif
