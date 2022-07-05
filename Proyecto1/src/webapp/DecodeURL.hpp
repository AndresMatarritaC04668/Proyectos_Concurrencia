//  "Copyright [2022] <Equipo Dinamita>"
#ifndef DECODEURL_HPP_
#define DECODEURL_HPP_

#include <string>
#include <utility>
#include <regex>
#include "HttpRequest.hpp"
#include "HttpApp.hpp"
#include "Assembler.hpp"
#include "Queue.hpp"
#include "cola.hpp"
#include "HttpResponse.hpp"

class DecodeURL : public Assembler<std::pair<HttpRequest*,
  HttpResponse*>, shared_data_t*> {
 public:
    /**
     * @brief Construye un nuevo objeto DecodeURL
     * 
     */
    DecodeURL(/* args */);

    /**
     * @brief metodo virtual que destruye el objeto DecodeURL
     * 
     */
    virtual ~DecodeURL() {}

    /**
     * @brief override del consume, se encarga de trabajar con
     * el request que pidio el cliente y el response que va a ser
     *
     * @param request pair que contiene puntero al request y al response
     */
    void consume(std::pair<HttpRequest*, HttpResponse*> request) override;

    /**
     * @brief Override de run del consumer de la clase Assembler
     * y se encarga de consumir para siempre hasta encontrar una condicion de 
     * parada
     * @return int que fue exitoso
     */
    int run() override;

    /**
     * @brief Se encargar de manejar el request por medio del analisis del
     * URL, si tiene que ir goldbach o a homepage, o incluso si no fue 
     * encontrado el request
     * 
     * @param httpRequest que pidio el usuario
     * @param httpResponse es el resultado que se le va a mostrar al ususario
     * @return true / false 
     */
    bool handle(HttpRequest& httpRequest, HttpResponse& httpResponse);

    /**
     * @brief Crea el cuerpo del html donde se va a mostrar al usuario
     * una caja de texto para que ingrese los numeros a calcular y un
     * boton para iniciar el calculo
     * 
     * @param httpRequest que pidio el usuario
     * @param httpResponse es el resultado que se le va a mostrar al ususario 
     * @return true / false 
     */
    bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);


    /**
     * @brief Se encarga de llamar metodos como el de almacenar
     *  los datos, inicializa la cola y el shared data
     * 
     * @param httpRequest que pidio el usuario
     * @param httpResponse es el resultado que se le va a mostrar al ususario 
     * @return true / false 
     */
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
