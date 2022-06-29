//  "Copyright [2022] <Equipo Dinamita>"
#include "distribuidor.hpp"

using std::string;

string distribuidor::extractKey(const std::pair<HttpRequest*,
HttpResponse*> &solicitud) const {
  HttpRequest* request = std::get<0>(solicitud);
  string keySol = request->getURI();
  std::cout<<"iden: "<<request->identificador<<"\n";

  Log::getInstance().append(Log::INFO, "Distribuidor", "Solicitud para "+ keySol);
  return keySol;
}


int distribuidor::run() {
    this->consumeForever();
    return EXIT_SUCCESS;
}