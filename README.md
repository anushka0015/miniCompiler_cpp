# Mini Compiler in C++

## 📌 Overview
This project is a mini compiler/interpreter implemented in C++ that demonstrates
core compiler design concepts including lexical analysis, parsing, abstract syntax
trees, semantic analysis, and execution.

The language supports variables, expressions, control flow, scopes, and debugging
through symbol table visualization.

---

## 🧱 Compiler Architecture

1. **Lexer**
   - Converts source code into tokens
   - Handles identifiers, numbers, keywords, operators, braces, parentheses

2. **Parser**
   - Recursive descent parser
   - Builds an Abstract Syntax Tree (AST)
   - Supports compound (block) statements

3. **AST (Abstract Syntax Tree)**
   - Represents program structure
   - Nodes for expressions, statements, blocks, loops, conditionals

4. **Interpreter**
   - Executes the AST
   - Manages scopes and symbol tables
   - Performs semantic checks

---

## ✨ Language Features

- Variable assignments
- Arithmetic expressions (`+ - * /`)
- Boolean literals (`true`, `false`)
- `if`, `else`, `else-if`
- `while` loops
- `break` statement
- `print(expression);`
- Compound blocks `{ statement* }`
- Nested scopes with shadowing
- Semantic error detection
- Symbol table debug visualization (optional)

---

## 🧪 Sample Program

```txt
a = 10;
if { a > 5 } {
    b = 20;
    print(b);
}
while { a > 0 } {
    print(a);
    a = a - 1;
}

