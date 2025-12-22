#include <iostream>
#include "lexer.h"
#include "parser.h"

void printExpr(const Expr* expr) {
    if (auto num = dynamic_cast<const NumberExpr*>(expr)) {
        std::cout << num->value;
    } else if (auto var = dynamic_cast<const VariableExpr*>(expr)) {
        std::cout << var->name;
    } else if (auto bin = dynamic_cast<const BinaryExpr*>(expr)) {
        std::cout << "(";
        printExpr(bin->left.get());
        std::cout << " " << bin->op << " ";
        printExpr(bin->right.get());
        std::cout << ")";
    }
}

int main() {
    std::string code = "a = 10 + 20;";
    Lexer lexer(code);
    Parser parser(lexer);

    auto ast = parser.parseStatement();

    std::cout << ast->variable << " = ";
    printExpr(ast->expression.get());
    std::cout << std::endl;

    return 0;
}
