#include "interpreter.h"
#include <iostream>
#include <cstdlib>

void Interpreter::semanticError(const std::string& message) {
    std::cerr << "Semantic Error: " << message << std::endl;
    exit(1);
}

int Interpreter::evalExpr(const Expr* expr) {
    if (auto num = dynamic_cast<const NumberExpr*>(expr))
        return num->value;

    if (auto var = dynamic_cast<const VariableExpr*>(expr)) {
        if (initialized.find(var->name) == initialized.end()) {
            semanticError("Variable '" + var->name + "' used before initialization");
        }
        return variables[var->name];
    }

    if (auto bin = dynamic_cast<const BinaryExpr*>(expr)) {
        int left = evalExpr(bin->left.get());
        int right = evalExpr(bin->right.get());

        if (bin->op == "+") return left + right;
        if (bin->op == "-") return left - right;
        if (bin->op == "*") return left * right;

        if (bin->op == "/") {
            if (right == 0)
                semanticError("Division by zero");
            return left / right;
        }
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

    semanticError("Invalid condition expression");
    return false;
}

void Interpreter::execute(const ASTNode& node) {
    if (auto assign = dynamic_cast<const Assignment*>(&node)) {
        int value = evalExpr(assign->expression.get());
        variables[assign->variable] = value;
        initialized.insert(assign->variable);
        std::cout << assign->variable << " = " << value << std::endl;
    }

    else if (auto ifStmt = dynamic_cast<const IfStatement*>(&node)) {
        if (evalCondition(ifStmt->condition.get()))
            execute(*ifStmt->thenBranch);
        else
            execute(*ifStmt->elseBranch);
    }

    else if (auto whileStmt = dynamic_cast<const WhileStatement*>(&node)) {
        while (evalCondition(whileStmt->condition.get())) {
            execute(*whileStmt->body);
        }
    }

    else if (auto program = dynamic_cast<const Program*>(&node)) {
        for (const auto& stmt : program->statements)
            execute(*stmt);
    }
}


