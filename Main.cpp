#include <iostream>
#include <di.hpp>

#include "CustomExceptions.hpp"
#include "ChainModel.hpp"
#include "AllWork.hpp"
#include "Main.hpp"

using namespace std;
namespace di = boost::di;

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
  string inputFileString{argv[1]};

  auto inputFile = [] {};

  struct app {
    BOOST_DI_INJECT(app, (named = inputFile) string inputFile) : inputFile(inputFile) {
      AllWork allwork;
      ChainModel model;
      model.inputFile = inputFile;
      allwork.processAll(model);
    }
  private:
    string inputFile = 0;
  };

  auto injector = di::make_injector(
    di::bind<string>().named(inputFile).to(inputFileString)
    // due to a conflict with the unsorted_map of ChainModel, it requires more work to inject ChainModel
    // di::bind<ChainModel>().to(ChainModel)
  );
  auto object = injector.create<app>();
  return 0;
}
