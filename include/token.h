#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    IDENTIFIER,
    NUMBER,
    ASSIGN,
    OPERATOR,
    SEMICOLON,
    END
};

struct Token {
    TokenType type;
    std::string value;
};

#endif
