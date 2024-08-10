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
    std::regex multiline_comment_regex(R"(\(:.*?\:\))");
    std::regex single_line_comment_regex(R"(\:\)[^\n]*$)");

    //check for match adn create tokens as per
    while (!remainingInput.empty()) {
        std::smatch match;
        if (std::regex_match(remainingInput, match, whitespace_regex)) {
            remainingInput = match.suffix().str();
            continue;
        }

        if (std::regex_match(remainingInput, match, string_regex)) {
            tokens.push_back({Token::STRING, match[0]});
            remainingInput = match.suffix().str();
            continue;
        }

        if (std::regex_match(remainingInput, match, keyword_regex)) {
            tokens.push_back({Token::KEYWORD, match[0]});
            remainingInput = match.suffix().str();
            continue;
        }

        if (std::regex_match(remainingInput, match, identifier_regex)) {
            tokens.push_back({Token::IDENTIFIER, match[0]});
            remainingInput = match.suffix().str();
            continue;
        }

        if (std::regex_match(remainingInput, match, integer_regex)) {
            tokens.push_back({Token::PURNA, match[0]});
            remainingInput = match.suffix().str();
            continue;
        }

        if (std::regex_match(remainingInput, match, float_regex)) {
            tokens.push_back({Token::DASA, match[0]});
            remainingInput = match.suffix().str();
            continue;
        }

        if (std::regex_match(remainingInput, match, char_regex)) {
            tokens.push_back({Token::AKSHAR, match[1]});
            remainingInput = match.suffix().str();
            continue;
        }

        if (std::regex_match(remainingInput, match, operator_regex)) {
            tokens.push_back({Token::OPERATOR, match[0]});
            remainingInput = match.suffix().str();
            continue;
        }

        if (std::regex_match(remainingInput, match, delimiter_regex)) {
            if (match[0] == "(") {
                tokens.push_back({Token::LEFT_PAREN, "("});
            } else if (match[0] == ")") {
                tokens.push_back({Token::RIGHT_PAREN, ")"});
            } else if (match[0] == "{") {
                tokens.push_back({Token::LEFT_BRACE, "{"});
            } else if (match[0] == "}") {
                tokens.push_back({Token::RIGHT_BRACE, "}"});
            } else if (match[0] == ";") {
                tokens.push_back({Token::SEMICOLON, ";"});
            }
            remainingInput = match.suffix().str();
            continue;
        }

    }

    return tokens;
}