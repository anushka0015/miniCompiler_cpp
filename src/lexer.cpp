#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input) : input(input), pos(0) {}

Token Lexer::getNextToken() {
    while (pos < input.length() && isspace(input[pos]))
        pos++;

    if (pos >= input.length())
        return {TokenType::END, ""};

    if (isalpha(input[pos])) {
        std::string id;
        while (pos < input.length() && isalnum(input[pos]))
            id += input[pos++];
        return {TokenType::IDENTIFIER, id};
    }

    if (isdigit(input[pos])) {
        std::string num;
        while (pos < input.length() && isdigit(input[pos]))
            num += input[pos++];
        return {TokenType::NUMBER, num};
    }

    char ch = input[pos++];
    if (ch == '=') return {TokenType::ASSIGN, "="};
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return {TokenType::OPERATOR, std::string(1, ch)};
    if (ch == ';') return {TokenType::SEMICOLON, ";"};

    return {TokenType::END, ""};
}
