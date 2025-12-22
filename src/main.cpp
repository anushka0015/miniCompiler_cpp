#include <iostream>
#include "lexer.h"

int main() {
    std::string code = "a = 10 + 20;";
    Lexer lexer(code);

    Token token;
    do {
        token = lexer.getNextToken();
        std::cout << token.value << std::endl;
    } while (token.type != TokenType::END);

    return 0;
}
