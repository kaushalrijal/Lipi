#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include "ast.hpp"
#include "lexer.hpp"

class Parser{
    std::vector<Token> tokens;
    size_t current;

    // Methods to manage tokens
    Token& currentToken();  
    Token& nextToken();    
    void consumeToken();   
    bool match(TokenType type);
    void expect(TokenType type);

    // Parsing Methods
    ASTNode* parseExpression();
    ASTNode* parseStatement();
    ASTNode* parseDeclaration();

    public:
        Parser(std::vector<Token>&);

        // Main parse function
        ASTNode* parse();
};

#endif  // PARSER_HPP