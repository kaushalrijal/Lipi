#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

struct Token {
    enum Type {
        // Keywords
        KEYWORD,
        // Data types
        PURNA, DASA, AKSHAR, PAATH, SAHI_GALAT,
        // Identifiers
        IDENTIFIER,
        // Literals
        NUMBER, STRING,
        // Operators
        OPERATOR,
        // Delimiters
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, SEMICOLON,
    } type;
    std::string value;
};

class Lexer {
    std::string input;
public:
    Lexer(const std::string&);
    std::vector<Token> tokenize();
};

#endif
