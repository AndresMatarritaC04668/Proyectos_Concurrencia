//  "Copyright [2022] <Equipo Dinamita>"
#include "distribuidor.hpp"

std::string distribuidor::extractKey(const std::pair<HttpRequest*, 
HttpResponse*> &solicitud) const{
    HttpRequest* request = std::get<0>(solicitud);
    std::string keySol = request->getURI();
    size_t pos = keySol.find_first_of('?',0);

    //  si se encontro la key
    if(pos < keySol.size()) {
        keySol = keySol.substr(0,pos);
    }

    return keySol;
}

int distribuidor::run() {
    this->consumeForever();
    return 0;
}