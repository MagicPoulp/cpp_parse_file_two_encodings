#pragma once

#include <string>
#include <unordered_map>

struct ChainModel {
  std::string inputFile;
  std::unordered_map<std::string, int> glossary;
};
