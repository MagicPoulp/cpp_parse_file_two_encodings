#include <iostream>
#include <fstream>
#include <string>

#include "CustomExceptions.hpp"

using namespace std;

// https://stackoverflow.com/questions/4059775/convert-iso-8859-1-strings-to-utf-8-in-c-c
std::string iso_8859_1_to_utf8(std::string &str)
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

int mainWrapped(int argc, char* argv[]);

int main(int argc, char* argv[])
{
  try {
    return mainWrapped(argc, argv);
  }
  catch (const DetailedErrorCustomException& ex) {
    cerr << "Error: " << ex.what() << endl;
    return -1;
  }
  catch (const std::exception& ex) {
    cerr << "Error: unexpected error" << endl;
    // throw the exception to debug
    throw ex;
    return -1;
  }
}

int mainWrapped(int argc, char* argv[])
{
  if (argc != 2) {
    DetailedErrorCustomException ex("wrong number of arguments");
    throw ex;
  }
  ifstream newfile;
  newfile.open(argv[1], ios::in);
  if (newfile.is_open()) {
    string tp;
    while(getline(newfile, tp)) {
      std::string utf8_string = iso_8859_1_to_utf8(tp);
      cout << utf8_string << "\n";
    }
    newfile.close();
  }
  return 0;
}
