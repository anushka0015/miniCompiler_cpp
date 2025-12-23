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

void Interpreter::printSymbolTable() {
    std::cout << "\n--- SYMBOL TABLE ---\n";
    for (size_t i = 0; i < scopes.size(); ++i) {
        std::cout << "Scope " << i;
        if (i == 0) std::cout << " (global)";
        std::cout << ":\n";

        for (const auto& pair : scopes[i]) {
            std::cout << "  " << pair.first << " = " << pair.second << "\n";
        }
    }
    std::cout << "--------------------\n";
}

int Interpreter::evalExpr(const Expr* expr) {
    if (auto b = dynamic_cast<const BooleanExpr*>(expr))
        return b->value ? 1 : 0;

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
    if (auto b = dynamic_cast<const BooleanExpr*>(expr))
        return b->value;

    if (auto bin = dynamic_cast<const BinaryExpr*>(expr)) {
        int left = evalExpr(bin->left.get());
        int right = evalExpr(bin->right.get());

        if (bin->op == ">") return left > right;
        if (bin->op == "<") return left < right;
        if (bin->op == "==") return left == right;
    }

    semanticError("Invalid condition expression");
    return false;
}

void Interpreter::execute(const ASTNode& node) {

    // ---------- Program ----------
    if (auto program = dynamic_cast<const Program*>(&node)) {
        enterScope();  // global
        for (const auto& stmt : program->statements)
            execute(*stmt);
        printSymbolTable();      // 🔍 final state
        exitScope();
        return;
    }

    // ---------- Assignment ----------
    if (auto assign = dynamic_cast<const Assignment*>(&node)) {
        int value = evalExpr(assign->expression.get());

        for (int i = scopes.size() - 1; i >= 0; --i) {
            if (initialized[i].count(assign->variable)) {
                scopes[i][assign->variable] = value;
                std::cout << assign->variable << " = " << value << std::endl;
                printSymbolTable();   // 🔍 debug
                return;
            }
        }

        scopes.back()[assign->variable] = value;
        initialized.back().insert(assign->variable);

        std::cout << assign->variable << " = " << value << std::endl;
        printSymbolTable();       // 🔍 debug
        return;
    }

    // ---------- Print ----------
    if (auto printStmt = dynamic_cast<const PrintStatement*>(&node)) {
        int value = evalExpr(printStmt->expression.get());
        std::cout << value << std::endl;
        printSymbolTable();       // 🔍 debug
        return;
    }

    // ---------- If ----------
    if (auto ifStmt = dynamic_cast<const IfStatement*>(&node)) {
        enterScope();

        if (evalCondition(ifStmt->condition.get()))
            execute(*ifStmt->thenBranch);
        else if (ifStmt->elseBranch)
            execute(*ifStmt->elseBranch);

        exitScope();
        return;
    }

    // ---------- Break ----------
    if (auto brk = dynamic_cast<const BreakStatement*>(&node)) {
        breakSignal = true;
        return;
    }

    // ---------- While ----------
    if (auto whileStmt = dynamic_cast<const WhileStatement*>(&node)) {
        while (evalCondition(whileStmt->condition.get())) {
            execute(*whileStmt->body);
            if (breakSignal) {
                breakSignal = false;
                break;
            }
        }
        return;
    }
}
