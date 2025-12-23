#include "interpreter.h"
#include <iostream>
#include <cstdlib>

void Interpreter::semanticError(const std::string& message) {
    std::cerr << "Semantic Error: " << message << std::endl;
    exit(1);
}

void Interpreter::enterScope() {
    scopes.push_back({});
    initialized.push_back({});
}

void Interpreter::exitScope() {
    scopes.pop_back();
    initialized.pop_back();
}

int Interpreter::evalExpr(const Expr* expr) {
    if (auto num = dynamic_cast<const NumberExpr*>(expr))
        return num->value;

    if (auto var = dynamic_cast<const VariableExpr*>(expr)) {
        for (int i = scopes.size() - 1; i >= 0; --i) {
            if (initialized[i].count(var->name))
                return scopes[i][var->name];
        }
        semanticError("Variable '" + var->name + "' used before initialization");
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

    // ---------- Program (global scope) ----------
    if (auto program = dynamic_cast<const Program*>(&node)) {
        enterScope();  // global scope
        for (const auto& stmt : program->statements)
            execute(*stmt);
        exitScope();
        return;
    }

    // ---------- Assignment ----------
    if (auto assign = dynamic_cast<const Assignment*>(&node)) {

        // Redeclaration check (same scope)
        if (initialized.back().count(assign->variable)) {
            semanticError("Variable '" + assign->variable + "' redeclared in same scope");
        }

        int value = evalExpr(assign->expression.get());
        scopes.back()[assign->variable] = value;
        initialized.back().insert(assign->variable);

        std::cout << assign->variable << " = " << value << std::endl;
        return;
    }

    // ---------- If statement (ELSE OPTIONAL) ----------
    if (auto ifStmt = dynamic_cast<const IfStatement*>(&node)) {
        enterScope();

        if (evalCondition(ifStmt->condition.get())) {
            execute(*ifStmt->thenBranch);
        }
        else if (ifStmt->elseBranch) {   // ⭐ THIS IS THE KEY CHANGE
            execute(*ifStmt->elseBranch);
        }

        exitScope();
        return;
    }

    // ---------- While loop ----------
    if (auto whileStmt = dynamic_cast<const WhileStatement*>(&node)) {
        enterScope();
        while (evalCondition(whileStmt->condition.get())) {
            execute(*whileStmt->body);
        }
        exitScope();
        return;
    }
}


