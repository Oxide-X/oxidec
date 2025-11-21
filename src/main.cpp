#include "lexer/lexer.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Incorrect usage " << std::endl;
    std::cerr << "Correct usage: oxidec main.ox" << std::endl;
    return EXIT_FAILURE;
  }

  std::fstream MainFile(argv[1], std::ios::in);
  if (!MainFile) {
    std::cerr << "Error opening file for reading" << std::endl;
    return EXIT_FAILURE;
  }

  std::stringstream FileBuffer;
  FileBuffer << MainFile.rdbuf();

  std::string sourceCode = FileBuffer.str();

  LexicalAnalyser lexicalAnalyser = LexicalAnalyser(sourceCode);
  std::vector<Token> tokenVector = lexicalAnalyser.tokenize();

  lexicalAnalyser.printTokens(tokenVector);

  return EXIT_SUCCESS;
}
