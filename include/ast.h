#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include <vector>

// ---------- Base Node ----------
struct ASTNode {
    virtual ~ASTNode() = default;
};

// ---------- Expressions ----------
struct Expr : ASTNode {};

struct NumberExpr : Expr {
    int value;
    NumberExpr(int value) : value(value) {}
};

struct VariableExpr : Expr {
    std::string name;
    VariableExpr(const std::string& name) : name(name) {}
};

struct BinaryExpr : Expr {
    std::string op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(const std::string& op,
               std::unique_ptr<Expr> left,
               std::unique_ptr<Expr> right)
        : op(op), left(std::move(left)), right(std::move(right)) {}
};

// ---------- Statements ----------
struct Assignment : ASTNode {
    std::string variable;
    std::unique_ptr<Expr> expression;

    Assignment(const std::string& variable,
               std::unique_ptr<Expr> expression)
        : variable(variable), expression(std::move(expression)) {}
};

struct IfStatement : ASTNode {
    std::unique_ptr<Expr> condition;
    std::unique_ptr<ASTNode> thenBranch;
    std::unique_ptr<ASTNode> elseBranch;

    IfStatement(std::unique_ptr<Expr> condition,
                std::unique_ptr<ASTNode> thenBranch,
                std::unique_ptr<ASTNode> elseBranch)
        : condition(std::move(condition)),
          thenBranch(std::move(thenBranch)),
          elseBranch(std::move(elseBranch)) {}
};

struct WhileStatement : ASTNode {
    std::unique_ptr<Expr> condition;
    std::unique_ptr<ASTNode> body;

    WhileStatement(std::unique_ptr<Expr> condition,
                   std::unique_ptr<ASTNode> body)
        : condition(std::move(condition)),
          body(std::move(body)) {}
};

// ---------- Program ----------
struct Program : ASTNode {
    std::vector<std::unique_ptr<ASTNode>> statements;
};

#endif
