// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include "HttpApp.hpp"

void HttpApp::start() {
  // Default base class implementation does nothing
}

void HttpApp::stop() {
  // Default base class implementation does nothing
}

int HttpApp::run() {
  this->consumeForever();
  return 0;
}

void HttpApp::consume(std::pair<HttpRequest*, HttpResponse*> datos) {
  this->handleHttpRequest(*std::get<0>(datos),*std::get<1>(datos));
}
