#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include "ast.hpp"
#include <string>

class CodeGenerator {
public:
    std::string generate(ASTNode* root); // Main method to generate code from AST

private:
    std::string generateExpression(Expression* expr);
    std::string generateStatement(Statement* stmt);
    std::string generateDeclaration(Declaration* decl);
    std::string generateFunctionDeclaration(FunctionDeclaration* funcDecl);
};

#endif