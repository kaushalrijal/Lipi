#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

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

    std::stringstream buffer;
    buffer << inf.rdbuf();
    std::string code = buffer.str();

    std::cout << code << std::endl;


    return 0;
}