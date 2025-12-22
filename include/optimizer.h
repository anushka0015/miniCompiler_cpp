#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "ast.h"
#include <memory>

class Optimizer {
public:
    std::unique_ptr<Expr> fold(std::unique_ptr<Expr> expr);
};

#endif
