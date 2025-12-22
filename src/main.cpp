#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "tac.h"

int main() {
    std::string code = "a = 10 + 20;";
    Lexer lexer(code);
    Parser parser(lexer);

    auto ast = parser.parseStatement();

    TACGenerator tac;
    tac.generate(*ast);
    tac.print();

    return 0;
}

