#pragma once

#include <string>
#include <vector>

#include "AbstractChainHandler.hpp"


using namespace std;

class SaveReversedChainHandler : public AbstractChainHandler {
public:
  std::string handle(const std::string& request) override;

private:
  string getReverseFile(const string& inputFile);
  static void saveWithReversedGlossaryWords(unordered_map<string, int>& glossary, const string& line, ofstream& fileStream);
};
