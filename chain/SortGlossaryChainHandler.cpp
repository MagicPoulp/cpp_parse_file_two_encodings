#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "AbstractChainHandler.hpp"
#include "ChainModel.hpp"
#include "SortGlossaryChainHandler.hpp"
#include <iostream>

using namespace std;

string SortGlossaryChainHandler::handle(const string& request) {
  if (request == "sort_glossary") {
    sortGlossary(pModel->glossary, pModel->sortedGlossary);
    return "success";
  } else {
    return AbstractChainHandler::handle(request);
  }
}

struct higher_value_sorter
{
    inline bool operator() (const pair<string, int>& elem1, const pair<string, int>& elem2)
    {
        return elem1.second >= elem2.second;
    }
};

void SortGlossaryChainHandler::sortGlossary(unordered_map<string, int>& glossary, vector<pair<string, int>>& sortedGlossary) {
  sortedGlossary.clear();
  sortedGlossary.reserve(glossary.size());
  for (auto& it: glossary) {
    sortedGlossary.push_back(pair(it.first, it.second));
  }
  std::sort(sortedGlossary.begin(), sortedGlossary.end(), higher_value_sorter());
}
