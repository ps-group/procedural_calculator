#pragma once
#include <string>

struct Expression;

enum class Operation
{
    NOP, // just a value
    ADD, // +
    SUB, // -
    MUL, // *
    DIV, // /
    MOD, // %
};

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
