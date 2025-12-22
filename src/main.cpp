#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
    std::string code = "a = 10 + 20;";
    Lexer lexer(code);
    Parser parser(lexer);

    auto ast = parser.parseStatement();

    Interpreter interpreter;
    interpreter.execute(*ast);

    return 0;
}


