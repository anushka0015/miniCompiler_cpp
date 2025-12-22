#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
    Interpreter interpreter;

    {
        std::string code = "a = 20;";
        Lexer lexer(code);
        Parser parser(lexer);
        auto ast = parser.parseStatement();
        interpreter.execute(*ast);
    }

    {
        std::string code = "if { a > 10 } { b = 1; } else { b = 0; }";
        Lexer lexer(code);
        Parser parser(lexer);
        auto ast = parser.parseStatement();
        interpreter.execute(*ast);
    }

    return 0;
}




