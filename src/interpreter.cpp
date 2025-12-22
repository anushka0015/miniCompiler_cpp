#include "interpreter.h"
#include <iostream>

int Interpreter::evalExpr(const Expr* expr) {
    if (auto num = dynamic_cast<const NumberExpr*>(expr)) {
        return num->value;
    }

    if (auto var = dynamic_cast<const VariableExpr*>(expr)) {
        return variables[var->name];
    }

    if (auto bin = dynamic_cast<const BinaryExpr*>(expr)) {
        int left = evalExpr(bin->left.get());
        int right = evalExpr(bin->right.get());

        if (bin->op == "+") return left + right;
        if (bin->op == "-") return left - right;
        if (bin->op == "*") return left * right;
        if (bin->op == "/") return left / right;
    }

    return 0;
}

bool Interpreter::evalCondition(const Expr* expr) {
    auto bin = dynamic_cast<const BinaryExpr*>(expr);
    int left = evalExpr(bin->left.get());
    int right = evalExpr(bin->right.get());

    if (bin->op == ">") return left > right;
    if (bin->op == "<") return left < right;
    if (bin->op == "==") return left == right;

    return false;
}

void Interpreter::execute(const ASTNode& node) {
    if (auto assign = dynamic_cast<const Assignment*>(&node)) {
        int value = evalExpr(assign->expression.get());
        variables[assign->variable] = value;
        std::cout << assign->variable << " = " << value << std::endl;
    }

    else if (auto ifStmt = dynamic_cast<const IfStatement*>(&node)) {
        if (evalCondition(ifStmt->condition.get())) {
            execute(*ifStmt->thenBranch);
        } else {
            execute(*ifStmt->elseBranch);
        }
    }
}
