// Copyright Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0
#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP
#include <string>
#include "HttpApp.hpp"
#include "SumGoldbachSolver.hpp"
#include "cola.hpp"
#include "nodo.hpp"
#include "regex"

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
   * @brief add in a string the results of the goldbach conjectures
   *  if the number has to show sums it adds the sums if not, only the
   *  amount of sums
   * 
   * @param cola is the conteiner with the numbers
   * @return string that has the final message for the user
   */
  std::string mensaje(cola_t* cola);

  /**
   * @brief Called when the web server stops, in order to allow the web application
   * clean up and finish as well 
   * 
   */
  void stop() override;


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

  /**
   * @brief Personal server of Goldbach Conjecture, it can calculate
   * the conjecture to the numbers sent in the input
   * 
   * @param httpRequest 
   * @param httpResponse 
   * @return true if the conjecure was handled, false if it must be 
   */
  bool serveGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse);

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
  void htmlResponse(HttpResponse& httpResponse, std::string title,
  cola_t* cola, int option);

  /**
   * @brief It has the begining of a html file and the end as well
   * depends on the opcion it choose the begining or the end part
   * 
   * 
   * @param httpResponse is the http result that the user is waiting
   * @param title message to show in html file
   * @param option is a flag, to know which html use
   */
  void beginAndEndHtml(HttpResponse& httpResponse, std::string title,
  int option);

  /**
   * @brief Set the Header Response object
   * 
   * @param httpResponse is the http result that the user is waiting
   */
  void setHeaderResponse(HttpResponse& httpResponse);

  /**
   * @brief Clean the URL, delete the garbage and let only 
   * the useful parts to work 
   * 
   * @param httpRequest is the page asked
   * @param inQuery use to identify the wep app
   * @return string that it is the new URL 
   */
  std::string decodeURI(HttpRequest& httpRequest, std::regex& inQuery);

  /**
   * @brief 
   * 
   * @param end this iterator has the value null, is the last one
   * @param iter this iterator is the first position
   * @param cola is a conteiner with the numbers to work
   * @return int64_t the last number inserted in the conteiner
   */
  int64_t storageData(std::sregex_iterator end, std::sregex_iterator iter,
   cola_t* cola);

  /**
   * @brief 
   * 
   * 
   * @param resultado is the final message to show to the user
   * @param nodo is the current working nodo
   * @param i is the index use in nodo->desglose to know with what number work
   */
  void addToResults(std::ostringstream& resultado, nodo_t* nodo, int& i);
};

#endif  // GoldbachWebApp_HPP
