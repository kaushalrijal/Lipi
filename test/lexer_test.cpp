#include <iostream>
#include "lexer.hpp"

int main() {
    std::string code;
    std::cout << "Enter code: ";

    std::getline(std::cin, code);

    Lexer lexer(code);
    
    std::vector<Token> tokens = lexer.tokenize();
    
    for (const Token& token : tokens) {
        std::cout << token.type << ": " << token.value << std::endl;
    }


    return 0;
}