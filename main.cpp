#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "lexer.hpp"
#include "parser.hpp"
#include "semantic_analyzer.hpp"
#include "code_generator.hpp"

int main(int argc, char** argv){
    if(argc<2){
        std::cerr << "Arguments list cannot be empty.";
    }
    
    std::ifstream inf(argv[1]);

    if(inf.fail()){
        std::cerr << "Failed to open file " << argv[1];
    }

    std::stringstream buffer;
    buffer << inf.rdbuf();
    std::string code = buffer.str();

    std::cout << code << std::endl;

    try{

    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    std::cout << "This should printing before initialization of parser\n";

    Parser parser(tokens);

    std::cout << "This should print before parse function is called\n";
    ASTNode* root = parser.parse();

    std::cout << "This should print after the parse function!";
    root->print();

    SemanticAnalyzer semanticAnalyzer;
    semanticAnalyzer.analyze(root);

    CodeGenerator codeGenerator;
    std::string gen = codeGenerator.generate(root);

    std::cout << "Generated Code:\n" << gen << std::endl;

    } catch(std::runtime_error){
        std::cout << "someone threw a fucking runtime error!\n";
    }

    return 0;
}