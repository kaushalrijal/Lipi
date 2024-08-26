#include"lexer.hpp"
#include<regex>
#include <iostream>


Lexer::Lexer(const std::string& in) : input(in) {}

void printToken(Token token){
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
        case TokenType::COMMA: typeStr = "COMMA"; break;
        case TokenType::ADD: typeStr =  "+"; break;
        case TokenType::SUB: typeStr =  "-"; break;
        case TokenType::MUL: typeStr =  "*"; break;
        case TokenType::DIV: typeStr =  "/"; break;
        case TokenType::MOD: typeStr =  "%"; break;
        case TokenType::AND: typeStr =  "&&"; break;
        case TokenType::OR: typeStr =  "||"; break;
        case TokenType::NOT: typeStr =  "!"; break;
        case TokenType::EQ: typeStr =  "=="; break;
        case TokenType::NEQ: typeStr =  "!="; break;
        case TokenType::LT: typeStr =  "<"; break;
        case TokenType::GT: typeStr =  ">"; break;
        case TokenType::LE: typeStr =  "<="; break;
        case TokenType::GE: typeStr =  ">="; break;
        case TokenType::TRUE: typeStr = "TRUE"; break;
        case TokenType::FALSE: typeStr = "FALSE"; break;
        case TokenType::SKIP: typeStr = "SKIP"; break;
        case TokenType::NEWLINE: typeStr = "NEWLINE"; break;
        case TokenType::COMMENT: typeStr = "COMMENT"; break;
        case TokenType::MISMATCH: typeStr = "MISMATCH"; break;
        case TokenType::END_OF_FILE: typeStr = "END OF FILE"; break;
    }
    std::cout << typeStr << ": " << token.value << std::endl;
}

std::string printTokenType(TokenType type){
    std::string typeStr;
    switch (type) {
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
        case TokenType::COMMA: typeStr = "COMMA"; break;
        case TokenType::ADD: typeStr =  "+"; break;
        case TokenType::SUB: typeStr =  "-"; break;
        case TokenType::MUL: typeStr =  "*"; break;
        case TokenType::DIV: typeStr =  "/"; break;
        case TokenType::MOD: typeStr =  "%"; break;
        case TokenType::AND: typeStr =  "&&"; break;
        case TokenType::OR: typeStr =  "||"; break;
        case TokenType::NOT: typeStr =  "!"; break;
        case TokenType::EQ: typeStr =  "=="; break;
        case TokenType::NEQ: typeStr =  "!="; break;
        case TokenType::LT: typeStr =  "<"; break;
        case TokenType::GT: typeStr =  ">"; break;
        case TokenType::LE: typeStr =  "<="; break;
        case TokenType::GE: typeStr =  ">="; break;
        case TokenType::TRUE: typeStr = "TRUE"; break;
        case TokenType::FALSE: typeStr = "FALSE"; break;
        case TokenType::SKIP: typeStr = "SKIP"; break;
        case TokenType::NEWLINE: typeStr = "NEWLINE"; break;
        case TokenType::COMMENT: typeStr = "COMMENT"; break;
        case TokenType::MISMATCH: typeStr = "MISMATCH"; break;
        case TokenType::END_OF_FILE: typeStr = "END OF FILE"; break;
    }
    return typeStr;
}

std::vector<Token> Lexer::tokenize(){
    std::vector<Token> tokens;
    std::string::const_iterator start = input.begin();
    std::string::const_iterator end = input.end();
    std::smatch match;

    //regex for different token types
    const std::vector<std::pair<TokenType, std::regex>> tokenPatterns = {
        {PRINT, std::regex("bhana")},
        {INPUT, std::regex("suna")},
        {TYPE,  std::regex("purna|dasa|akshar|paath|khali")},
        {IF, std::regex("yadi")},
        {ELSE, std::regex("anyatha")},
        {WHILE, std::regex("jabasamma")},
        {FOR, std::regex("lagi")},
        {FUNC_DEF, std::regex("kaam")},
        {RETURN, std::regex("firta")},
        {TRUE, std::regex("thik")},
        {FALSE, std::regex("bethik")},
        {NUMBER, std::regex("\\d+(\\.\\d*)?")},
        {STRING, std::regex("\"[^\"]*\"")},
        {CHAR, std::regex("'[^']'")},
        {ID, std::regex("[a-zA-Z_][a-zA-Z0-9_]*")},
        {END, std::regex(";")},
        {LPAREN, std::regex("\\(")},
        {RPAREN, std::regex("\\)")},
        {LBRACE, std::regex("\\{")},
        {RBRACE, std::regex("\\}")},
        {COMMA, std::regex(",")},
        {ADD, std::regex("\\+")},
        {SUB, std::regex("\\-")},
        {MUL, std::regex("\\*")},
        {DIV, std::regex("\\/")},
        {MOD, std::regex("%")},
        {AND, std::regex("&&")},
        {OR, std::regex("\\|\\|")},
        {EQ, std::regex("==")},
        {NEQ, std::regex("!=")},
        {LT, std::regex("<")},
        {GT, std::regex(">")},
        {LE, std::regex("<=")},
        {GE, std::regex(">=")},
        {ASSIGN, std::regex("=")},
        {NOT, std::regex("!")},
        {SKIP, std::regex("[ \t]+")},
        {NEWLINE, std::regex("\n")},
        {MISMATCH, std::regex(".")}
    };

    //check for match adn create tokens as per
    while (start != end) {
        bool matched = false;

        for (const auto &pattern : tokenPatterns) {
            if (std::regex_search(start, end, match, pattern.second, std::regex_constants::match_continuous)) {
                if (pattern.first != TokenType::SKIP) {
                    tokens.push_back({pattern.first, match.str()});
                }
                start = match[0].second;
                matched = true;
                break;
            }
        }

        if (!matched) {
            throw std::runtime_error("Unexpected character: " + std::string(1, *start));
        }
    }

    
    tokens.push_back({END_OF_FILE, "END OF FILE"});

    return tokens;
}