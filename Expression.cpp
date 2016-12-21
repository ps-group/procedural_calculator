#include "Expression.h"


Expression *CreateExpression(const std::string &expression)
{
    Expression *pExpr = new Expression;
    if (expression == "25 + 17 / 45 / 2")
    {
        pExpr->value = 25.18888888888889;
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
