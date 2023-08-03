#pragma once

#include <string>
#include <unordered_map>
#include <vector>

struct ChainModel {
  std::string inputFile;
  std::unordered_map<std::string, int> glossary;
  std::vector<std::pair<std::string, int>> sortedGlossary;
};
