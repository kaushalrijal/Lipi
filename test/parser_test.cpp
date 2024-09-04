#include <iostream>
#include <vector>
#include "lexer.hpp"
#include "parser.hpp"
#include "ast.hpp"

void printAST(ASTNode* node, int indent = 0) {
    if (!node) return;
    for (int i = 0; i < indent; ++i) std::cout << "  ";
    node->print();
    std::cout << std::endl;


    if (auto block = dynamic_cast<BlockStatement*>(node)) {
        for (auto child : block->nodes) {
            printAST(child, indent + 1);
        }
    } else if (auto func = dynamic_cast<FunctionDeclaration*>(node)) {
        printAST(func->body, indent + 1);
    }
}

int main() {

    std::string sourceCode = R"(
        purna x;
        x = 42;
        bhana("dai van dai");
        yadi (x > 10) {
            x = x + 1;
        }
    )";


    Lexer lexer(sourceCode);


    std::vector<Token> tokens = lexer.tokenize();


    Parser parser(tokens);


    ASTNode* ast = parser.parse();


    printAST(ast);


    delete ast;

    return 0;
}