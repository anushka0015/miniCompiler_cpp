#include "parser.h"
#include <cstdlib>
#include <iostream>

Parser::Parser(Lexer& lexer) : lexer(lexer) {
    currentToken = lexer.getNextToken();
}

void Parser::eat(TokenType type) {
    if (currentToken.type == type) {
        currentToken = lexer.getNextToken();
    } else {
        std::cerr << "Syntax Error\n";
        exit(1);
    }
}

std::unique_ptr<Expr> Parser::parseTerm() {
    if (currentToken.type == TokenType::NUMBER) {
        int value = std::stoi(currentToken.value);
        eat(TokenType::NUMBER);
        return std::make_unique<NumberExpr>(value);
    }

    if (currentToken.type == TokenType::IDENTIFIER) {
        std::string name = currentToken.value;
        eat(TokenType::IDENTIFIER);
        return std::make_unique<VariableExpr>(name);
    }

    std::cerr << "Invalid term\n";
    exit(1);
}

std::unique_ptr<Expr> Parser::parseExpression() {
    auto left = parseTerm();

    while (currentToken.type == TokenType::OPERATOR) {
        std::string op = currentToken.value;
        eat(TokenType::OPERATOR);
        auto right = parseTerm();
        left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Assignment> Parser::parseStatement() {
    std::string var = currentToken.value;
    eat(TokenType::IDENTIFIER);
    eat(TokenType::ASSIGN);
    auto expr = parseExpression();
    eat(TokenType::SEMICOLON);

    return std::make_unique<Assignment>(var, std::move(expr));
}
