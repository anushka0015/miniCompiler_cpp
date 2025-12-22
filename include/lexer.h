#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>

class Lexer {
public:
    Lexer(const std::string& input);
    Token getNextToken();

private:
    std::string input;
    size_t pos;
};

#endif
