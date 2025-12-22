#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
    std::string code =
        "a = 20;"
        "b = 5;"
        "if { a > b } { c = a; } else { c = b; }";

    Lexer lexer(code);
    Parser parser(lexer);

    auto program = parser.parseProgram();

    Interpreter interpreter;
    interpreter.execute(*program);

    return 0;
}




