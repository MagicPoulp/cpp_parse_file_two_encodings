#pragma once

#include <fstream>
#include <iostream>
#include <functional>
#include <string>

#include "ChainModel.hpp"

class FileManager {
private:
  std::ifstream readingFile;

public:
  ~FileManager();
  void processFileByLine(const std::string& filename, std::function<void(const std::string&, ChainModel&)>& lambda, ChainModel& model);

private:
  std::string iso_8859_1_to_utf8(std::string &str);
public:
  static std::string UTF8toISO8859_1(const std::string& inString);
  static void utf8rev(std::string& inString);
};
