// Copyright Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0
#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP
#include <string>
#include <vector>
#include "HttpApp.hpp"
#include "cola.hpp"
#include "regex"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "SumGoldbachSolver.hpp"
#include "Empaquetador.hpp"
#include "Despachador.hpp"
#include "DecodeURL.hpp"

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
  std::vector<SumGoldbachSolver*> goldbachThreads; /**< vector con sumas */
  Queue<cola_t*> empaquetadorProduct; /**< Productos del empaquetador */
  Queue<shared_data_t*> solversProduct; /**< Productos del solver */
  Queue<shared_data_t*> urlProduct; /**< Productos del url */
};
#endif  // GoldbachWebApp_HPP
