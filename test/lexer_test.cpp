#include <iostream>
#include <lexer.hpp>
#include <vector>

void printTokens(const std::vector<Token> &tokens) {
    for (const auto &token : tokens) {
        std::string typeStr;
        switch (token.type) {
            case TokenType::PRINT: typeStr = "PRINT"; break;
            case TokenType::INPUT: typeStr = "INPUT"; break;
            case TokenType::TYPE: typeStr = "TYPE"; break;
            case TokenType::IF: typeStr = "IF"; break;
            case TokenType::ELSE: typeStr = "ELSE"; break;
            case TokenType::WHILE: typeStr = "WHILE"; break;
            case TokenType::FOR: typeStr = "FOR"; break;
            case TokenType::FUNC_DEF: typeStr = "FUNC_DEF"; break;
            case TokenType::RETURN: typeStr = "RETURN"; break;
            case TokenType::NUMBER: typeStr = "NUMBER"; break;
            case TokenType::STRING: typeStr = "STRING"; break;
            case TokenType::CHAR: typeStr = "CHAR"; break;
            case TokenType::ID: typeStr = "ID"; break;
            case TokenType::ASSIGN: typeStr = "ASSIGN"; break;
            case TokenType::END: typeStr = "END"; break;
            case TokenType::LPAREN: typeStr = "LPAREN"; break;
            case TokenType::RPAREN: typeStr = "RPAREN"; break;
            case TokenType::LBRACE: typeStr = "LBRACE"; break;
            case TokenType::RBRACE: typeStr = "RBRACE"; break;
            case TokenType::OP: typeStr = "OP"; break;
            case TokenType::SKIP: typeStr = "SKIP"; break;
            case TokenType::NEWLINE: typeStr = "NEWLINE"; break;
            case TokenType::MISMATCH: typeStr = "MISMATCH"; break;
            case TokenType::END_OF_FILE: typeStr = "END OF FILE"; break;
        }
        std::cout << typeStr << ": " << token.value << std::endl;
    }
}


int main() {
    std::string sourceCode;

    std::getline(std::cin, sourceCode);

    // Initialize the lexer with the source code
    Lexer lexer(sourceCode);

    // Tokenize the source code
    auto tokens = lexer.tokenize();
    printTokens(tokens);

    return 0;
}
