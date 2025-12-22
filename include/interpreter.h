#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include <unordered_map>
#include <string>

class Interpreter {
public:
    void execute(const Assignment& stmt);

private:
    std::unordered_map<std::string, int> variables;

    int evalExpr(const Expr* expr);
};

#endif
