#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType {
    PRINT, INPUT, TYPE, IF, ELSE, WHILE, FOR, FUNC_DEF, RETURN,
    NUMBER, STRING, CHAR, ID, ASSIGN, END, LPAREN, RPAREN,
    LBRACE, RBRACE, ADD, SUB, MUL, DIV, MOD, AND, OR, NOT, EQ, NEQ, LT, GT, LE, GE,
    SKIP, NEWLINE, COMMENT, MISMATCH, END_OF_FILE
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
