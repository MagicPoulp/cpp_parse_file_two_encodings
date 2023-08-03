#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "ChainModel.hpp"
#include "AbstractChainHandler.hpp"
#include "SaveReversedChainHandler.hpp"
#include "CustomExceptions.hpp"
#include "FileManager.hpp"
#include "LambdaUtilities.hpp"

using namespace std;

string SaveReversedChainHandler::handle(const string& request) {
  if (request == "save_reversed_to_file") {
    FileManager fm;
    string reverseFile = getReverseFile(pModel->inputFile);
    ofstream fileStream(reverseFile);
    if (fileStream.is_open()) {
      auto lambda = [&fileStream](const string& line, ChainModel& model2) {
        SaveReversedChainHandler::saveWithReversedGlossaryWords(model2.glossary, line, fileStream);
      };
      auto funcLambda = LambdaUtilities::to_function(lambda);
      fm.processFileByLine(pModel->inputFile, funcLambda, *pModel);
    }
    else {
      DetailedErrorCustomException ex("Unable to open the file: " + reverseFile);
      throw ex;
    }
    fileStream.close();
    return "success";
  } else {
    return AbstractChainHandler::handle(request);
  }
}

string SaveReversedChainHandler::getReverseFile(const string& inputFile) {
  // https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
  auto hasEnding = [](std::string const& fullString, std::string const& ending) {
    if (fullString.length() >= ending.length()) {
      return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
      return false;
    }
  };
  auto removeLastN = [](string& str, int n) {
    if (str.length() < n) {
      return;
    }
    str.erase(str.length() - n);
  };
  string reverseFile = "" + inputFile;
  if (hasEnding(reverseFile, ".txt")) {
    removeLastN(reverseFile, 4);
  }
  reverseFile += ".reverse.txt";
  return reverseFile;
}

void SaveReversedChainHandler::saveWithReversedGlossaryWords(unordered_map<string, int>& glossary, const string& line,
                                                              ofstream& fileStream) {
  string newLine = "";

  string word;
  vector<string> wordsToReverse;
  int wordStart = 0;
  bool wordStarted = true;
  int countWordSize = 0;
  int loopIndex = 0;
  for (auto it = line.begin(); it != line.end(); it++) {
    switch (*it) {
    case '\r':
    case '\n':
      continue;
      break;
    case '\0':
    case ' ':
    case '\'':
    case '.':
    case ',':
    case ':':
    case ';': {
      string word = line.substr(wordStart, countWordSize);
      if (word.length() <= 1 || glossary.find(word) == glossary.end()) {
        newLine += word;
      } else {
        // utf8 can have 2 bytes per characters, so we use a special reverse function
        // reverse(reversedWord.begin(), reversedWord.end());
        // "" + will keep the initial word unchanged
        string reversedWord = "" + word;
        FileManager::utf8rev(reversedWord);
        newLine += reversedWord;
      }
      newLine += *it;
      wordStart = loopIndex+1;
      countWordSize = 0;
      break;
    }
    default:
      countWordSize++;
      break;
    }
    loopIndex++;
  }
  if (countWordSize > 0) {
    string word = line.substr(wordStart, countWordSize);
    if (word.length() <= 1 || glossary.find(word) == glossary.end()) {
      newLine += word;
    } else {
      string reversedWord = "" + word;
      reverse(reversedWord.begin(), reversedWord.end());
      newLine += reversedWord;
    }
  }
  string newLineIsoEncoded = FileManager::UTF8toISO8859_1(newLine);
  fileStream << newLineIsoEncoded << '\r' << endl;
}
