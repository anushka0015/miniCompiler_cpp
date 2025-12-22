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

void Interpreter::execute(const Assignment& stmt) {
    int value = evalExpr(stmt.expression.get());
    variables[stmt.variable] = value;

    std::cout << stmt.variable << " = " << value << std::endl;
}
