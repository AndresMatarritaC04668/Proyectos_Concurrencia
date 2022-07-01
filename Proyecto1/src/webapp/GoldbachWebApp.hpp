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
  /// Handle a HTTP request that starts with "/fact"
  /// @return true if the factorization was handled, false if it must be
  /// handled by another application



  


  // METODOS QUE ESTAN EN DecodeURL

  /**
   * @brief Personal server of Goldbach Conjecture, it can calculate
   * the conjecture to the numbers sent in the input
   * 
   * @param httpRequest 
   * @param httpResponse 
   * @return true if the conjecure was handled, false if it must be 
   */
//  bool serveGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Fix code redundancy in the following methods

  /**
   * @brief It implements the body html depends on the 
   * option that was request
   * 
   * @param httpResponse is the http result that the user is waiting
   * @param title message to show in html file
   * @param cola is a conteiner with the numbers to work
   * @param option is a flag, to know which html use
   */
//  void htmlResponse(HttpResponse& httpResponse, std::string title,
//  cola_t* cola, int option);

  /**
   * @brief It has the begining of a html file and the end as well
   * depends on the opcion it choose the begining or the end part
   * 
   * 
   * @param httpResponse is the http result that the user is waiting
   * @param title message to show in html file
   * @param option is a flag, to know which html use
   */
 // void beginAndEndHtml(HttpResponse& httpResponse, std::string title,
 // int option);

  /**
   * @brief Set the Header Response object
   * 
   * @param httpResponse is the http result that the user is waiting
   */
 // void setHeaderResponse(HttpResponse& httpResponse);

  /**
   * @brief Clean the URL, delete the garbage and let only 
   * the useful parts to work 
   * 
   * @param httpRequest is the page asked
   * @param inQuery use to identify the wep app
   * @return string that it is the new URL 
   */
 // std::string decodeURI(HttpRequest& httpRequest, std::regex& inQuery);

  /**
   * @brief 
   * 
   * @param end this iterator has the value null, is the last one
   * @param iter this iterator is the first position
   * @param cola is a conteiner with the numbers to work
   * @return int64_t the last number inserted in the conteiner
   */
 // int64_t storageData(std::sregex_iterator end, std::sregex_iterator iter,
  // cola_t* cola);

  /**
    * @brief Sends a page for a non found resouce in this server. This method is called
     if none of the registered web applications handled the request.
    * @param httpRequest httpRequest con la peticion del usuario
    * @param httpResponse usado para avisar al usuario que la pagina no fue encontrada
    * @return el resultado de hacer send() del HttpResponse
    */
 // bool serveNotFound(HttpRequest& httpRequest,
  // HttpResponse& httpResponse);
  
};

#endif  // GoldbachWebApp_HPP
