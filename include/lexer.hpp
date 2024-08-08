#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

struct Token;

enum TokenType {
    KEYWORD, IDENTIFIER, NUMBER, STRING, OPERATOR,
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();
private:
    std::string input;
};

#endif
