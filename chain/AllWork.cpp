#include <vector>
#include <string>
#include <iostream>

#include "AllWork.hpp"
#include "MakeGlossaryChainHandler.hpp"
#include "SortGlossaryChainHandler.hpp"
#include "SaveSortedGlossaryChainHandler.hpp"
#include "SaveReversedChainHandler.hpp"
#include "CustomExceptions.hpp"

using namespace std;

void AllWork::processAll(ChainModel& model) {
  MakeGlossaryChainHandler handler1;
  handler1.setModel(model);
  SortGlossaryChainHandler handler2;
  handler2.setModel(model);
  handler1.setNext(&handler2);
  SaveSortedGlossaryChainHandler handler3;
  handler3.setModel(model);
  handler2.setNext(&handler3);
  SaveReversedChainHandler handler4;
  handler4.setModel(model);
  handler3.setNext(&handler4);

  vector<string> steps = {
    "make_glossary",
    "sort_glossary",
    "save_sorted_glossary_to_file",
    "save_reversed_to_file",
  };
  for (const std::string &step : steps) {
    cout << "step started: " << step;
    const std::string result = handler1.handle(step);
    if (!result.empty()) {
      cout << "...done" << endl;
    } else {
      DetailedErrorCustomException ex("Processing step " + step + " was not run as expected");
      throw ex;
    }
  }
}
