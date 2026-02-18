#include "index.hpp"
#include "version.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

InvocationDriver *InvocationDriver::instance = nullptr;

InvocationDriver::InvocationDriver() {
  setupArguments();
}

void InvocationDriver::setupArguments() {
  // Define the version flag using the macro from version.hpp
  app.set_version_flag("--version", std::string("oxidec v") + OXIDEC_VERSION);

  // Output file option
  app.add_option("-o,--output", options.buildFile, "Specify the output binary path")
      ->capture_default_str();

  // Boolean flags
  app.add_flag("-v,--verbose", options.verboseLogs, "Enable detailed debug logging");
  app.add_flag("--Wall", options.printAllWarnings, "Enable all compiler warnings");
  app.add_flag("--dump-ir", options.dumpIR, "Display LLVM intermediate representation");

  // Positional argument (The file to compile)
  app.add_option("file", options.baseFile, "The .ox source file to compile")
      ->check(CLI::ExistingFile) // Auto-validates that file exists
      ->required();              // Errors out if no file is provided
}

void InvocationDriver::parse(int argc, char *argv[]) {
  try {
    char **utf8argv = app.ensure_utf8(argv);
    app.parse(argc, utf8argv);

    spdlog::set_pattern("[%H:%M:%S] [%l] [tid: %t] : %v");
    // Apply logging level immediately based on flags
    if (options.verboseLogs) {
      spdlog::set_level(spdlog::level::debug);
      spdlog::debug("Verbose logging enabled.");
    }

    spdlog::debug("InvocationDriver: file=\"{}\" output=\"{}\"",
                  options.baseFile, options.buildFile);

  } catch (const CLI::ParseError &e) {
    // Automatically handles --help, --version, and formatting errors
    std::exit(app.exit(e));
  }
}

InvocationDriver *InvocationDriver::init(int argc, char *argv[]) {
  if (instance == nullptr) {
    instance = new InvocationDriver();
    instance->parse(argc, argv);
  }
  return instance;
}

InvocationDriver *InvocationDriver::getInstance() {
  return instance;
}