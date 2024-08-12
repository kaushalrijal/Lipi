#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    Purna, Dasa, Akshar, Paath, Bhana, Suna, Lagi, Jabasamma,
    Yadi, Anyatha, Thik, Bethik, Khali, // Keywords

    Plus, Minus, Multiply, Divide, Assign, Equal, NotEqual, LessThan,
    GreaterThan, LessEqual, GreaterEqual, And, Or, // Operators

    Semicolon, Comma, LeftParen, RightParen, LeftBrace, RightBrace, // Symbols

    IntegerLiteral, FloatLiteral, CharLiteral, StringLiteral, // Literals

    Identifier, // Identifiers

    EndOfFile, Unknown // Special Tokens
};

// thik bethik to be used for booleans
struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
    std::string input;
public:
    Lexer(const std::string&);
    std::vector<Token> tokenize();
};

#endif
