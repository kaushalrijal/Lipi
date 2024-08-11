#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "lexer.hpp"

class Parser {
public:
    Parser(Lexer& lexer);
    ~Parser();

    ASTNode* parseProgram();

private:
    Lexer& lexer_;
    Token currentToken_;

    void error(const std::string& message);
    Token getNextToken();
    Token peekNextToken();

    ASTNode* parseStatementList();
    ASTNode* parseStatement();
    ASTNode* parseBhanaStmt();
    ASTNode* parseSunaStmt();
    ASTNode* parseJabasammaLoop();
    ASTNode* parseLagiLoop();
    ASTNode* parseYadiStmt();
    ASTNode* parseAnyathaStmt();
    ASTNode* parseKaamDecl();
    ASTNode* parseFirtaStmt();
    ASTNode* parseExpression();
    ASTNode* parseTerm();
    ASTNode* parseFactor();
    ASTNode* parseVariable();
    ASTNode* parseNumber();
    ASTNode* parseString();

    // Helper functions for parsing specific syntax elements
    bool match(TokenType type);
    bool match(ASTNodeType type);
};

#endif  // PARSER_HPP