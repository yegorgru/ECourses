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
//  EXPECT_EQ(1, 1);
//  EXPECT_TRUE(true);