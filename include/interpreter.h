#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

class Interpreter {
public:
    void execute(const ASTNode& node);

private:
    std::unordered_map<std::string, int> variables;
    std::unordered_set<std::string> initialized;

    int evalExpr(const Expr* expr);
    bool evalCondition(const Expr* expr);

    void semanticError(const std::string& message);
};

#endif
