#include "cstring"
#include "exception"
#include "index.hpp"
#include "iostream"
#include "util/ox.consts.hpp"
#include "version.hpp"

bool InvocationDriver::compareArgOptionKey(char *arg, std::string shortHand) const {
  return arg == shortHand;
}

bool InvocationDriver::compareArgOptionKey(char *arg, std::string shortHand, std::string longHand) const {
  return arg == shortHand || arg == longHand;
}

bool InvocationDriver::isRootFilePath(char *arg) const {
  int argLength = std::strlen(arg);
  char *fileExtensionPointer = arg + sizeof(char) * (argLength - languageExtension.length());
  return std::strcmp(fileExtensionPointer, languageExtension.c_str()) == 0 ? true : false;
}

// TODO:
void InvocationDriver::displayCompilerVersion() {
  this->argOptions.terminateCompileLoop = true;
  std::cout
      << "oxidec: v" << OXIDEC_VERSION << std::endl;
}

InvocationDriver::InvocationDriver(int argc, char *argv[]) {
  if (argc == 1)
    std::cout << "ReadEvalPrintLoop (REPL): Under development" << std::endl;

  for (int i = 0; i < argc; i++) {
    if (compareArgOptionKey(argv[i], "-o", "--output"))
      this->argOptions.outputPath = argv[++i];
    else if (compareArgOptionKey(argv[i], "-v", "--version"))
      displayCompilerVersion();
    else if (compareArgOptionKey(argv[i], "-Wall"))
      this->argOptions.printAllWarnings = true;
    else if (isRootFilePath(argv[i]))
      this->argOptions.rootFilePath = argv[i];
  }
}
