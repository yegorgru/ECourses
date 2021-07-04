#include "pch.h"

#include <string>

#include "../ExpressionTree.h"

TEST(ValidationTest, HandleNumberInput) {
    std::string s = "123";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "-123";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
}

TEST(ValidationTest, HandleBasicOperations) {
    std::string s = "123+5";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123-5";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123*5";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123/5";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123/5";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
}

TEST(ValidationTest, HandleBasicOperationsWithoutParameter) {
    std::string s = "123/";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123+";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123-";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123*";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "+123";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "*123";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "/123";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
}

TEST(ValidationTest, HandleExpressionWithParenthesesAndSingleNumber) {
    std::string s = ")123";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "(123";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = ")(123";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "12)(3";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "123)(";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "(123)";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "(((123)))";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
}

TEST(ValidationTest, HandleComplexExpressions) {
    std::string s = "-((((5)+(123)/8))-2)";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "5-(3+3*2)";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "5-(-(3+3*2))";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "5-(--(3+3*2))";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "5-(-(3+*3*2))";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "5-((3+3*2)";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "5-((3+3*2a)";
    EXPECT_FALSE(ExpressionTree::CheckValidity(s.begin(), s.end()));
    s = "(5)-(-3)";
    EXPECT_TRUE(ExpressionTree::CheckValidity(s.begin(), s.end()));
}

TEST(CalculationTest, HandlePlusMinus) {
    ExpressionTree tree("5+5");
    EXPECT_EQ(tree.Calculate().ToString(), "10");
    tree.SetExpression("5-5");
    EXPECT_EQ(tree.Calculate().ToString(), "0");
    tree.SetExpression("-5+3");
    EXPECT_EQ(tree.Calculate().ToString(), "-2");
    tree.SetExpression("5-10");
    EXPECT_EQ(tree.Calculate().ToString(), "-5");
    tree.SetExpression("-5-7");
    EXPECT_EQ(tree.Calculate().ToString(), "-12");
    tree.SetExpression("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111+111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    EXPECT_EQ(tree.Calculate().ToString(), "222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");
}

TEST(CalculationTest, HandleMultiplicationDivision) {
    ExpressionTree tree("5*5");
    EXPECT_EQ(tree.Calculate().ToString(), "25");
    tree.SetExpression("-5*5");
    EXPECT_EQ(tree.Calculate().ToString(), "-25");
    tree.SetExpression("5*(-5)");
    EXPECT_EQ(tree.Calculate().ToString(), "-25");
    tree.SetExpression("-5*(-5)");
    EXPECT_EQ(tree.Calculate().ToString(), "25");
    tree.SetExpression("15/3");
    EXPECT_EQ(tree.Calculate().ToString(), "5");
    tree.SetExpression("-15/3");
    EXPECT_EQ(tree.Calculate().ToString(), "-5");
    tree.SetExpression("15/(-3)");
    EXPECT_EQ(tree.Calculate().ToString(), "-5");
    tree.SetExpression("(-15)/(-3)");
    EXPECT_EQ(tree.Calculate().ToString(), "5");
}

TEST(CalculationTest, HandleComplexExpressions) {
    ExpressionTree tree("(5-3)");
    EXPECT_EQ(tree.Calculate().ToString(), "2");
    tree.SetExpression("(5)-(-3)");
    EXPECT_EQ(tree.Calculate().ToString(), "8");
    tree.SetExpression("-3-4");
    EXPECT_EQ(tree.Calculate().ToString(), "-7");
    tree.SetExpression("(5*3)-(-3-4)");
    EXPECT_EQ(tree.Calculate().ToString(), "22");
    tree.SetExpression("-(5*3)-(-3-4)");
    EXPECT_EQ(tree.Calculate().ToString(), "-8");
    tree.SetExpression("-(-(5*3)-(-3-4))");
    EXPECT_EQ(tree.Calculate().ToString(), "8");
    tree.SetExpression("-(-(5*3)-(-3-4/2))");
    EXPECT_EQ(tree.Calculate().ToString(), "10");
    tree.SetExpression("-(-(5*3))-(-3-4/2)");
    EXPECT_EQ(tree.Calculate().ToString(), "20");
    tree.SetExpression("10*10-20*3+5+5-11*2");
    EXPECT_EQ(tree.Calculate().ToString(), "28");
    tree.SetExpression("10*10-20*3+5+5-11*2");
    EXPECT_EQ(tree.Calculate().ToString(), "28");
    tree.SetExpression("(1)+(2)+(3)");
    EXPECT_EQ(tree.Calculate().ToString(), "6");
    tree.SetExpression("42/(-2)");
    EXPECT_EQ(tree.Calculate().ToString(), "-21");
    tree.SetExpression("35-19*2-(5-6/2)");
    EXPECT_EQ(tree.Calculate().ToString(), "-5");
}