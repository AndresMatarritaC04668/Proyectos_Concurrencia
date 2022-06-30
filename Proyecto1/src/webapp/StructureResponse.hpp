
#ifndef STRUCTURERESPONSE_HPP
#define STRUCTURERESPONSE_HPP

#include "HttpResponse.hpp"
#include <cstdint> 


/**
 * @brief Es el objeto productor del empaquetador, y el consumido
 *        por el despachador, en el se encuentra el httpResponse
 *        que es donde se ensambla el mensaje.
 */
struct StructureResponse{
 public:

  HttpResponse&  httpResponse;

 public:
  /// Convenience constructor
  /// @param httpResponse HttpResponse&
  explicit StructureResponse(HttpResponse& httpResponse)
    : httpResponse(httpResponse) {
  }
};

#endif  
