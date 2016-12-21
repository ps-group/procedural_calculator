#include <iostream>
#include <string>
#include "Expression.h"

double Calculate(const std::string &expression)
{
    Expression *pExpression = CreateExpression(expression);
    const double result = CalculateExpression(pExpression);
    DisposeExpression(pExpression);

    return result;
}

void PrintExpressionResult(const std::string &expression)
{
    try
    {
        const double result = Calculate(expression);
        std::cout << "'" << expression << "' = " << result << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what();
    }
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    PrintExpressionResult("404");
    PrintExpressionResult("   404");
    PrintExpressionResult("25 + 17 / 45 / 2");
    PrintExpressionResult("42 + 42 / 2 * 2");

    return 0;
}
