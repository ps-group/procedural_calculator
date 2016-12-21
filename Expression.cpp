#include "Expression.h"
#include <ctype.h>
#include <stdexcept>
#include <memory>

Expression *ParseAtom(std::string &str);
Expression *ParseMulDiv(std::string &str);
Expression *ParseAddSub(std::string &str);

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

    expression = expression.substr(1);

    return (op != Operation::NOP);
}

Expression *ParseAddSub(std::string &str)
{
    (void)str;
    return nullptr;
}

Expression *ParseMulDiv(std::string &str)
{
    Expression *left = ParseAtom(str);
    Operation op = Operation::NOP;
    if (!ParseOperator(str, op))
    {
        return left;
    }

    switch (op)
    {
    case Operation::MUL:
    case Operation::DIV:
    case Operation::MOD:
        break;
    default:
        return left;
    }

    Expression *right = nullptr;
    try
    {
        right = ParseAtom(str);
    }
    catch (...)
    {
        DisposeExpression(left);
        throw;
    }

    try
    {
        Expression *expr = new Expression;
        expr->pLeft = left;
        expr->pRight = right;
        expr->op = op;
        return expr;
    }
    catch (...)
    {
        DisposeExpression(left);
        DisposeExpression(right);
        throw;
    }
}

Expression *ParseAtom(std::string &str)
{
    Expression *expr = new Expression;
    if (!ParseDouble(str, expr->value))
    {
        DisposeExpression(expr);
        throw std::invalid_argument("Expected number at: " + str);
    }
    return expr;
}

Expression *CreateExpression(const std::string &expression)
{
    std::string remainingStr = expression;
    Expression *pExpr = ParseMulDiv(remainingStr);

    SkipSpaces(remainingStr); // just to ensure
    if (!remainingStr.empty())
    {
        const auto message = "Unexpected symbol at: " + remainingStr;
        throw std::runtime_error(message);
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
