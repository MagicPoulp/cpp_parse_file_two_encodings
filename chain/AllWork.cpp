#include <vector>
#include <string>
#include <iostream>

#include "AllWork.hpp"
#include "MakeGlossaryChainHandler.hpp"

using namespace std;

void AllWork::processAll(ChainModel model) {
  MakeGlossaryChainHandler handler;
  handler.setModel(model);

  std::vector<std::string> food = {"Nut", "Banana"};
  for (const std::string &f : food) {
    const std::string result = handler.Handle(f);
    if (!result.empty()) {
      std::cout << "  " << result;
    } else {
      std::cout << "  " << f << " was left untouched.\n";
    }
  }
}
