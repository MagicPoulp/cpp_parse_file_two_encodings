#include <iostream>

#include "CustomExceptions.hpp"
#include "ChainModel.hpp"
#include "AllWork.hpp"
#include "Main.hpp"

using namespace std;

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
  AllWork allwork;
  ChainModel model;
  model.inputFile = string(argv[1]);
  allwork.processAll(model);
  return 0;
}
