#include "parser.h"
#include <iostream>
#include <cstdlib>

Parser::Parser(Lexer& lexer) : lexer(lexer) {
    currentToken = lexer.getNextToken();
}

void Parser::eat(TokenType type) {
    if (currentToken.type == type)
        currentToken = lexer.getNextToken();
    else {
        std::cerr << "Syntax Error\n";
        exit(1);
    }
}

// ---------- Expressions ----------

std::unique_ptr<Expr> Parser::parseTerm() {

    if (currentToken.type == TokenType::NUMBER) {
        int value = std::stoi(currentToken.value);
        eat(TokenType::NUMBER);
        return std::make_unique<NumberExpr>(value);
    }

    if (currentToken.type == TokenType::KEYWORD_TRUE) {
        eat(TokenType::KEYWORD_TRUE);
        return std::make_unique<BooleanExpr>(true);
    }

    if (currentToken.type == TokenType::KEYWORD_FALSE) {
        eat(TokenType::KEYWORD_FALSE);
        return std::make_unique<BooleanExpr>(false);
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

std::unique_ptr<Expr> Parser::parseCondition() {
    auto left = parseTerm();

    if (currentToken.type == TokenType::GREATER ||
        currentToken.type == TokenType::LESS ||
        currentToken.type == TokenType::EQUAL_EQUAL) {

        std::string op = currentToken.value;
        eat(currentToken.type);
        auto right = parseTerm();
        return std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
    }

    return left;
}

// ---------- Statements ----------
std::unique_ptr<ASTNode> Parser::parseAssignment() {
    std::string var = currentToken.value;
    eat(TokenType::IDENTIFIER);
    eat(TokenType::ASSIGN);
    auto expr = parseExpression();
    eat(TokenType::SEMICOLON);
    return std::make_unique<Assignment>(var, std::move(expr));
}

std::unique_ptr<ASTNode> Parser::parseIfStatement() {
    eat(TokenType::KEYWORD_IF);
    eat(TokenType::LBRACE);
    auto condition = parseCondition();
    eat(TokenType::RBRACE);

    eat(TokenType::LBRACE);
    auto thenStmt = parseStatement();
    eat(TokenType::RBRACE);

    std::unique_ptr<ASTNode> elseStmt = nullptr;

    // else or else-if
    if (currentToken.type == TokenType::KEYWORD_ELSE) {
        eat(TokenType::KEYWORD_ELSE);

        // else if
        if (currentToken.type == TokenType::KEYWORD_IF) {
            elseStmt = parseIfStatement();  // 🔥 recursion
        }
        // else block
        else {
            eat(TokenType::LBRACE);
            elseStmt = parseStatement();
            eat(TokenType::RBRACE);
        }
    }

    return std::make_unique<IfStatement>(
        std::move(condition),
        std::move(thenStmt),
        std::move(elseStmt)
    );
}



std::unique_ptr<ASTNode> Parser::parseWhileStatement() {
    eat(TokenType::KEYWORD_WHILE);
    eat(TokenType::LBRACE);
    auto condition = parseCondition();
    eat(TokenType::RBRACE);

    eat(TokenType::LBRACE);
    auto body = parseStatement();
    eat(TokenType::RBRACE);

    return std::make_unique<WhileStatement>(
        std::move(condition),
        std::move(body)
    );
}

std::unique_ptr<ASTNode> Parser::parseBreakStatement() {
    eat(TokenType::KEYWORD_BREAK);
    eat(TokenType::SEMICOLON);
    return std::make_unique<BreakStatement>();
}


std::unique_ptr<ASTNode> Parser::parseStatement() {
    if (currentToken.type == TokenType::KEYWORD_IF)
        return parseIfStatement();

    if (currentToken.type == TokenType::KEYWORD_WHILE)
        return parseWhileStatement();

    if (currentToken.type == TokenType::KEYWORD_BREAK)
        return parseBreakStatement();

    return parseAssignment();
}


// ---------- Program ----------
std::unique_ptr<Program> Parser::parseProgram() {
    auto program = std::make_unique<Program>();

    while (currentToken.type != TokenType::END) {
        program->statements.push_back(parseStatement());
    }

    return program;
}
