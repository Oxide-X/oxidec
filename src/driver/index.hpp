#pragma once

#include <CLI/CLI.hpp>
#include <string>

// Plain Data Object to hold compiler state
struct CompilerOptions {
  std::string baseFile;
  std::string buildFile = "main.out";
  bool printAllWarnings = false;
  bool verboseLogs = false;
  bool dumpIR = false;
};

class InvocationDriver {
public:
  // Singleton-like access
  static InvocationDriver *init(int argc, char *argv[]);
  static InvocationDriver *getInstance();

  // The core logic
  void parse(int argc, char *argv[]);

  // Getters for the rest of the compiler to use
  const CompilerOptions &getOptions() const { return options; }

private:
  InvocationDriver(); // Private constructor for singleton use
  static InvocationDriver *instance;

  CLI::App app{"oxidec: A modern high-performance compiler"};
  CompilerOptions options;

  void setupArguments();
};