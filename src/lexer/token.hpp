#ifndef TOKEN_H
#define TOKEN_H

#include <cassert>
#include <string>
#include <unordered_map>

enum class TokenType {
  // Literals
  IntegerLiteral,
  FloatLiteral,
  BinaryLiteral,
  HexLiteral,
  StringLiteral,
  BooleanLiteral,
  ByteLiteral,

  // Identifiers
  Identifier,

  // Keywords
  KeywordIf,
  KeywordElse,
  KeywordWhile,
  KeywordFor,
  KeywordSwitch,
  KeywordCase,
  KeywordBreak,
  KeywordContinue,
  KeywordReturn,
  KeywordInt,
  KeywordFloat,
  KeywordBinary,
  KeywordHex,
  KeywordString,
  KeywordBool,
  KeywordByte,
  KeywordVoid,
  KeywordNull,
  KeywordConst,
  KeywordClass,
  KeywordStruct,
  KeywordEnum,
  KeywordPublic,
  KeywordPrivate,
  KeywordProtected,
  KeywordStatic,

  // Operators
  OpAssign,         // =
  OpEqual,          // ==
  OpNotEqual,       // !=
  OpLess,           // <
  OpLessEqual,      // <=
  OpGreater,        // >
  OpGreaterEqual,   // >=
  OpPlus,           // +
  OpMinus,          // -
  OpMultiply,       // *
  OpDivide,         // /
  OpModulo,         // %
  OpLogicalAnd,     // &&
  OpLogicalOr,      // ||
  OpLogicalNot,     // !
  OpBitwiseAnd,     // &
  OpBitwiseOr,      // |
  OpIncrement,      // ++
  OpDecrement,      // --
  OpPlusAssign,     // +=
  OpMinusAssign,    // -=
  OpMultiplyAssign, // *=
  OpDivideAssign,   // /=
  OpModuloAssign,   // %=

  // Punctuation
  LeftParen,    // (
  RightParen,   // )
  LeftBrace,    // {
  RightBrace,   // }
  LeftBracket,  // [
  RightBracket, // ]
  Semicolon,    // ;
  Comma,        // ,
  Dot,          // .
  Colon,        // :
  Question,     // ?

  // Special
  EndOfFile,
  Invalid
};

const std::unordered_map<std::string, TokenType> keywordMap = {
    // Flow control
    {"if", TokenType::KeywordIf},
    {"else", TokenType::KeywordElse},
    {"while", TokenType::KeywordWhile},
    {"for", TokenType::KeywordFor},
    {"switch", TokenType::KeywordSwitch},
    {"case", TokenType::KeywordCase},
    {"break", TokenType::KeywordBreak},
    {"continue", TokenType::KeywordContinue},
    {"return", TokenType::KeywordReturn},

    // Types
    {"int", TokenType::KeywordInt},
    {"float", TokenType::KeywordFloat},
    {"binary", TokenType::KeywordBinary},
    {"hex", TokenType::KeywordHex},
    {"string", TokenType::KeywordString},
    {"bool", TokenType::KeywordBool},
    {"byte", TokenType::KeywordByte},
    {"void", TokenType::KeywordVoid},
    {"null", TokenType::KeywordNull},

    // Storage/modifiers
    {"const", TokenType::KeywordConst},
    {"static", TokenType::KeywordStatic},

    // Structure
    {"class", TokenType::KeywordClass},
    {"struct", TokenType::KeywordStruct},
    {"enum", TokenType::KeywordEnum},

    // Access specifiers
    {"public", TokenType::KeywordPublic},
    {"private", TokenType::KeywordPrivate},
    {"protected", TokenType::KeywordProtected},

    // Boolean literals
    {"true", TokenType::BooleanLiteral},
    {"false", TokenType::BooleanLiteral}};

struct Token {
  TokenType type;
  std::string lexeme; // The actual text from source
  int line;
  int column;

  Token(TokenType t, std::string lex, int ln, int col)
      : type(t), lexeme(std::move(lex)), line(ln), column(col) {}
};

#endif // TOKEN_H
