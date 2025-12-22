#include "optimizer.h"

std::unique_ptr<Expr> Optimizer::fold(std::unique_ptr<Expr> expr) {
    // If number or variable → nothing to optimize
    if (dynamic_cast<NumberExpr*>(expr.get()) ||
        dynamic_cast<VariableExpr*>(expr.get())) {
        return expr;
    }

    // If binary expression
    if (auto bin = dynamic_cast<BinaryExpr*>(expr.get())) {
        bin->left = fold(std::move(bin->left));
        bin->right = fold(std::move(bin->right));

        auto leftNum = dynamic_cast<NumberExpr*>(bin->left.get());
        auto rightNum = dynamic_cast<NumberExpr*>(bin->right.get());

        if (leftNum && rightNum) {
            int result = 0;

            if (bin->op == "+") result = leftNum->value + rightNum->value;
            else if (bin->op == "-") result = leftNum->value - rightNum->value;
            else if (bin->op == "*") result = leftNum->value * rightNum->value;
            else if (bin->op == "/") result = leftNum->value / rightNum->value;

            return std::make_unique<NumberExpr>(result);
        }
    }

    return expr;
}
