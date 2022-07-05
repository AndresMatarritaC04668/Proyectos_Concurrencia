
// Copyright Equipo Dinamita. Universidad de Costa Rica. CC BY 4.0
#ifndef STRUCTURERESPONSE_HPP
#define STRUCTURERESPONSE_HPP
#include <cstdint>
#include "HttpResponse.hpp"
/**
 * @brief Es el objeto productor del empaquetador, y el consumido
 *        por el despachador, en el se encuentra el httpResponse
 *        que es donde se ensambla el mensaje.
 */
struct StructureResponse{
 public:
  HttpResponse&  httpResponse;
  /// Convenience constructor
  /// @param httpResponse HttpResponse&
  explicit StructureResponse(HttpResponse& httpResponse)
    : httpResponse(httpResponse) {
  }

  /// Convenience destrutuc
  /// @param httpResponse HttpResponse&
  ~StructureResponse() {
  }
};

#endif  // STRUCTURERESPONSE_HPP
