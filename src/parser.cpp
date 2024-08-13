#include "parser.hpp"
#include <stdexcept>

Parser::Parser(std::vector<Token>& tok) : tokens(tok), current(0) {};

// Return Current Token
Token& Parser::currentToken(){
    if(current>=tokens.size()){
        throw std::runtime_error("No more tokens");
    }
    return tokens[current+1];
}

// Move to next token
void Parser::consumeToken() {
    if (current < tokens.size()) {
        ++current;
    }
}

// Checks if the current token matches specific type
bool Parser::match(TokenType type) {
    if (currentToken().type == type) {
        consumeToken();
        return true;
    }
    return false;
}

// Check if the tokens matches a specific type and consume it. 
void Parser::expect(TokenType type) {
    if (!match(type)) {
        throw std::runtime_error("Unexpected token type");
    }
}