#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "AbstractChainHandler.hpp"
#include "FileManager.hpp"
#include "LambdaUtilities.hpp"
#include "ChainModel.hpp"

class SortGlossaryChainHandler : public AbstractChainHandler {
public:
  std::string handle(const std::string& request) override;

private:
  void sortGlossary(std::unordered_map<std::string, int>& glossary, std::vector<std::pair<std::string, int>>& sortedGlossary);
};
