#include "cstring"
#include "exception"
#include "index.hpp"
#include "util/ox.consts.hpp"
#include "version.hpp"
#include <iostream>
#include <spdlog/spdlog.h>
#include <sstream>

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

void InvocationDriver::displayCompilerVersion() {
  this->argOptions.terminateCompileLoop = true;
  std::cout
      << "oxidec: v" << OXIDEC_VERSION << std::endl;
}

void InvocationDriver::displayCompilerOptions() {
  spdlog::info(
      "compiler.options:{}root=\"{}\" output=\"{}\" terminate={} warnings={} verbose={} dump_ir={}",
      "\n",
      argOptions.rootFilePath,
      argOptions.outputPath,
      argOptions.terminateCompileLoop,
      argOptions.printAllWarnings,
      argOptions.verboseLogs,
      argOptions.dumpIR);
}

InvocationDriver::InvocationDriver(int argc, char *argv[]) {
  if (argc == 1)
    std::cout << "ReadEvalPrintLoop (REPL): Under development" << std::endl;

  for (int i = 0; i < argc; i++) {
    if (compareArgOptionKey(argv[i], "-o", "--output"))
      this->argOptions.outputPath = argv[++i];
    else if (compareArgOptionKey(argv[i], "--version"))
      displayCompilerVersion();
    else if (compareArgOptionKey(argv[i], "-Wall"))
      this->argOptions.printAllWarnings = true;
    else if (compareArgOptionKey(argv[i], "-v", "--verbose"))
      this->argOptions.verboseLogs = true;
    else if (isRootFilePath(argv[i]))
      this->argOptions.rootFilePath = argv[i];
  }

  displayCompilerOptions();
}
