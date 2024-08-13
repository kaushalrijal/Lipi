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
        {TokenType::PRINT, std::regex("bhana")},
        {TokenType::INPUT, std::regex("suna")},
        {TokenType::TYPE, std::regex("purna|dasa|akshar|paath|khali")},
        {TokenType::IF, std::regex("yadi")},
        {TokenType::ELSE, std::regex("anyatha")},
        {TokenType::WHILE, std::regex("jabasamma")},
        {TokenType::FOR, std::regex("lagi")},
        {TokenType::FUNC_DEF, std::regex("kaam")},
        {TokenType::RETURN, std::regex("firta")},
        {TokenType::NUMBER, std::regex("\\d+(\\.\\d*)?")},
        {TokenType::STRING, std::regex("\"[^\"]*\"")},
        {TokenType::CHAR, std::regex("'[^']'")},
        {TokenType::ID, std::regex("[a-zA-Z_][a-zA-Z0-9_]*")},
        {TokenType::ASSIGN, std::regex("=")},
        {TokenType::END, std::regex(";")},
        {TokenType::LPAREN, std::regex("\\(")},
        {TokenType::RPAREN, std::regex("\\)")},
        {TokenType::LBRACE, std::regex("\\{")},
        {TokenType::RBRACE, std::regex("\\}")},
        {TokenType::OP, std::regex("[+\\-*/]")},
        {TokenType::SKIP, std::regex("[ \t]+")},
        {TokenType::NEWLINE, std::regex("\n")},
        {TokenType::MISMATCH, std::regex(".")}
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

    tokens.push_back({END_OF_FILE, ""});

    return tokens;
}