#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include <unordered_map>
#include <string>

class Interpreter {
public:
    void execute(const ASTNode& node);

private:
    std::unordered_map<std::string, int> variables;

    int evalExpr(const Expr* expr);
    bool evalCondition(const Expr* expr);
};

#endif
