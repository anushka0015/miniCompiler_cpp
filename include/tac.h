#ifndef TAC_H
#define TAC_H

#include "ast.h"
#include <string>
#include <vector>

struct Instruction {
    std::string result;
    std::string arg1;
    std::string op;
    std::string arg2;
};

class TACGenerator {
public:
    std::vector<Instruction> generate(const Assignment& stmt);
    void print() const;

private:
    int tempCount = 0;
    std::vector<Instruction> instructions;

    std::string newTemp();
    std::string genExpr(const Expr* expr);
};

#endif
