#include <vector>
#include <string>
#include <iostream>

#include "AllWork.hpp"
#include "MakeGlossaryChainHandler.hpp"
#include "SortGlossaryChainHandler.hpp"
#include "CustomExceptions.hpp"

using namespace std;

void AllWork::processAll(ChainModel& model) {
  MakeGlossaryChainHandler handler1;
  handler1.setModel(model);
  SortGlossaryChainHandler handler2;
  handler2.setModel(model);
  handler1.setNext(&handler2);

  vector<string> steps = {"make_glossary", "sort_glossary"};
  for (const std::string &step : steps) {
    cout << "step started: " << step << endl;
    const std::string result = handler1.handle(step);
    if (!result.empty()) {
      cout << "step done: " << step << endl;
    } else {
      DetailedErrorCustomException ex("Processing step " + step + " was not run as expected");
      throw ex;
    }
  }
}
