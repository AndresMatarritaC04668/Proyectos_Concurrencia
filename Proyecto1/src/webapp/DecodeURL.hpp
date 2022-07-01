#ifndef DESEMPAQUETADOR_HPP_
#define DESEMPAQUETADOR_HPP_

#include "Queue.hpp"
#include "cola.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "HttpApp.hpp"
#include "Assembler.hpp"

class DecodeURL : public Assembler<std::pair<HttpRequest*,
  HttpResponse*>, shared_data_t*> {

  public:
    HttpApp* app;
/*
    //Cosntructor con argumentos
    explicit DecodeURL(Queue<std::pair<HttpRequest*,
    HttpResponse*>> *colaRequest, Queue<shared_data_t*> shared_data_t):
    Assembler<std::pair<HttpRequest*, HttpResponse*>, shared_data_t*>
    (colaRequest, shared_data) {}
*/

    DecodeURL();
    virtual ~DecodeURL() {}

    void consume(std::pair<HttpRequest*, HttpResponse*> request) override;

    int run() override;

    bool handle(HttpRequest& httpRequest, HttpResponse& httpResponse);

    bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

    bool serveDecodeURL(HttpRequest& httpRequest, HttpResponse& httpResponse);



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
  std::string workingURL(HttpRequest& httpRequest, std::regex& inQuery);

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
    * @brief Sends a page for a non found resouce in this server. This method is called
     if none of the registered web applications handled the request.
    * @param httpRequest httpRequest con la peticion del usuario
    * @param httpResponse usado para avisar al usuario que la pagina no fue encontrada
    * @return el resultado de hacer send() del HttpResponse
    */
  bool serveNotFound(HttpRequest& httpRequest,
  HttpResponse& httpResponse);


};

#endif  // DESEMPAQUETADOR_HPP__