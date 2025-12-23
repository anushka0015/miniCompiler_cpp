#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
   std::string code =
    "a = 20;"
    "if { a > 10 } {"
    "x = 1;"
    "} else if { a > 5 } {"
    "x = 2;"
    "}";



    Lexer lexer(code);
    Parser parser(lexer);

    auto program = parser.parseProgram();

    Interpreter interpreter;
    interpreter.execute(*program);

    return 0;
}