#ifndef LEXICAL_ANALYSER_HPP
#define LEXICAL_ANALYSER_HPP

#include "token.hpp"
#include <string>
#include <vector>

class LexicalAnalyser {
private:
  std::string input;
  std::size_t position;
  int line;
  int column;

  char peek(int offset = 0) const;
  char advance();
  void skipWhitespace();
  void skipLineComment();
  void skipBlockCommment();
  Token createToken(TokenType type, const std::string &lexeme, int startLine,
                    int startCol);
  Token scanIdentifierOrKeyword();
  Token scanNumber();
  Token scanString();
  Token scanOperatorOrPunctuation();

public:
  LexicalAnalyser(const std::string &source);
  std::vector<Token> tokenize();
  void printTokens(const std::vector<Token> &tokens);
};

#endif
