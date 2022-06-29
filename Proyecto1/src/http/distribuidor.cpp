//  "Copyright [2022] <Equipo Dinamita>"
#include "distribuidor.hpp"

std::string distribuidor::extractKey(const std::pair<HttpRequest*,
HttpResponse*> &solicitud) const {
  //  Extraemos el uri del request
  HttpRequest* request = std::get<0>(solicitud);
  std::string keySol = request->getURI();

  // revisamos si la solicitud es de tipo /Goldbach
  size_t pos = keySol.find_first_of('?', 0);
  if (pos < keySol.size()) {
    //  si lo es sacamos /goldbach de todo el uri
    keySol = keySol.substr(0, pos);
  }

  bool keyRegistrada = false;
  Log::getInstance().append(Log::INFO, "Repartidor", "Request for "+ keySol);
  for (size_t index = 0; index <
  this->keysDis.size(); ++index) {
    // If this application handles the request
    if (request->getMethod() == "GET" &&
    keySol.compare(keysDis[index]) == 0)
      keyRegistrada = true;
  }
  if (!keyRegistrada) {
    keySol = "/noEncontrada";
  }
  return keySol;
}


int distribuidor::run() {
    this->consumeForever();
    return EXIT_SUCCESS;
}