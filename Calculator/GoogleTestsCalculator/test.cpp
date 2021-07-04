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
//  EXPECT_EQ(1, 1);
//  EXPECT_TRUE(true);