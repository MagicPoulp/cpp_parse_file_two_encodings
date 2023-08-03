#pragma once

#include "AbstractChainHandler.hpp"

class MakeGlossaryChainHandler : public AbstractChainHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "Banana") {
      return "Monkey: I'll eat the " + request + ".\n";
    } else {
      return AbstractChainHandler::Handle(request);
    }
  }
};
