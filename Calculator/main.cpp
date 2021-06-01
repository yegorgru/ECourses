#include <iostream>
#include <stdexcept>

#include "Number.h"
#include "ExpressionTree.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main()
{
    doctest::Context context;
    int res = context.run();

    std::string expression;
    ExpressionTree tree("0");
    while (true) {
        std::cout << "Enter expression" << std::endl;
        std::cin >> expression;
        if (expression == "exit") { break; }
        try
        {
            tree.SetExpression(expression);
            std::cout << tree.Calculate().ToString() << std::endl;
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }
    return 0;
}
