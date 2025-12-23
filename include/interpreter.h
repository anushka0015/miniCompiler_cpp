#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

class Interpreter {
public:
    void execute(const ASTNode& node);

private:
    std::vector<std::unordered_map<std::string, int>> scopes;
    std::vector<std::unordered_set<std::string>> initialized;

    bool breakSignal = false;

    void enterScope();
    void exitScope();

    int evalExpr(const Expr* expr);
    bool evalCondition(const Expr* expr);

    void semanticError(const std::string& message);

    // 🔍 DEBUG
    void printSymbolTable();
};

#endif


