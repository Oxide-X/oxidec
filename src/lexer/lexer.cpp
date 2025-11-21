#include "lexer.hpp"
#include "token.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

char LexicalAnalyser::peek(int offset) const {
  std::size_t pos = position + offset;
  return pos < input.length() ? input[pos] : '\0';
}

char LexicalAnalyser::advance() {
  if (position < input.length()) {
    char c = input[position++];
    if (c == '\n') {
      line++;
      column = 1;
    } else {
      column++;
    }
    return c;
  }
  return '\0';
}

void LexicalAnalyser::skipWhitespace() {
  while (position < input.length() && std::isspace(peek())) {
    advance();
  }
}

void LexicalAnalyser::skipLineComment() {
  advance();
  advance();
  while (peek() != '\0' && peek() != '\n') {
    advance();
  }
}

void LexicalAnalyser::skipBlockCommment() {
  advance();
  advance();

  while (peek() != '\0') {
    if (peek() == '*' && peek(1) == '/') {
      advance();
      advance();
      break;
    }
    advance();
  }
}

Token LexicalAnalyser::createToken(TokenType type, const std::string &lexeme,
                                   int startLine, int startCol) {
  return Token(type, lexeme, startLine, startCol);
}

Token LexicalAnalyser::scanIdentifierOrKeyword() {
  int startLine = line;
  int startCol = column;
  std::string lexeme;

  while (peek() != '\0' && (std::isalnum(peek()) || peek() == '_')) {
    lexeme += advance();
  }

  auto it = keywordMap.find(lexeme);
  if (it != keywordMap.end()) {
    return createToken(it->second, lexeme, startLine, startCol);
  }
  return createToken(TokenType::Identifier, lexeme, startLine, startCol);
}

Token LexicalAnalyser::scanNumber() {
  int startLine = line;
  int startCol = column;
  std::string lexeme;
  bool isFloat = false;

  if (peek() == '0' && peek(1) == 'x') {
    lexeme += advance();
    lexeme += advance();
    while (std::isxdigit(peek()))
      lexeme += advance();
    return createToken(TokenType::IntegerLiteral, lexeme, startLine, startCol);
  }

  if (peek() == '0' && peek(1) == 'b') {
    lexeme += advance();
    lexeme += advance();
    while (peek() == '0' || peek() == '1')
      lexeme += advance();
    return createToken(TokenType::IntegerLiteral, lexeme, startLine, startCol);
  }

  while (std::isdigit(peek()))
    lexeme += advance();

  if (peek() == '.' && std::isdigit(peek(1))) {
    isFloat = true;
    lexeme += advance();
    while (std::isdigit(peek()))
      lexeme += advance();
  }

  if (peek() == 'e') {
    isFloat = true;
    lexeme += advance();
    if (peek() == '+' || peek() == '-')
      lexeme += advance();
    while (std::isdigit(peek()))
      lexeme += advance();
  }

  TokenType type =
      isFloat ? TokenType::FloatLiteral : TokenType::IntegerLiteral;
  return createToken(type, lexeme, startLine, startCol);
}

Token LexicalAnalyser::scanString() {
  int startLine = line;
  int startCol = column;
  std::string lexeme;

  char quote = advance();
  lexeme += quote;

  while (peek() != '\0' && peek() != quote) {
    if (peek() == '\\') {
      lexeme += advance();
      if (peek() != '\0')
        lexeme += advance();
    } else {
      lexeme += advance();
    }
  }

  if (peek() == quote) {
    lexeme += advance();
    return createToken(TokenType::StringLiteral, lexeme, startLine, startCol);
  }

  return createToken(TokenType::Invalid, lexeme, startLine, startCol);
}

Token LexicalAnalyser::scanOperatorOrPunctuation() {
  int startLine = line;
  int startCol = column;
  char c = peek();

  switch (c) {
  case '(':
    advance();
    return createToken(TokenType::LeftParen, "(", startLine, startCol);
  case ')':
    advance();
    return createToken(TokenType::RightParen, ")", startLine, startCol);
  case '{':
    advance();
    return createToken(TokenType::LeftBrace, "{", startLine, startCol);
  case '}':
    advance();
    return createToken(TokenType::RightBrace, "}", startLine, startCol);
  case '[':
    advance();
    return createToken(TokenType::LeftBracket, "[", startLine, startCol);
  case ']':
    advance();
    return createToken(TokenType::RightBracket, "]", startLine, startCol);
  case ';':
    advance();
    return createToken(TokenType::Semicolon, ";", startLine, startCol);
  case ',':
    advance();
    return createToken(TokenType::Comma, ",", startLine, startCol);
  case '.':
    advance();
    return createToken(TokenType::Dot, ".", startLine, startCol);
  case '?':
    advance();
    return createToken(TokenType::Question, "?", startLine, startCol);
  case ':':
    advance();
    return createToken(TokenType::Colon, ":", startLine, startCol);

  case '+':
    advance();
    if (peek() == '+') {
      advance();
      return createToken(TokenType::OpIncrement, "++", startLine, startCol);
    }
    if (peek() == '=') {
      advance();
      return createToken(TokenType::OpPlusAssign, "+=", startLine, startCol);
    }
    return createToken(TokenType::OpPlus, "+", startLine, startCol);

  case '-':
    advance();
    if (peek() == '-') {
      advance();
      return createToken(TokenType::OpDecrement, "--", startLine, startCol);
    }
    if (peek() == '=') {
      advance();
      return createToken(TokenType::OpMinusAssign, "-=", startLine, startCol);
    }
    return createToken(TokenType::OpMinus, "-", startLine, startCol);

  case '*':
    advance();
    if (peek() == '=') {
      advance();
      return createToken(TokenType::OpMultiplyAssign, "*=", startLine,
                         startCol);
    }
    return createToken(TokenType::OpMultiply, "*", startLine, startCol);

  case '/':
    advance();
    if (peek() == '=') {
      advance();
      return createToken(TokenType::OpDivideAssign, "/=", startLine, startCol);
    }
    return createToken(TokenType::OpDivide, "/", startLine, startCol);

  case '%':
    advance();
    if (peek() == '=') {
      advance();
      return createToken(TokenType::OpModuloAssign, "%=", startLine, startCol);
    }
    return createToken(TokenType::OpModulo, "%", startLine, startCol);

  case '=':
    advance();
    if (peek() == '=') {
      advance();
      return createToken(TokenType::OpEqual, "==", startLine, startCol);
    }
    return createToken(TokenType::OpAssign, "=", startLine, startCol);

  case '!':
    advance();
    if (peek() == '=') {
      advance();
      return createToken(TokenType::OpNotEqual, "!=", startLine, startCol);
    }
    return createToken(TokenType::OpLogicalNot, "!", startLine, startCol);

  case '<':
    advance();
    if (peek() == '=') {
      advance();
      return createToken(TokenType::OpLessEqual, "<=", startLine, startCol);
    }
    return createToken(TokenType::OpLess, "<", startLine, startCol);

  case '>':
    advance();
    if (peek() == '=') {
      advance();
      return createToken(TokenType::OpGreaterEqual, ">=", startLine, startCol);
    }
    return createToken(TokenType::OpGreater, ">", startLine, startCol);

  case '&':
    advance();
    if (peek() == '&') {
      advance();
      return createToken(TokenType::OpLogicalAnd, "&&", startLine, startCol);
    }
    return createToken(TokenType::OpBitwiseAnd, "&", startLine, startCol);

  case '|':
    advance();
    if (peek() == '|') {
      advance();
      return createToken(TokenType::OpLogicalOr, "||", startLine, startCol);
    }
    return createToken(TokenType::OpBitwiseOr, "|", startLine, startCol);
  }

  advance();
  return createToken(TokenType::Invalid, std::string(1, c), startLine,
                     startCol);
}

LexicalAnalyser::LexicalAnalyser(const std::string &source)
    : input(source), position(0), line(1), column(1) {}

std::vector<Token> LexicalAnalyser::tokenize() {
  std::vector<Token> tokens;

  while (position < input.length()) {
    skipWhitespace();
    if (position >= input.length())
      break;

    if (peek() == '/' && peek(1) == '/') {
      skipLineComment();
      continue;
    }
    if (peek() == '/' && peek(1) == '*') {
      skipBlockCommment();
      continue;
    }

    char c = peek();

    if (std::isalpha(c))
      tokens.push_back(scanIdentifierOrKeyword());
    else if (std::isdigit(c))
      tokens.push_back(scanNumber());
    else if (c == '"' || c == '\'')
      tokens.push_back(scanString());
    else
      tokens.push_back(scanOperatorOrPunctuation());
  }

  tokens.emplace_back(TokenType::EndOfFile, "", line, column);
  return tokens;
}

// TODO: Delete this by combining this with keywordMap
std::string token_type_to_string(TokenType type) {
  switch (type) {
  case TokenType::IntegerLiteral:
    return "INTEGER_LITERAL";
  case TokenType::FloatLiteral:
    return "FLOAT_LITERAL";
  case TokenType::StringLiteral:
    return "STRING_LITERAL";
  case TokenType::BooleanLiteral:
    return "BOOLEAN_LITERAL";
  case TokenType::Identifier:
    return "IDENTIFIER";
  case TokenType::KeywordInt:
    return "KEYWORD_INT";
  case TokenType::KeywordFloat:
    return "KEYWORD_FLOAT";
  case TokenType::KeywordIf:
    return "KEYWORD_IF";
  case TokenType::KeywordElse:
    return "KEYWORD_ELSE";
  case TokenType::KeywordWhile:
    return "KEYWORD_WHILE";
  case TokenType::KeywordReturn:
    return "KEYWORD_RETURN";
  case TokenType::OpPlus:
    return "OP_PLUS";
  case TokenType::OpMinus:
    return "OP_MINUS";
  case TokenType::OpMultiply:
    return "OP_MULTIPLY";
  case TokenType::OpDivide:
    return "OP_DIVIDE";
  case TokenType::OpEqual:
    return "OP_EQUAL";
  case TokenType::OpAssign:
    return "OP_ASSIGN";
  case TokenType::LeftParen:
    return "LEFT_PAREN";
  case TokenType::RightParen:
    return "RIGHT_PAREN";
  case TokenType::LeftBrace:
    return "LEFT_BRACE";
  case TokenType::RightBrace:
    return "RIGHT_BRACE";
  case TokenType::Semicolon:
    return "SEMICOLON";
  case TokenType::EndOfFile:
    return "EOF";
  case TokenType::Invalid:
    return "INVALID";
  default:
    return "UNKNOWN";
  }
}

void LexicalAnalyser::printTokens(const std::vector<Token> &tokens) {
  for (const Token &tok : tokens) {
    std::cout << "[" << tok.line << ":" << tok.column << "] "
              << token_type_to_string(tok.type) << " '" << tok.lexeme << "'\n";
  }
}
