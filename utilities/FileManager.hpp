#include <fstream>
#include <iostream>
#include <functional>
#include <string>

class FileManager {
private:
  std::ifstream readingFile;

public:
  ~FileManager();
  void processFileByLine(std::string filename, std::function<void(std::string)>& lambda);

private:
  std::string iso_8859_1_to_utf8(std::string &str);
};
