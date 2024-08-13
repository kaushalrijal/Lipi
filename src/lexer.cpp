#include"lexer.hpp"
#include<regex>
#include <iostream>


Lexer::Lexer(const std::string& in) : input(in) {}

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
        {NUMBER, std::regex("\\d+(\\.\\d*)?")},
        {STRING, std::regex("\"[^\"]*\"")},
        {CHAR, std::regex("'[^']'")},
        {ID, std::regex("[a-zA-Z_][a-zA-Z0-9_]*")},
        {ASSIGN, std::regex("=")},
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

    return tokens;
}