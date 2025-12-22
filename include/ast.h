#ifndef AST_H
#define AST_H

#include <string>
#include <memory>

// Base class
struct ASTNode {
    virtual ~ASTNode() = default;
};

// Expression base
struct Expr : ASTNode {};

// Number node
struct NumberExpr : Expr {
    int value;
    NumberExpr(int value) : value(value) {}
};

// Variable node
struct VariableExpr : Expr {
    std::string name;
    VariableExpr(const std::string& name) : name(name) {}
};

// Binary operation node
struct BinaryExpr : Expr {
    std::string op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(std::string op,
               std::unique_ptr<Expr> left,
               std::unique_ptr<Expr> right)
        : op(op), left(std::move(left)), right(std::move(right)) {}
};

// Assignment node
struct Assignment : ASTNode {
    std::string variable;
    std::unique_ptr<Expr> expression;

    Assignment(std::string variable, std::unique_ptr<Expr> expr)
        : variable(variable), expression(std::move(expr)) {}
};

#endif
