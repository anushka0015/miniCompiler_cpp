#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "optimizer.h"
#include "interpreter.h"

int main() {
    std::string code = "a = 10 + 20;";
    Lexer lexer(code);
    Parser parser(lexer);

    auto ast = parser.parseStatement();

    Optimizer optimizer;
    ast->expression = optimizer.fold(std::move(ast->expression));

    Interpreter interpreter;
    interpreter.execute(*ast);

    return 0;
}



