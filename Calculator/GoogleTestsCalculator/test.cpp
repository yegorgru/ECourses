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

//  EXPECT_EQ(1, 1);
//  EXPECT_TRUE(true);