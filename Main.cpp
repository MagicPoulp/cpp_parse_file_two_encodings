#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// https://stackoverflow.com/questions/4059775/convert-iso-8859-1-strings-to-utf-8-in-c-c
string latin1_to_utf8(string & ins) {
  unsigned char *in, *out, *outStart;
  int lenOut = ins.length();
  out = new unsigned char[lenOut*2];
  outStart = out;
  in = reinterpret_cast<unsigned char*>(const_cast<char*>(ins.c_str()));
  while (*in)
    if (*in<128) *out++=*in++;
    else *out++=0xc2+(*in>0xbf), *out++=(*in++&0x3f)+0x80;
  std::string result(reinterpret_cast<char*>(outStart));
  delete[](outStart);
  return result;
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
    while(getline(newfile, tp)){
      std::string utf8_string = latin1_to_utf8(tp);
      cout << utf8_string << "\n";
    }
    newfile.close();
  }
  return 0;
}
