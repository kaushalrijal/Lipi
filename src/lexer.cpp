#include"lexer.hpp"
#include<regex>
#include <iostream>


Lexer::Lexer(const std::string& in) : input(in) {}

std::vector<Token> Lexer::tokenize(){
    std::vector<Token> tokens;
    std::string remainingInput = input;
    std::smatch match;

    //regex for different token types
    std::regex keyword_regex(R"(\b(bhana|suna|yadi|anyatha|jabasamma|kaam|firta|lagi|purna|dasa|akshar|paath|thik|galat)\b)");
    std::regex string_regex(R"("(\\.|[^"])*")");
    std::regex identifier_regex(R"([a-zA-Z_][a-zA-Z0-9_]*)");
    std::regex integer_regex(R"(\d+)");
    std::regex float_regex(R"([-+]?[0-9]*\.[0-9]+)");
    std::regex char_regex(R"('(.)')");
    std::regex operator_regex(R"([+\-*/%=<>!&|])");
    std::regex delimiter_regex(R"([(){}|;])");
    std::regex whitespace_regex(R"(^\s+)");
    std::regex multiline_comment_regex(R"(\(:.*?\:\))");
    std::regex single_line_comment_regex(R"(\:\)[^\n]*$)");


    //check for match adn create tokens as per
   while (!remainingInput.empty()) {
        // Handle comments
        if (std::regex_search(remainingInput, match, multiline_comment_regex)) {
            remainingInput.erase(match.position(), match.length());
            continue;
        }

        // Single Line comments
        if (std::regex_search(remainingInput, match, single_line_comment_regex)) {
            remainingInput.erase(match.position(), match.length());
            continue;
        }

        // Match and handle each token type
        if (std::regex_search(remainingInput, match, string_regex)) {
            tokens.push_back({TokenType::STRING, match[0]});
            remainingInput.erase(match.position(), match.length());
        } 
        // Handle whitespace
        if (std::regex_search(remainingInput, match, whitespace_regex)) {
            remainingInput.erase(match.position(), match.length());
            continue;
        }
        
        if (std::regex_search(remainingInput, match, keyword_regex)) {
            tokens.push_back({TokenType::KEYWORD, match[0]});
            remainingInput.erase(match.position(), match.length());
        } 
        
        if (std::regex_search(remainingInput, match, identifier_regex)) {
            tokens.push_back({TokenType::IDENTIFIER, match[0]});
            remainingInput.erase(match.position(), match.length());
        } 
        
        if (std::regex_search(remainingInput, match, integer_regex)) {
            tokens.push_back({TokenType::NUMBER, match[0]});
            remainingInput.erase(match.position(), match.length());
        } 
        
        if (std::regex_search(remainingInput, match, float_regex)) {
            tokens.push_back({TokenType::NUMBER, match[0]});
            remainingInput.erase(match.position(), match.length());
        } 
        
        if (std::regex_search(remainingInput, match, char_regex)) {
            tokens.push_back({TokenType::AKSHAR, match[1]});
            remainingInput.erase(match.position(), match.length());
        } 
        
        if (std::regex_search(remainingInput, match, operator_regex)) {
            tokens.push_back({TokenType::OPERATOR, match[0]});
            remainingInput.erase(match.position(), match.length());
        } 
        
        if (std::regex_search(remainingInput, match, delimiter_regex)) {
            std::string delimiter = match[0];
            if (delimiter == "(") {
                tokens.push_back({TokenType::LEFT_PAREN, "("});
            } else if (delimiter == ")") {
                tokens.push_back({TokenType::RIGHT_PAREN, ")"});
            } else if (delimiter == "{") {
                tokens.push_back({TokenType::LEFT_BRACE, "{"});
            } else if (delimiter == "}") {
                tokens.push_back({TokenType::RIGHT_BRACE, "}"});
            } else if (delimiter == ";") {
                tokens.push_back({TokenType::SEMICOLON, ";"});
            }
            remainingInput.erase(match.position(), match.length());
        } else {
            std::cerr << "Unexpected input: " << remainingInput[0] << std::endl;
            // Handle unexpected input or continue
            remainingInput.erase(0, 1); // Or adjust to continue processing
        }
    }
    
    return tokens;
}