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
    bool check(TokenType);

    // Parsing Methods
    // Parse different types of expressions
    ASTNode* parsePrimaryExpression();  // Parse Literals, variables, and parenthesized expressions
    Expression* parseUnaryExpression(); // parse unary operations like -, !
    Expression* parseBinaryExpression(int);
    ASTNode* parseExpression();

    ASTNode* parseStatement();
    ASTNode* parseDeclaration();
    ASTNode* parseFunctionDeclaration();

    // Error Handling
    void reportError(const std::string& message);

    public:
        Parser(std::vector<Token>&);

        // Main parse function
        ASTNode* parse();
};

#endif  