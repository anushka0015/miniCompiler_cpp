#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
  std::string code =
    "a = 10;"
    "print(a);";





    Lexer lexer(code);
    Parser parser(lexer);

    auto program = parser.parseProgram();

    Interpreter interpreter;
    interpreter.execute(*program);

    return 0;
}