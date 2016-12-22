#pragma once
#include <string>

/// @struct Expression - represents expression tree.
///  @fn CreateExpression - parses string to create expression,
///      can throw exception on parse error.
///  @fn CalculateExpression - visits expression tree nodes and calculates
///      expression result.
///  @fn DisposeExpression - removes expression tree from memory.

// BNF grammar for expression parsing:
// expression ::= add_sub_expr
// add_sub_expr ::= mul_div_expr '+' add_sub_expr
//     | mul_div_expr '-' add_sub_expr
//     | mul_div_expr
// mul_div_expr ::= atom_expr '*' mul_div_expr
//     | atom_expr '/' mul_div_expr
//     | atom_expr '%' mul_div_expr
//     | atom_expr
// atom_expr ::= [0-9]+


struct Expression;

// Expression tree node operation code.
enum class Operation
{
    NOP, // just a value
    ADD, // +
    SUB, // -
    MUL, // *
    DIV, // /
    MOD, // %
};

// Expression tree node is expression itself,
//  since expressions are recursively defined.
struct Expression
{
    double value = 0;
    Operation op = Operation::NOP;
    Expression *pLeft = nullptr;
    Expression *pRight = nullptr;
};

Expression *CreateExpression(const std::string &expression);
double CalculateExpression(Expression *pExpression);
void DisposeExpression(Expression *pExpression);
