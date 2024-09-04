#include "ast.hpp"
#include <iostream>

int main() {
    IntegerLiteral* intLit = new IntegerLiteral(42);
    FloatLiteral* floatLit = new FloatLiteral(3.14);
    StringLiteral* strLit = new StringLiteral("Hello, World!");
    BooleanLiteral* boolLit = new BooleanLiteral(true);

    Variable* var = new Variable("x");

    AssignmentStatement* assignStmt = new AssignmentStatement("x", intLit);

    PrintStatement* printStmt = new PrintStatement(strLit);

    std::vector<ASTNode*> blockNodes = {assignStmt, printStmt};
    BlockStatement* blockStmt = new BlockStatement(blockNodes);

    std::vector<ASTNode*> programNodes = {blockStmt};
    Program* program = new Program(programNodes);

    program->print();

    delete program;

    return 0;
}