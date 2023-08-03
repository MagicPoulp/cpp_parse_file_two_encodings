#include <string>
#include <regex>
#include <algorithm>

#include "AbstractChainHandler.hpp"
#include "FileManager.hpp"
#include "LambdaUtilities.hpp"
#include "ChainModel.hpp"
#include "CustomExceptions.hpp"
#include "MakeGlossaryChainHandler.hpp"

using namespace std;

std::string MakeGlossaryChainHandler::Handle(const std::string& request) {
  if (request == "make_glossary") {
    FileManager fm;
    auto lambda = [](const string& line, ChainModel& model2) {
      MakeGlossaryChainHandler::addLinesToGlossary(model2.glossary, line);
    };
    auto funcLambda = LambdaUtilities::to_function(lambda);
    fm.processFileByLine(model.inputFile, funcLambda, model);
    return "success";
  } else {
    return AbstractChainHandler::Handle(request);
  }
}

void MakeGlossaryChainHandler::addLinesToGlossary(unordered_map<string, int>& glossary, const string& line) {
  string line2 = line;
  std::replace(line2.begin(), line2.end(), '\'', ' ');
  std::replace(line2.begin(), line2.end(), '.', ' ');
  stringstream ss(line2);
  string word;
  while (ss >> word) {
    if (word.length() <= 1) {
      continue;
    }
    regex validWordRegex{"([a-zA-Z][0-9]éèêàâëûùîçôöü)+"};
    if (!regex_match("word", validWordRegex)) {
      DetailedErrorCustomException ex("Invalid character in the word: " + word);
    }
    if (auto [it, inserted] = glossary.try_emplace(word, 1); !inserted) {
      it->second++;
    }
    cout << word << endl;
  }
}
