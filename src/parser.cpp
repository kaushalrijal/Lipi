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

ASTNode* Parser::parsePrimaryExpression(){
    if(match(TokenType::NUMBER)){
        int value = std::stoi(currentToken().value);
        consumeToken();
        return new IntegerLiteral(value);
    } else if (match(TokenType::STRING)){
        std::string value = currentToken().value;
        consumeToken();
        return new StringLiteral(value);
    } else if (match(TokenType::ID)){
        std::string name = currentToken().value;
        consumeToken();
        return new Variable(name);
    } else if (match(TokenType::CHAR)){
        char value = currentToken().value[1];
        consumeToken();
        return new CharacterLiteral(value);
    } else if (match(TokenType::LPAREN)){
        consumeToken(); // Consume (
        ASTNode* expression = parseExpression();
        expect(TokenType::RPAREN);
        return expression;
    }
    throw std::runtime_error("Unexpected token in primary expression.");
}

// Methods for parsing
ASTNode* Parser::parseExpression(){
    return nullptr;
}

ASTNode* Parser::parseStatement(){
    if(match(TokenType::PRINT)){ // Print Statement
        expect(TokenType::LPAREN);
        Expression* expr = dynamic_cast<Expression*>(parseExpression());
        expect(TokenType::LPAREN);
        expect(TokenType::END);
        return new PrintStatement(expr);
    } else if(match(TokenType::INPUT)){ // Input Statement
        expect(TokenType::LPAREN);
        expect(TokenType::ID);
        std::string vName = currentToken().value;
        expect(TokenType::RPAREN);
        expect(TokenType::END);
        return new InputStatement(vName);
    } else if (match(TokenType::TYPE)) { // Assignment statement
        Token typeToken = currentToken();  
        expect(TokenType::ID);  
        std::string varName = currentToken().value; 
        expect(TokenType::ASSIGN); 
        Expression* expr = dynamic_cast<Expression*>(parseExpression()); 
        expect(TokenType::END); 
        return new AssignmentStatement(varName, expr); 
    }
}