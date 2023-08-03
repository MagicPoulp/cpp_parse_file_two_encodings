#include <iostream>
#include <fstream>
#include <string>

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

int main(int argc, char* argv[])
{
  if (argc != 2) {
    cerr << "Error: wrong number of arguments" << endl;
    return -1;
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
