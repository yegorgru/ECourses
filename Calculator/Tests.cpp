#include "Number.h"
#include "ExpressionTree.h"

#include "doctest.h"

TEST_CASE("testing validation") {
    std::string s = "123";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "-123";

    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123+5";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123-5";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123*5";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123/5";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123/5";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "123/";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123+";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123-";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123*";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "+123";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "*123";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "/123";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = ")123";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "(123";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = ")(123";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "12)(3";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "123)(";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "(123)";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "(((123)))";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "-((((5)+(123)/8))-2)";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "5-(3+3*2)";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "5-(-(3+3*2))";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "5-(--(3+3*2))";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "5-(-(3+*3*2))";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "5-((3+3*2)";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "5-((3+3*2a)";
    CHECK(!ExpressionTree::CheckValidity(s.begin(), s.end()));

    s = "(5)-(-3)";
    CHECK(ExpressionTree::CheckValidity(s.begin(), s.end()));
    
}

TEST_CASE("testing calculation") {
    ExpressionTree tree("5+5");
    CHECK(tree.Calculate().ToString() == "10");
    tree.SetExpression("5-5");
    CHECK(tree.Calculate().ToString() == "0");
    tree.SetExpression("-5+3");
    CHECK(tree.Calculate().ToString() == "-2");
    tree.SetExpression("5-10");
    CHECK(tree.Calculate().ToString() == "-5");
    tree.SetExpression("-5-7");
    CHECK(tree.Calculate().ToString() == "-12");
    tree.SetExpression("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111+111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    CHECK(tree.Calculate().ToString() == "222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");
    tree.SetExpression("5*5");
    CHECK(tree.Calculate().ToString() == "25");
    tree.SetExpression("-5*5");
    CHECK(tree.Calculate().ToString() == "-25");
    tree.SetExpression("5*(-5)");
    CHECK(tree.Calculate().ToString() == "-25");
    tree.SetExpression("-5*(-5)");
    CHECK(tree.Calculate().ToString() == "25");
    tree.SetExpression("15/3");
    CHECK(tree.Calculate().ToString() == "5");
    tree.SetExpression("-15/3");
    CHECK(tree.Calculate().ToString() == "-5");
    tree.SetExpression("15/(-3)");
    CHECK(tree.Calculate().ToString() == "-5");
    tree.SetExpression("(-15)/(-3)");
    CHECK(tree.Calculate().ToString() == "5");
    tree.SetExpression("(5-3)");
    CHECK(tree.Calculate().ToString() == "2");
    tree.SetExpression("(5)-(-3)");
    CHECK(tree.Calculate().ToString() == "8");
    tree.SetExpression("-3-4");
    CHECK(tree.Calculate().ToString() == "-7");
    tree.SetExpression("(5*3)-(-3-4)");
    CHECK(tree.Calculate().ToString() == "22");
    tree.SetExpression("-(5*3)-(-3-4)");
    CHECK(tree.Calculate().ToString() == "-8");
    tree.SetExpression("-(-(5*3)-(-3-4))");
    CHECK(tree.Calculate().ToString() == "8");
    tree.SetExpression("-(-(5*3)-(-3-4/2))");
    CHECK(tree.Calculate().ToString() == "10");
    tree.SetExpression("-(-(5*3))-(-3-4/2)");
    CHECK(tree.Calculate().ToString() == "20");
    tree.SetExpression("10*10-20*3+5+5-11*2");
    CHECK(tree.Calculate().ToString() == "28");
    tree.SetExpression("10*10-20*3+5+5-11*2");
    CHECK(tree.Calculate().ToString() == "28");
    tree.SetExpression("(1)+(2)+(3)");
    CHECK(tree.Calculate().ToString() == "6");
    tree.SetExpression("42/(-2)");
    CHECK(tree.Calculate().ToString() == "-21");
    tree.SetExpression("35-19*2-(5-6/2)");
    CHECK(tree.Calculate().ToString() == "-5");
}