//  "Copyright [2022] <Equipo Dinamita>"

#ifndef DISTRIBUIDOR_H
#define DISTRIBUIDOR_H

#include <string.h>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Dispatcher.hpp"
#include "HttpApp.hpp"
#include "Log.hpp"

/**
 * @brief clase que distribuye las solicitudes a la correspondiente WebApp
 * @param aplicaciones vector de referencias a las aplicaciones del Server
 */
class distribuidor : public Dispatcher<std::string, 
std::pair<HttpRequest*, HttpResponse*>> {
    public:
        /**
         * @brief Construct a new distribuidor object con argumento
         * 
         * @param queueAConsumir la cola donde son extraidas las solicitudes 
           que entran a las aplicaciones
         */
        explicit distribuidor(Queue<std::pair<HttpRequest*, 
            HttpResponse*>> *queueAConsumir): Dispatcher<std::string, 
            std::pair<HttpRequest*, HttpResponse*>>(queueAConsumir) {}

        /**
         * @brief Destroy the distribuidor object
         * 
         */
        virtual ~distribuidor() {}

        /**
         * @brief override del extractKey de dispatcher, saca la key
           del Request contenida en el mapa del dispatcher
         * 
         * @param solicitud entrada de datos del usuario a la cual se le saca la key
         * @return std::string retorna la key de la solicitud
         */
        std::string extractKey(const std::pair<HttpRequest*, 
            HttpResponse*> &solicitud) const override;

        /**
         * @brief llama al consume contenido en el dispatcher
         * 
         * @return int retorna 0
         */
        int run() override;

};

#endif