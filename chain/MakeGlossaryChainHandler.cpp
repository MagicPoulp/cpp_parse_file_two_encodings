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

string MakeGlossaryChainHandler::handle(const string& request) {
  if (request == "make_glossary") {
    FileManager fm;
    auto lambda = [](const string& line, ChainModel& model2) {
      MakeGlossaryChainHandler::addLinesToGlossary(model2.glossary, line);
    };
    auto funcLambda = LambdaUtilities::to_function(lambda);
    fm.processFileByLine(pModel->inputFile, funcLambda, *pModel);
    return "success";
  } else {
    return AbstractChainHandler::handle(request);
  }
}

void MakeGlossaryChainHandler::addLinesToGlossary(unordered_map<string, int>& glossary, const string& line) {
  regex reg("['.,:;]");
  string line2 = regex_replace(line, reg, " ");
  stringstream ss(line2);
  string word;
  while (ss >> word) {
    if (word.length() <= 1) {
      continue;
    }
    if (word.length() > 64) {
      DetailedErrorCustomException ex("A too large word was found, size: " + word.length());
      throw ex;
    }
    regex validWordRegex{"([a-zA-Z0-9éèêàâëûùîçôöü]|-)+"};
    if (!regex_match(word, validWordRegex)) {
      DetailedErrorCustomException ex("Invalid character in the word: " + word);
      throw ex;
    }
    // We do not save only in lower case here because, according to the example,
    // "les" and "Les" must be counted separately.
    if (auto [it, inserted] = glossary.try_emplace(word, 1); !inserted) {
      it->second++;
    }
  }
}
