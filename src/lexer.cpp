#include"lexer.hpp"
#include<regex>

std::vector<Token> Lexer::tokenize(){
    std::vector<Token> tokens;
    std::string remainingInput = input;

    //regex for different token types
    std::regex keyword_regex(R"(\b(bhana|suna|yadi|anyatha|jabasamma|kaam|firta|lagi|purna|dasa|akshar|paath|sahi|galat)\b)");
    std::regex string_regex(R"(^"(\\.|[^"])*"$)");
    std::regex identifier_regex(R"([a-zA-Z_][a-zA-Z0-9_]*)");
    std::regex integer_regex(R"(\d+)");
    std::regex float_regex(R"([-+]?[0-9]*\.[0-9]+)");
    std::regex char_regex(R"('(.)')");
    std::regex operator_regex(R"([+\-*/%=<>!&|])");
    std::regex delimiter_regex(R"([(){}|;])");
    std::regex whitespace_regex(R"(\s+)");

    
}