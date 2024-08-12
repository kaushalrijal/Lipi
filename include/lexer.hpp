#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType {
        // Keywords
        KEYWORD,
        // Data types
        PURNA, DASA, AKSHAR, PAATH, KHALI,
        // Identifiers
        IDENTIFIER,
        // Literals
        INTEGER, STRING, FLOAT, BOOLEAN,
        // Operator
        OPERATOR,
        // Delimiters
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, SEMICOLON,
        // End of File
        END_OF_FILE,
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
