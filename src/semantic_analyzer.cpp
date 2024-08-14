#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "ast.hpp"
#include "symbol_table.hpp"
#include <string>

class SemanticAnalyzer{
    SymbolTable symbolTable;

    void analyzeStatement(Statement*);
    void analyzeExpression(Expression*);
    void checkType(Expression* , const std::string&);

    public:
        void analyze(ASTNode* root);
};

#endif
