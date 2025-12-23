#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
  std::string code =
    "a = 1;"
    "while { false } {"
    "a = a + 1;"
    "}";




    Lexer lexer(code);
    Parser parser(lexer);

    auto program = parser.parseProgram();

    Interpreter interpreter;
    interpreter.execute(*program);

    return 0;
}