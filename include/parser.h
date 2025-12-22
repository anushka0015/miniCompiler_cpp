#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

class Parser {
public:
    Parser(Lexer& lexer);
    std::unique_ptr<Assignment> parseStatement();

private:
    Lexer& lexer;
    Token currentToken;

    void eat(TokenType type);
    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseTerm();
};

#endif
