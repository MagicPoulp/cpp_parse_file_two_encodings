#pragma once

#include <string>

#include "AbstractChainHandler.hpp"
#include "FileManager.hpp"
#include "LambdaUtilities.hpp"

using namespace std;

class MakeGlossaryChainHandler : public AbstractChainHandler {
public:
  std::string Handle(std::string request) override {
    FileManager fm;
    auto lambda = [](string line) {
      cout << line << endl;
    };
    auto funcLambda = LambdaUtilities::to_function(lambda);
    fm.processFileByLine(model.inputFile, funcLambda);
    if (request == "Banana") {
      return "Monkey: I'll eat the " + request + ".\n";
    } else {
      return AbstractChainHandler::Handle(request);
    }
  }
};
