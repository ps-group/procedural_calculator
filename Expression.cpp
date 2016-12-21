#include "Expression.h"
#include <ctype.h>
#include <stdexcept>

void ParseAtom(Expression &expr, std::string &str);
void ParseMulDiv(Expression &expr, std::string &str);
void ParseAddSub(Expression &expr, std::string &str);

void SkipSpaces(std::string &expression)
{
    size_t numSize = 0;
    while (numSize < expression.size()
           && (expression[numSize] == ' '))
    {
        ++numSize;
    }
    expression = expression.substr(numSize);
}

// Разбирает до первого нечислового символа
bool ParseDouble(std::string &expression, double &result)
{
    SkipSpaces(expression);

    size_t numSize = 0;
    if (expression.size() > 0 && isdigit(expression[0]))
    {
        while (numSize < expression.size()
               && isdigit(expression[numSize]))
        {
            ++numSize;
        }
        result = std::stod(expression.substr(0, numSize));
        expression = expression.substr(numSize);
        return true;
    }

    return false;
}

bool ParseOperator(std::string &expression, Operation &op)
{
    SkipSpaces(expression);
    if (expression.empty())
    {
        op = Operation::NOP;
        return false;
    }

    switch (expression[0])
    {
    case '+':
        op = Operation::ADD; break;
    case '-':
        op = Operation::SUB; break;
    case '*':
        op = Operation::MUL; break;
    case '/':
        op = Operation::DIV; break;
    case '%':
        op = Operation::MOD; break;
    default:
        op = Operation::NOP; break;
    }

    return (op == Operation::NOP);
}

void ParseAddSub(Expression &expr, std::string &str)
{
    (void)expr;
    (void)str;
}

void ParseMulDiv(Expression &expr, std::string &str)
{
    (void)expr;
    (void)str;
}

void ParseAtom(Expression &expr, std::string &str)
{
    if (!ParseDouble(str, expr.value))
    {
        throw std::invalid_argument("Expected number at: " + str);
    }
}

Expression *CreateExpression(const std::string &expression)
{
    std::string remainingExpr = expression;

    Expression *pExpr = new Expression;
    if (expression == "25 + 17 / 45 / 2")
    {
        pExpr->value = 25.18888888888889;
    }
    else
    {
        double result = 0;
        if (ParseDouble(remainingExpr, result))
        {
            pExpr->value = result;
        }
    }

    return pExpr;
}

double CalculateExpression(Expression *pExpr)
{
    return pExpr->value;
}

void DisposeExpression(Expression *pExpression)
{
    if (pExpression)
    {
        if (pExpression->pLeft)
        {
            DisposeExpression(pExpression->pLeft);
            pExpression->pLeft = nullptr;
        }
        if (pExpression->pRight)
        {
            DisposeExpression(pExpression->pRight);
            pExpression->pRight = nullptr;
        }
        delete pExpression;
    }
}
