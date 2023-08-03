#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <functional>

#include "FileManager.hpp"
#include "CustomExceptions.hpp"

using namespace std;

// Following the RAII technique, in case of an exception, we clear the resources
FileManager::~FileManager() {
  if (readingFile.is_open()) {
    readingFile.close();
  }
}

void FileManager::processFileByLine(string filename, std::function<void(string)>& lambda) {
  readingFile.open(filename, ios::in);
  if (readingFile.is_open()) {
    try {
      string tp;
      while(getline(readingFile, tp)) {
        std::string utf8_string = iso_8859_1_to_utf8(tp);
        lambda(utf8_string);
      }
      readingFile.close();
    } catch(std::exception ex) {
      std::istringstream ss(ex.what());
      std::string line1, line2;
      std::getline(ss, line1);
      std::getline(ss, line2);
      std::stringstream ss2;
      ss2 << "Error while processing the file." << endl << line1 << endl << line2 << endl;
      DetailedErrorCustomException ex2(ss2.str().c_str());
      throw ex2;
    }
  } else {
    DetailedErrorCustomException ex("Unable to open the file");
    throw ex;
  }
}

// https://stackoverflow.com/questions/4059775/convert-iso-8859-1-strings-to-utf-8-in-c-c
std::string FileManager::iso_8859_1_to_utf8(std::string &str)
{
    string strOut;
    strOut.reserve(str.length() + 1);
    for (std::string::iterator it = str.begin(); it != str.end(); ++it)
    {
        uint8_t ch = *it;
        if (ch < 0x80) {
            strOut.push_back(ch);
        }
        else {
            strOut.push_back(0xc0 | ch >> 6);
            strOut.push_back(0x80 | (ch & 0x3f));
        }
    }
    return strOut;
}
