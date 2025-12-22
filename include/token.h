#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    IDENTIFIER,
    NUMBER,
    ASSIGN,
    OPERATOR,
    SEMICOLON,
    END,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_WHILE,
    LBRACE,
    RBRACE,
    GREATER,
    LESS,
    EQUAL_EQUAL,
};

struct Token {
    TokenType type;
    std::string value;
};

#endif
