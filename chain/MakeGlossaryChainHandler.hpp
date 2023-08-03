#pragma once

#include <string>

#include "AbstractChainHandler.hpp"
#include "FileManager.hpp"
#include "LambdaUtilities.hpp"
#include "ChainModel.hpp"

class MakeGlossaryChainHandler : public AbstractChainHandler {
public:
  std::string Handle(const std::string& request) override;

private:
  static void addLinesToGlossary(std::unordered_map<std::string, int>& glossary, const std::string& line);
};
