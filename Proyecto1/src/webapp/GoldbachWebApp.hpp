// Copyright Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0
#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP
#include <string>
#include "HttpApp.hpp"
#include "cola.hpp"
#include "nodo.hpp"
#include "regex"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "DecodeURL.hpp"

class SumGoldbachSolver;
class Empaquetador;
class Despachador;
class DecodeURL;
/**
* @brief A web application that calculates
* the Goldbach Conjecture
*
*/
class GoldbachWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachWebApp);

 public:
  /// Constructor
  /**
   * @brief Constructor of class GoldbachWebApp
   * 
   */
  GoldbachWebApp();

  /// Destructor
  /**
   * @brief Destructor of class GoldbachWebApp
   * 
   */
  ~GoldbachWebApp();

  /**
   * @brief Called by the web server when the web server is started
   * 
   */
  void start() override;

  /**
   * @brief chained application that should handle it
   * 
   * @param httpRequest has URL of the page asked
   * @param httpResponse has the result of the page request
   * @return true If this application handled the request, false otherwise
   */
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;

  
  /**
   * @brief Called when the web server stops, in order to allow the web application
   * clean up and finish as well 
   * 
   */
  void stop() override;
    
    /**
   * @brief Empaquetador, se encarga de verificar que la solicitud ya haya sido
   * completamente procesada, por lo que verifica que las sumas de goldbach
   * ya este listas.
  */
   Empaquetador * empaquetador;

   /**
   * @brief Despachador, se encarga de ensamblar el mensaje e imprimirselo
   * al usuario.
  */
  Despachador* despachador;

  DecodeURL* decodeURL;

    /**
   * @brief Called when the web server stops, in order to allow the web application
   *        clean up and finish as well
   * @return void
   * @param pair<HttpRequest*, HttpResponse*>
   * @return void
  */
  std::vector<SumGoldbachSolver*> goldbachThreads;
  Queue<shared_data_t*> empaquetadorProduct;
  Queue<shared_data_t*> solversProduct;
  Queue<shared_data_t*> urlProduct;

 protected:
  /**
   * @brief Sends the homepage as HTTP response 
   * 
   * @param httpRequest has URL of the page asked
   * @param httpResponse has the result of the page request
   * @return true If this application handled the request, false otherwise
   */
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

 

};

#endif  // GoldbachWebApp_HPP
