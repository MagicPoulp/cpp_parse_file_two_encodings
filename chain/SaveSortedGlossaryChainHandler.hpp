#pragma once

#include <string>
#include <vector>

#include "AbstractChainHandler.hpp"


using namespace std;

class SaveSortedGlossaryChainHandler : public AbstractChainHandler {
public:
  std::string handle(const std::string& request) override;

private:
  void saveSortedGlossaryToFile(std::vector<std::pair<std::string, int>>& sortedGlossary);
};
