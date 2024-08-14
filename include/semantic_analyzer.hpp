#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "ast.hpp"
#include "symbol_table.hpp"
#include <string>

class SemanticAnalyzer{
    SymbolTable symbolTable;

    void analyzeNode(ASTNode* root);
    void analyzeStatement(Statement*);
    void analyzeExpression(Expression*);
    void analyzeDeclaration(Declaration*);
    void checkType(Expression*, VarType);

    public:
        void analyze(ASTNode* root);
};

#endif
