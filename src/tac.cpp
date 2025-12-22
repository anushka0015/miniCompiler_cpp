#include "tac.h"
#include <iostream>

std::string TACGenerator::newTemp() {
    return "t" + std::to_string(++tempCount);
}

std::string TACGenerator::genExpr(const Expr* expr) {
    if (auto num = dynamic_cast<const NumberExpr*>(expr)) {
        return std::to_string(num->value);
    }

    if (auto var = dynamic_cast<const VariableExpr*>(expr)) {
        return var->name;
    }

    if (auto bin = dynamic_cast<const BinaryExpr*>(expr)) {
        std::string left = genExpr(bin->left.get());
        std::string right = genExpr(bin->right.get());
        std::string temp = newTemp();

        instructions.push_back({temp, left, bin->op, right});
        return temp;
    }

    return "";
}

std::vector<Instruction> TACGenerator::generate(const Assignment& stmt) {
    instructions.clear();
    tempCount = 0;

    std::string rhs = genExpr(stmt.expression.get());
    instructions.push_back({stmt.variable, rhs, "=", ""});

    return instructions;
}

void TACGenerator::print() const {
    for (const auto& inst : instructions) {
        if (inst.op == "=") {
            std::cout << inst.result << " = " << inst.arg1 << std::endl;
        } else {
            std::cout << inst.result << " = "
                      << inst.arg1 << " "
                      << inst.op << " "
                      << inst.arg2 << std::endl;
        }
    }
}
