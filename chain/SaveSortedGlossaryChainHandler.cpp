#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "AbstractChainHandler.hpp"
#include "ChainModel.hpp"
#include "SaveSortedGlossaryChainHandler.hpp"
#include "CustomExceptions.hpp"

using namespace std;

string SaveSortedGlossaryChainHandler::handle(const string& request) {
  if (request == "save_sorted_glossary_to_file") {
    saveSortedGlossaryToFile(pModel->sortedGlossary);
    return "success";
  } else {
    return AbstractChainHandler::handle(request);
  }
}

void SaveSortedGlossaryChainHandler::saveSortedGlossaryToFile(vector<pair<string, int>>& sortedGlossary) {
  // https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
  auto hasEnding = [](std::string const& fullString, std::string const& ending) {
    if (fullString.length() >= ending.length()) {
      return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
      return false;
    }
  };
  auto removeLastN = [](std::string& str, int n) {
    if (str.length() < n) {
      return;
    }
    str.erase(str.length() - n);
  };
  string glossaryFile = pModel->inputFile;
  if(hasEnding(glossaryFile, ".txt")) {
    removeLastN(glossaryFile, 4);
  }
  glossaryFile += ".table.txt";
  ofstream fileStream(glossaryFile);
  if (fileStream.is_open()) {
    for (auto elem : sortedGlossary) {
      fileStream << elem.first << "," << elem.second << endl;
    }
    // to add: close in case of an exception
    fileStream.close();
  }
  else {
    DetailedErrorCustomException ex("Unable to open the file: " + glossaryFile);
    throw ex;
  }
}
