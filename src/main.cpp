#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
    std::string code =
    "if { 1 == 1 } {"
    "b = 5;"
    "} else {"
    "b = 6;"
    "}"
    "c = b + 1;";


    Lexer lexer(code);
    Parser parser(lexer);

    auto program = parser.parseProgram();

    Interpreter interpreter;
    interpreter.execute(*program);

    return 0;
}