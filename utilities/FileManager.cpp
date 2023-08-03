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

void FileManager::processFileByLine(const string& filename, std::function<void(const string&, ChainModel&)>& lambda, ChainModel& model) {
  readingFile.open(filename, ios::in);
  if (readingFile.is_open()) {
    try {
      string tp;
      while (getline(readingFile, tp)) {
        // we need utf8 to print on the debian terminal
        // it also ensures the regex works fine with accents
        // a stable clasical utf-8 encoding ensures robustness
        std::string utf8_string = iso_8859_1_to_utf8(tp);
        lambda(utf8_string, model);
      }
      readingFile.close();
    } catch(DetailedErrorCustomException ex) {
      throw ex;
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

// https://stackoverflow.com/questions/23689733/convert-string-from-utf-8-to-iso-8859-1
std::string FileManager::UTF8toISO8859_1(const string& inString)
{
  const char* in = inString.c_str();
  std::string out;
  if (in == NULL)
    return out;

  unsigned int codepoint;
  while (*in != 0) {
    unsigned char ch = static_cast<unsigned char>(*in);
    if (ch <= 0x7f)
      codepoint = ch;
    else if (ch <= 0xbf)
      codepoint = (codepoint << 6) | (ch & 0x3f);
    else if (ch <= 0xdf)
      codepoint = ch & 0x1f;
    else if (ch <= 0xef)
      codepoint = ch & 0x0f;
    else
      codepoint = ch & 0x07;
    ++in;
    if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff))
      {
        if (codepoint <= 255)
          {
            out.append(1, static_cast<char>(codepoint));
          }
        else
          {
            // do whatever you want for out-of-bounds characters
          }
      }
  }
  return out;
}
