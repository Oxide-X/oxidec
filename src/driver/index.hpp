#pragma once

#include <string>

struct argOptions {
  std::string rootFilePath;
  std::string outputPath = "build/oxide.out";
  bool terminateCompileLoop = false;
  bool printAllWarnings = false;
  bool verboseLogs = false;
  bool dumpIR = false;
};

class InvocationDriver {
private:
  struct argOptions argOptions;
  bool compareArgOptionKey(char *arg, std::string shortHand) const;
  bool compareArgOptionKey(char *arg, std::string shortHand, std::string longHand) const;
  bool isRootFilePath(char *arg) const;
  void displayCompilerVersion();
  void displayCompilerOptions();

public:
  InvocationDriver(int argc, char *argv[]);
};
