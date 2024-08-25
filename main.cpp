#include <fstream>
#include <iostream>
#include <vector>

#include "lexer.hpp"
// #include "parser.hpp"
// #include "semantic_analyzer.hpp"

int main(int argc, char** argv){
    if(argc<2){
        std::cerr << "Arguments list cannot be empty.";
    }
    
    std::ifstream inf(argv[1]);

    if(inf.fail()){
        std::cerr << "Failed to open file " << argv[1];
    }

    char ch[1000];

    std::string code;
    
    while(inf.eof()!=true){
        inf.getline(ch, 1000);
        code.append(ch);
    } 

    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();


    return 0;
}