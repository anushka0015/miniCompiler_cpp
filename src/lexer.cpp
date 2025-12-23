#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input) : input(input), pos(0) {}

Token Lexer::getNextToken() {
    // Skip whitespace
    while (pos < input.length() && isspace(input[pos]))
        pos++;

    if (pos >= input.length())
        return {TokenType::END, ""};

    // ---------- IDENTIFIERS & KEYWORDS ----------
    if (isalpha(input[pos])) {
        std::string word;
        while (pos < input.length() && isalnum(input[pos]))
            word += input[pos++];

        // Keywords
        if (word == "if")   return {TokenType::KEYWORD_IF, word};
        if (word == "else") return {TokenType::KEYWORD_ELSE, word};
        if (word == "while") return {TokenType::KEYWORD_WHILE, word};
        if (word == "break") return {TokenType::KEYWORD_BREAK, word};
        if (word == "true")  return {TokenType::KEYWORD_TRUE, word};
        if (word == "false") return {TokenType::KEYWORD_FALSE, word};
        if (word == "print") return {TokenType::KEYWORD_PRINT, word};


        // Normal identifier
        return {TokenType::IDENTIFIER, word};
    }

    // ---------- NUMBERS ----------
    if (isdigit(input[pos])) {
        std::string num;
        while (pos < input.length() && isdigit(input[pos]))
            num += input[pos++];
        return {TokenType::NUMBER, num};
    }

    // ---------- SYMBOLS & OPERATORS ----------
    char ch = input[pos++];

    // ==
    if (ch == '=' && pos < input.length() && input[pos] == '=') {
        pos++;
        return {TokenType::EQUAL_EQUAL, "=="};
    }

    // =
    if (ch == '=') return {TokenType::ASSIGN, "="};

    // Arithmetic operators
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return {TokenType::OPERATOR, std::string(1, ch)};

    // Comparison operators
    if (ch == '>') return {TokenType::GREATER, ">"};
    if (ch == '<') return {TokenType::LESS, "<"};

    // Braces
    if (ch == '{') return {TokenType::LBRACE, "{"};
    if (ch == '}') return {TokenType::RBRACE, "}"};

    if (ch == '(') return {TokenType::LPAREN, "("};
    if (ch == ')') return {TokenType::RPAREN, ")"};


    // Semicolon
    if (ch == ';') return {TokenType::SEMICOLON, ";"};

    // Unknown character
    return {TokenType::END, ""};
}
